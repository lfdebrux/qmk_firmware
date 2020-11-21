/*
Copyright 2020 Laurence de Bruxelles

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xF860
#define PRODUCT_ID   0x2531
#define DEVICE_VER   0x0001
#define MANUFACTURER Fujitsu
#define PRODUCT      Sanyo MBC-55 keyboard

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 12

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { D1, D0, D4, C6, D7, E6, B4, B5 } /* pins 33 to 27 on PCB */
#define UNUSED_PINS /* if using a Pro Micro there are no unused pins */

/* Pins for column selector demultiplexer
 * in A, B, C, D order (pins 21 to 24 on PCB)
 */
#define SANYO_COL_SEL_PINS { B1, B3, B2, B6 }

/* Control and shift have separate pins */
#define SANYO_CTRL_PIN F6
#define SANYO_SHIFT_PIN F7

/* the Sanyo has two LEDs */
#define SANYO_LED_LOCK_PIN F4
#define SANYO_LED_GRAPH_PIN F5

#define LED_PIN_ON_STATE 0

#define LED_CAPS_LOCK_PIN SANYO_LED_LOCK_PIN

/* leave it up to keymaps to decide what the graph LED should do */
//#define LED_COMPOSE_PIN SANYO_LED_GRAPH_PIN
//#define LED_NUM_LOCK_PIN SANYO_LED_GRAPH_PIN
//#define LED_SCROLL_LOCK_PIN SANYO_LED_GRAPH_PIN
//#define LED_KANA_PIN SANYO_LED_GRAPH_PIN

/* Debounce reduces chatter (unintended double-presses)
 * The bounce time for these switches is around 10 ms
 * according to https://telcontar.net/KBK/Fujitsu/FKB2500
 */
#define DEBOUNCE 10

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0
