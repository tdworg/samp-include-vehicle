/* ========================================================================== *\
	Vehicle Engine

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
			- StartVehicleEngine
			- StopVehicleEngine
			- IsVehicleEngineStarted
		Static:
			- ToggleVehicleEngineState
			- IsVehicleHasEngine
		Public:
			- OnFilterScriptInit
			- OnGameModeInit
			- OnPlayerStateChange
			- @_TDW_VEHICLE_ENGINE
		Hooks:
			-
	[Callbacks]:
		- TDWVH_ENGIN@OnFilterScriptInit
		- TDWVH_ENGIN@OnGameModeInit
		- TDWVH_ENGIN@OnPlayerStateChange
		- OnVehicleEngineStateChange
	[Definitions]:
		- TDW_ENGINE_TIMER_TICK
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
			- TDW_g_sIsVehicleEngineStarted
			- TDW_g_sCallbacks
			- TDW_g_sOnVehEngineStateChange
			- TDW_g_sVehicleTimerId
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_vyengine
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_vyengine
#endif

#if defined _TDW_VH_SYS_VEHICLE_ENGINE
	#endinput
#endif

#define _TDW_VH_SYS_VEHICLE_ENGINE

#include "tdw_vehicle"

// Modules
#include "tdw_vsa_data"

// -----------------------------------------------------------------------------
// Definitions:

#if !defined TDW_ENGINE_TIMER_TICK
	#define TDW_ENGINE_TIMER_TICK				(1000)
#endif

// -----------------------------------------------------------------------------
// Static scope:

static stock
	bool:TDW_g_sIsVehicleEngineStarted[MAX_VEHICLES char] = {false, ...},
	TDW_g_sCallbacks;

static stock const
	TDW_g_sOnVehEngineStateChange[] = !"OnVehicleEngineStateChange";

#if TDW_ENGINE_TIMER_TICK > 0
	static stock
		TDW_g_sVehicleTimerId[MAX_VEHICLES] = {-1, ...};
#endif

// -----------------------------------------------------------------------------
// Hooks:

// OnFilterScriptInit / OnGameModeInit hook
#if defined FILTERSCRIPT
	#if defined TDWVH_ENGIN@OnFilterScriptInit
		forward TDWVH_ENGIN@OnFilterScriptInit();
	#endif

	public OnFilterScriptInit()
	{
		ManualVehicleEngineAndLights();

		if (-1 != funcidx(TDW_g_sOnVehEngineStateChange))
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_ENGIN@OnFilterScriptInit
			TDWVH_ENGIN@OnFilterScriptInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVH_ENGIN@OnFilterScriptInit
#else
	#if defined TDWVH_ENGIN@OnGameModeInit
		forward TDWVH_ENGIN@OnGameModeInit();
	#endif

	public OnGameModeInit()
	{
		ManualVehicleEngineAndLights();

		if (-1 != funcidx(TDW_g_sOnVehEngineStateChange))
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_ENGIN@OnGameModeInit
			TDWVH_ENGIN@OnGameModeInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVH_ENGIN@OnGameModeInit
#endif


// OnPlayerStateChange hook
#if defined TDWVH_ENGIN@OnPlayerStateChange
	forward TDWVH_ENGIN@OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER) {
		new vehicleid = GetPlayerVehicleID(playerid);

		if (0 == IsVehicleHasEngine(vehicleid))
			ToggleVehicleEngineState(vehicleid, VEHICLE_PARAMS_ON);
	}

	#if defined TDWVH_ENGIN@OnPlayerStateChange
		TDWVH_ENGIN@OnPlayerStateChange(playerid, newstate, oldstate);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVH_ENGIN@OnPlayerStateChange

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>StartVehicleEngine</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock StartVehicleEngine(vehicleid)
{
	if (0 == IsVehicleHasEngine(vehicleid))
		return 0;
	if (TDW_g_sIsVehicleEngineStarted{vehicleid})
		return 0;

	#if TDW_ENGINE_TIMER_TICK > 0
		if (TDW_g_sVehicleTimerId[vehicleid] != -1)
			return 0;
		TDW_g_sVehicleTimerId[vehicleid] = SetTimerEx(!"@_TDW_VEHICLE_ENGINE",
			TDW_ENGINE_TIMER_TICK, false, !"i", vehicleid);
	#else
		ToggleVehicleEngineState(vehicleid, VEHICLE_PARAMS_ON);
	#endif

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>StopVehicleEngine</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock StopVehicleEngine(vehicleid)
{
	if (0 == IsVehicleHasEngine(vehicleid))
		return 0;
	if (0 == _:TDW_g_sIsVehicleEngineStarted{vehicleid})
		return 0;

	#if TDW_ENGINE_TIMER_TICK > 0
		new timer_id = TDW_g_sVehicleTimerId[vehicleid];

		if (timer_id != -1)
			KillTimer(timer_id);
	#endif

	ToggleVehicleEngineState(vehicleid, VEHICLE_PARAMS_OFF);

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>IsVehicleEngineStarted</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock IsVehicleEngineStarted(vehicleid)
{
	return IsValidVehicle(vehicleid) &&
		TDW_g_sIsVehicleEngineStarted{vehicleid};
}

// -----------------------------------------------------------------------------
// Internal:

static stock IsVehicleHasEngine(vehicleid)
{
	new model = GetVehicleModel(vehicleid);

	if (0 == model)
		return 0;

	return GetModelStaticType(model) != BIKE;
}

static stock ToggleVehicleEngineState(vehicleid,
	newstate = VEHICLE_PARAMS_UNSET)
{
	new
		engine,
		lights,
		alarm,
		doors,
		bonnet,
		boot,
		objective;

	if (0 == GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet,
		boot, objective))
		return 0;

	if (newstate == engine)
		return 0;

	if (newstate == VEHICLE_PARAMS_UNSET)
		newstate = engine ? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON;

	TDW_g_sIsVehicleEngineStarted{vehicleid} =
		bool:(newstate == VEHICLE_PARAMS_ON);

	SetVehicleParamsEx(vehicleid, newstate, lights, alarm, doors, bonnet, boot,
		objective);

	if (TDW_g_sCallbacks & 1)
		CallLocalFunction(TDW_g_sOnVehEngineStateChange, !"ii", vehicleid,
			newstate);

	return 1;
}

@_TDW_VEHICLE_ENGINE(vehicleid);
@_TDW_VEHICLE_ENGINE(vehicleid)
{
	ToggleVehicleEngineState(vehicleid, VEHICLE_PARAMS_ON);

	#if TDW_ENGINE_TIMER_TICK > 0
		TDW_g_sVehicleTimerId[vehicleid] = -1;
	#endif

	return 1;
}

// -----------------------------------------------------------------------------
// Forwards:

forward OnVehicleEngineStateChange(vehicleid, engine);
