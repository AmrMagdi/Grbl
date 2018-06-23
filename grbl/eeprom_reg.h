   /*
  eeprom_reg.h - EEPROM methods
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef eeprom_reg_h
#define eeprom_reg_h

#define EEARL     *((volatile unsigned char*)(0x41))
#define EEARH     *((volatile unsigned char*)(0x42))
#define EEDR      *((volatile unsigned char*)(0x40))
#define EECR      *((volatile unsigned char*)(0x3F))
#define SPMCSR    *((volatile unsigned char*)(0x57))

#define SPMEN     0
#define EERE	  0

#define EEPM0     4 //!< EEPROM Programming Mode Bit 0.
#define EEPM1     5 //!< EEPROM Programming Mode Bit 1.


#define EEWE      1
#define EEMWE     2

/* These EEPROM bits have different names on different devices. */
#define EEPE      1
#define EEMPE     2

#ifndef EEPE
    #define EEPE  EEWE  //!< EEPROM program/write enable.
    #define EEMPE EEMWE //!< EEPROM master program/write enable.
#endif

/* Define to reduce code size. */
#define EEPROM_IGNORE_SELFPROG //!< Remove SPM flag polling.


#endif
