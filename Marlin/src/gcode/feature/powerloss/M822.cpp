/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "../../../inc/MarlinConfig.h"

/**
 * M822 Stop printing and save remaining print job to SD
 */
 
#if (HAS_Z_MAX && HAS_Z_MIN) //ENABLED(POWER_FAILURE_FEATURE)

#include "../../gcode.h"
#include "../../../feature/power_loss_recovery.h"
#include "../../../lcd/ultralcd.h"

void GcodeSuite::M822() {  
	recovery.save_stop();
  }
#endif