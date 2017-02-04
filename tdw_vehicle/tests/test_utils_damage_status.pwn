/* ========================================================================== *\
| License:
	Copyright (c) 2016-2017 Double V

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgement in the product documentation would be
		appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.
\* ========================================================================== */

#define FILTERSCRIPT

#include <a_samp>
#include <tdw_vdamage>

public OnFilterScriptInit()
{

}

public OnVehicleSpawn(vehicleid)
{
	// Lights
	new
		front_left_light,
		front_right_light,
		back_lights;
	GetVehicleLightsStatus(vehicleid, front_left_light, front_right_light,
		back_lights);
	SetVehicleLightsStatus(vehicleid, front_left_light, front_right_light,
		back_lights);

	// Tires
	new
		rear_right_tire,
		front_right_tire,
		rear_left_tire,
		front_left_tire;
	GetVehicleTiresStatus(vehicleid, rear_right_tire, front_right_tire,
		rear_left_tire, front_left_tire);
	SetVehicleTiresStatus(vehicleid, rear_right_tire, front_right_tire,
		rear_left_tire, front_left_tire);

	// Panels
	new
		front_left_panel,
		front_right_panel,
		rear_left_panel,
		rear_right_panel,
		windshield,
		front_bumper,
		rear_bumper;
	GetVehiclePanelsStatus(vehicleid, front_left_panel, front_right_panel,
		rear_left_panel, rear_right_panel, windshield, front_bumper,
		rear_bumper);
	SetVehiclePanelsStatus(vehicleid, front_left_panel, front_right_panel,
		rear_left_panel, rear_right_panel, windshield, front_bumper,
		rear_bumper);

	// Doors
	new
		bonnet,
		boot,
		driver_door,
		passenger_door;
	GetVehicleDoorsStatus(vehicleid, bonnet, boot, driver_door,
		passenger_door);
	SetVehicleDoorsStatus(vehicleid, bonnet, boot, driver_door,
		passenger_door);
}
