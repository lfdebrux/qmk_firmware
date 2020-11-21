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

#include "sanyo.h"

void keyboard_pre_init_kb(void) {
    /* set up the LED pins */
    setPinOutput(SANYO_LED_LOCK_PIN);
    setPinOutput(SANYO_LED_GRAPH_PIN);
    writePin(SANYO_LED_LOCK_PIN, LED_PIN_ON_STATE);
    writePin(SANYO_LED_GRAPH_PIN, LED_PIN_ON_STATE);
}
