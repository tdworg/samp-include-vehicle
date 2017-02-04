/* ========================================================================== *\
	Number plate

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
			- GetVehicleNumberPlate
		Static:
			-
		Public:
			-
		Hooks:
			- SetVehicleNumberPlate
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
			-
		Static scope:
			- TDW_g_sVehicle@NumberPlate
	[Natives]:
		- BAD_SetVehicleNumberPlate
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_vnplate
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_vnplate
#endif

#if defined _TDW_VH_NUMBER_PLATE
	#endinput
#endif

#define _TDW_VH_NUMBER_PLATE

#include "tdw_vehicle"

// -----------------------------------------------------------------------------
// Static scope:

static stock
	TDW_g_sVehicle@NumberPlate[MAX_VEHICLES][MAX_NUMBER_PLATE_SIZE char];

// -----------------------------------------------------------------------------
// Hooks:

// SetVehicleNumberPlate hook
#if !defined BAD_SetVehicleNumberPlate
	native BAD_SetVehicleNumberPlate(vehicleid,
		numberplate[]) = SetVehicleNumberPlate;
#endif

stock TDW_NUMPL@SetVehicleNumberPlate(vehicleid, const number_plate[])
{
	new
		Float:current_x,
		Float:current_y,
		Float:current_z;

	if (0 == GetVehiclePos(vehicleid, current_x, current_y, current_z))
		return 0;

	new
		Float:current_z_angle,
		Float:current_health,
		current_panels,
		current_doors,
		current_lights,
		current_tires,
		passenegers[MAX_VEHICLE_PASSENGERS];

	GetVehicleZAngle(vehicleid, current_z_angle);

	#if !defined TDW_NUMPLATE_NOT_SAFE_DAMAGE
		GetVehicleHealth(vehicleid, current_health);
		GetVehicleDamageStatus(vehicleid, current_panels, current_doors,
			current_lights, current_tires);
	#endif

	GetVehicleOccupantPlayers(vehicleid, passengers);

	const
		PUSH_ARGS_COUNT = 2 * 4,
		PUSHED_ARGS = PUSH_ARGS_COUNT + 4;

	#emit PUSH.s number_plate
	#emit PUSH.s vehicleid
	#emit PUSH.c PUSH_ARGS_COUNT
	#emit SYSREQ.c SetVehicleNumberPlate
	#emit STACK PUSHED_ARGS

	SetVehicleToRespawn(vehicleid);

	#if !defined TDW_NUMPLATE_NOT_SAFE_NUMBER
		strcpy(TDW_g_sVehicle@NumberPlate[vehicleid], number_plate);
	#endif

	SetVehiclePos(vehicleid, current_x, current_y, current_z);

	new i;
	do {
		PutPlayerInVehicle(passengers[i], vehicleid, i);
	} while (++i < sizeof passengers);

	#if !defined TDW_NUMPLATE_NOT_SAFE_DAMAGE
		SetVehicleHealth(vehicleid, current_health);
		UpdateVehicleDamageStatus(vehicleid, current_panels, current_doors,
			current_lights, current_tires);
	#endif

	return 1;
}

#if defined _ALS_SetVehicleNumberPlate
	#undef SetVehicleNumberPlate
#else
	#define _ALS_SetVehicleNumberPlate
#endif

#define SetVehicleNumberPlate TDW_NUMPL@SetVehicleNumberPlate

// -----------------------------------------------------------------------------
// Internal:

// Checks if a string is packed.
// Other information: //www.compuphase.com/pawn/String_Manipulation.pdf
// Author: Untonyst.
#if !defined IsPackedString
	#define IsPackedString(%0) ((%0){0} != 0)
#endif

#if !defined strcpy
	static stock strcpy(dest[], const string[], dest_size = sizeof dest)
	{
		return
			(IsPackedString(dest) ? (dest{0} = '\0') : (dest[0] = '\0')),
			strcat(dest, string, dest_size);
	}
#endif

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleNumberPlate</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleNumberPlate(vehicleid, dest[], bool:packed = false,
	dest_size = sizeof dest)
{
	#if !defined TDW_NPLATE_NOT_SAFE_NUMBER
		return packed
			? strcpy(dest, TDW_g_sNumberPlate[vehicleid], dest_size)
			: strunpack(dest, TDW_g_sNumberPlate[vehicleid], dest_size);
	#else
		return 0;
	#endif
}