/* MSPDebug - debugging tool for MSP430 MCUs
 * Copyright (C) 2009-2012 Daniel Beer
 * Copyright (C) 2012-2014 Peter Bägel
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/* jtag functions are taken from TIs SLAA149–September 2002
 *
 * 2012-10-03 Peter Bägel (DF5EQ)
 * 2012-10-03   initial release          Peter Bägel (DF5EQ)
 * 2014-12-26   jtag_single_step added   Peter Bägel (DF5EQ)
 */

#ifndef JTAGLIB_H_
#define JTAGLIB_H_

#include <stdint.h>

#include "jtdev.h"
#include "util.h"

/* Flash erasing modes */
#define JTAG_ERASE_MASS 0xA506
#define JTAG_ERASE_MAIN 0xA504
#define JTAG_ERASE_SGMT 0xA502

/* Take target device under JTAG control. */
unsigned int jtag_init(struct jtdev *p);

unsigned int jtag_get_device(struct jtdev *p);

/* Read the target chip id. */
unsigned int jtag_chip_id(struct jtdev *p);

/* Reads one byte/word from a given address */
uint16_t jtag_read_mem(struct jtdev *p,
		       unsigned int format,
		       address_t address);

/* Reads an array of words from target memory */
void jtag_read_mem_quick(struct jtdev *p,
			 address_t start_address,
			 unsigned int word_count,
			 uint16_t *data);

/* Writes one byte/word at a given address */
void jtag_write_mem(struct jtdev *p,
		    unsigned int format,
		    address_t address,
		    uint16_t data);

/* Writes an array of words into target memory */
void jtag_write_mem_quick(struct jtdev *p,
			  address_t start_address,
			  unsigned int word_count,
			  const uint16_t *data);

/* This function checks if the JTAG access security fuse is blown */
int jtag_is_fuse_blown(struct jtdev *p);

/* Execute a Power-Up Clear (PUC) using JTAG CNTRL SIG register */
unsigned int jtag_execute_puc(struct jtdev *p);

/* Release the target device from JTAG control */
void jtag_release_device(struct jtdev *p, address_t address);

/* Performs a verification over the given memory range */
int jtag_verify_mem(struct jtdev *p,
		    address_t start_address,
		    unsigned int word_count,
		    const uint16_t *data);

/* Performs an erase check over the given memory range */
int jtag_erase_check(struct jtdev *p,
		     address_t start_address,
		     unsigned int word_count);

/* Programs/verifies an array of words into a FLASH */
void jtag_write_flash(struct jtdev *p,
		      address_t start_address,
		      unsigned int word_count,
		      const uint16_t *data);

/* Performs a mass erase or a segment erase of a FLASH module */
void jtag_erase_flash(struct jtdev *p,
		      unsigned int erase_mode,
		      address_t erase_address);

/* Reads a register from the target CPU */
address_t jtag_read_reg(struct jtdev *p, int reg);

/* Writes a value into a register of the target CPU */
void jtag_write_reg(struct jtdev *p, int reg, address_t value);
void jtag_single_step(struct jtdev *p);

#endif
