/** ======================================================================== **\
	Vehicle Damage Status

| License:
Copyright (c) 2016 Double V

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
\** ======================================================================== **/


#if defined _inc_damage_status
	#undef _inc_damage_status
#endif

#if defined _TDW_VHLIB_DAMAGE_STATUS
	#endinput
#endif
#define _TDW_VHLIB_DAMAGE_STATUS


static stock TDW_g_sDataStorage;

stock
	GetVehiclePanelsStatus(vehicleid, &front_left_panel, &front_right_panel,
		&rear_left_panel, &rear_right_panel, &windshield, &front_bumper,
		&rear_bumper)
{
	new panels;
	if (GetVehicleDamageStatus(vehicleid, panels, TDW_g_sDataStorage,
		TDW_g_sDataStorage, TDW_g_sDataStorage))
		return 0;
	front_left_panel = panels & 0xF;
	front_right_panel = panels >>> 4 & 0xF;
	rear_left_panel = panels >>> 8 & 0xF;
	rear_right_panel = panels >>> 12 & 0xF;
	windshield = panels >>> 16 & 0xF;
	front_bumper = panels >>> 20 & 0xF;
	rear_bumper = panels >>> 24 & 0xF;
	return 1;
}


stock
	SetVehiclePanelsStatus(vehicleid, front_left_panel, front_right_panel,
		rear_left_panel, rear_right_panel, windshield, front_bumper,
		rear_bumper)
{
	new doors, lights, tires;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sDataStorage, doors, lights,
		tires) == 0)
		return 0;
	UpdateVehicleDamageStatus(vehicleid, front_left_panel |
		(front_right_panel << 4) | (rear_left_panel << 8) |
		(rear_right_panel << 12) | (windshield << 16) | (front_bumper << 20) |
		(rear_bumper << 24), doors, lights, tires
	);
	return 1;
}


stock
	GetVehicleDoorsStatus(vehicleid, &bonnet, &boot, &driver_door,
		&passenger_door)
{
	new doors;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sDataStorage, doors,
		TDW_g_sDataStorage, TDW_g_sDataStorage) == 0)
		return 0;
	bonnet = doors & 7;
	boot = doors >>> 8 & 7;
	driver_door = doors >>> 16 & 7;
	passenger_door = doors >>> 24 & 7;
	return 1;
}


stock
	SetVehicleDoorsStatus(vehicleid, bonnet, boot, driver_door, passenger_door)
{
	new panels, lights, tires;
	if (GetVehicleDamageStatus(vehicleid, panels, TDW_g_sDataStorage, lights,
		tires) == 0)
		return 0;
	UpdateVehicleDamageStatus(vehicleid, panels, bonnet | (boot << 8) |
		(driver_door << 16) | (passenger_door << 24), lights, tires
	);
	return 1;
}


stock
	GetVehicleLightsStatus(vehicleid, &front_left_light, &front_right_light,
		&back_lights)
{
	new lights;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sDataStorage,
		TDW_g_sDataStorage, lights, TDW_g_sDataStorage) == 0)
		return 0;
	front_left_light = lights & 1;
	front_right_light = lights >>> 2 & 1;
	back_lights = lights >>> 6 & 1;
	return 1;
}


stock
	SetVehicleLightsStatus(vehicleid, front_left_light, front_right_light,
		back_lights)
{
	new panels, doors, tires;
	if (GetVehicleDamageStatus(vehicleid, panels, doors, TDW_g_sDataStorage,
		tires) == 0)
		return 0;
	UpdateVehicleDamageStatus(vehicleid, panels, doors,
		front_left_light | (front_right_light << 2) | (back_lights << 6), tires
	);
	return 1;
}


stock
	GetVehicleTiresStatus(vehicleid, &rear_right_tire, &front_right_tire,
		&rear_left_tire, &front_left_tire)
{
	new tires;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sDataStorage,
		TDW_g_sDataStorage, TDW_g_sDataStorage, tires) == 0)
		return 0;
	rear_right_tire = tires & 1;
	front_right_tire = tires >>> 1 & 1;
	rear_left_tire = tires >>> 2 & 1;
	front_left_tire = tires >>> 3 & 1;
	return 1;
}


stock
	SetVehicleTiresStatus(vehicleid, rear_right_tire, front_right_tire,
		rear_left_tire, front_left_tire)
{
	new panels, doors, lights;
	if (GetVehicleDamageStatus(vehicleid, panels, doors, lights,
		TDW_g_sDataStorage) == 0)
		return 0;
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights,
		rear_right_tire | (front_right_tire << 1) | (rear_left_tire << 2) |
		(front_left_tire << 3)
	);
	return 1;
}
