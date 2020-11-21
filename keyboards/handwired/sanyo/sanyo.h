/* Copyright 2020 Laurence de Bruxelles
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 *
 * For the Sanyo shift and control are direct keys and not part of the same
 * matrix as the other keys, but we put them in anyway. Also notice there is no
 * right shift in the layout, as the shift keys share the same pin.
 */
#define LAYOUT( \
    kF1,  k10, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, k1i, k1j, k1k, k1l, k1m, k11, k12,  k1w, k1x, k1y, k1z, \
    kF2,  k20,  k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, k2i, k2j, k2k,  k2l,               k2w, k2x, k2y, k2z, \
    kF3,  k30,   k3a, k3b, k3c, k3d, k3e, k3f, k3g, k3h, k3i, k3j, k3k,  k3l,     k32,     k3w, k3x, k3y, k3z, \
    kF4,  k40,  k4a, k4b, k4c, k4d, k4e, k4f, k4g, k4h, k4i, k4j, k4k, k4l,          k41,  k4w, k4x, k4y,      \
    kF5,           k50,                    k5a,               k51,                         k5w, k5x, k5y, k5z  \
) { \
    { k1m,   k11,   k12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   k30,   k40   }, /* pin 34 */ \
    { k10,   k20,   k32, KC_NO,   k3w,   k3x,   k3y,   k2w,   k2x,   k2y, KC_NO, KC_NO   },              \
    { k41,   k5a,   k50,   k51,   k5w,   k5x,   k5y,   k4w,   k4x,   k4y, KC_NO, KC_NO   },              \
    { k1a,   k1b,   k1c,   k1d,   k1e,   k1f,   k1g,   k1h,   k1i,   k1j,   k1k,   k1l   }, /*  PCB   */ \
    { k2a,   k2b,   k2c,   k2d,   k2e,   k2f,   k2g,   k2h,   k2i,   k2j,   k2k,   k2l   }, /* pin #s */ \
    { k3a,   k3b,   k3c,   k3d,   k3e,   k3f,   k3g,   k3h,   k3i,   k3j,   k3k,   k3l   },              \
    { k4a,   k4b,   k4c,   k4d,   k4e,   k4f,   k4g,   k4h,   k4i,   k4j,   k4k,   k4l   },              \
    { kF1,   kF2,   kF3,   kF4,   kF5,   k1w,   k1x,   k1y,   k1z,   k2z,   k3z,   k5z   }, /* pin 27 */ \
}

#define SANYO_CTRL_SHIFT_ROW 0
#define SANYO_CTRL_COL 10
#define SANYO_SHIFT_COL 11
