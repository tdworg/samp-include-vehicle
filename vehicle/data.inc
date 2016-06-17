/** ======================================================================== **\
	Vehicle Dynamic data

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

#if defined _TDW_VEHICLE_DATA_INC_
	#endinput
#endif
#define _TDW_VEHICLE_DATA_INC_

#if defined _TDW_VEHICLE_FOREACH_DEFINED && _TDW_VEHICLE_FOREACH_DEFINED
	#if !defined Vehicle@YSII_Ag
		new Iterator:Vehicle<MAX_VEHICLES>;
	#endif
	#if !defined _TDW_VEHICLE_FOREACH_ARRAY
		#define _TDW_VEHICLE_FOREACH_ARRAY
	#endif
	#pragma unused Vehicle@YSII_Ag
	#pragma unused Vehicle@YSII_Cg
#endif

enum e_TDW_VEHICLE
{
	// I created only necessary elements in the enumeration.
	Float:ei_pos_x,
	Float:ei_pos_y,
	Float:ei_pos_z,
	Float:ei_pos_rotation,
	ei_color_1,
	ei_color_2,
	ei_model_id
};

enum e_TDW_BLOWNED_STATE
{
	BLOWNED_STATE_DEATH,
	BLOWNED_STATE_RESPAWNED
};

static stock // The general variables.
	TDW_g_sVehicleData[MAX_VEHICLES][e_TDW_VEHICLE],
	TDW_g_sVehicleId;
static stock // The dynamic variables.
	TDW_g_sVehicleD@Interior[MAX_VEHICLES],
	TDW_g_sVehicleD@VirtualWorld[MAX_VEHICLES],
	TDW_g_sVehicleD@Paintjob[MAX_VEHICLES],
	TDW_g_sVehicleD@LastDriver[MAX_VEHICLES],
	e_TDW_BLOWNED_STATE:TDW_g_sVehicleD@BlownedState[MAX_VEHICLES char];

native BAD_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2) = AddStaticVehicle;
native BAD_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2, respawn_delay,
	addsiren) = AddStaticVehicleEx;
native BAD_CreateVehicle(vehicletype, Float:x, Float:y, Float:z,
	Float:rotation, color1, color2, respawn_delay, addsiren) = CreateVehicle;
native BAD_DestroyVehicle(vehicleid) = DestroyVehicle;
native BAD_SetVehicleToRespawn(vehicleid) = SetVehicleToRespawn;
native BAD_SetVehicleVirtualWorld(vehicleid, worldid) = SetVehicleVirtualWorld;

#if _TDW_DEBUG_
static const
	TDW_DEBUG_MSG@VCreated[] = "Vehicle created! id: %d | Func: %s",
	TDW_DEBUG_MSG@VDestroyed[] = "Vehicle destroyed! id: %d";
#endif

// AddStaticVehicle hook
stock
	TDWVH@AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2)
{
	if ((TDW_g_sVehicleId = AddStaticVehicle(modelid, spawn_x, spawn_y,
		spawn_z, z_angle, color1, color2)) != INVALID_VEHICLE_ID)
	{
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_model_id]     = modelid;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_1]      = color1;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_2]      = color2;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_x]        = spawn_x;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_y]        = spawn_y;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_z]        = spawn_z;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_rotation] = z_angle;

		#if defined _TDW_VEHICLE_FOREACH_ARRAY
		Iter_Add(TDW_g_sVehicleId, Vehicle);
		#endif
		#if _TDW_DEBUG_
		static const debug[] = "AddStaticVehicle";
		printf(TDW_DEBUG_MSG@VCreated, TDW_g_sVehicleId, AddStaticVehicle);
		#endif
	}
	return TDW_g_sVehicleId;
}
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle(%0) TDWVH@AddStaticVehicle(%0)

// AddStaticVehicleEx hook
stock
	TDWVH@AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2, respawn_delay,
		addsiren = 0)
{
	if ((TDW_g_sVehicleId = AddStaticVehicleEx(modelid, spawn_x, spawn_y,
		spawn_z, z_angle, color1, color2, respawn_delay, addsiren)) !=
		INVALID_VEHICLE_ID)
	{
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_model_id]     = modelid;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_1]      = color1;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_2]      = color2;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_x]        = spawn_x;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_y]        = spawn_y;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_z]        = spawn_z;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_rotation] = z_angle;

		#if defined _TDW_VEHICLE_FOREACH_ARRAY
		Iter_Add(TDW_g_sVehicleId, Vehicle);
		#endif
		#if _TDW_DEBUG_
		static const debug[] = "AddStaticVehicleEx";
		printf(TDW_DEBUG_MSG@VCreated, TDW_g_sVehicleId, AddStaticVehicle);
		#endif
	}
	return TDW_g_sVehicleId;
}
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx(%0) TDWVH@AddStaticVehicleEx(%0)

// CreateVehicle hook
stock
	TDWVH@CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation,
		color1, color2, respawn_delay, addsiren = 0)
{
	if ((TDW_g_sVehicleId = CreateVehicle(vehicletype, x, y, z, rotation,
		color1, color2, respawn_delay, addsiren)) != INVALID_VEHICLE_ID)
	{
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_model_id]     = modelid;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_1]      = color1;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_2]      = color2;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_x]        = x;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_y]        = y;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_z]        = z;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_rotation] = rotation;

		#if defined _TDW_VEHICLE_FOREACH_ARRAY
		Iter_Add(TDW_g_sVehicleId, Vehicle);
		#endif
		#if _TDW_DEBUG_
		static const debug[] = "CreateVehicle";
		printf(TDW_DEBUG_MSG@VCreated, TDW_g_sVehicleId, AddStaticVehicle);
		#endif
	}
	return TDW_g_sVehicleId;
}
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#define CreateVehicle(%0) TDWVH@CreateVehicle(%0)

stock
	TDWVH@DestroyVehicle(vehicleid)
{
	if (DestroyVehicle(vehicleid) == 0)
		return 0;
	// I know that zero and floating zero it's equal things,
	// but the compiler gives a warning.
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_model_id]     =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_1]      =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_2]      = 0;
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_x]        =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_y]        =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_z]        =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_rotation] = 0.0;

	#if defined _TDW_VEHICLE_FOREACH_ARRAY
	Iter_Remove(TDW_g_sVehicleId, Vehicle);
	#endif
	#if _TDW_DEBUG_
	printf(TDW_DEBUG_MSG@VDestroyed, vehicleid);
	#endif
	return 1;
}
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle(%0) TDWVH@DestroyVehicle(%0)

#if defined OnVehicleRespawn
	#if defined OnVehicleRespawn
	forward OnVehicleRespawn(vehicleid);
	#endif

	stock
		TDWVH@SetVehicleToRespawn(vehicleid)
	{
		if (SetVehicleToRespawn(vehicleid))
		{
			OnVehicleRespawn(vehicleid);
			return 1;
		}
		return 0;
	}
	#if defined _ALS_SetVehicleToRespawn
	#undef SetVehicleToRespawn
	#else
		#define _ALS_SetVehicleToRespawn
	#endif
	#define SetVehicleToRespawn(%0) TDWVH@SetVehicleToRespawn(%0)
#endif

stock
	TDWVH@SetVehicleVirtualWorld(vehicleid, worldid)
{
	if (TDW_g_sVehicleData[vehicleid][ei_model_id] != 0)
	{
		TDW_g_sVehicleD@VirtualWorld[vehicleid] = worldid;
	}
	return 0;
}
#if defined _ALS_SetVehicleVirtualWorld
#undef SetVehicleVirtualWorld
#else
	#define _ALS_SetVehicleVirtualWorld
#endif
#define SetVehicleVirtualWorld(%0) TDWVH@SetVehicleVirtualWorld(%0)

stock
	GetVehicleColor(vehicleid, &color1, &color2)
{
	if (TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		return (color1 = color2 = 0); // I optimized this.
	color1 = TDW_g_sVehicleData[vehicleid][ei_color_1];
	color2 = TDW_g_sVehicleData[vehicleid][ei_color_2];
	return 1;
}
#if !defined SetVehicleColor
	#define SetVehicleColor(%0) ChangeVehicleColor(%0)
#endif

stock
	GetVehiclePaintjob(vehicleid)
{
	return (
		(TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		? INVALID_VEHICLE_ID
		: TDW_g_sVehicleD@Paintjob[vehicleid]
	)
}

stock
	SetVehiclePaintjob(vehicleid, paintjobid)
{
	if (TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		return INVALID_VEHICLE_ID;
	return (
		(VEHICLE_PAINTJOB_MIN <= paintjobid <= VEHICLE_PAINTJOB_MAX)
		? ChangeVehiclePaintjob(vehicleid,
			(TDW_g_sVehicleD@Paintjob[vehicleid] = paintjobid)
		)
		: 0
	);
}

stock
	GetVehicleInterior(vehicleid)
{
	return (
		(TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		? INVALID_VEHICLE_ID
		: TDW_g_sVehicleD@Interior[vehicleid]
	);
}

stock
	SetVehicleInterior(vehicleid, interiorid)
{
	if (TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		return INVALID_VEHICLE_ID;
	if (_:(0 <= interiorid <= MAX_INTERIORS) == 0)
		return 0;
	return LinkVehicleToInterior(vehicleid,
		(TDW_g_sVehicleD@Interior[vehicleid] = interiorid)
	);
}

stock
	GetVehicleLastDriver(vehicleid)
{
	return (
		(IsValidVehicle(vehicleid))
		? TDW_g_sVehicleD@LastDriver[vehicleid]
		: INVALID_PLAYER_ID
	);
}

stock
	IsVehicleBlown(vehicleid)
{
	if (TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		return false;
	return (TDW_g_sVehicleD@BlownedState{vehicleid} == BLOWNED_STATE_DEATH);
}

// If you don't want to use the functions(publics), add this to your code(before
// a_samp):
// #define _TDW_VEHICLE_NOT_USE_PUBLICS

#if !defined _TDW_VEHICLE_NOT_USE_PUBLICS
	// OnVehicleRespray hook
	public
		OnVehicleRespray(playerid, vehicleid, color1, color2)
	{
		TDW_g_sVehicleData[vehicleid][ei_color_1] = color1;
		TDW_g_sVehicleData[vehicleid][ei_color_2] = color2;
	#if defined TDWVH@OnVehicleRespray
		return TDWVH@OnVehicleRespray(playerid, vehicleid, color1, color2);
	#else
		return 1;
	#endif
	}
	#if defined _ALS_OnVehicleRespray
		#undef OnVehicleRespray
	#else
		#define _ALS_OnVehicleRespray
	#endif

	#define OnVehicleRespray(%0) TDWVH@OnVehicleRespray(%0)

	#if defined TDWVH@OnVehicleRespray
		forward TDWVH@OnVehicleRespray(playerid, vehicleid, color1, color2);
	#endif

	// OnVehiclePaintjob hook
	public
		OnVehiclePaintjob(playerid, vehicleid, paintjobid)
	{
		TDW_g_sVehicleD@Paintjob[vehicleid] = paintjobid;
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

	// OnPlayerStateChange hook
	public
		OnPlayerStateChange(playerid, newstate, oldstate)
	{
		if (newstate == PLAYER_STATE_DRIVER)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			TDW_g_sVehicleD@LastDriver[vehicleid] = playerid;
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

	// OnVehicleDeath hook
	public
		OnVehicleDeath(vehicleid, killerid)
	{
		if (TDW_g_sVehicleD@BlownedState{vehicleid} != BLOWNED_STATE_DEATH)
			TDW_g_sVehicleD@BlownedState{vehicleid} = BLOWNED_STATE_DEATH;
		#if defined TDWVH@OnVehicleDeath
			return TDWVH@OnVehicleDeath(vehicleid, killerid);
		#else
			return 1;
		#endif
	}
	#if defined _ALS_OnVehicleDeath
		#undef OnVehicleDeath
	#else
		#define _ALS_OnVehicleDeath
	#endif

	#define OnVehicleDeath(%0) TDWVH@OnVehicleDeath(%0)

	#if defined TDWVH@OnVehicleDeath
		forward TDWVH@OnVehicleDeath(vehicleid);
	#endif

	// OnVehicleSpawn hook
	public
		OnVehicleSpawn(vehicleid)
	{
		if (TDW_g_sVehicleD@BlownedState{vehicleid} == BLOWNED_STATE_DEATH)
			TDW_g_sVehicleD@BlownedState{vehicleid} = BLOWNED_STATE_RESPAWNED;
		#if defined TDWVH@OnVehicleSpawn
			return TDWVH@OnVehicleSpawn(vehicleid);
		#else
			return 1;
		#endif
	}
	#if defined _ALS_OnVehicleSpawn
		#undef OnVehicleSpawn
	#else
		#define _ALS_OnVehicleSpawn
	#endif

	#define OnVehicleSpawn(%0) TDWVH@OnVehicleSpawn(%0)

	#if defined TDWVH@OnVehicleSpawn
		forward TDWVH@OnVehicleSpawn(vehicleid);
	#endif
#endif