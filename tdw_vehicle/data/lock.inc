/** ======================================================================== **\
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


#if defined _inc_lock
	#undef _inc_lock
#endif

#if defined _TDW_VHLIB__LOCK
	#endinput
#endif

#define _TDW_VHLIB__LOCK


enum
	E_TDW_DOOR_STATE
{
	EI_TDW_DOOR_STATE_LOCKED,
	EI_TDW_DOOR_STATE_UNLOCKED
};


static stock
	E_TDW_DOOR_STATE:TDW_g_sVehicleDoorState[MAX_VEHICLES char] = {
		EI_TDW_DOOR_STATE_UNLOCKED, ...
	};


stock
	LockVehicleDoors(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	if (TDW_g_sVehicleDoorState{vehicleid} == EI_TDW_DOOR_STATE_LOCKED)
		return 0;
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot,
		objective
	);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, true, bonnet, boot,
		objective
	);
	TDW_g_sVehicleDoorState{vehicleid} = EI_TDW_DOOR_STATE_LOCKED;
	return 1;
}


stock
	UnlockVehicleDoor(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	if (TDW_g_sVehicleDoorState{vehicleid} == EI_TDW_DOOR_STATE_UNLOCKED)
		return 0;
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot,
		objective
	);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, false, bonnet, boot,
		objective
	);
	TDW_g_sVehicleDoorState{vehicleid} = EI_TDW_DOOR_STATE_UNLOCKED;
	return 1;
}


stock
	IsVehicleLocked(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	if (TDW_g_sVehicleDoorState{vehicleid} != EI_TDW_DOOR_STATE_LOCKED)
		return 0;
	return 1;
}
