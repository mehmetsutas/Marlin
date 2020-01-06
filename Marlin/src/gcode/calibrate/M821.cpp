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

#include "../../inc/MarlinConfig.h"

#include "../gcode.h"

#include "../../module/stepper.h"
#include "../../module/endstops.h"
#include "../../module/motion.h"
#include "../../module/configuration_store.h"

#if ENABLED(SENSORLESS_HOMING)
  #include "../../feature/tmc_util.h"
#endif

#include "../../lcd/ultralcd.h"

 /**
 * M821 Measure and Save Zmax position
 */
#if (HAS_Z_MAX && HAS_Z_MIN)
	
void GcodeSuite::M821() {

    home_all_axes();

    #if HAS_SOFTWARE_ENDSTOPS
      // Store the status of the soft endstops and disable if we're probing a non-printable location
      static bool enable_soft_endstops = soft_endstops_enabled;
      soft_endstops_enabled = false;
    #endif     
    
    // Wait for planner moves to finish!
    planner.synchronize();
	
	remember_feedrate_scaling_off();

    endstops.enable(true);
	
  #if ENABLED(SENSORLESS_HOMING)
		#if Z_SENSORLESS
			sensorless_t stealth_states;
			stealth_states.z = tmc_enable_stallguard(stepperZ);
		#endif
		#if ENABLED(IMPROVE_HOMING_RELIABILITY)
			sg_guard_period = millis() + default_sg_guard_duration;
		#endif
		#if (defined(Z_CURRENT_HOME) && Z_CURRENT_HOME != Z_CURRENT)
			const int16_t tmc_save_current_Z = stepperZ.getMilliamps();
			stepperZ.rms_current(Z_CURRENT_HOME);
		#endif
  #endif	
    
    sync_plan_position();

    do_blocking_move_to_z(zmax_pos_calc * 1.5, MMM_TO_MMS(Z_PROBE_SPEED_FAST));
    endstops.validate_homing_move();
	set_current_from_steppers_for_axis(Z_AXIS);
    sync_plan_position();

    do_blocking_move_to_z(current_position[Z_AXIS] - Z_CLEARANCE_BETWEEN_PROBES, MMM_TO_MMS(Z_PROBE_SPEED_FAST));

    do_blocking_move_to_z(zmax_pos_calc * 1.5, MMM_TO_MMS(Z_PROBE_SPEED_SLOW));
    endstops.validate_homing_move();
    set_current_from_steppers_for_axis(Z_AXIS);
    sync_plan_position();
 
    zmax_pos_calc=current_position[Z_AXIS];

    settings.save();
    
    #if HAS_SOFTWARE_ENDSTOPS
      // Restore the soft endstop status
      soft_endstops_enabled = enable_soft_endstops;
    #endif
    
    endstops.not_homing();
	
  #if ENABLED(SENSORLESS_HOMING)
		#if Z_SENSORLESS
			tmc_disable_stallguard(stepperZ, enable_stealth.z);
		#endif
		#if (defined(Z_CURRENT_HOME) && Z_CURRENT_HOME != Z_CURRENT)
			stepperZ.rms_current(tmc_save_current_Z);
		#endif
  #endif	

restore_feedrate_and_scaling();

ui.refresh();

report_current_position();
    
  }
#endif