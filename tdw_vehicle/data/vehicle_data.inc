/* ========================================================================== *\
	Data

| Description:
	All repeatedly updated information, e.g., colors, interior, spawn
	information, etc..

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
			- CreateVehicleEx
			- GetVehicleColor
			- SetVehicleColor
		Static:
			-
		Public:
			- OnVehicleRespray
		Hooks:
			- AddStaticVehicle
			- AddStaticVehicleEx
			- ChangeVehicleColor
			- CreateVehicle
			- DestroyVehicle
	[Callbacks]:
		- TDWVH_DATA@OnVehicleRespray
	[Definitions]:
		-
	[Enumerations]:
		- E_TDW_VEHICLE_DATA
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			- TDW_g_sVehicle@Color1
			- TDW_g_sVehicle@Data
			- TDW_g_sVehicle@Interior
			- TDW_g_sVehicle@Siren
			- TDW_g_sVehicleId
	[Natives]:
		- BAD_AddStaticVehicle
		- BAD_AddStaticVehicleEx
		- BAD_ChangeVehicleColor
		- BAD_CreateVehicle
		- BAD_DestroyVehicle
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_vehicle_data
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_vehicle_data
#endif

#if defined _TDW_VH_VEHICLE_DATA
	#endinput
#endif

#define _TDW_VH_VEHICLE_DATA

// -----------------------------------------------------------------------------
// Enumerations:

enum E_TDW_VEHICLE_DATA
{
	Float:EI_VEHICLE_SPAWN_POS_X,
	Float:EI_VEHICLE_SPAWN_POS_Y,
	Float:EI_VEHICLE_SPAWN_POS_Z,
	Float:EI_VEHICLE_SPAWN_ANGLE,
	EI_VEHICLE_RESPAWN_TIME,
	EI_VEHICLE_MODEL_ID
};

// -----------------------------------------------------------------------------
// Static scope:

static stock
	TDW_g_sVehicle@Data[MAX_VEHICLES][E_TDW_VEHICLE_DATA],
	// To reduce the data segment, we will create a few arrays with char
	// operator. It reduces the size of the arrays.
	TDW_g_sVehicle@Color1[MAX_VEHICLES char], // 0 - 255
	TDW_g_sVehicle@Color2[MAX_VEHICLES char], // 0 - 255
	bool:TDW_g_sVehicle@Siren[MAX_VEHICLES char], // 0-1
	TDW_g_sVehicle@Interior[MAX_VEHICLES char], // 0 - 18
	// We use a global variable to not use the stack.
	TDW_g_sVehicleId;

// -----------------------------------------------------------------------------
// Hooks:

// AddStaticVehicle hook
#if !defined BAD_AddStaticVehicle
	native BAD_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2) = AddStaticVehicle;
#endif

stock TDWVH_DATA@AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2)
{
	if (INVALID_VEHICLE_ID != (TDW_g_sVehicleId = AddStaticVehicle(modelid,
		spawn_x, spawn_y, spawn_z, z_angle, color1, color2))) {
		// Store all values
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_MODEL_ID] = modelid;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_POS_X] = spawn_x;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_POS_Y] = spawn_y;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_POS_Z] = spawn_z;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_ANGLE] = z_angle;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_RESPAWN_TIME] = -1;
		TDW_g_sVehicle@Color1{TDW_g_sVehicleId} = color1;
		TDW_g_sVehicle@Color2{TDW_g_sVehicleId} = color2;
		TDW_g_sVehicle@Siren{TDW_g_sVehicleId} = false;
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif

#define AddStaticVehicle TDWVH_DATA@AddStaticVehicle


// AddStaticVehicleEx hook
#if !defined BAD_AddStaticVehicleEx
	native BAD_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2, respawn_delay,
		addsiren = 0) = AddStaticVehicleEx;
#endif

stock TDWVH_DATA@AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren = 0)
{
	if (INVALID_VEHICLE_ID != (TDW_g_sVehicleId = AddStaticVehicleEx(modelid,
		spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay,
		addsiren))) {
		// Store all values
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_MODEL_ID] = modelid;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_POS_X] = spawn_x;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_POS_Y] = spawn_y;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_POS_Z] = spawn_z;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_ANGLE] = z_angle;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_RESPAWN_TIME] =
			respawn_delay;
		TDW_g_sVehicle@Color1{TDW_g_sVehicleId} = color1;
		TDW_g_sVehicle@Color2{TDW_g_sVehicleId} = color2;
		TDW_g_sVehicle@Siren{TDW_g_sVehicleId} = bool:addsiren;
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif

#define AddStaticVehicleEx TDWVH_DATA@AddStaticVehicleEx


// CreateVehicle hook
#if !defined BAD_CreateVehicle
	native BAD_CreateVehicle(vehicletype, Float:x, Float:y, Float:z,
		Float:rotation, color1, color2, respawn_delay,
		addsiren = 0) = CreateVehicle;
#endif

stock TDWVH_DATA@CreateVehicle(vehicletype, Float:x, Float:y, Float:z,
	Float:rotation, color1, color2, respawn_delay, addsiren = 0)
{
	if (INVALID_VEHICLE_ID != (TDW_g_sVehicleId = CreateVehicle(vehicletype,
		x, y, z, rotation, color1, color2, respawn_delay,
		addsiren))) {
		// Store all values
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_MODEL_ID] =
			vehicletype;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_POS_X] = x;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_POS_Y] = y;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_POS_Z] = z;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_SPAWN_ANGLE] =
			rotation;
		TDW_g_sVehicle@Data[TDW_g_sVehicleId][EI_VEHICLE_RESPAWN_TIME] =
			respawn_delay;
		TDW_g_sVehicle@Color1{TDW_g_sVehicleId} = color1;
		TDW_g_sVehicle@Color2{TDW_g_sVehicleId} = color2;
		TDW_g_sVehicle@Siren{TDW_g_sVehicleId} = bool:addsiren;
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif

#define CreateVehicle TDWVH_DATA@CreateVehicle


// DestroyVehicle hook
#if !defined BAD_DestroyVehicle
	native BAD_DestroyVehicle(vehicleid) = DestroyVehicle;
#endif

stock TDWVH_DATA@DestroyVehicle(vehicleid)
{
	if (0 == DestroyVehicle(vehicleid))
		return 0;

	// Reset all values
	TDW_g_sVehicle@Data[vehicleid][EI_VEHICLE_MODEL_ID] =
	TDW_g_sVehicle@Data[vehicleid][EI_VEHICLE_RESPAWN_TIME] =
	TDW_g_sVehicle@Color1{vehicleid} =
	TDW_g_sVehicle@Color2{vehicleid} =
	TDW_g_sVehicle@Interior{vehicleid} = 0;
	TDW_g_sVehicle@Siren{vehicleid} = false; // bool
	TDW_g_sVehicle@Data[vehicleid][EI_VEHICLE_SPAWN_POS_X] =
	TDW_g_sVehicle@Data[vehicleid][EI_VEHICLE_SPAWN_POS_Y] =
	TDW_g_sVehicle@Data[vehicleid][EI_VEHICLE_SPAWN_POS_Z] =
	TDW_g_sVehicle@Data[vehicleid][EI_VEHICLE_SPAWN_ANGLE] = 0.0; // float

	return 1;
}

#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#define DestroyVehicle TDWVH_DATA@DestroyVehicle


// OnVehicleRespray hook
#if defined TDWVH_DATA@OnVehicleRespray
	forward TDWVH_DATA@OnVehicleRespray(playerid, vehicleid, color1, color2);
#endif

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	TDW_g_sVehicle@Color1{vehicleid} = color1;
	TDW_g_sVehicle@Color2{vehicleid} = color2;

	#if defined TDWVH_DATA@OnVehicleRespray
		// The server checks the return value:
		//  Returning 0 in this callback will deny the colour change.
		//  Returning 1 will allow it. This can be used to prevent hackers from
		//  changing vehicle colours using cheats.
		return TDWVH_DATA@OnVehicleRespray(playerid, vehicleid, color1, color2);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnVehicleRespray
	#undef OnVehicleRespray
#else
	#define _ALS_OnVehicleRespray
#endif

#define OnVehicleRespray TDWVH_DATA@OnVehicleRespray


// ChangeVehicleColor hook
#if !defined ChangeVehicleColor
	native BAD_ChangeVehicleColor(vehicleid, color1,
		color2) = ChangeVehicleColor;
#endif

//
// -- See SetVehicleColor
//

#if defined _ALS_ChangeVehicleColor
	#undef ChangeVehicleColor
#else
	#define _ALS_ChangeVehicleColor
#endif

#define ChangeVehicleColor SetVehicleColor

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleColor</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="&color1">The vehicle's primary color</param>
<param name="&color2">The vehicle's secondary color</param>
<returns>
	-
</returns>
<remarks>
	Get the colors of a vehicle.
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleColor(vehicleid, &color1, &color2)
{
	if (0 == IsValidVehicle(vehicleid))
		return _:(color1 = color2 = 0); // return 0

	color1 = TDW_g_sVehicle@Color1{vehicleid};
	color2 = TDW_g_sVehicle@Color2{vehicleid};

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>SetVehicleColor</summary>
<param name="vehicleid">The ID of the vehicle</param>
<param name="color1">The vehicle's primary color</param>
<param name="color2">The vehicle's secondary color</param>
<returns>
	-
</returns>
<remarks>
	Change the colors of the vehicle, and store it in the array.
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetVehicleColor(vehicleid, color1, color2)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;

	TDW_g_sVehicle@Color1{vehicleid} = color1;
	TDW_g_sVehicle@Color2{vehicleid} = color2;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>CreateVehicleEx</summary>
<param name="vehicletype">The model for the vehicle</param>
<param name="Flaot:x">The X coordinate for the vehicle</param>
<param name="Flaot:y">The Y coordinate for the vehicle</param>
<param name="Flaot:z">The Z coordinate for the vehicle</param>
<param name="Float:rotation">The facing angle for the vehicle</param>
<param name="color1">The primary color ID</param>
<param name="color2">The secondary color ID</param>
<param name="respawn_delay">
	The delay until the car is respawned without a driver in seconds.
	Using -1 will prevent the vehicle from respawning.
</param>
<param name="addsiren">
	Has a default value 0. Enables the vehicle to have a siren, providing
	the vehicle has a horn.
</param>
<returns>
	-
</returns>
<remarks>
	Creates a vehicle in the world. It can create any vehicle, such as: train,
	etc..

	We can't create the trains using CreateVehicle. Instead, we use
	AddStaticVehicleEx because it contains all the arguments that contains in
	CreateVehicle.

	ID  - Vehicle Name
	537 - Freight (Train)
	538 - Brownstreak (Train)
	570 - Streak Trailer (Train)
	449 - Tram

	Notice: AddStaticVehicleEx, CreateVehicle functions are hooked.
</remarks>
\** ------------------------------------------------------------------------ **/

stock CreateVehicleEx(vehicletype, Float:x, Float:y, Float:z, Float:rotation,
	color1, color2, respawn_delay, addsiren = 0)
{
	switch (vehicletype) {
		case 449, 537, 538, 570:
			return AddStaticVehicleEx(vehicletype, x, y, z, rotation, color1,
				color2, respawn_delay, addsiren);
		default:
			return CreateVehicle(vehicletype, x, y, z, rotation, color1, color2,
				respawn_delay, addsiren);
	}

	return 0;
}
