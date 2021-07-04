/* Copyright 2020 Stephen J. Bush @muppetjones
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

// Tap Mod Layers
// Mod-tap
// #define NAV_SPC LT(_NAV, KC_SPC)
#define LOW_ENT LT(_LOWER, KC_ENT)
#define LOW_SPC LT(_LOWER, KC_SPC)
#define RSE_ENT LT(_RAISE, KC_ENT)
#define RSE_SPC LT(_RAISE, KC_SPC)
#define RSE_TAB LT(_RAISE, KC_TAB)

// for casemodes
enum custom_keycodes {
#ifdef CAPSWORD_ENABLE
    CAPSWRD = SAFE_RANGE,
#else
    CAPSWRD = KC_CAPS,
#endif
};
