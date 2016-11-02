/** ======================================================================== **\
	Vehicle Additionally Data

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


#if defined _inc_other_data
	#undef _inc_other_data
#endif

#if defined _TDW_VHLIB__OTHER_DATA
	#endinput
#endif

#define _TDW_VHLIB__OTHER_DATA


static stock
	// I used the char operator to optimize the data segment.
	TDW_g_sVDynamic@Paintjob[MAX_VEHICLES char],
	// Limit of the virtual world is cellmax, i.e. cellmax > 255
	// cellmax is 2147483647
	TDW_g_sVDynamic@VirtualWorld[MAX_VEHICLES],
	TDW_g_sVDynamic@LastDriver[MAX_VEHICLES];


stock
	GetVehicleLastDriverId(vehicleid)
{
	return (IsValidVehicle(vehicleid) == 0
		? TDW_g_sVDynamic@LastDriver[vehicleid]
		: INVALID_VEHICLE_ID
	);
}


stock
	GetVehiclePaintjobId(vehicleid)
{
	return (IsValidVehicle(vehicleid) == 0
		? TDW_g_sVDynamic@Paintjob{vehicleid}
		: INVALID_VEHICLE_ID
	);
}


stock
	SetVehiclePaintjobId(vehicleid, paintjobid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return INVALID_VEHICLE_ID;
	if (_:IS_PAINTJOB_VALID(paintjobid) == 0)
		return 0;
	return ChangeVehiclePaintjob(vehicleid,
		(TDW_g_sVDynamic@Paintjob{vehicleid} = paintjobid)
	);
}


native nts_SetVehicleVirtualWorld(vehicleid, worldid) = SetVehicleVirtualWorld;

stock
	TDWVH_OD@SetVehicleVirtualWorld(vehicleid, worldid)
{
	return (IsValidVehicle(vehicleid) == 0
		? SetVehicleVirtualWorld(vehicleid,
			(TDW_g_sVDynamic@VirtualWorld[vehicleid] = worldid)
		)
		: INVALID_VEHICLE_ID
	);
}

#if defined _ALS_SetVehicleVirtualWorld
	#undef SetVehicleVirtualWorld
#else
	#define _ALS_SetVehicleVirtualWorld
#endif

#define SetVehicleVirtualWorld TDWVH_OD@SetVehicleVirtualWorld


public
	OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	TDW_g_sVDynamic@Paintjob{vehicleid} = paintjobid;
	#if defined TDWVH_OD@OnVehiclePaintjob
	return TDWVH_OD@OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	#else
	return 1;
	#endif
}

#if defined _ALS_OnVehiclePaintjob
	#undef OnVehiclePaintjob
#else
	#define _ALS_OnVehiclePaintjob
#endif

#define OnVehiclePaintjob TDWVH_OD@OnVehiclePaintjob

#if defined TDWVH_OD@OnVehiclePaintjob
forward TDWVH_OD@OnVehiclePaintjob(playerid, vehicleid, paintjobid);
#endif


public
	OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		TDW_g_sVDynamic@LastDriver[vehicleid] = playerid;
	}
	#if defined TDWVH_OD@OnPlayerStateChange
	return TDWVH_OD@OnPlayerStateChange(playerid, newstate, oldstate);
	#else
	return 1;
	#endif
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVH_OD@OnPlayerStateChange

#if defined TDWVH_OD@OnPlayerStateChange
forward TDWVH_OD@OnPlayerStateChange(playerid, newstate, oldstate);
#endif
