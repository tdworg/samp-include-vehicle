/* ========================================================================== *\
	Vehicle Mileage

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
			- GetVehicleMileage
			- SetVehicleMileage
		Static:
			-
		Public:
			- @__TDW_TIMER_MILEAGE
		Hooks:
			- SetVehiclePos
			- DestroyVehicle
	[Callbacks]:
		- TDWVH_MILEG@OnFilterScriptInit
		- TDWVH_MILEG@OnGameModeInit
		- TDWVH_MILEG@OnPlayerStateChange
		- OnVehicleMileageUpdate
	[Definitions]:
		- TDW_MILEAGE_TIMER_UPDATE
		- TDW_VEHICLE_MILEAGE_MILE_FLOAT
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
			- TDW_g_sVehicleMileage
			- TDW_g_sVehicleOldPosX
			- TDW_g_sVehicleOldPosY
			- TDW_g_sVehicleOldPosZ
			- TDW_g_sVehicleTimerName
			- TDW_g_sCallbacks
			- TDW_g_sOnVehicleMileageUpdate
			- TDW_g_sSpecifier@i
	[Natives]:
		- BAD_DestroyVehicle
		- BAD_SetVehiclePos
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_vymileage
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_vymileage
#endif

#if defined _TDW_VH_SYS_VEHICLE_MILEAGE
	#endinput
#endif

#define _TDW_VH_SYS_VEHICLE_MILEAGE

#include "tdw_vehicle"

// Modules
#include "tdw_vmath"

// -----------------------------------------------------------------------------
// Definitions:

#if !defined TDW_MILEAGE_TIMER_UPDATE
	#define TDW_MILEAGE_TIMER_UPDATE			(950)
#else
	#assert (0 < TDW_MILEAGE_TIMER_UPDATE)
#endif

#define TDW_VEHICLE_MILEAGE_MILE_FLOAT			(1.609343)

// -----------------------------------------------------------------------------
// Static scope:

static stock
	Float:TDW_g_sVehicleMileage[MAX_VEHICLES],
	Float:TDW_g_sVehicleTotalMileage[MAX_VEHICLES],
	Float:TDW_g_sVehicleOldPosX[MAX_VEHICLES],
	Float:TDW_g_sVehicleOldPosY[MAX_VEHICLES],
	Float:TDW_g_sVehicleOldPosZ[MAX_VEHICLES],
	TDW_g_sVehicleTimerName[] = !"@__TDW_TIMER_MILEAGE",
	TDW_g_sCallbacks;

static stock const
	TDW_g_sOnVehicleMileageUpdate[] = !"OnVehicleMileageUpdate",
	TDW_g_sSpecifier@i[] = !"i";

// -----------------------------------------------------------------------------
// Hooks:

// OnFilterScriptInit / OnGameModeInit hook
#if defined FILTERSCRIPT
	#if defined TDWVH_MILEG@OnFilterScriptInit
		forward TDWVH_MILEG@OnFilterScriptInit();
	#endif

	public OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnVehicleMileageUpdate) != -1)
				TDW_g_sCallbacks |= 1;

		#if defined TDWVH_MILEG@OnFilterScriptInit
			TDWVH_MILEG@OnFilterScriptInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVH_MILEG@OnFilterScriptInit
#else
	#if defined TDWVH_MILEG@OnGameModeInit
		forward TDWVH_MILEG@OnGameModeInit();
	#endif

	public OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnVehicleMileageUpdate) != -1)
				TDW_g_sCallbacks |= 1;

		#if defined TDWVH_MILEG@OnGameModeInit
			TDWVH_MILEG@OnGameModeInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVH_MILEG@OnGameModeInit
#endif


// OnPlayerStateChange hook
#if defined TDWVH_MILEG@OnPlayerStateChange
	forward TDWVH_MILEG@OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER) {
		new vehicleid = GetPlayerVehicleID(playerid);

		if (0 == vehicleid)
			return 0;

		SetTimerEx(TDW_g_sVehicleTimerName, TDW_MILEAGE_TIMER_UPDATE, false,
			TDW_g_sSpecifier@i, vehicleid);
	}

	#if defined TDWVH_MILEG@OnPlayerStateChange
		TDWVH_MILEG@OnPlayerStateChange(playerid, newstate, oldstate);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVH_MILEG@OnPlayerStateChange


// DestroyVehicle hook
#if !defined BAD_DestroyVehicle
	native BAD_DestroyVehicle(vehicleid) = DestroyVehicle;
#endif

stock TDWVH_MILEG@DestroyVehicle(vehicleid)
{
	if (0 == DestroyVehicle(vehicleid))
		return 0;

	TDW_g_sVehicleOldPosX[vehicleid] =
	TDW_g_sVehicleOldPosY[vehicleid] =
	TDW_g_sVehicleOldPosZ[vehicleid] =
	TDW_g_sVehicleMileage[vehicleid] = 0.0;

	return 1;
}

#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#define DestroyVehicle TDWVH_MILEG@DestroyVehicle


// SetVehiclePos hook
#if !defined BAD_SetVehiclePos
	native BAD_SetVehiclePos(vehicleid, Float:x, Float:y,
		Float:z) = SetVehiclePos;
#endif

stock TDWVH_MILEG@SetVehiclePos(vehicleid, Float:x, Float:y, Float:z)
{
	if (0 == SetVehiclePos(vehicleid, x, y, z))
		return 0;

	TDW_g_sVehicleOldPosX[vehicleid] = x;
	TDW_g_sVehicleOldPosY[vehicleid] = y;
	TDW_g_sVehicleOldPosZ[vehicleid] = z;

	return 1;
}

#if defined _ALS_SetVehiclePos
	#undef SetVehiclePos
#else
	#define _ALS_SetVehiclePos
#endif

#define SetVehiclePos TDWVH_MILEG@SetVehiclePos

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleMileage</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleMileage(vehicleid)
{
	return
		IsValidVehicle(vehicleid)
		? floatround(TDW_g_sVehicleTotalMileage[vehicleid])
		: INVALID_VEHICLE_ID;
}

/** ------------------------------------------------------------------------ **\
<summary>SetVehicleMileage</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetVehicleMileage(vehicleid, Float:mileage)
{
	if (IsValidVehicle(vehicleid))
		TDW_g_sVehicleTotalMileage[vehicleid] = mileage;

	return 0;
}

// -----------------------------------------------------------------------------
// Internal:

@__TDW_TIMER_MILEAGE(vehicleid);
@__TDW_TIMER_MILEAGE(vehicleid)
{
	static
		Float:speed,
		Float:tmp___;

	speed = GetVehicleSpeed(vehicleid);
	tmp___ = TDW_g_sVehicleMileage[vehicleid] += (speed / 1.4) / 1000.0;

	if (tmp___ >= TDW_VEHICLE_MILEAGE_MILE_FLOAT) {
		TDW_g_sVehicleTotalMileage[vehicleid] += tmp___;
		TDW_g_sVehicleMileage[vehicleid] -= TDW_VEHICLE_MILEAGE_MILE_FLOAT;
	}

	if (TDW_g_sCallbacks & 1)
		CallLocalFunction(TDW_g_sOnVehicleMileageUpdate, TDW_g_sSpecifier@i,
			vehicleid);

	return SetTimerEx(TDW_g_sVehicleTimerName, TDW_MILEAGE_TIMER_UPDATE, false,
		TDW_g_sSpecifier@i, vehicleid);
}

// -----------------------------------------------------------------------------
// Forwards:

forward OnVehicleMileageUpdate(vehicleid);
