#ifndef EMBD_H
# define EMBD_H

# ifndef __AVR_ATmega328P__
#  define __AVR_ATmega328P__
# endif
# include "avr/io.h"
# include "util/delay.h"

# include "mask.h"

# define SET_BIT(reg, nBit)	(reg |= (1 << (nBit)))
# define SET_BITS(reg, ...)	((reg) |= MASK(__VA_ARGS__))

# define UNSET_BIT(reg, nBit)	(reg &= ~(1 << (nBit)))
# define UNSET_BITS(reg, ...)	((reg) &= ~MASK(__VA_ARGS__))

# define SET_BIT_VAL(reg, nBit, val) ((reg) = ((reg & ~(1 << (nBit)))) | (((val) != 0) << (nBit)))

# define TOGGLE_BIT(reg, nBit) ((reg) ^= (1 << (nBit)))
# define TOGGLE_BITS(reg, ...)	((reg) ^= MASK(__VA_ARGS__))

# define GET_BIT(reg, nBit) (((reg) >> (nBit)) & 1)


# define INTERUPT_ON	SET_BIT(SREG, SREG_I);
# define INTERUPT_OFF	UNSET_BIT(SREG, SREG_I);

__attribute__((constructor))
void init(void);

#endif
