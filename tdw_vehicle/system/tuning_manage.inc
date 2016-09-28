/** ======================================================================== **\
	Vehicle Tuning system

| License:
Copyright (c) 2016 Double V

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
\** ======================================================================== **/


#if defined _inc_tuning_manage
	#undef _inc_tuning_manage
#endif

#if defined _TDW_VHSYS__TUNING_MANAGE
	#endinput
#endif

#define _TDW_VHSYS__TUNING_MANAGE

enum
	e_TDW_VEHICLE_TUNING
{
	spoiler,
	hood,
	roof,
	sideskirt,
	lamps,
	nitro,
	exhaust,
	wheels,
	stereo,
	hydraulics,
	front_bumper,
	rear_bumper,
	vent_right,
	vent_left
};

static stock TDW_g_sVComponents[MAX_VEHICLES][e_TDW_VEHICLE_TUNING];


stock
	TDWVH@AddVehicleComponent(vehicleid, componentid)
{
	if (AddVehicleComponent(vehicleid, componentid) == 0)
		return 0;
	UpdateComponentInArray(vehicleid, componentid);
	return 1;
}

public
	OnVehicleMod(playerid, vehicleid, componentid)
{
	UpdateComponentInArray(vehicleid, componentid);
	#if defined TDWVH@OnVehicleMod
	return TDWVH@OnVehicleMod(playerid, vehicleid, componentid);
	#else
	return 1;
	#endif
}

#if defined _ALS_OnVehicleMod
	#undef OnVehicleMod
#else
	#define _ALS_OnVehicleMod
#endif

#define OnVehicleMod(%0) TDWVH@OnVehicleMod(%0)

#if defined TDWVH@OnVehicleMod
forward TDWVH@OnVehicleMod(playerid, vehicleid, componentid);
#endif

public
	OnVehicleSpawn(vehicleid)
{
	if (TDW_g_sVComponents[vehicleid][spoiler] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][spoiler]
		);
	if (TDW_g_sVComponents[vehicleid][hood] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][hood]
		);
	if (TDW_g_sVComponents[vehicleid][roof] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][roof]
		);
	if (TDW_g_sVComponents[vehicleid][sideskirt] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][sideskirt]
		);
	if (TDW_g_sVComponents[vehicleid][lamps] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][lamps]
		);
	if (TDW_g_sVComponents[vehicleid][nitro] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][nitro]
		);
	if (TDW_g_sVComponents[vehicleid][exhaust] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][exhaust]
		);
	if (TDW_g_sVComponents[vehicleid][wheels] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][wheels]
		);
	if (TDW_g_sVComponents[vehicleid][stereo] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][stereo]
		);
	if (TDW_g_sVComponents[vehicleid][hydraulics] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][hydraulics]
		);
	if (TDW_g_sVComponents[vehicleid][front_bumper] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][front_bumper]
		);
	if (TDW_g_sVComponents[vehicleid][rear_bumper] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][rear_bumper]
		);
	if (TDW_g_sVComponents[vehicleid][vent_right] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][vent_right]
		);
	if (TDW_g_sVComponents[vehicleid][vent_left] != 0)
		AddVehicleComponent(vehicleid,
			TDW_g_sVComponents[vehicleid][vent_left]
		);
	#if defined TDWVH@OnVehicleSpawn
	return TDWVH@OnVehicleSpawn(vehicleid);
	#else
	return 1;
	#endif
}

#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif

#define OnVehicleSpawn(%0) TDWVH@OnVehicleSpawn(%0)

#if defined TDWVH@OnVehicleSpawn
forward TDWVH@OnVehicleSpawn(vehicleid);
#endif


stock
	UpdateComponentInArray(vehicleid, componentid)
{
	static comp_type;
	#pragma unused comp_type
	switch ((comp_type = GetVehicleComponentType(componentid)))
	{
		case CARMODTYPE_SPOILER:
			TDW_g_sVComponents[vehicleid][spoiler] = componentid;
		case CARMODTYPE_HOOD:
			TDW_g_sVComponents[vehicleid][hood] = componentid;
		case CARMODTYPE_ROOF:
			TDW_g_sVComponents[vehicleid][roof] = componentid;
		case CARMODTYPE_SIDESKIRT:
			TDW_g_sVComponents[vehicleid][sideskirt] = componentid;
		case CARMODTYPE_LAMPS:
			TDW_g_sVComponents[vehicleid][lamps] = componentid;
		case CARMODTYPE_NITRO:
			TDW_g_sVComponents[vehicleid][nitro] = componentid;
		case CARMODTYPE_EXHAUST:
			TDW_g_sVComponents[vehicleid][exhaust] = componentid;
		case CARMODTYPE_WHEELS:
			TDW_g_sVComponents[vehicleid][wheels] = componentid;
		case CARMODTYPE_STEREO:
			TDW_g_sVComponents[vehicleid][stereo] = componentid;
		case CARMODTYPE_HYDRAULICS:
			TDW_g_sVComponents[vehicleid][hydraulics] = componentid;
		case CARMODTYPE_FRONT_BUMPER:
			TDW_g_sVComponents[vehicleid][front_bumper] = componentid;
		case CARMODTYPE_REAR_BUMPER:
			TDW_g_sVComponents[vehicleid][rear_bumper] = componentid;
		case CARMODTYPE_VENT_RIGHT:
			TDW_g_sVComponents[vehicleid][vent_right] = componentid;
		case CARMODTYPE_VENT_LEFT:
			TDW_g_sVComponents[vehicleid][vent_left] = componentid;
		default:
			return 0;
	}
	return 1;
}

stock
	IsVehicleComponentAdded(vehicleid, e_TDW_VEHICLE_TUNING:type)
{
	return TDW_g_sVComponents[vehicleid][type] != 0;
}


stock
	TDWVH_TM@DestroyVehicle(vehicleid)
{
	if (DestroyVehicle(vehicleid) == 0)
		return 0;
	new i;
	while (i++ != sizeof TDW_g_sVComponents[])
		TDW_g_sVComponents[vehicleid][e_TDW_VEHICLE_TUNING:i] = 0;
	return 1;
}

#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#define DestroyVehicle(%0) TDWVH_TM@DestroyVehicle(%0)
