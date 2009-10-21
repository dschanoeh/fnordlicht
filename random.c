/* vim:fdm=marker ts=4 et ai
 * {{{
 *         fnordlicht firmware next generation
 *
 *    for additional information please
 *    see http://koeln.ccc.de/prozesse/running/fnordlicht
 *
 * (c) by Jan-Niklas Meier <dschanoeh@googlemail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 }}} */

#include <stdint.h>
#include "random.h"


uint16_t lfsr = PRAND_START;

uint8_t prand() {
    uint8_t bit0,bit2,bit3,bit5,bit16,res,i;

    /*save result*/
    res = lfsr;

    /*shift lfsr for 8 bit*/
    for(i=0;i<8;i++) {
        bit0 = lfsr & 0b00000001;
        bit2 = (lfsr & 0b00000100) >> 2;
        bit3 = (lfsr & 0b00001000) >> 3;
        bit5 = (lfsr & 0b00010000) >> 5;
        bit16 = ((bit0 ^ bit2) ^ bit3) ^ bit5;
        lfsr >>= 1;
        /*if bit16 should be set, set it in lfsr*/
        if(bit16)
            lfsr |= 0x8000;
    }
    return res;
}
