/* ========================================================================== *\
	Trailer Manager

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
			- GetLastAttachedTrailerId
		Static:
			-
		Public:
			- OnFilterScriptInit
			- OnGameModeInit
			- OnTrailerUpdate
			- @_TDW_TIMER_OnTrailerUpdate
		Hooks:
			- AttachTrailerToVehicle
			- DetachTrailerFromVehicle
	[Callbacks]:
		- TDWVH_TREIM@OnFilterScriptInit
		- TDWVH_TREIM@OnGameModeInit
		- TDWVH_TREIM@OnTrailerUpdate
		- OnTrailerAttached
		- OnTrailerDetached
	[Definitions]:
		- TDW_MAX_TRAILER_UPDATE
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
			- TDW_g_sVehicleLastTrailerId
			- TDW_g_sVehicleIsTrailerAttached
			- TDW_g_sTimerName
			- TDW_g_sSpecifier@ii
			- TDW_g_sCallbacks
			- TDW_g_sOnTrailerAttached
			- TDW_g_sOnTrailerDetached
	[Natives]:
		- BAD_AttachTrailerToVehicle
		- BAD_DetachTrailerFromVehicle
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_trailer_manager
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_trailer_manager
#endif

#if defined _TDW_VH_SYS_TRAILER_MANAGER
	#endinput
#endif

#define _TDW_VH_SYS_TRAILER_MANAGER

// -----------------------------------------------------------------------------
// Definitions:

#if !defined TDW_MAX_TRAILER_UPDATE
	#define TDW_MAX_TRAILER_UPDATE				(1000) // second
#endif

// -----------------------------------------------------------------------------
// Static scope:

static stock
	TDW_g_sVehicleLastTrailerId[MAX_VEHICLES] = {INVALID_VEHICLE_ID, ...},
	TDW_g_sVehicleIsTrailerAttached[MAX_VEHICLES char],
	TDW_g_sTimerName[] = !"@_TDW_TIMER_OnTrailerUpdate",
	TDW_g_sSpecifier@ii[] = !"ii",
	TDW_g_sCallbacks,
	TDW_g_sOnTrailerAttached[] = !"OnTrailerAttached",
	TDW_g_sOnTrailerDetached[] = !"OnTrailerDetached";

// -----------------------------------------------------------------------------
// Hooks:

// OnFilterScriptInit / OnGameModeInit hook
#if defined FILTERSCRIPT
	#if defined TDWVH_TREIM@OnFilterScriptInit
		forward TDWVH_TREIM@OnFilterScriptInit();
	#endif

	public OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnTrailerAttached) != -1)
			TDW_g_sCallbacks |= 1;
		if (funcidx(TDW_g_sOnTrailerDetached) != -1)
			TDW_g_sCallbacks |= 2;

		#if defined TDWVH_TREIM@OnFilterScriptInit
			TDWVH_TREIM@OnFilterScriptInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVH_TREIM@OnFilterScriptInit
#else
	#if defined TDWVH_TREIM@OnGameModeInit
		forward TDWVH_TREIM@OnGameModeInit();
	#endif

	public OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnTrailerAttached) != -1)
			TDW_g_sCallbacks |= 1;
		if (funcidx(TDW_g_sOnTrailerDetached) != -1)
			TDW_g_sCallbacks |= 2;

		#if defined TDWVH_TREIM@OnGameModeInit
			TDWVH_TREIM@OnGameModeInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVH_TREIM@OnGameModeInit
#endif


// AttachTrailerToVehicle hook
#if !defined BAD_AttachTrailerToVehicle
	native BAD_AttachTrailerToVehicle(trailerid,
		vehicleid) = AttachTrailerToVehicle;
#endif

stock TDWVH_TREIM@AttachTrailerToVh(trailerid, vehicleid)
{
	if (0 == IsValidVehicle(trailerid))
		return 0;
	if (0 == IsValidVehicle(vehicleid))
		return 0;

	AttachTrailerToVehicle(trailerid, vehicleid);

	TDW_g_sVehicleLastTrailerId[vehicleid] = trailerid;
	TDW_g_sVehicleIsTrailerAttached{trailerid} = true;

	if (TDW_g_sCallbacks & 1)
		CallLocalFunction(TDW_g_sOnTrailerAttached, TDW_g_sSpecifier@ii,
			trailerid, vehicleid);

	return 1;
}

#if defined _ALS_AttachTrailerToVehicle
	#undef AttachTrailerToVehicle
#else
	#define _ALS_AttachTrailerToVehicle
#endif

#define AttachTrailerToVehicle TDWVH_TREIM@AttachTrailerToVh


// DetachTrailerFromVehicle hook
#if !defined BAD_DetachTrailerFromVehicle
	native BAD_DetachTrailerFromVehicle(vehicleid) = DetachTrailerFromVehicle;
#endif

stock TDWVH_TREIM@DetachTrailerFromVh(vehicleid)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;

	new trailerid = TDW_g_sVehicleLastTrailerId[vehicleid];

	if (0 == IsValidVehicle(trailerid))
		return 0;
	if (0 == IsTrailerAttachedToVehicle(vehicleid))
		return 0;

	DetachTrailerFromVehicle(vehicleid);
	TDW_g_sVehicleIsTrailerAttached{trailerid} = false;

	if (TDW_g_sCallbacks & 2)
		CallLocalFunction(TDW_g_sOnTrailerDetached, TDW_g_sSpecifier@ii,
			trailerid, vehicleid);

	return 1;
}

#if defined _ALS_DetachTrailerFromVehicle
	#undef DetachTrailerFromVehicle
#else
	#define _ALS_DetachTrailerFromVehicle
#endif

#define DetachTrailerFromVehicle TDWVH_TREIM@DetachTrailerFromVh


// OnTrailerUpdate hook
#if defined TDWVH_TREIM@OnTrailerUpdate
	forward TDWVH_TREIM@OnTrailerUpdate(vehicleid);
#endif

public OnTrailerUpdate(playerid, vehicleid /* trailerid */)
{
	if (0 == _:TDW_g_sVehicleIsTrailerAttached{vehicleid})
	{
		new player_vehicleid = GetPlayerVehicleID(playerid);

		TDW_g_sVehicleIsTrailerAttached{vehicleid} = true;

		if (TDW_g_sCallbacks & 1)
			CallLocalFunction(TDW_g_sOnTrailerAttached, TDW_g_sSpecifier@ii,
				vehicleid, player_vehicleid);

		SetTimerEx(TDW_g_sTimerName, TDW_MAX_TRAILER_UPDATE, false,
			TDW_g_sSpecifier@ii, vehicleid, player_vehicleid);
	}

	return
	#if defined TDWVH_TREIM@OnTrailerUpdate
		TDWVH_TREIM@OnTrailerUpdate(vehicleid);
	#else
		1;
	#endif
}

#if defined _ALS_OnTrailerUpdate
	#undef OnTrailerUpdate
#else
	#define _ALS_OnTrailerUpdate
#endif

#define OnTrailerUpdate TDWVH_TREIM@OnTrailerUpdate

// -----------------------------------------------------------------------------
// Functions:

stock GetLastAttachedTrailerId(vehicleid)
{
	return 0 == IsValidVehicle(vehicleid)
		? TDW_g_sVehicleLastTrailerId[vehicleid]
		: INVALID_VEHICLE_ID;
}

// -----------------------------------------------------------------------------
// Internal:

@_TDW_TIMER_OnTrailerUpdate(trailerid, vehicleid);
@_TDW_TIMER_OnTrailerUpdate(trailerid, vehicleid)
{
	if (0 == IsTrailerAttachedToVehicle(vehicleid))
	{
		if (TDW_g_sCallbacks & 2)
			CallLocalFunction(TDW_g_sOnTrailerDetached, TDW_g_sSpecifier@ii,
				trailerid, vehicleid);

		TDW_g_sVehicleIsTrailerAttached{vehicleid} = true;
		TDW_g_sVehicleLastTrailerId[vehicleid] = trailerid;

		return 0;
	}

	return SetTimerEx(TDW_g_sTimerName, TDW_MAX_TRAILER_UPDATE, false,
		TDW_g_sSpecifier@ii, vehicleid, trailerid);
}

// -----------------------------------------------------------------------------
// Forwards:

forward OnTrailerAttached(trailerid, vehicleid);
forward OnTrailerDetached(trailerid, vehicleid);
