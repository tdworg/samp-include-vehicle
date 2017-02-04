/* ========================================================================== *\
	Drift System

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
			- @_TDW_VEHICLE_DRIFT
			- OnPlayerStateChange
			- OnFilterScriptInit
			- OnGameModeInit
		Hooks:
			-
	[Callbacks]:
		- TDWVH_DRIFT@OnPlayerStateChange
		- TDWVH_DRIFT@OnFilterScriptInit
		- TDWVH_DRIFT@OnGameModeInit
		- OnPlayerVehicleDrift
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
			- TDW_g_sOnPlayerVehicleDrift
			- TDW_g_sCallbacks
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_vydrift
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_vydrift
#endif

#if defined _TDW_VH_SYS_DRIFT
	#endinput
#endif

#define _TDW_VH_SYS_DRIFT

#include "tdw_vehicle"

// Modules
#include "tdw_vsa_data"
#include "tdw_vmath"

// -----------------------------------------------------------------------------
// Static scope:

static stock
	TDW_g_sOnPlayerVehicleDrift[] = !"OnPlayerVehicleDrift",
	TDW_g_sCallbacks;

// -----------------------------------------------------------------------------
// Hooks:

// OnPlayerStateChange hook
#if defined TDWVH_DRIFT@OnPlayerStateChange
	forward TDWVH_DRIFT@OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER) {
		new
			vehicleid = GetPlayerVehicleID(playerid);

		if (GetModelStaticType(GetVehicleModel(vehicleid)) == CAR) {
			if (TDW_g_sCallbacks & 1) {
				@_TDW_VEHICLE_DRIFT(playerid, vehicleid);
			}
		}
	}

	#if defined TDWVH_DRIFT@OnPlayerStateChange
		TDWVH_DRIFT@OnPlayerStateChange(playerid, newstate, oldstate);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVH_DRIFT@OnPlayerStateChange


// OnFilterScriptInit / OnGameModeInit hook
#if defined FILTERSCRIPT
	#if defined TDWVH_DRIFT@OnFilterScriptInit
		forward TDWVH_DRIFT@OnFilterScriptInit();
	#endif

	public OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnPlayerVehicleDrift) != -1)
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_DRIFT@OnFilterScriptInit
			TDWVH_DRIFT@OnFilterScriptInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVH_DRIFT@OnFilterScriptInit
#else
	#if defined TDWVH_DRIFT@OnGameModeInit
		forward TDWVH_DRIFT@OnGameModeInit();
	#endif

	public OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnPlayerVehicleDrift) != -1)
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_DRIFT@OnGameModeInit
			TDWVH_DRIFT@OnGameModeInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVH_DRIFT@OnGameModeInit
#endif

// -----------------------------------------------------------------------------
// Functions:

@_TDW_VEHICLE_DRIFT(playerid, vehicleid);
@_TDW_VEHICLE_DRIFT(playerid, vehicleid)
{
	static
		Float:speed,
		Float:direction,
		Float:drift_angle,
		Float:z_angle,
		bool:is_player_drifting[MAX_PLAYERS char];

	if (0 == GetVehicleVelocityDirection(vehicleid, direction))
		return 0;

	speed = GetVehicleSpeed(vehicleid);

	if (speed > 5.0) {
		GetVehicleZAngle(vehicleid, z_angle);

		drift_angle = floatabs(floatsub(direction, z_angle));

		if (drift_angle >= 180.0)
			drift_angle = floatsub(360.0, drift_angle);

		static bool:is_drifting;
		is_drifting = is_player_drifting{playerid};

		if (15.0 < drift_angle < 80.0)
			if (0 == _:is_drifting)
				CallLocalFunction(TDW_g_sOnPlayerVehicleDrift, !"iif", playerid,
					vehicleid, drift_angle);
		if (0 != _:is_drifting)
			is_player_drifting{playerid} = false;
	}
	return SetTimerEx(!"@_TDW_VEHICLE_DRIFT", 250, false, !"ii", playerid,
		vehicleid);
}

// -----------------------------------------------------------------------------
// Forwards:

forward OnPlayerVehicleDrift(playerid, vehicleid, Float:drift_angle);
