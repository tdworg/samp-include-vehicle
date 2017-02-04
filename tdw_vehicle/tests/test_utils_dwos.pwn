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
#include <tdw_vdwos>

new TDW_gVehicleId;

public OnFilterScriptInit()
{
	TDW_gVehicleId = CreateVehicle(400, 12.5, 10.5, 4.2, 0.0, 0, 0, -1, 0);
}

public OnVehicleSpawn(vehicleid)
{
	// ! Doors
	new door_state = GetVehicleDoorState(vehicleid, FRONT_LEFT_DOOR);
	SetVehicleDoorState(vehicleid, FRONT_LEFT_DOOR, DOOR_OPENED);
	printf("[D] Old: %d Current: %d", door_state, GetVehicleDoorState(vehicleid,
		FRONT_LEFT_DOOR));
	CloseVehicleDoor(vehicleid, FRONT_LEFT_DOOR);
	if (IsVehicleDoorInState(vehicleid, FRONT_LEFT_DOOR, DOOR_CLOSED))
		print(!"C");
	OpenVehicleDoor(vehicleid, FRONT_LEFT_DOOR);
	if (IsVehicleDoorInState(vehicleid, FRONT_LEFT_DOOR, DOOR_OPENED))
		print(!"O");

	// Utils
	new
		Float:x,
		Float:y,
		Float:z;
	GetVehicleDoorPos(vehicleid, FRONT_LEFT_DOOR, x, y, z);

	// ! Windows
	new window_state = GetVehicleWindowState(vehicleid, FRONT_LEFT_DOOR);
	SetVehicleWindowState(vehicleid, FRONT_LEFT_DOOR, WINDOW_OPENED);
	printf("[W] Old: %d Current: %d", window_state, GetVehicleWindowState(
		vehicleid, FRONT_LEFT_DOOR));
	CloseVehicleWindow(vehicleid, FRONT_LEFT_DOOR);
	if (IsVehicleWindowInState(vehicleid, FRONT_LEFT_DOOR, WINDOW_CLOSED))
		print(!"C");
	OpenVehicleWindow(vehicleid, FRONT_LEFT_DOOR);
	if (IsVehicleWindowInState(vehicleid, FRONT_LEFT_DOOR, WINDOW_OPENED))
		print(!"O");
}
