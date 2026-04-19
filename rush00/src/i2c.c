#include "rush00.h"
#include "i2c.h"

static volatile enum eRole role = UNKNOWN;
static volatile uint8_t	trySending = 0;
static volatile TIW_Send dataSend = {};
volatile TIW_Recv dataRecv = {};

__attribute__((constructor))
void	init_I2C(void) {
	TWAR = (ADDR << 1);	// My slave adress
	TWBR = TWBR_VAL;	// Set bitrate
	UNSET_BITS(TWSR, TWPS1, TWPS0);	// Prescaler value = 1
	
	TWDR = 0;		// Adress destination, not relevant

	TWCR = TWCR_ACK;	// Enable interupt, Enable Acknowledge Enable TWI
}

uint8_t	sendOffline(void) {
	state = idle;
	return (send(NULL, 0, offline));
}

uint8_t	sendState(const uint8_t _state) {
	return (send(NULL, 0, _state));
}

uint8_t	send(uint8_t toSend[], const uint8_t len, const uint8_t _state) {
	uint16_t	i;
	for (i = 0; i < 10 && role != UNKNOWN; ++i) _delay_ms(1);	// Wait for the line to be idl
	if (i >= 10) {		// If the line wasnt free
		reset_game();
		return (0);
	}
	dataSend.header = (_state & MASK_STATE) | ((len & MASK_STATE) << SHIFT_LEN);	// Setup dataPackage
	dataSend.len = len + 1;
	dataSend.i = 0;
	for (uint8_t i = 0; i < len; ++i)
		dataSend.raw[i] = toSend[i];
	trySending = 1;
	TWCR = TWCR_START;	// Start condition
	for (i = 0; i < 10 && trySending; ++i) _delay_ms(1);	// Wait to send
	if (i >= 10 && trySending) {				// If ze never got master
		reset_game();
		return (0);
	}
	for (i = 0; i < 10 && role != UNKNOWN; ++i) _delay_ms(1);	// Wait to the line to be idle/transmition finished
	if (trySending) {	// Bus error || received NACK, no one listening
		reset_game();
		return (0);
	}
	return (1);
}

void	__sendData(void) {
	if (dataSend.i == 0) {
		TWDR = dataSend.header;
		++dataSend.i;
		TWCR = TWCR_ACK;
	} else if (dataSend.i < dataSend.len) {
		TWDR = dataSend.raw[dataSend.i - 1];
		++dataSend.i;
		TWCR = TWCR_ACK;
	} else {
		dataSend.len = 0;
		role = UNKNOWN;
		TWCR = TWCR_STOP;
	}
}

void	__reveiveData(void) {
	if (dataRecv.i == 0) {
		dataRecv.header = TWDR;
	} else {
		dataRecv.raw[dataRecv.i - 1] = TWDR;
	}
	++dataRecv.i;
}

void	__receiveDataDone(void) {
	const uint8_t	len = (dataRecv.header >> 4);
	const uint8_t	headerState = (dataRecv.header & 0xf);

	role = UNKNOWN;
	dataRecv.i = 0;
	__dataReceivedUpdateState(headerState);
}
void	__dataReceivedUpdateState(const uint8_t headerState) {
	if (headerState == offline) {
		state = idle;
	} else if (headerState == player_ready) {
		event |= MASK(EVNT_RCV_RDY);
	} else if (headerState == player_finished) {
		event |= MASK(EVNT_RCV_FNSH);
	}
}


__attribute__((signal, used))
void	TWI_vect(void) {
	const uint8_t	statusCode = TWSR & ~MASK(TWPS1, TWPS0);

	switch (statusCode) {
		case 0x08:	// Start transmited
			trySending = 0;
			role = MASTER;
			TWDR = TWDR_WRITE;
			TWCR = TWCR_ACK;
			return;
		case 0x18:	// Slave Ackknoledged Start, send data/STOP
		case 0x28:	// Slave Acknowledged data,  send data/STOP
			trySending = 0;
			__sendData();
			return;
		case 0x38:	// Arvitration lost in Data/Start send
		case 0x60:	// Received packet with our adress
		case 0x68:	// We previously lost arbitration
			role = SLAVE;
			TWCR = TWCR_ACK;
			return;
		case 0x80:	// Received data after Ack
		case 0x88:	// Received data after Nack
			__reveiveData();
			TWCR = TWCR_ACK;
			return;
		case 0xA0:	// Stop received as slave
			__receiveDataDone();
			TWCR = TWCR_ACK;
			return;
		case 0x30:	// Slave did NACK after Data, Stoping
		case 0x20:	// Slave did NACK after Start, Stoping
		case 0x00:	//Bus Error
			role = UNKNOWN;
			trySending = 1;
			TWCR = TWCR_STOP;
			return;
		default:
			TWCR = TWCR_ACK;	// Clear interupt
	}
}