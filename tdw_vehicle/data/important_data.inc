/** ======================================================================== **\
	Vehicle Static Data

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


#if defined _inc_important_data
	#undef _inc_important_data
#endif

#if defined _TDW_VHLIB__IMPORTANT_DATA
	#endinput
#endif

#define _TDW_VHLIB__IMPORTANT_DATA


enum
	E_TDW_VEHICLE
{
	// I created only necessary elements in the enumeration.
	Float:ei_spos_x,
	Float:ei_spos_y,
	Float:ei_spos_z,
	Float:ei_spos_a,
	ei_stime,
	ei_modelid
};


static stock
	TDW_g_sVehicleData[MAX_VEHICLES][E_TDW_VEHICLE],
	// I used the char operator to optimize the data segment.
	TDW_g_sVehicleColor1[MAX_VEHICLES char],
	TDW_g_sVehicleColor2[MAX_VEHICLES char],
	TDW_g_sVehicleSiren[MAX_VEHICLES char],
	TDW_g_sVehicleInterior[MAX_VEHICLES char],
	TDW_g_sVehicleInfoChanged[MAX_VEHICLES char],
	TDW_g_sVehicleId;



#if !defined _YSF_included
	stock
		GetVehicleSpawnInfo(vehicleid, &Float:x, &Float:y, &Float:z,
			&Float:rot, &color1, &color2)
	{
		return TDW_g_sVehicleData[vehicleid][ei_modelid] != 0
			? (
				x = TDW_g_sVehicleData[vehicleid][ei_spos_x],
				y = TDW_g_sVehicleData[vehicleid][ei_spos_y],
				z = TDW_g_sVehicleData[vehicleid][ei_spos_z],
				rot = TDW_g_sVehicleData[vehicleid][ei_spos_a],
				color1 = TDW_g_sVehicleColor1{vehicleid},
				color2 = TDW_g_sVehicleColor2{vehicleid},
				0
			) : (_:x = _:y = _:z = _:z_angle = color1 = color2 = 0.0);
	}


	stock
		SetVehicleSpawnInfo(vehicleid, modelid, Float:x, Float:y, Float:z, Float:rot,
			color1, color2, respawn_delay = 300, interiorid = 0)
	{
		if (TDW_g_sVehicleData[vehicleid][ei_modelid] != 0)
		{
			TDW_g_sVehicleData[vehicleid][ei_modelid] = modelid;
			TDW_g_sVehicleData[vehicleid][ei_spos_x] = x;
			TDW_g_sVehicleData[vehicleid][ei_stime] = respawn_delay;
			TDW_g_sVehicleData[vehicleid][ei_spos_y] = y;
			TDW_g_sVehicleData[vehicleid][ei_spos_z] = z;
			TDW_g_sVehicleData[vehicleid][ei_spos_a] = rot;
			TDW_g_sVehicleColor1{vehicleid} = color1;
			TDW_g_sVehicleColor2{vehicleid} = color2;
			TDW_g_sVehicleInterior{vehicleid} = interiorid;
			TDW_g_sVehicleInfoChanged{vehicleid} = 1;
		}
		return;
	}


	public
		OnVehicleSpawn(vehicleid)
	{
		if (TDW_g_sVehicleInfoChanged{vehicleid} != 0)
		{
			DestroyVehicle(vehicleid);
			CreateVehicle(
				TDW_g_sVehicleData[vehicleid][ei_modelid],
				TDW_g_sVehicleData[vehicleid][ei_spos_x],
				TDW_g_sVehicleData[vehicleid][ei_spos_y],
				TDW_g_sVehicleData[vehicleid][ei_spos_z],
				TDW_g_sVehicleData[vehicleid][ei_spos_a],
				TDW_g_sVehicleColor1{vehicleid},
				TDW_g_sVehicleColor2{vehicleid},
				TDW_g_sVehicleData[vehicleid][ei_stime],
				TDW_g_sVehicleSiren{vehicleid}
			);
			LinkVehicleToInterior(vehicleid, TDW_g_sVehicleInterior{vehicleid});
			TDW_g_sVehicleInfoChanged{vehicleid} = 0;
		}
		#if defined TDWVH_ID@OnVehicleSpawn
		return TDWVH_ID@OnVehicleSpawn(vehicleid);
		#else
		return 1;
		#endif
	}

	#if defined _ALS_OnVehicleSpawn
		#undef OnVehicleSpawn
	#else
		#define _ALS_OnVehicleSpawn
	#endif

	#define OnVehicleSpawn TDWVH_ID@OnVehicleSpawn

	#if defined TDWVH_ID@OnVehicleSpawn
	forward TDWVH_ID@OnVehicleSpawn(vehicleid);
	#endif

#endif


#if !defined nst_AddStaticVehicle
native nst_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2) = AddStaticVehicle;
#endif

stock
	TDWVH_ID@AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2)
{
	if ((TDW_g_sVehicleId = AddStaticVehicle(modelid, spawn_x, spawn_y, spawn_z,
		z_angle, color1, color2)) != INVALID_VEHICLE_ID)
	{
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_modelid] = modelid;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_x] = spawn_x;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_y] = spawn_y;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_z] = spawn_z;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_a] = z_angle;
		TDW_g_sVehicleSiren{TDW_g_sVehicleId} = 0;
		TDW_g_sVehicleColor1{TDW_g_sVehicleId} = color1;
		TDW_g_sVehicleColor2{TDW_g_sVehicleId} = color2;
		#if _TDW_VEHICLE_FOREACH_ARRAY
		Iter_Add(Vehicle, TDW_g_sVehicleId);
		#endif
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif

#define AddStaticVehicle TDWVH_ID@AddStaticVehicle


#if !defined nst_AddStaticVehicleEx
native nst_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren
	) = AddStaticVehicleEx;
#endif

stock
	TDWVH_ID@AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2, respawn_delay,
		addsiren = 0)
{
	if ((TDW_g_sVehicleId = AddStaticVehicleEx(modelid, spawn_x, spawn_y,
		spawn_z, z_angle, color1, color2, respawn_delay, addsiren)
		) != INVALID_VEHICLE_ID)
	{
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_modelid] = modelid;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_x] = spawn_x;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_y] = spawn_y;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_z] = spawn_z;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_a] = z_angle;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_stime] = respawn_delay;
		TDW_g_sVehicleSiren{TDW_g_sVehicleId} = addsiren;
		TDW_g_sVehicleColor1{TDW_g_sVehicleId} = color1;
		TDW_g_sVehicleColor2{TDW_g_sVehicleId} = color2;
		#if _TDW_VEHICLE_FOREACH_ARRAY
		Iter_Add(Vehicle, TDW_g_sVehicleId);
		#endif
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif

#define AddStaticVehicleEx TDWVH_ID@AddStaticVehicleEx


#if !defined nst_CreateVehicle
native nst_CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation,
	color1, color2, respawn_delay, addsiren) = CreateVehicle;
#endif

stock
	TDWVH_ID@CreateVehicle(vehicletype, Float:x, Float:y, Float:z,
		Float:rotation, color1, color2, respawn_delay, addsiren = 0)
{
	if ((TDW_g_sVehicleId = CreateVehicle(vehicletype, x, y, z, rotation,
		color1, color2, respawn_delay, addsiren)) != INVALID_VEHICLE_ID)
	{
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_modelid] = vehicletype;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_x] = x;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_y] = y;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_z] = z;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_spos_a] = rotation;
		TDW_g_sVehicleData[TDW_g_sVehicleId][ei_stime] = respawn_delay;
		TDW_g_sVehicleSiren{TDW_g_sVehicleId} = addsiren;
		TDW_g_sVehicleColor1{TDW_g_sVehicleId} = color1;
		TDW_g_sVehicleColor2{TDW_g_sVehicleId} = color2;
		#if _TDW_VEHICLE_FOREACH_ARRAY
		Iter_Add(Vehicle, TDW_g_sVehicleId);
		#endif
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif

#define CreateVehicle TDWVH_ID@CreateVehicle


#if !defined nst_DestroyVehicle
native nst_DestroyVehicle(vehicleid) = DestroyVehicle;
#endif

stock
	TDWVH_ID@DestroyVehicle(vehicleid)
{
	if (DestroyVehicle(vehicleid) == 0)
		return 0;
	TDW_g_sVehicleData[vehicleid][ei_modelid] =
	TDW_g_sVehicleData[vehicleid][ei_stime] =
	TDW_g_sVehicleColor1{vehicleid} =
	TDW_g_sVehicleColor2{vehicleid} =
	TDW_g_sVehicleInterior{vehicleid} =
	#if !defined _YSF_included
	TDW_g_sVehicleInfoChanged{vehicleid} =
	#endif
	TDW_g_sVehicleSiren{vehicleid} = 0;
	TDW_g_sVehicleData[vehicleid][ei_spos_x] =
	TDW_g_sVehicleData[vehicleid][ei_spos_y] =
	TDW_g_sVehicleData[vehicleid][ei_spos_z] =
	TDW_g_sVehicleData[vehicleid][ei_spos_a] = 0.0;
	#if _TDW_VEHICLE_FOREACH_ARRAY
	Iter_Remove(Vehicle, vehicleid);
	#endif
	return 1;
}

#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#define DestroyVehicle TDWVH_ID@DestroyVehicle


public
	OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	TDW_g_sVehicleColor1{vehicleid} = color1;
	TDW_g_sVehicleColor2{vehicleid} = color2;
	#if defined TDWVH_ID@OnVehicleRespray
	return TDWVH_ID@OnVehicleRespray(playerid, vehicleid, color1, color2);
	#else
	return 1;
	#endif
}

#if defined _ALS_OnVehicleRespray
	#undef OnVehicleRespray
#else
	#define _ALS_OnVehicleRespray
#endif

#define OnVehicleRespray TDWVH_ID@OnVehicleRespray

#if defined TDWVH_ID@OnVehicleRespray
forward TDWVH_ID@OnVehicleRespray(playerid, vehicleid, color1, color2);
#endif


stock
	GetVehicleColor(vehicleid, &color1, &color2)
{
	if (TDW_g_sVehicleData[vehicleid][ei_modelid] == 0)
		return _:(color1 = color2 = 0);
	color1 = TDW_g_sVehicleColor1{vehicleid};
	color2 = TDW_g_sVehicleColor2{vehicleid};
	return 1;
}

stock
	SetVehicleColor(vehicleid, color1, color2)
{
	return (TDW_g_sVehicleData[vehicleid][ei_modelid] != 0
		? ChangeVehicleColor(vehicleid,
			(TDW_g_sVehicleColor1{vehicleid} = color1),
			(TDW_g_sVehicleColor2{vehicleid} = color2)
		)
		: INVALID_VEHICLE_ID
	);
}


stock
	CreateVehicleEx(vehicletype, Float:x, Float:y, Float:z, Float:rotation,
		color1, color2, respawn_delay, addsiren = 0)
{
	switch (vehicletype)
	{
		// We can't create the trains using CreateVehicle. Instead,
		// we use AddStaticVehicleEx because it contains all the arguments
		// that contains CreateVehicle.
		//
		// ID  - Vehicle Name
		//
		// 537 - Freight (Train)
		// 538 - Brownstreak (Train)
		// 570 - Streak Trailer (Train)
		// 449 - Tram
		//
		// Notice: AddStaticVehicleEx, CreateVehicle functions are hooked.
		case 537, 538, 570, 449:
		{
			AddStaticVehicleEx(vehicletype, x, y, z,
				rotation, color1, color2, respawn_delay, addsiren);
		}
		default:
		{
			CreateVehicle(vehicletype, x, y, z, rotation,
				color1, color2, respawn_delay, addsiren);
		}
	}
	return TDW_g_sVehicleId;
}

#if !defined nst_ChangeVehicleColor
native nst_ChangeVehicleColor(vehicleid,
	color1, color2) = ChangeVehicleColor;
#endif

#if defined _ALS_ChangeVehicleColor
	#undef ChangeVehicleColor
#else
	#define _ALS_ChangeVehicleColor
#endif

#define ChangeVehicleColor SetVehicleColor




