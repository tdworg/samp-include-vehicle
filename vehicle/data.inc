#if defined _TDW_VEHICLE_DATA_INC_
	#endinput
#endif
#define _TDW_VEHICLE_DATA_INC_

enum e_TDW_VEHICLE
{
	// I created only necessary elements in the enumeration.
	Float:ei_pos_x,
	Float:ei_pos_y,
	Float:ei_pos_z,
	Float:ei_pos_rotation,
	ei_color_1,
	ei_color_2,
	ei_model_id
};

static stock // The general variables.
	TDW_g_sVehicleData[MAX_VEHICLES][e_TDW_VEHICLE],
	TDW_g_sVehicleId;
static stock // The dynamic variables.
	TDW_g_sVehicleD@Interior[MAX_VEHICLES],
	TDW_g_sVehicleD@VirtualWorld[MAX_VEHICLES],
	TDW_g_sVehicleD@Paintjob[MAX_VEHICLES];

// AddStaticVehicle hook
stock
	TDWVH@AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2)
{
	if ((TDW_g_sVehicleId = AddStaticVehicle(modelid, spawn_x, spawn_y,
		spawn_z, z_angle, color1, color2)) != INVALID_VEHICLE_ID)
	{
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_model_id]     = modelid;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_1]      = color1;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_2]      = color2;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_x]        = spawn_x;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_y]        = spawn_y;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_z]        = spawn_z;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_rotation] = z_angle;
	}
	return TDW_g_sVehicleId;
}
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle(%0) TDWVH@AddStaticVehicle(%0)

// AddStaticVehicleEx hook
stock
	TDWVH@AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2, respawn_delay,
		addsiren = 0)
{
	if ((TDW_g_sVehicleId = AddStaticVehicleEx(modelid, spawn_x, spawn_y,
		spawn_z, z_angle, color1, color2, respawn_delay, addsiren)) !=
		INVALID_VEHICLE_ID)
	{
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_model_id]     = modelid;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_1]      = color1;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_2]      = color2;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_x]        = spawn_x;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_y]        = spawn_y;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_z]        = spawn_z;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_rotation] = z_angle;
	}
	return TDW_g_sVehicleId;
}
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx(%0) TDWVH@AddStaticVehicleEx(%0)

// CreateVehicle hook
stock
	TDWVH@CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation,
		color1, color2, respawn_delay, addsiren = 0)
{
	if ((TDW_g_sVehicleId = CreateVehicle(vehicletype, x, y, z, rotation,
		color1, color2, respawn_delay, addsiren)) != INVALID_VEHICLE_ID)
	{
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_model_id]     = modelid;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_1]      = color1;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_2]      = color2;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_x]        = x;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_y]        = y;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_z]        = z;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_rotation] = rotation;
	}
	return TDW_g_sVehicleId;
}
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#define CreateVehicle(%0) TDWVH@CreateVehicle(%0)

stock
	TDWVH@DestroyVehicle(vehicleid)
{
	if (DestroyVehicle(vehicleid) == 0)
		return 0;
	// I know that zero and floating zero it's equal things,
	// but the compiler gives a warning.
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_model_id]     =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_1]      =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_color_2]      = 0;
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_x]        =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_y]        =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_z]        =
	TDW_g_sVehicleData[TDW_g_sVehicleId][ei_pos_rotation] = 0.0;
	return 1;
}
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle(%0) TDWVH@DestroyVehicle(%0)

stock
	GetVehicleColor(vehicleid, &color1, &color2)
{
	if (TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		return (color1 = color2 = 0); // I optimized this.
	color1 = TDW_g_sVehicleData[vehicleid][ei_color_1];
	color2 = TDW_g_sVehicleData[vehicleid][ei_color_2];
	return 1;
}
#if !defined SetVehicleColor
	#define SetVehicleColor(%0) ChangeVehicleColor(%0)
#endif

stock
	GetVehiclePaintjob(vehicleid)
{
	return (
		(TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		? INVALID_VEHICLE_ID
		: TDW_g_sVehicleD@Paintjob[vehicleid]
	)
}

stock
	SetVehiclePaintjob(vehicleid, paintjobid)
{
	if (TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		return INVALID_VEHICLE_ID;
	return (
		(VEHICLE_PAINTJOB_MIN <= paintjobid <= VEHICLE_PAINTJOB_MAX)
		? ChangeVehiclePaintjob(vehicleid,
			(TDW_g_sVehicleD@Paintjob[vehicleid] = paintjobid)
		)
		: 0
	);
}

stock
	GetVehicleInterior(vehicleid)
{
	return (
		(TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		? INVALID_VEHICLE_ID
		: TDW_g_sVehicleD@Interior[vehicleid]
	);
}

stock
	SetVehicleInterior(vehicleid, interiorid)
{
	if (TDW_g_sVehicleData[vehicleid][ei_model_id] == 0)
		return INVALID_VEHICLE_ID;
	if (_:(0 <= interiorid <= MAX_INTERIORS) == 0)
		return 0;
	return LinkVehicleToInterior(vehicleid,
		(TDW_g_sVehicleD@Interior[vehicleid] = interiorid)
	);
}

// If you want to use the functions(publics), add this to your code(before
// a_samp):
// #define _TDW_VEHICLE_USE_PUBLICS

#if defined _TDW_VEHICLE_USE_PUBLICS
	// OnVehicleRespray hook
	public
		OnVehicleRespray(playerid, vehicleid, color1, color2)
	{
		TDW_g_sVehicleData[vehicleid][ei_color_1] = color1;
		TDW_g_sVehicleData[vehicleid][ei_color_2] = color2;
	#if defined TDWVH@OnVehicleRespray
		return TDWVH@OnVehicleRespray(playerid, vehicleid, color1, color2);
	#else
		return 1;
	#endif
	}
	#if defined _ALS_OnVehicleRespray
		#undef OnVehicleRespray
	#else
		#define _ALS_OnVehicleRespray
	#endif

	#define OnVehicleRespray(%0) TDWVH@OnVehicleRespray(%0)

	#if defined TDWVH@OnVehicleRespray
		forward TDWVH@OnVehicleRespray(playerid, vehicleid, color1, color2);
	#endif

	// OnVehiclePaintjob hook
	public
		OnVehiclePaintjob(playerid, vehicleid, paintjobid)
	{
		TDW_g_sVehicleD@Paintjob[vehicleid] = paintjobid;
	#if defined TDWVH@OnVehiclePaintjob
		return TDWVH@OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	#else
		return 1;
	#endif
	}
	#if defined _ALS_OnVehiclePaintjob
		#undef OnVehiclePaintjob
	#else
		#define _ALS_OnVehiclePaintjob
	#endif

	#define OnVehiclePaintjob(%0) TDWVH@OnVehiclePaintjob(%0)

	#if defined TDWVH@OnVehiclePaintjob
		forward TDWVH@OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	#endif
#endif