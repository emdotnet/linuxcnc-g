/*    This is a component of LinuxCNC
 *    Copyright 2011, 2012 Jeff Epler <jepler@dsndata.com>, Michael Haberler
 *    <git@mah.priv.at>, Sebastian Kuzminsky <seb@highlab.com>
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#define BOOST_PYTHON_MAX_ARITY 13
#include <boost/python/def.hpp>
#include <boost/python/module.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/enum.hpp>

namespace bp = boost::python;

#include "emc/rs274ngc/rs274ngc_interp.hh"
#include "emc/rs274ngc/interp_queue.hh"

static void wrap_canon_error(const char *s)
{
    if ((s == NULL) || (strlen(s) == 0)) {
        return;
    }
    CANON_ERROR("%s", s);
}


BOOST_PYTHON_MODULE(emccanon) {
    using namespace boost::python;
    scope().attr("__doc__") =
        "Canon access & introspection\n"
        ;
    enum_<CANON_PLANE>("CANON_PLANE")
            .value("CANON_PLANE_XY", CANON_PLANE_XY)
            .value("CANON_PLANE_YZ", CANON_PLANE_YZ)
            .value("CANON_PLANE_XZ", CANON_PLANE_XZ)
            .value("CANON_PLANE_UV", CANON_PLANE_UV)
            .value("CANON_PLANE_VW", CANON_PLANE_VW)
            .value("CANON_PLANE_UW", CANON_PLANE_UW)
            .export_values();

    enum_<CANON_UNITS>("CANON_UNITS")
            .value("CANON_UNITS_INCHES", CANON_UNITS_INCHES)
            .value("CANON_UNITS_MM", CANON_UNITS_MM)
            .value("CANON_UNITS_CM", CANON_UNITS_CM)
            .export_values();

    enum_<CANON_MOTION_MODE>("CANON_MOTION_MODE")
            .value("CANON_EXACT_STOP", CANON_EXACT_STOP)
            .value("CANON_EXACT_PATH", CANON_EXACT_PATH)
            .value("CANON_CONTINUOUS", CANON_CONTINUOUS)
            .export_values();

    enum_<CANON_SPEED_FEED_MODE>("CANON_FEED_SPEED_MODE")
            .value("CANON_SYNCHED", CANON_SYNCHED)
            .value("CANON_INDEPENDENT", CANON_INDEPENDENT)
            .export_values();

    enum_<CANON_DIRECTION>("CANON_DIRECTION")
            .value("CANON_STOPPED", CANON_STOPPED)
            .value("CANON_CLOCKWISE", CANON_CLOCKWISE)
            .value("CANON_COUNTERCLOCKWISE", CANON_COUNTERCLOCKWISE)
            .export_values();

    enum_<CANON_FEED_REFERENCE>("CANON_FEED_REFERENCE")
            .value("CANON_WORKPIECE", CANON_WORKPIECE)
            .value("CANON_XYZ", CANON_XYZ)
            .export_values();

    enum_<CANON_SIDE>("CANON_SIDE")
            .value("CANON_SIDE_RIGHT", CANON_SIDE_RIGHT)
            .value("CANON_SIDE_LEFT", CANON_SIDE_LEFT)
            .value("CANON_SIDE_OFF", CANON_SIDE_OFF)
            .export_values();

    enum_<CANON_AXIS>("CANON_AXIS")
            .value("CANON_AXIS_X", CANON_AXIS_X)
            .value("CANON_AXIS_Y", CANON_AXIS_Y)
            .value("CANON_AXIS_Z", CANON_AXIS_Z)
            .value("CANON_AXIS_A", CANON_AXIS_A)
            .value("CANON_AXIS_B", CANON_AXIS_B)
            .value("CANON_AXIS_C", CANON_AXIS_C)
            .value("CANON_AXIS_U", CANON_AXIS_U)
            .value("CANON_AXIS_V", CANON_AXIS_V)
            .value("CANON_AXIS_W", CANON_AXIS_W)
            .export_values();

    //  scope().attr("") =  ;

    def("ARC_FEED",&ARC_FEED);
    def("CANON_ERROR",&wrap_canon_error);
    def("CHANGE_TOOL",&CHANGE_TOOL);
    def("CHANGE_TOOL_NUMBER",&CHANGE_TOOL_NUMBER);
    def("CLAMP_AXIS",&CLAMP_AXIS);
    def("CLEAR_AUX_OUTPUT_BIT",&CLEAR_AUX_OUTPUT_BIT);
    def("CLEAR_MOTION_OUTPUT_BIT",&CLEAR_MOTION_OUTPUT_BIT);
    def("COMMENT",&COMMENT);
    def("DISABLE_ADAPTIVE_FEED",&DISABLE_ADAPTIVE_FEED);
    def("DISABLE_FEED_HOLD",&DISABLE_FEED_HOLD);
    def("DISABLE_FEED_OVERRIDE",&DISABLE_FEED_OVERRIDE);
    def("DISABLE_SPEED_OVERRIDE",&DISABLE_SPEED_OVERRIDE);
    def("DWELL",&DWELL);
    def("ENABLE_ADAPTIVE_FEED",&ENABLE_ADAPTIVE_FEED);
    def("ENABLE_FEED_HOLD",&ENABLE_FEED_HOLD);
    def("ENABLE_FEED_OVERRIDE",&ENABLE_FEED_OVERRIDE);
    def("ENABLE_SPEED_OVERRIDE",&ENABLE_SPEED_OVERRIDE);
    def("PLUGIN_CALL",&PLUGIN_CALL);
    def("IO_PLUGIN_CALL",&IO_PLUGIN_CALL);
    def("FINISH",&FINISH);
    def("ON_RESET", &ON_RESET);
    def("FLOOD_OFF",&FLOOD_OFF);
    def("FLOOD_ON",&FLOOD_ON);
    def("GET_BLOCK_DELETE",&GET_BLOCK_DELETE);
    def("GET_EXTERNAL_ADAPTIVE_FEED_ENABLE",&GET_EXTERNAL_ADAPTIVE_FEED_ENABLE);
    def("GET_EXTERNAL_ANALOG_INPUT",&GET_EXTERNAL_ANALOG_INPUT);
    def("GET_EXTERNAL_ANGLE_UNITS",&GET_EXTERNAL_ANGLE_UNITS);
    def("GET_EXTERNAL_AXIS_MASK",&GET_EXTERNAL_AXIS_MASK);
    def("GET_EXTERNAL_DIGITAL_INPUT",&GET_EXTERNAL_DIGITAL_INPUT);
    def("GET_EXTERNAL_FEED_HOLD_ENABLE",&GET_EXTERNAL_FEED_HOLD_ENABLE);
    def("GET_EXTERNAL_FEED_OVERRIDE_ENABLE",&GET_EXTERNAL_FEED_OVERRIDE_ENABLE);
    def("GET_EXTERNAL_FEED_RATE",&GET_EXTERNAL_FEED_RATE);
    def("GET_EXTERNAL_FLOOD",&GET_EXTERNAL_FLOOD);
    def("GET_EXTERNAL_LENGTH_UNITS",&GET_EXTERNAL_LENGTH_UNITS);
    def("GET_EXTERNAL_MIST",&GET_EXTERNAL_MIST);
    def("GET_EXTERNAL_MOTION_CONTROL_MODE",&GET_EXTERNAL_MOTION_CONTROL_MODE);
    def("GET_EXTERNAL_MOTION_CONTROL_TOLERANCE",&GET_EXTERNAL_MOTION_CONTROL_TOLERANCE);
    def("SET_PARAMETER_FILE_NAME",&SET_PARAMETER_FILE_NAME);
    def("GET_EXTERNAL_MOTION_CONTROL_NAIVECAM_TOLERANCE",
	&GET_EXTERNAL_MOTION_CONTROL_NAIVECAM_TOLERANCE);
    def("GET_EXTERNAL_PARAMETER_FILE_NAME",&GET_EXTERNAL_PARAMETER_FILE_NAME);
    def("GET_EXTERNAL_PLANE",&GET_EXTERNAL_PLANE);
    def("GET_EXTERNAL_POSITION_A",&GET_EXTERNAL_POSITION_A);
    def("GET_EXTERNAL_POSITION_B",&GET_EXTERNAL_POSITION_B);
    def("GET_EXTERNAL_POSITION_C",&GET_EXTERNAL_POSITION_C);
    def("GET_EXTERNAL_POSITION_U",&GET_EXTERNAL_POSITION_U);
    def("GET_EXTERNAL_POSITION_V",&GET_EXTERNAL_POSITION_V);
    def("GET_EXTERNAL_POSITION_W",&GET_EXTERNAL_POSITION_W);
    def("GET_EXTERNAL_POSITION_X",&GET_EXTERNAL_POSITION_X);
    def("GET_EXTERNAL_POSITION_Y",&GET_EXTERNAL_POSITION_Y);
    def("GET_EXTERNAL_POSITION_Z",&GET_EXTERNAL_POSITION_Z);
    def("GET_EXTERNAL_PROBE_POSITION_A",&GET_EXTERNAL_PROBE_POSITION_A);
    def("GET_EXTERNAL_PROBE_POSITION_B",&GET_EXTERNAL_PROBE_POSITION_B);
    def("GET_EXTERNAL_PROBE_POSITION_C",&GET_EXTERNAL_PROBE_POSITION_C);
    def("GET_EXTERNAL_PROBE_POSITION_U",&GET_EXTERNAL_PROBE_POSITION_U);
    def("GET_EXTERNAL_PROBE_POSITION_V",&GET_EXTERNAL_PROBE_POSITION_V);
    def("GET_EXTERNAL_PROBE_POSITION_W",&GET_EXTERNAL_PROBE_POSITION_W);
    def("GET_EXTERNAL_PROBE_POSITION_X",&GET_EXTERNAL_PROBE_POSITION_X);
    def("GET_EXTERNAL_PROBE_POSITION_Y",&GET_EXTERNAL_PROBE_POSITION_Y);
    def("GET_EXTERNAL_PROBE_POSITION_Z",&GET_EXTERNAL_PROBE_POSITION_Z);
    def("GET_EXTERNAL_PROBE_TRIPPED_VALUE",&GET_EXTERNAL_PROBE_TRIPPED_VALUE);
    def("GET_EXTERNAL_PROBE_VALUE",&GET_EXTERNAL_PROBE_VALUE);
    def("GET_EXTERNAL_QUEUE_EMPTY",&GET_EXTERNAL_QUEUE_EMPTY);
    def("GET_EXTERNAL_SELECTED_TOOL_SLOT",&GET_EXTERNAL_SELECTED_TOOL_SLOT);
    def("GET_EXTERNAL_SPEED",&GET_EXTERNAL_SPEED);
    def("GET_EXTERNAL_SPINDLE",&GET_EXTERNAL_SPINDLE);
    def("GET_EXTERNAL_SPINDLE_OVERRIDE_ENABLE",&GET_EXTERNAL_SPINDLE_OVERRIDE_ENABLE);
    def("GET_EXTERNAL_TC_FAULT",&GET_EXTERNAL_TC_FAULT);
    def("GET_EXTERNAL_TOOL_LENGTH_AOFFSET",&GET_EXTERNAL_TOOL_LENGTH_AOFFSET);
    def("GET_EXTERNAL_TOOL_LENGTH_BOFFSET",&GET_EXTERNAL_TOOL_LENGTH_BOFFSET);
    def("GET_EXTERNAL_TOOL_LENGTH_COFFSET",&GET_EXTERNAL_TOOL_LENGTH_COFFSET);
    def("GET_EXTERNAL_TOOL_LENGTH_UOFFSET",&GET_EXTERNAL_TOOL_LENGTH_UOFFSET);
    def("GET_EXTERNAL_TOOL_LENGTH_VOFFSET",&GET_EXTERNAL_TOOL_LENGTH_VOFFSET);
    def("GET_EXTERNAL_TOOL_LENGTH_WOFFSET",&GET_EXTERNAL_TOOL_LENGTH_WOFFSET);
    def("GET_EXTERNAL_TOOL_LENGTH_XOFFSET",&GET_EXTERNAL_TOOL_LENGTH_XOFFSET);
    def("GET_EXTERNAL_TOOL_LENGTH_YOFFSET",&GET_EXTERNAL_TOOL_LENGTH_YOFFSET);
    def("GET_EXTERNAL_TOOL_LENGTH_ZOFFSET",&GET_EXTERNAL_TOOL_LENGTH_ZOFFSET);
    def("GET_EXTERNAL_TOOL_SLOT",&GET_EXTERNAL_TOOL_SLOT);
    def("GET_EXTERNAL_TOOL_TABLE",&GET_EXTERNAL_TOOL_TABLE);
    def("GET_EXTERNAL_TRAVERSE_RATE",&GET_EXTERNAL_TRAVERSE_RATE);
    def("GET_OPTIONAL_PROGRAM_STOP",&GET_OPTIONAL_PROGRAM_STOP);
    def("INIT_CANON",&INIT_CANON);
    def("LOCK_ROTARY",&LOCK_ROTARY);
    //    def("LOCK_SPINDLE_Z",&LOCK_SPINDLE_Z);
    def("LOGAPPEND",&LOGAPPEND);
    def("LOGCLOSE",&LOGCLOSE);
    def("LOG",&LOG);
    def("LOGOPEN",&LOGOPEN);
    def("MESSAGE",&MESSAGE);
    def("MIST_OFF",&MIST_OFF);
    def("MIST_ON",&MIST_ON);
    // def("NURB_CONTROL_POINT",&NURB_CONTROL_POINT);
    //  def("NURB_FEED",&NURB_FEED);
    // def("NURB_KNOT_VECTOR",&NURB_KNOT_VECTOR);
    def("NURBS_FEED",&NURBS_FEED);
    def("OPTIONAL_PROGRAM_STOP",&OPTIONAL_PROGRAM_STOP);
    // def("ORIENT_SPINDLE",&ORIENT_SPINDLE);
    def("PALLET_SHUTTLE",&PALLET_SHUTTLE);
    def("PROGRAM_END",&PROGRAM_END);
    def("PROGRAM_STOP",&PROGRAM_STOP);
    def("RIGID_TAP",&RIGID_TAP);
    def("SELECT_PLANE",&SELECT_PLANE);
    def("SELECT_TOOL",&SELECT_TOOL);
    def("UPDATE_TAG",&UPDATE_TAG);
    def("SET_AUX_OUTPUT_BIT",&SET_AUX_OUTPUT_BIT);
    def("SET_AUX_OUTPUT_VALUE",&SET_AUX_OUTPUT_VALUE);
    def("SET_BLOCK_DELETE",&SET_BLOCK_DELETE);
    def("SET_CUTTER_RADIUS_COMPENSATION",&SET_CUTTER_RADIUS_COMPENSATION);
    def("SET_FEED_MODE",&SET_FEED_MODE);
    def("SET_FEED_RATE",&SET_FEED_RATE);
    //    def("SET_FEED_REFERENCE",&SET_FEED_REFERENCE);
    def("SET_G5X_OFFSET",&SET_G5X_OFFSET);
    def("SET_G92_OFFSET",&SET_G92_OFFSET);
    //   def("SET_MOTION_CONTROL_MODE",&SET_MOTION_CONTROL_MODE);
    def("SET_MOTION_OUTPUT_BIT",&SET_MOTION_OUTPUT_BIT);
    def("SET_MOTION_OUTPUT_VALUE",&SET_MOTION_OUTPUT_VALUE);
    def("SET_NAIVECAM_TOLERANCE",&SET_NAIVECAM_TOLERANCE);
    def("SET_OPTIONAL_PROGRAM_STOP",&SET_OPTIONAL_PROGRAM_STOP);
    def("SET_SPINDLE_MODE",&SET_SPINDLE_MODE);
    def("SET_SPINDLE_SPEED",&SET_SPINDLE_SPEED);
    def("SET_TOOL_TABLE_ENTRY",&SET_TOOL_TABLE_ENTRY);
    def("SET_TRAVERSE_RATE",&SET_TRAVERSE_RATE);
    def("SET_XY_ROTATION",&SET_XY_ROTATION);
    def("SPINDLE_RETRACT",&SPINDLE_RETRACT);
    def("SPINDLE_RETRACT_TRAVERSE",&SPINDLE_RETRACT_TRAVERSE);
    def("START_CHANGE",&START_CHANGE);
    def("START_CUTTER_RADIUS_COMPENSATION",&START_CUTTER_RADIUS_COMPENSATION);
    def("START_SPEED_FEED_SYNCH",&START_SPEED_FEED_SYNCH);
    def("START_SPINDLE_CLOCKWISE",&START_SPINDLE_CLOCKWISE);
    def("START_SPINDLE_COUNTERCLOCKWISE",&START_SPINDLE_COUNTERCLOCKWISE);
    def("STOP_CUTTER_RADIUS_COMPENSATION",&STOP_CUTTER_RADIUS_COMPENSATION);
    def("STOP_SPEED_FEED_SYNCH",&STOP_SPEED_FEED_SYNCH);
    def("STOP_SPINDLE_TURNING",&STOP_SPINDLE_TURNING);
    // def("STOP",&STOP);
    def("STRAIGHT_FEED",&STRAIGHT_FEED);
    def("STRAIGHT_PROBE",&STRAIGHT_PROBE);
    def("STRAIGHT_TRAVERSE",&STRAIGHT_TRAVERSE);
    def("TURN_PROBE_OFF",&TURN_PROBE_OFF);
    def("TURN_PROBE_ON",&TURN_PROBE_ON);
    // def("UNCLAMP_AXIS",&UNCLAMP_AXIS);
    def("UNLOCK_ROTARY",&UNLOCK_ROTARY);
    def("USE_LENGTH_UNITS",&USE_LENGTH_UNITS);
    def("USE_NO_SPINDLE_FORCE",&USE_NO_SPINDLE_FORCE);
    // def("USER_DEFINED_FUNCTION_ADD",&USER_DEFINED_FUNCTION_ADD);
    // def("USE_SPINDLE_FORCE",&USE_SPINDLE_FORCE);
    def("USE_TOOL_LENGTH_OFFSET",&USE_TOOL_LENGTH_OFFSET);
    def("WAIT",&WAIT);

    // from interp_queue.cc
    def("enqueue_SET_FEED_RATE", &enqueue_SET_FEED_RATE);
    def("enqueue_SET_FEED_MODE", &enqueue_SET_FEED_MODE);
    def("enqueue_DWELL", &enqueue_DWELL);
    def("enqueue_MIST_ON", &enqueue_MIST_ON);
    def("enqueue_MIST_OFF", &enqueue_MIST_OFF);
    def("enqueue_FLOOD_ON", &enqueue_FLOOD_ON);
    def("enqueue_FLOOD_OFF", &enqueue_FLOOD_OFF);
    def("enqueue_START_SPINDLE_CLOCKWISE", &enqueue_START_SPINDLE_CLOCKWISE);
    def("enqueue_START_SPINDLE_COUNTERCLOCKWISE", &enqueue_START_SPINDLE_COUNTERCLOCKWISE);
    def("enqueue_STOP_SPINDLE_TURNING", &enqueue_STOP_SPINDLE_TURNING);
    def("enqueue_SET_SPINDLE_MODE", &enqueue_SET_SPINDLE_MODE);
    def("enqueue_SET_SPINDLE_SPEED", &enqueue_SET_SPINDLE_SPEED);
    def("enqueue_COMMENT", &enqueue_COMMENT);

    // these need a wrapping so _setup can be passed in - probably better as Interp methods
    // def("enqueue_STRAIGHT_FEED", &enqueue_STRAIGHT_FEED);
    // def("enqueue_STRAIGHT_TRAVERSE", &enqueue_STRAIGHT_TRAVERSE);
    // def("enqueue_ARC_FEED", &enqueue_ARC_FEED);
    // def("enqueue_M_USER_COMMAND ", &enqueue_M_USER_COMMAND);
    // def("enqueue_START_CHANGE", & enqueue_START_CHANGE);
    def("GET_EXTERNAL_OFFSET_APPLIED",&GET_EXTERNAL_OFFSET_APPLIED);
    def("GET_EXTERNAL_OFFSETS",&GET_EXTERNAL_OFFSETS);

}
