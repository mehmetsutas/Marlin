/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * lcd/extui/malyan/malyan.h
 */

<<<<<<<< HEAD:Marlin/src/lcd/extui/mks_ui/mks_hardware.h
#include <lvgl.h>

// Functions for MKS_TEST
#if BOTH(MKS_TEST, SDSUPPORT)
  void mks_hardware_test();
  void mks_test_get();
  void mks_gpio_test();
  extern uint8_t mks_test_flag;
#else
  #define mks_test_flag 0
#endif

// String display and assets
void disp_string(uint16_t x, uint16_t y, const char * cstr, uint16_t charColor, uint16_t bkColor);
void disp_string(uint16_t x, uint16_t y, FSTR_P const fstr, uint16_t charColor, uint16_t bkColor);
void disp_assets_update();
void disp_assets_update_progress(FSTR_P const msg);
========
#include "../../../HAL/shared/Marduino.h"

// Track incoming command bytes from the LCD
extern uint16_t inbound_count;

// For sending print completion messages
extern bool last_printing_status;

void write_to_lcd(FSTR_P const fmsg);
void write_to_lcd(const char * const cmsg);

void set_lcd_error(FSTR_P const error, FSTR_P const component=nullptr);

void process_lcd_c_command(const char *command);
void process_lcd_eb_command(const char *command);

template<typename T>
void j_move_axis(const char *command, const T axis);

void process_lcd_j_command(const char *command);
void process_lcd_p_command(const char *command);
void process_lcd_s_command(const char *command);
void process_lcd_command(const char *command);

void parse_lcd_byte(const byte b);
void update_usb_status(const bool forceUpdate);
>>>>>>>> bugfix-2.1.x:Marlin/src/lcd/extui/malyan/malyan.h
