/* ========================================================================== *\
	Damage status

| Description:
	Change the visual appearance of the vehicle. It interacts with all parts of
	the vehicles.

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

| Metadata:
	[Functions]:
		Stock:
			- GetVehicleDoorsStatus
			- GetVehicleLightsStatus
			- GetVehiclePanelsStatus
			- GetVehicleTiresStatus
			- SetVehicleDoorsStatus
			- SetVehicleLightsStatus
			- SetVehiclePanelsStatus
			- SetVehicleTiresStatus
		Static:
			-
		Public:
			-
		Hooks:
			-
	[Callbacks]:
		-
	[Definitions]:
		-
	[Enumerations]:
		-
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			- TDW_g_sNullStorage
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_vdamage
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_vdamage
#endif

#if defined _TDW_VH_DAMAGE_STATUS
	#endinput
#endif

#define _TDW_VH_DAMAGE_STATUS

#include "tdw_vehicle"

// -----------------------------------------------------------------------------
// Static scope:

static stock
	TDW_g_sNullStorage = 0; // We use this to reduce the size of the stack.

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleLightsStatus</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="&front_left_light">The state of the front left light</param>
<param name="&front_right_light">The state of the front right light</param>
<param name="&back_lights">The state of the back lights</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleLightsStatus(vehicleid, &front_left_light, &front_right_light,
	&back_lights)
{
	new
		lights;

	// Check availability of the vehicle in the game and get the flag of
	// the headlights.
	if (0 == GetVehicleDamageStatus(vehicleid, TDW_g_sNullStorage,
		TDW_g_sNullStorage, lights, TDW_g_sNullStorage))
		return 0;

	front_left_light = lights & 1;
	front_right_light = (lights >>> 2) & 1;
	back_lights = (lights >>> 6) & 1;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>SetVehicleLightsStatus</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="front_left_light">The state of the front left light</param>
<param name="front_right_light">The state of the front right light</param>
<param name="back_lights">The state of the back lights</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetVehicleLightsStatus(vehicleid, front_left_light, front_right_light,
	back_lights)
{
	new
		panels,
		doors,
		tires;

	// Check availability of the vehicle in the game and get the flags of
	// other statuses.
	if (0 == GetVehicleDamageStatus(vehicleid, panels, doors,
		TDW_g_sNullStorage, tires))
		return 0;

	UpdateVehicleDamageStatus(vehicleid, panels, doors,
		((back_lights & 1) << 6) | ((front_right_light & 1) << 2) |
		(front_left_light & 1), tires);

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleTiresStatus</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="&rear_right_tire">The state of the rear right tire</param>
<param name="&front_right_tire">The state of the front right tire</param>
<param name="&rear_left_tire">The state of the rear left tire</param>
<param name="&front_left_tire">The state of the front left tire</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleTiresStatus(vehicleid, &rear_right_tire, &front_right_tire,
		&rear_left_tire, &front_left_tire)
{
	new
		tires;

	if (0 == GetVehicleDamageStatus(vehicleid, TDW_g_sNullStorage,
		TDW_g_sNullStorage, TDW_g_sNullStorage, tires))
		return 0;

	rear_right_tire = tires & 1;
	front_right_tire = (tires >>> 1) & 1;
	rear_left_tire = (tires >>> 2) & 1;
	front_left_tire = (tires >>> 3) & 1;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>SetVehicleTiresStatus</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="rear_right_tire">The state of the rear right tire</param>
<param name="front_right_tire">The state of the front right tire</param>
<param name="rear_left_tire">The state of the rear left tire</param>
<param name="front_left_tire">The state of the front left tire</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetVehicleTiresStatus(vehicleid, rear_right_tire, front_right_tire,
		rear_left_tire, front_left_tire)
{
	new
		panels,
		doors,
		lights;

	if (0 == GetVehicleDamageStatus(vehicleid, panels, doors, lights,
		TDW_g_sNullStorage))
		return 0;

	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights,
		rear_right_tire | (front_right_tire << 1) | (rear_left_tire << 2) |
		(front_left_tire << 3)
	);

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehiclePanelsStatus</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="&front_left_panel">The state of the front left panel</param>
<param name="&front_right_panel">The state of the front right panel</param>
<param name="&rear_left_panel">The state of the rear left panel</param>
<param name="&rear_right_panel">The state of the rear right panel</param>
<param name="&windshield">The state of the windshield</param>
<param name="&front_bumper">The state of the front bumper</param>
<param name="&rear_bumper">The state of the rear bumper</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehiclePanelsStatus(vehicleid, &front_left_panel, &front_right_panel,
	&rear_left_panel, &rear_right_panel, &windshield, &front_bumper,
	&rear_bumper)
{
	new
		panels;

	if (0 == GetVehicleDamageStatus(vehicleid, panels, TDW_g_sNullStorage,
		TDW_g_sNullStorage, TDW_g_sNullStorage))
		return 0;

	front_left_panel = panels & 0xF;
	front_right_panel = (panels >> 4) & 0xF;
	rear_left_panel = (panels >> 8) & 0xF;
	rear_right_panel = (panels >> 12) & 0xF;
	windshield = (panels >> 16) & 0xF;
	front_bumper = (panels >> 20) & 0xF;
	rear_bumper = (panels >> 24) & 0xF;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>SetVehiclePanelsStatus</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="front_left_panel">The state of the front left panel</param>
<param name="front_right_panel">The state of the front right panel</param>
<param name="rear_left_panel">The state of the rear left panel</param>
<param name="rear_right_panel">The state of the rear right panel</param>
<param name="windshield">The state of the windshield</param>
<param name="front_bumper">The state of the front bumper</param>
<param name="rear_bumper">The state of the rear bumper</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetVehiclePanelsStatus(vehicleid, front_left_panel, front_right_panel,
	rear_left_panel, rear_right_panel, windshield, front_bumper,
	rear_bumper)
{
	new
		doors,
		lights,
		tires;

	if (0 == GetVehicleDamageStatus(vehicleid, TDW_g_sNullStorage, doors,
		lights, tires))
		return 0;

	UpdateVehicleDamageStatus(vehicleid, (front_left_panel |
		(front_right_panel << 4) | (rear_left_panel << 8) |
		(rear_right_panel << 12) | (windshield << 16) | (front_bumper << 20) |
		(rear_bumper << 24)), doors, lights, tires
	);

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleDoorsStatus</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="&bonnet">The state of the bonnet</param>
<param name="&boot">The state of the rear boot</param>
<param name="&driver_door">The state of the driver door</param>
<param name="&passenger_door">The state of the passenger door</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleDoorsStatus(vehicleid, &bonnet, &boot, &driver_door,
	&passenger_door)
{
	new
		doors;

	if (0 == GetVehicleDamageStatus(vehicleid, TDW_g_sNullStorage, doors,
		TDW_g_sNullStorage, TDW_g_sNullStorage))
		return 0;

	bonnet = doors & 7;
	boot = (doors >>> 8) & 7;
	driver_door = (doors >>> 16) & 7;
	passenger_door = (doors >>> 24) & 7;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>SetVehicleDoorsStatus</summary>
<param name="bonnet">The state of the bonnet</param>
<param name="boot">The state of the rear boot</param>
<param name="driver_door">The state of the driver door</param>
<param name="passenger_door">The state of the passenger door</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetVehicleDoorsStatus(vehicleid, bonnet, boot, driver_door,
	passenger_door)
{
	new
		panels,
		lights,
		tires;

	if (0 == GetVehicleDamageStatus(vehicleid, panels, TDW_g_sNullStorage,
		lights, tires))
		return 0;

	UpdateVehicleDamageStatus(vehicleid, panels, bonnet | (boot << 8) |
		(driver_door << 16) | (passenger_door << 24), lights, tires
	);

	return 1;
}
