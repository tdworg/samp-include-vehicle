/** ======================================================================== **\
| Name:
	Vehicle Additionally Data

| Category:
	data

| Version:
	2.0.1

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


#if defined _inc_vehicle_additionally_data
	#undef _inc_vehicle_additionally_data
#endif

#if defined _TDW_VEHICLE_D_ADDITIONALLY
	#endinput
#endif

#define _TDW_VEHICLE_D_ADDITIONALLY


static stock
	TDW_g_sVDynamic@Interior[MAX_VEHICLES char],
	TDW_g_sVDynamic@Paintjob[MAX_VEHICLES char],
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


native Original_SetVehicleVirtualWorld(vehicleid,
	worldid) = SetVehicleVirtualWorld;

stock
	TDWVH@SetVehicleVirtualWorld(vehicleid, worldid)
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
#define SetVehicleVirtualWorld(%0) TDWVH@SetVehicleVirtualWorld(%0)


public
	OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	TDW_g_sVDynamic@Paintjob{vehicleid} = paintjobid;
#if defined TDWVH@OnVehiclePaintjob
	return TDWVH@OnVehiclePaintjob(playerid, vehicleid, paintjobid);
#else
	return 1;
#endif
}
#if defined _ALS_OnVehiclePaintjob
	#undef OnVehiclePaintjob
#else
	#define _ALS_OnVehiclePaintjob
#endif
#define OnVehiclePaintjob(%0) TDWVH@OnVehiclePaintjob(%0)
#if defined TDWVH@OnVehiclePaintjob
	forward TDWVH@OnVehiclePaintjob(playerid, vehicleid, paintjobid);
#endif


public
	OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		TDW_g_sVDynamic@LastDriver[vehicleid] = playerid;
	}
#if defined TDWVH@OnPlayerStateChange
	return TDWVH@OnPlayerStateChange(playerid, newstate, oldstate);
#else
	return 1;
#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange(%0) TDWVH@OnPlayerStateChange(%0)
#if defined TDWVH@OnPlayerStateChange
	forward TDWVH@OnPlayerStateChange(playerid, newstate, oldstate);
#endif