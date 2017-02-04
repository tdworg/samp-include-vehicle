/* ========================================================================== *\
	Lock

| Description:


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
			- LockVehicleDoors
			- UnlockVehicleDoors
			- IsVehicleLocked
		Static:
			-
		Public:
			- OnFilterScriptInit
			- OnGameModeInit
			- OnPlayerEnterVehicle
			- OnPlayerStateChange
		Hooks:
			-
	[Callbacks]:
		- OnPlayerTryingEnterVehicle
		- TDWVH_LOCK@OnFilterScriptInit
		- TDWVH_LOCK@OnGameModeInit
		- TDWVH_LOCK@OnPlayerEnterVehicle
		- TDWVH_LOCK@OnPlayerStateChange
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
			- TDW_g_sOnPlayerTryEnterVehicle
			- TDW_g_sCallbacks
			- TDW_g_sSpecifier@ii
			- TDW_g_sIsVehicleDoorsLocked
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_vylock
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_vylock
#endif

#if defined _TDW_VH_SYS_LOCK
	#endinput
#endif

#define _TDW_VH_SYS_LOCK

#include "tdw_vehicle"

// -----------------------------------------------------------------------------
// Static scope:

static stock
	TDW_g_sOnPlayerTryEnterVehicle[] = !"OnPlayerTryingEnterVehicle",
	TDW_g_sCallbacks,
	TDW_g_sSpecifier@ii[] = !"ii",
	bool:TDW_g_sIsVehicleDoorsLocked[MAX_VEHICLES char] = {false, ...};

// -----------------------------------------------------------------------------
// Hooks:

// OnFilterScriptInit / OnGameModeInit hook
#if defined FILTERSCRIPT
	#if defined TDWVH_LOCK@OnFilterScriptInit
		forward TDWVH_LOCK@OnFilterScriptInit();
	#endif

	public OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnPlayerTryEnterVehicle) != -1)
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_LOCK@OnFilterScriptInit
			TDWVH_LOCK@OnFilterScriptInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVH_LOCK@OnFilterScriptInit
#else
	#if defined TDWVH_LOCK@OnGameModeInit
		forward TDWVH_LOCK@OnGameModeInit();
	#endif

	public OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnPlayerTryEnterVehicle) != -1)
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_LOCK@OnGameModeInit
			TDWVH_LOCK@OnGameModeInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVH_LOCK@OnGameModeInit
#endif


// OnPlayerEnterVehicle hook
#if defined TDWVH_LOCK@OnPlayerEnterVehicle
	forward TDWVH_LOCK@OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (IsVehicleLocked(vehicleid))
		if (TDW_g_sCallbacks & 1)
			if (0 == CallLocalFunction(TDW_g_sOnPlayerTryEnterVehicle,
				TDW_g_sSpecifier@ii, playerid, vehicleid))
					ClearAnimations(playerid, 1);

	#if defined TDWVH_LOCK@OnPlayerEnterVehicle
		TDWVH_LOCK@OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif

#define OnPlayerEnterVehicle TDWVH_LOCK@OnPlayerEnterVehicle


// OnPlayerStateChange hook
#if defined TDWVH_LOCK@OnPlayerStateChange
	forward TDWVH_LOCK@OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	switch (newstate) {
		case PLAYER_STATE_PASSENGER, PLAYER_STATE_DRIVER: {
			if (IsVehicleLocked(GetPlayerVehicleID(playerid))) {
				RemovePlayerFromVehicle(playerid);
				ClearAnimations(playerid, 1);
			}
		}
	}

	#if defined TDWVH_LOCK@OnPlayerStateChange
		TDWVH_LOCK@OnPlayerStateChange(playerid, newstate, oldstate);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVH_LOCK@OnPlayerStateChange

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>LockVehicleDoors</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock LockVehicleDoors(vehicleid)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;
	if (TDW_g_sIsVehicleDoorsLocked{vehicleid})
		return 0;

	new
		engine,
		lights,
		alarm,
		doors,
		bonnet,
		boot,
		objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot,
		objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, VEHICLE_PARAMS_ON,
		bonnet, boot, objective);

	TDW_g_sIsVehicleDoorsLocked{vehicleid} = true;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>UnlockVehicleDoors</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock UnlockVehicleDoors(vehicleid)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;
	if (0 == _:TDW_g_sIsVehicleDoorsLocked{vehicleid})
		return 0;

	new
		engine,
		lights,
		alarm,
		doors,
		bonnet,
		boot,
		objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet,
		boot, objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, VEHICLE_PARAMS_OFF,
		bonnet, boot, objective);

	TDW_g_sIsVehicleDoorsLocked{vehicleid} = false;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>IsVehicleLocked</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock IsVehicleLocked(vehicleid)
{
	return IsValidVehicle(vehicleid) && TDW_g_sIsVehicleDoorsLocked{vehicleid};
}

// -----------------------------------------------------------------------------
// Forwards:

forward OnPlayerTryingEnterVehicle(playerid, vehicleid);
