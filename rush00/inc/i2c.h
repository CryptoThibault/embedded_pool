#ifndef I2C_H
# define I2C_H

# ifndef NULL
# define NULL ((void *)0)
# endif

//# define F_SCL	F_CPU / (16 + 2 * TWBR_VAL * PRESCALER_VAL)
//# define F_SCL	100000	// Frequence du SCL a 100kHz
// 100 000 = 16 000 000 / ( 16 + 2 * TWBR_VAL * PRESCALER_VAL)
// 1 = 160 / (16 + 2 * TWBR_VAL * PRESCALER_VAL)
// 160 = 16 + 2 * TWBR_VAL * PRESCALER_VAL
// 144 = 2 * TWBR_VAL * PRESCALER_VAL
// 72 =  TWBR_VAL * PRESCALER_VAL (1)
// TWBR_VAL = 72
# define TWBR_VAL	72UL

// TWIE  ->  Generate interupt on TWI event
// TWEA  ->  Aknolledge on received packet
// TWEN  ->  TWI enable
// TWINT -> Set to one on interupt, cleared to 0 on software write

// TWSTA -> Send a Start / reStart
// TWSTO -> Send a Stop

# define TWCR_ACK	(MASK(TWINT, TWIE, TWEN, TWEA))
# define TWCR_START	(TWCR_ACK | MASK(TWSTA))
# define TWCR_STOP	(TWCR_ACK | MASK(TWSTO))

# define ADDR		((uint8_t)0x0f)
# define TWDR_WRITE	(uint8_t)((ADDR << 1) | 0)
# define TWDR_READ	(uint8_t)((ADDR << 1) | 1)

enum eRole {UNKNOWN, SLAVE, MASTER};

# define MAX_RAW_LEN	16
# define MASK_STATE	0xf
# define SHIFT_LEN	4
typedef struct s_TIWDataSend {
	uint8_t		header;
	uint8_t		raw[MAX_RAW_LEN];
	uint16_t	len;
	uint16_t	i;
} TIW_Send;

typedef struct s_TIWDataRecv {
	uint8_t		header;
	uint8_t		raw[MAX_RAW_LEN];
	uint16_t	i;
} TIW_Recv;

extern volatile TIW_Recv dataRecv;

uint8_t	send(uint8_t toSend[], const uint8_t len, const uint8_t state);
uint8_t	sendState(const uint8_t state);
uint8_t	sendOffline(void);

void	__dataReceivedUpdateState(const uint8_t headerState);

#endif

