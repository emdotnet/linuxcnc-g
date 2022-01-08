#ifndef VTI_H
#define VTI_H

/** This is the driver for a Vigilant technologies ENCDAC board.
	The board includes 4 channels of quadrature encoder input,
	4 channels of analog output, 8 on board digital I/O, and up
	to 128 digital I/O on the expanded I/O module, 3 timers
	with interrupt.
	
	A further 4 quadrature encoder inputs, 4 channels of DAC
	output and 8 additional channels of digital I/O are
	available through the Industry Pack interface. While some
	of the hooks are in place, the IP interface is not
	currently supported, nor is the ISA version of the board.
	
 To Do:	Add full support for the Industray pack
 	Add support for the ISA version of the board.
	Add support for timers	
**/

/** Copyright (C) 2006 Eric H. Johnson
					   <ejohnson AT AAAINC DOT com>
**/

/** This program is free software; you can redistribute it and/or
	modify it under the terms of version 2 of the GNU General
	Public License as published by the Free Software Foundation.
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

	THE AUTHORS OF THIS LIBRARY ACCEPT ABSOLUTELY NO LIABILITY FOR
	ANY HARM OR LOSS RESULTING FROM ITS USE.  IT IS _EXTREMELY_ UNWISE
	TO RELY ON SOFTWARE ALONE FOR SAFETY.  Any machinery capable of
	harming persons must have provisions for completely removing power
	from all motors, etc, before persons enter any danger area.  All
	machinery must be designed to comply with local and national safety
	codes, and the authors of this software can not, and do not, take
	any responsibility for such compliance.

	This code was written as part of the EMC HAL project.  For more
	information, go to www.linuxcnc.org.
**/

/*
	Vigilant Technologies' board decls
*/
#define VENDOR 0x10b5
#define DEVICE 0x9050

#define MAX_CHANS  4
#define MAX_IO_PORTS 17
#define PINS_PER_PORT 8

#define DAC_DISABLE 0x00a5
#define DAC_IND_MODE 0x005a
#define DAC_WATCHDOG_MODE 0x000f
#define DAC_ZERO_VOLTS 0x8000

#define EPSILON 1e-20

/* Structures used by the PCI card */
struct encoder {
    uint16_t Counter[4];
    uint8_t Status;		// 0x08
    uint8_t dummy;		// dummy space
    uint16_t Reset;		// 0x0a
    uint8_t reserved[3];	// dummy space 0x0c - 0x0f
    uint16_t Interrupt;	// 0x10
    uint16_t DAC;		// 0x12
    uint16_t DIO;		// 0x14
    };

struct timer {
    uint8_t reserved[0x2c];
    uint8_t ctc0;		// 8254 Counter 0
    uint8_t ctc1;		// 8254 Counter 1
    uint8_t ctc2;		// 8254 Counter 2
    uint8_t control;		// 8254 command register
    };

struct dac {
    uint8_t reserved1[0x13f]; // dummy space
    uint16_t dac[4];
    uint16_t dac_adj[4];
    uint16_t mode;
    uint16_t update;
    uint16_t reset;
    uint8_t dummy[0x2a];	// dummy space
    uint8_t DIO[0x10];	// Digital IO channels
    uint16_t config0;	// Direction configs for channels 00-63
    uint16_t config1;	// Direction configs for channels 64-127
    uint16_t status;
    };

/* IndustryPack mappings - Need to check IF uint8_t or uint16_t, also check boundary address*/
struct ip {
    uint8_t ID[0x40];	// IndustryPack ID - The first (12*2) addresses used for ID info
			// consult P20 of vip-4encdac.pdf for more info.
    uint16_t IP_int;		// Interrupt status
    uint8_t reserved[0x3e];	// dummy space
    uint16_t IO[0x30];	// IndustryPack IO - Only need the first 0x30 address.
			// Again, consult manual - Might it be better to use another struct here ??
			// and also for the ID stuff....
    };

typedef union
{
  signed long int	Long;
  signed short int	Word[2];
} Longword;
    

#endif
