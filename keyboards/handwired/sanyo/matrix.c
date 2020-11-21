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
#include <stdbool.h>
#include <stdint.h>
#include "matrix.h"
#include "quantum.h"
#include "sanyo.h"

static const pin_t col_sel_pins[4] = SANYO_COL_SEL_PINS;
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

static void select_col(uint8_t col) {
    /* The demultiplexer basically treats its input as a
     * little-endian 4 bit number that selects an output pin.
     * The selected output pin is pulled low.
     */
    writePin(col_sel_pins[0], col & 1);
    writePin(col_sel_pins[1], col & 2);
    writePin(col_sel_pins[2], col & 4);
    writePin(col_sel_pins[3], col & 8);
}

static void unselect_cols(void) {
    /* select an unwired output pin */
    select_col(15);
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    /* copied from https://github.com/qmk/qmk_firmware/blob/master/quantum/matrix.c */
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    matrix_io_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // don't try and read matrix positions for control or shift
        if ((current_col == SANYO_CTRL_COL || current_col == SANYO_SHIFT_COL) && row_index == SANYO_CTRL_SHIFT_ROW) {
            continue;
	}

        // Store last value of row prior to reading
        matrix_row_t last_row_value    = current_matrix[row_index];
        matrix_row_t current_row_value = last_row_value;

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_row_value)) {
            matrix_changed |= true;
            current_matrix[row_index] = current_row_value;
        }
    }

    // Unselect col
    unselect_cols();

    return matrix_changed;
}

static bool read_ctrl_and_shift(matrix_row_t current_matrix[]) {
    /* read shift and control into free spots in the matrix */
    bool matrix_changed = false;

    matrix_row_t last_row_value    = current_matrix[SANYO_CTRL_SHIFT_ROW];
    matrix_row_t current_row_value = last_row_value;

    if (readPin(SANYO_CTRL_PIN) == 0) {
        current_row_value |= (MATRIX_ROW_SHIFTER << SANYO_CTRL_COL);
    } else {
        current_row_value &= ~(MATRIX_ROW_SHIFTER << SANYO_CTRL_COL);
    }

    if (readPin(SANYO_SHIFT_PIN) == 0) {
        current_row_value |= (MATRIX_ROW_SHIFTER << SANYO_SHIFT_COL);
    } else {
        current_row_value &= ~(MATRIX_ROW_SHIFTER << SANYO_SHIFT_COL);
    }

    // Determine if the matrix changed state
    if ((last_row_value != current_row_value)) {
        matrix_changed |= true;
        current_matrix[SANYO_CTRL_SHIFT_ROW] = current_row_value;
    }

    return matrix_changed;
}

void matrix_init_custom(void) {
    /* set up the column select demultiplexer */
    setPinOutput(col_sel_pins[0]);
    setPinOutput(col_sel_pins[1]);
    setPinOutput(col_sel_pins[2]);
    setPinOutput(col_sel_pins[3]);
    unselect_cols();

    /* row pins are connected to pull-ups externally so we just use high-z mode */
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        setPinInput(row_pins[i]);
    }

    /* same for shift and control pins */
    setPinInput(SANYO_CTRL_PIN);
    setPinInput(SANYO_SHIFT_PIN);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        matrix_has_changed |= read_rows_on_col(current_matrix, current_col);
    }

    matrix_has_changed |= read_ctrl_and_shift(current_matrix);

    return matrix_has_changed;
}
