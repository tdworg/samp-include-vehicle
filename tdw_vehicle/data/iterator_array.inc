/* ========================================================================== *\
	Iterator Array

| Description:
	Create the iterator. Add new functions.

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
			- DestroyVehicleSafe
		Static:
			-
		Public:
			-
		Hooks:
			-
	[Callbacks]:
		-
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
			- Vehicle
		Static scope:
			-
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	- foreach, or YSI with y_iterator (optional)
\* ========================================================================== */

#if defined _inc_iterator_array
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_iterator_array
#endif

#if defined _TDW_VH_ITERATOR_ARRAY
	#endinput
#endif

#define _TDW_VH_ITERATOR_ARRAY

// -----------------------------------------------------------------------------
// Definitions:

#if !defined _TDW_VH_DETECT_FOREACH
	#endinput
#endif

#if !defined Vehicle@YSII_Ag
	// Create the iterator.
	new Iterator:Vehicle<MAX_VEHICLES>;
	// Remove the warning messages.
	//
	// foreach generate names with tags.
	#pragma unused Vehicle@YSII_Ag, Vehicle@YSII_Cg
#endif

// -----------------------------------------------------------------------------
// Static scope:

static stock
	TDW_g_sVehicleId;

// -----------------------------------------------------------------------------
// Hooks:

// AddStaticVehicle hook
#if !defined BAD_AddStaticVehicle
	native BAD_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2) = AddStaticVehicle;
#endif

stock TDWVH_ITER@AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2)
{
	if (INVALID_VEHICLE_ID != (TDW_g_sVehicleId = AddStaticVehicle(modelid,
		spawn_x, spawn_y, spawn_z, z_angle, color1, color2))) {
		Iter_Add(Vehicle, TDW_g_sVehicleId);
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif

#define AddStaticVehicle TDWVH_ITER@AddStaticVehicle


// AddStaticVehicleEx hook
#if !defined BAD_AddStaticVehicleEx
	native BAD_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2, respawn_delay,
		addsiren = 0) = AddStaticVehicleEx;
#endif

stock TDWVH_ITER@AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren = 0)
{
	if (INVALID_VEHICLE_ID != (TDW_g_sVehicleId = AddStaticVehicleEx(modelid,
		spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay,
		addsiren))) {
		Iter_Add(Vehicle, TDW_g_sVehicleId);
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif

#define AddStaticVehicleEx TDWVH_ITER@AddStaticVehicleEx


// CreateVehicle hook
#if !defined BAD_CreateVehicle
	native BAD_CreateVehicle(vehicletype, Float:x, Float:y, Float:z,
		Float:rotation, color1, color2, respawn_delay,
		addsiren = 0) = CreateVehicle;
#endif

stock TDWVH_ITER@CreateVehicle(vehicletype, Float:x, Float:y, Float:z,
	Float:rotation, color1, color2, respawn_delay, addsiren = 0)
{
	if (INVALID_VEHICLE_ID != (TDW_g_sVehicleId = CreateVehicle(vehicletype,
		x, y, z, rotation, color1, color2, respawn_delay,
		addsiren))) {
		Iter_Add(Vehicle, TDW_g_sVehicleId);
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif

#define CreateVehicle TDWVH_ITER@CreateVehicle


// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>DestroyVehicleSafe</summary>
<param name="&vehicleid">The ID of the vehicle (ref)</param>
<returns>
	-
</returns>
<remarks>
	Delete the ID of the vehicle from the iterator.
</remarks>
\** ------------------------------------------------------------------------ **/

stock DestroyVehicleSafe(&vehicleid)
{
	Iter_SafeRemove(Vehicle, vehicleid, vehicleid);
	return DestroyVehicle(vehicleid);
}



// -----------------------------------------------------------------------------
// Hooks:

// DestroyVehicle hook
#if !defined BAD_DestroyVehicle
	native BAD_DestroyVehicle(vehicleid) = DestroyVehicle;
#endif

stock TDWVH_ITER@DestroyVehicle(vehicleid)
{
	return DestroyVehicleSafe(vehicleid);
}

#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#define DestroyVehicle TDWVH_ITER@DestroyVehicle
