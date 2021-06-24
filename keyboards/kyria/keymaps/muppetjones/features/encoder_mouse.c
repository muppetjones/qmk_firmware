/* Copyright 2020 Stephen J. Bush
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
 *
 * Much of this was taken directly from quantum/mousekey.c
 *
 * Usage:
 *  - Add the following to your rules.mk

        ENCODER_ENABLE = yes       # Enables the use of one or more encoders
        POINTING_DEVICE_ENABLE = yes

 *  - Add the following block to your keymap.c

        #ifdef ENCODER_ENABLE
        void encoder_update_user(uint8_t index, bool clockwise) {
        #    ifdef POINTING_DEVICE_ENABLE
            encoder_update_mouse(index, clockwise);
        #    endif
            return;
        #endif

 */

#include QMK_KEYBOARD_H
#include "encoder_mouse.h"
#include "pointing_device.h"

#ifdef POINTING_DEVICE_ENABLE
#    ifdef ENCODER_ENABLE

static uint16_t mouse_timer      = 0;
const uint16_t  mk_initial_speed = MOUSEKEY_INITIAL_SPEED;

static uint8_t move_unit(void) {
    const float time_elapsed = timer_elapsed(mouse_timer);
    const float modifier     = 200 < time_elapsed ? 1 : (200 - time_elapsed) / 2;
    float       speed        = mk_initial_speed + MOUSEKEY_MOVE_DELTA * modifier;

    /* convert speed to USB mouse speed 1 to 127 */
    speed = (uint8_t)(speed / (1000.0f / MOUSEKEY_INTERVAL));
    speed = speed < 1 ? 1 : speed;

    return speed > MOUSEKEY_MOVE_MAX ? MOUSEKEY_MOVE_MAX : speed;
}

void encoder_update_mouse(uint8_t index, bool clockwise) {
    report_mouse_t curr_report = pointing_device_get_report();
    const uint8_t  speed       = move_unit();
    mouse_timer                = timer_read();

    if (index == 0) {
        if (clockwise) {
            curr_report.x += speed;
        } else {
            curr_report.x -= speed;
        }
    } else {
        if (clockwise) {
            curr_report.y += speed;
        } else {
            curr_report.y -= speed;
        }
    }

    pointing_device_set_report(curr_report);
    pointing_device_send();
}

#    endif
#endif
