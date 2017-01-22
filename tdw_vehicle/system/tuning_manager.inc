/* ========================================================================== *\
	Tuning Manager

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
			- IsVehicleComponentAdded
		Static:
			- UpdateComponentInArray
			- RemoveComponentFromArray
			- RemoveComponentsFromArray
		Public:
			- OnVehicleMod
		Hooks:
			- AddVehicleComponent
			- RemoveVehicleComponent
			- DestroyVehicle
	[Callbacks]:
		- TDWVH_TUNEM@OnVehicleMod
	[Definitions]:
		-
	[Enumerations]:
		- E_TDW_VEHICLE_TUNING
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			- TDW_g_sVehicleComponents
	[Natives]:
		- BAD_AddVehicleComponent
		- BAD_RemoveVehicleComponent
		- BAD_DestroyVehicle
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tuning_manager
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tuning_manager
#endif

#if defined _TDW_VH_SYS_TUNING_MANAGER
	#endinput
#endif

#define _TDW_VH_SYS_TUNING_MANAGER

// -----------------------------------------------------------------------------
// Enumerations:

enum E_TDW_VEHICLE_TUNING
{
	EI_COMP_TYPE_SPOILER = CARMODTYPE_SPOILER, // 0
	EI_COMP_TYPE_HOOD,
	EI_COMP_TYPE_ROOF,
	EI_COMP_TYPE_SIDESKIRT,
	EI_COMP_TYPE_LAMPS,
	EI_COMP_TYPE_NITRO,
	EI_COMP_TYPE_EXHAUST,
	EI_COMP_TYPE_WHEELS,
	EI_COMP_TYPE_STEREO,
	EI_COMP_TYPE_HYDRAULICS,
	EI_COMP_TYPE_FRONT_BUMPER,
	EI_COMP_TYPE_REAR_BUMPER,
	EI_COMP_TYPE_VENT_RIGHT,
	EI_COMP_TYPE_VENT_LEFT
};

// -----------------------------------------------------------------------------
// Static scope:

static stock
	TDW_g_sVehicleComponents[MAX_VEHICLES][E_TDW_VEHICLE_TUNING];

// -----------------------------------------------------------------------------
// Hooks:

// AddVehicleComponent hook
#if !defined BAD_AddVehicleComponent
	native BAD_AddVehicleComponent(vehicleid,
		componentid) = AddVehicleComponent;
#endif

stock TDWVH_TUNEM@AddVehicleComponent(vehicleid)
{
	if (0 == AddVehicleComponent(vehicleid, componentid))
		return 0;

	UpdateComponentInArray(vehicleid, componentid);

	return 1;
}

#if defined _ALS_AddVehicleComponent
	#undef AddVehicleComponent
#else
	#define _ALS_AddVehicleComponent
#endif

#define AddVehicleComponent TDWVH_TUNEM@AddVehicleComponent


// RemoveVehicleComponent hook
#if !defined BAD_RemoveVehicleComponent
	native BAD_RemoveVehicleComponent(vehicleid,
		componentid) = RemoveVehicleComponent;
#endif

stock TDWVH_TUNEM@RemoveVehicleComp(vehicleid, componentid)
{
	RemoveVehicleComponent(vehicleid, componentid);
	RemoveComponentFromArray(vehicleid, componentid);

	return 0;
}

#if defined _ALS_RemoveVehicleComponent
	#undef RemoveVehicleComponent
#else
	#define _ALS_RemoveVehicleComponent
#endif

#define RemoveVehicleComponent TDWVH_TUNEM@RemoveVehicleComp


// OnVehicleMod hook
#if defined TDWVH_TUNEM@OnVehicleMod
	forward TDWVH_TUNEM@OnVehicleMod(playerid, vehicleid, componentid);
#endif

public OnVehicleMod(playerid, vehicleid, componentid)
{
	UpdateComponentInArray(vehicleid, componentid);

	#if defined TDWVH_TUNEM@OnVehicleMod
		return TDWVH_TUNEM@OnVehicleMod(playerid, vehicleid, componentid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnVehicleMod
	#undef OnVehicleMod
#else
	#define _ALS_OnVehicleMod
#endif

#define OnVehicleMod TDWVH_TUNEM@OnVehicleMod


// DestroyVehicle hook
#if !defined BAD_DestroyVehicle
	native BAD_DestroyVehicle(vehicleid) = DestroyVehicle;
#endif

stock TDWVH_TUNEM@DestroyVehicle(vehicleid)
{
	if (0 == DestroyVehicle(vehicleid))
		return 0;

	RemoveComponentsFromArray(vehicleid);

	return 1;
}

#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#define DestroyVehicle TDWVH_TUNEM@DestroyVehicle

// -----------------------------------------------------------------------------
// Internal:

static stock UpdateComponentInArray(vehicleid, componentid)
{
	static E_TDW_VEHICLE_TUNING:component_type;

	component_type = E_TDW_VEHICLE_TUNING:GetVehicleComponentType(componentid);
	if (_:component_type == -1)
		return 0;

	TDW_g_sVehicleComponents[vehicleid][component_type] = componentid;

	return 1;
}

static stock RemoveComponentFromArray(vehicleid, componentid)
{
	static E_TDW_VEHICLE_TUNING:component_type;

	component_type = E_TDW_VEHICLE_TUNING:GetVehicleComponentType(componentid);
	if (_:component_type == -1)
		return 0;

	TDW_g_sVehicleComponents[vehicleid][component_type] = 0;

	return 1;
}

static stock RemoveComponentsFromArray(vehicleid)
{
	if (0 == IS_VALID_VEHICLEID(vehicleid))
		return 0;

	TDW_g_sVehicleComponents[vehicleid] = 0;

	return 1;
}

// -----------------------------------------------------------------------------
// Functions:

stock IsVehicleComponentAdded(vehicleid, E_TDW_VEHICLE_TUNING:component_type)
{
	if (0 == _:(0 < component_type < sizeof TDW_g_sVehicleComponents[]))
		return 0;

	return TDW_g_sVehicleComponents[vehicleid][component_type] != 0;
}
