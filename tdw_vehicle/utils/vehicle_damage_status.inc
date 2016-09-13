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


#if defined _inc_vehicle_damage_status
	#undef _inc_vehicle_damage_status
#endif

#if defined _TDW_VEHICLE_U_DSTATUS
	#endinput
#endif

#define _TDW_VEHICLE_U_DSTATUS


#if __Pawn < 0x030A
@__TDW_VEHICLE_UTILS__FIX();
@__TDW_VEHICLE_UTILS__FIX()
{
	#emit retn
	// The stock compiler crashes because of using sysreq.c on a native
	// function.
	UpdateVehicleDamageStatus(0, 0, 0, 0, 0);
}
#endif


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
	#emit const.alt     0xF
	// front_left_panel
	#emit load.s.pri    panels
	#emit and
	#emit sref.s.pri    front_left_panel
	// front_right_panel
	#emit shr.c.pri     4 // 4
	#emit and
	#emit sref.s.pri    front_right_panel
	// rear_left_panel
	#emit shr.c.pri     4 // 8
	#emit and
	#emit sref.s.pri    rear_left_panel
	// rear_right_panel
	#emit shr.c.pri     4 // 12
	#emit and
	#emit sref.s.pri    rear_right_panel
	// windshield
	#emit shr.c.pri     4 // 16
	#emit and
	#emit sref.s.pri    windshield
	// front_bumper
	#emit shr.c.pri     4 // 20
	#emit and
	#emit sref.s.pri    front_bumper
	// rear_bumper
	#emit shr.c.pri     4 // 24
	#emit and
	#emit sref.s.pri    rear_bumper
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
	#emit push.s        tires // 4
	#emit push.s        lights // 8
	#emit push.s        doors // 12
	// front_left_panel
	#emit load.s.pri    front_left_panel
	// front_right_panel
	#emit load.s.alt    front_right_panel
	#emit shl.c.alt     4
	#emit or
	// rear_left_panel
	#emit load.s.alt    rear_left_panel
	#emit shl.c.alt     8
	#emit or
	// rear_right_panel
	#emit load.s.alt    rear_right_panel
	#emit shl.c.alt     12
	#emit or
	// windshield
	#emit load.s.alt    windshield
	#emit shl.c.alt     16
	#emit or
	// front_bumper
	#emit load.s.alt    front_bumper
	#emit shl.c.alt     20
	#emit or
	// rear_bumper
	#emit load.s.alt    rear_bumper
	#emit shl.c.alt     24
	#emit or
	// call the function
	#emit push.pri      // 16
	#emit push.s        vehicleid // 20
	#emit push.c        20
	#emit sysreq.c      UpdateVehicleDamageStatus
	#emit stack         24
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
	#emit const.alt     0x7
	// bonnet
	#emit load.s.pri    doors
	#emit and
	#emit sref.s.pri    bonnet
	// boot
	#emit shr.c.pri     8 // 8
	#emit and
	#emit sref.s.pri    boot
	// driver_door
	#emit shr.c.pri     8 // 16
	#emit and
	#emit sref.s.pri    driver_door
	// passenger_door
	#emit shr.c.pri     8 // 24
	#emit and
	#emit sref.s.pri    passenger_door
	return 1;
}


stock
	SetVehicleDoorsStatus(vehicleid, bonnet, boot, driver_door, passenger_door)
{
	new panels, lights, tires;
	if (GetVehicleDamageStatus(vehicleid, panels, TDW_g_sDataStorage, lights,
		tires) == 0)
		return 0;
	#emit push.s        tires // 4
	#emit push.s        lights // 8
	// bonnet
	#emit load.s.pri    bonnet
	// boot
	#emit load.s.alt    boot
	#emit shl.c.alt     8
	#emit or
	// driver_door
	#emit load.s.alt    driver_door
	#emit shl.c.alt     16
	#emit or
	// passenger_door
	#emit load.s.alt    passenger_door
	#emit shl.c.alt     24
	#emit or
	// call the function
	#emit push.pri      // 12
	#emit push.s        panels // 16
	#emit push.s        vehicleid // 20
	#emit push.c        20
	#emit sysreq.c      UpdateVehicleDamageStatus
	#emit stack         24
	return 1;
}


stock
	GetVehicleLightsStatus(vehicleid, &light1, &light2, &light3, &light4)
{
	new lights;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sDataStorage,
		TDW_g_sDataStorage, lights, TDW_g_sDataStorage) == 0)
		return 0;
	#emit const.alt     0x1
	// light1
	#emit load.s.pri    lights
	#emit and
	#emit sref.s.pri    light1
	// light2
	#emit shr.c.pri     1 // 2
	#emit and
	#emit sref.s.pri    light2
	// light3
	#emit shr.c.pri     1 // 3
	#emit and
	#emit sref.s.pri    light3
	// light4
	#emit shr.c.pri     1 // 4
	#emit and
	#emit sref.s.pri    light4
	return 1;
}


stock
	SetVehicleLightsStatus(vehicleid, light1, light2, light3, light4)
{
	new panels, doors, tires;
	if (GetVehicleDamageStatus(vehicleid, panels, doors, TDW_g_sDataStorage,
		tires) == 0)
		return 0;
	#emit push.s        tires // 4
	// light1
	#emit load.s.pri    light1
	// light2
	#emit load.s.alt    light2
	#emit shl.c.alt     1
	#emit or
	// light3
	#emit load.s.alt    light3
	#emit shl.c.alt     2
	#emit or
	// light4
	#emit load.s.alt    light4
	#emit shl.c.alt     3
	#emit or
	// call the function
	#emit push.pri      // 8
	#emit push.s        doors // 12
	#emit push.s        panels // 16
	#emit push.s        vehicleid // 20
	#emit push.c        20
	#emit sysreq.c      UpdateVehicleDamageStatus
	#emit stack         24
	return 1;
}


stock
	GetVehicleTiresStatus(vehicleid, &tire1, &tire2, &tire3, &tire4)
{
	new tires;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sDataStorage,
		TDW_g_sDataStorage, TDW_g_sDataStorage, tires) == 0)
		return 0;
	#emit const.alt     0x1
	// tire1
	#emit load.pri      tires
	#emit and
	#emit sref.s.pri    tire1
	// tire2
	#emit shr.c.pri     1 // 2
	#emit and
	#emit sref.s.pri    tire2
	// tire3
	#emit shr.c.pri     1 // 3
	#emit and
	#emit sref.s.pri    tire3
	// tire4
	#emit shr.c.pri     1 // 4
	#emit and
	#emit sref.s.pri    tire4
#endif
	return 1;
}


stock
	SetVehicleTiresStatus(vehicleid, tire1, tire2, tire3, tire4)
{
	new panels, doors, lights, tires;
	if (GetVehicleDamageStatus(vehicleid, panels, doors, lights,
		TDW_g_sDataStorage) == 0)
		return 0;
	// tire1
	#emit load.s.pri    tire1
	// tire2
	#emit load.s.alt    tire2
	#emit shl.c.alt     1
	#emit or
	// tire3
	#emit load.s.alt    tire3
	#emit shl.c.alt     2
	#emit or
	// tire4
	#emit load.s.alt    tire4
	#emit shl.c.alt     3
	#emit or
	// call the function
	#emit push.pri      // 4
	#emit push.s        lights // 8
	#emit push.s        doors // 12
	#emit push.s        panels // 16
	#emit push.s        vehicleid // 20
	#emit push.c        20
	#emit sysreq.c      UpdateVehicleDamageStatus
	#emit stack         24
	return 1;
}
