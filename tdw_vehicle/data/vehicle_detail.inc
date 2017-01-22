/* ========================================================================== *\
	Detailed Data

| Description:
	Detailed information about the vehicle, such as: paintjob id, virtual world,
	last driver of the vehicle.

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
			- GetVehicleLastDriverId
			- GetVehiclePaintjobId
			- SetVehiclePaintjobId
		Static:
			-
		Public:
			- OnPlayerStateChange
			- OnVehiclePaintjob
		Hooks:
			- ChangeVehiclePaintjob
			- SetVehicleVirtualWorld
	[Callbacks]:
		- TDW_DETAIL@OnPlayerStateChange
		- TDW_DETAIL@OnVehiclePaintjob
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
			- TDW_g_sVehicle@LastDriverId
			- TDW_g_sVehicle@PaintjobId
			- TDW_g_sVehicle@VirtualWorld
	[Natives]:
		- BAD_ChangeVehiclePaintjob
		- BAD_SetVehicleVirtualWorld
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_vehicle_detail
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_vehicle_detail
#endif

#if defined _TDW_VH_VEHICLE_DETAIL
	#endinput
#endif

#define _TDW_VH_VEHICLE_DETAIL

// -----------------------------------------------------------------------------
// Static scope:

static stock
	// To reduce the data segment, we will create a few arrays with char
	// operator. It reduces the size of the arrays.
	TDW_g_sVehicle@PaintjobId[MAX_VEHICLES char], // 0-3
	TDW_g_sVehicle@VirtualWorld[MAX_VEHICLES],
	TDW_g_sVehicle@LastDriverId[MAX_VEHICLES];

// -----------------------------------------------------------------------------
// Hooks:

// ChangeVehiclePaintjob hook
#if !defined BAD_ChangeVehiclePaintjob
	native BAD_ChangeVehiclePaintjob(vehicleid,
		paintjobid) = ChangeVehiclePaintjob;
#endif

//
// -- See SetVehiclePaintjobId
//

#if defined _ALS_ChangeVehiclePaintjob
	#undef ChangeVehiclePaintjob
#else
	#define _ALS_ChangeVehiclePaintjob
#endif

#define ChangeVehiclePaintjob SetVehiclePaintjobId


// SetVehicleVirtualWorld hook
#if !defined BAD_SetVehicleVirtualWorld
	native BAD_SetVehicleVirtualWorld(vehicleid,
		worldid) = SetVehicleVirtualWorld;
#endif

// We have to reduce the name of the function, because the full name does not
// fit in size (VM - VirtualWorld).
stock TDWVH_DETAIL@SetVehicleVW(vehicleid, worldid)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;

	SetVehicleVirtualWorld(vehicleid,
		(TDW_g_sVehicle@VirtualWorld[vehicleid] = worldid));

	return 1;
}

#if defined _ALS_SetVehicleVirtualWorld
	#undef SetVehicleVirtualWorld
#else
	#define _ALS_SetVehicleVirtualWorld
#endif

#define SetVehicleVirtualWorld TDWVH_DETAIL@SetVehicleVW


// OnVehiclePaintjob hook
#if defined TDW_DETAIL@OnVehiclePaintjob
	forward TDW_DETAIL@OnVehiclePaintjob(playerid, vehicleid, paintjobid);
#endif

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	TDW_g_sVehicle@PaintjobId{vehicleid} = paintjobid;

	#if defined TDW_DETAIL@OnVehiclePaintjob
		TDW_DETAIL@OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	#endif

	return 1;
}

#if defined _ALS_OnVehiclePaintjob
	#undef OnVehiclePaintjob
#else
	#define _ALS_OnVehiclePaintjob
#endif

#define OnVehiclePaintjob TDW_DETAIL@OnVehiclePaintjob


// OnPlayerStateChange hook
#if defined TDW_DETAIL@OnPlayerStateChange
	forward TDW_DETAIL@OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER) {
		new vehicleid = GetPlayerVehicleID(playerid);

		TDW_g_sVehicle@LastDriverId[vehicleid] = playerid;
	}

	#if defined TDW_DETAIL@OnPlayerStateChange
		TDW_DETAIL@OnPlayerStateChange(playerid, newstate, oldstate);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDW_DETAIL@OnPlayerStateChange

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>SetVehiclePaintjobId</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="paintjobid">The ID of the Paintjob</param>
<returns>
	-
</returns>
<remarks>
	Change a vehicle's paintjob.
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetVehiclePaintjobId(vehicleid, paintjobid)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;
	if (0 == IS_VALID_PAINTJOB(paintjobid))
		return 0;

	ChangeVehiclePaintjob(vehicleid, paintjobid);
	TDW_g_sVehicle@PaintjobId{vehicleid} = paintjobid;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleLastDriverId</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
	Returns the ID of the player
</remarks>
\** ------------------------------------------------------------------------ **/

stock
	GetVehicleLastDriverId(vehicleid)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;
	return TDW_g_sVehicle@LastDriverId[vehicleid];
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehiclePaintjobId</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
	Returns the ID of the paint job.
</remarks>
\** ------------------------------------------------------------------------ **/

stock
	GetVehiclePaintjobId(vehicleid)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;
	return TDW_g_sVehicle@PaintjobId{vehicleid};
}
