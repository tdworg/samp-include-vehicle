/* ========================================================================== *\
	Vehicle Speed Limiter

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
			-
		Static:
			-
		Public:
			- OnFilterScriptInit
			- OnGameModeInit
			- @_TDW_TIMER_@_LIMITER_
		Hooks:
			-
	[Callbacks]:
		- TDWVH_L@OnFilterScriptInit
		- TDWVH_L@OnGameModeInit
	[Definitions]:
		- TDW_LIMITER_TIMER_INTERVAL
	[Enumerations]:
		- E_LIMITER_TDW_CALLBACKS
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			- TDW_g_sVehiclesWithLimit@Max
			- TDW_g_sVehiclesWithLimit@Min
			- TDW_g_sTimerName
			- TDW_g_sSpecifier@ii
			- TDW_g_sCallbacks
			- TDW_g_sOnPlayerReachSpeedLimit
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_vylimit
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_vylimit
#endif

#if defined _TDW_VH_SYS_VEHICLE_SPEED_LIMIT
	#endinput
#endif

#define _TDW_VH_SYS_VEHICLE_SPEED_LIMIT

#include "tdw_vehicle"

// Modules
#include "tdw_vmath"

// -----------------------------------------------------------------------------
// Definitions

#if !defined TDW_LIMITER_TIMER_INTERVAL
	#define TDW_LIMITER_TIMER_INTERVAL (450)
#endif

// -----------------------------------------------------------------------------
// Static scope:

static stock
	Float:TDW_g_sVehiclesWithLimit@Max[MAX_VEHICLES] = {Float:-1.0, ...},
	Float:TDW_g_sVehiclesWithLimit@Min[MAX_VEHICLES] = {Float:-1.0, ...},
	TDW_g_sTimerName[] = !"@_TDW_TIMER_@_LIMITER_",
	TDW_g_sSpecifier@ii[] = !"ii",
	TDW_g_sCallbacks,
	TDW_g_sOnPlayerReachSpeedLimit[] = !"OnPlayerReachSpeedLimit";

// -----------------------------------------------------------------------------
// Hooks:

// OnFilterScriptInit / OnGameModeInit hook
#if defined FILTERSCRIPT
	#if defined TDWVH_L@OnFilterScriptInit
		forward TDWVH_L@OnFilterScriptInit();
	#endif

	public OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnPlayerReachSpeedLimit) != -1)
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_L@OnFilterScriptInit
			TDWVH_L@OnFilterScriptInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVH_L@OnFilterScriptInit
#else
	#if defined TDWVH_L@OnGameModeInit
		forward TDWVH_L@OnGameModeInit();
	#endif

	public OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnPlayerReachSpeedLimit) != -1)
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_L@OnGameModeInit
			TDWVH_L@OnGameModeInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVH_L@OnGameModeInit
#endif

// OnPlayerStateChange hook
#if defined TDWVH_L@OnPlayerStateChange
	forward TDWVH_L@OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
		SetTimerEx(TDW_g_sTimerName, TDW_LIMITER_TIMER_INTERVAL, false,
			TDW_g_sSpecifier@ii, GetPlayerVehicleID(playerid), playerid);

	#if defined TDWVH_L@OnPlayerStateChange
		TDWVH_L@OnPlayerStateChange(playerid, newstate, oldstate);
	#endif
	
	return 1;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVH_L@OnPlayerStateChange

// -----------------------------------------------------------------------------
// Functions:

stock Float:GetVehicleMaxLimit(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0.0;

	return TDW_g_sVehiclesWithLimit@Max[vehicleid];
}

stock SetVehicleMaxLimit(vehicleid, Float:max_limit)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;

	TDW_g_sVehiclesWithLimit@Max[vehicleid] = max_limit;

	return 1;
}

stock Float:GetVehicleMinLimit(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0.0;

	return TDW_g_sVehiclesWithLimit@Min[vehicleid];
}

stock SetVehicleMinLimit(vehicleid, Float:min_limit)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;

	TDW_g_sVehiclesWithLimit@Min[vehicleid] = min_limit;

	return 1;
}

// -----------------------------------------------------------------------------
// Internal

@_TDW_TIMER_@_LIMITER_(vehicleid, playerid);
@_TDW_TIMER_@_LIMITER_(vehicleid, playerid)
{
	static
		Float:speed;

	if ((speed = GetVehicleSpeed(vehicleid)) >
		TDW_g_sVehiclesWithLimit@Max[vehicleid])
	{
		SetVehicleSpeed(vehicleid, TDW_g_sVehiclesWithLimit@Max[vehicleid]);

		if (TDW_g_sCallbacks & 1)
		{
			CallLocalFunction(TDW_g_sOnPlayerReachSpeedLimit, !"iif",
				vehicleid, playerid, speed);
		}
	}
	else if (speed < TDW_g_sVehiclesWithLimit@Min[vehicleid])
		SetVehicleSpeed(vehicleid, TDW_g_sVehiclesWithLimit@Min[vehicleid]);

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return 0;

	return
		SetTimerEx(TDW_g_sTimerName, TDW_LIMITER_TIMER_INTERVAL, false,
			TDW_g_sSpecifier@ii, vehicleid, playerid);
}

// -----------------------------------------------------------------------------
// Forwards:

forward OnPlayerReachSpeedLimit(vehicleid, playerid, Float:speed);
