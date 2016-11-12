/** ======================================================================== **\
	Vehicle Mileage system

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


#if defined _inc_mileage
	#undef _inc_mileage
#endif

#if defined _TDW_VHSYS__MILEAGE
	#endinput
#endif

#define _TDW_VHSYS__MILEAGE


#if !defined TDW_MILEAGE_UPDATE
	#define TDW_MILEAGE_UPDATE (950)
#else
	#assert (0 < TDW_MILEAGE_UPDATE)
#endif


static stock
	Float:TDW_g_sVehicleMileage[MAX_VEHICLES],
	TDW_g_sVehicleTimerName[] = !"@__TDW_TIMER_MILEAGE",
	TDW_g_sVehicleTimerParams[] = !"d",
	Float:TDW_g_sPosX@MileageVehicle[MAX_VEHICLES],
	Float:TDW_g_sPosY@MileageVehicle[MAX_VEHICLES],
	Float:TDW_g_sPosZ@MileageVehicle[MAX_VEHICLES];


@__TDW_TIMER_MILEAGE(vehicleid);
@__TDW_TIMER_MILEAGE(vehicleid)
{
	static Float:x, Float:y, Float:z;

	if (GetVehiclePos(vehicleid, x, y, z) == 0)
		return 0;

	TDW_g_sVehicleMileage[vehicleid] += VectorSize(
		TDW_g_sPosX@MileageVehicle[vehicleid] - x,
		TDW_g_sPosY@MileageVehicle[vehicleid] - y,
		TDW_g_sPosZ@MileageVehicle[vehicleid] - z
	);

	TDW_g_sPosX@MileageVehicle[vehicleid] = x;
	TDW_g_sPosY@MileageVehicle[vehicleid] = y;
	TDW_g_sPosZ@MileageVehicle[vehicleid] = z;

	#if defined OnVehicleMileageUpdate
		OnVehicleMileageUpdate(vehicleid);
	#endif

	return SetTimerEx(TDW_g_sVehicleTimerName, TDW_MILEAGE_UPDATE, false,
		TDW_g_sVehicleTimerParams, vehicleid
	);
}


public
	OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if (vehicleid == 0)
			return 0;
		SetTimerEx(TDW_g_sVehicleTimerName, TDW_MILEAGE_UPDATE, false,
			TDW_g_sVehicleTimerParams, vehicleid
		);
	}
	#if defined TDWVH_ML@OnPlayerStateChange
	return TDWVH_ML@OnPlayerStateChange(playerid, newstate, oldstate);
	#else
	return 1;
	#endif
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVH_ML@OnPlayerStateChange

#if defined TDWVH_ML@OnPlayerStateChange
forward TDWVH_ML@OnPlayerStateChange(playerid, newstate, oldstate);
#endif


stock
	GetVehicleMileage(vehicleid)
{
	return
		IsValidVehicle(vehicleid)
		? floatround(TDW_g_sVehicleMileage[vehicleid])
		: INVALID_VEHICLE_ID;
}


stock
	SetVehicleMileage(vehicleid, Float:mileage)
{
	if (IsValidVehicle(vehicleid))
	{
		TDW_g_sVehicleMileage[vehicleid] = mileage;
	}
	return 0;
}


#if !defined nst_DestroyVehicle
native nst_DestroyVehicle(vehicleid) = DestroyVehicle;
#endif

stock
	TDWVH_ML@DestroyVehicle(vehicleid)
{
	if (DestroyVehicle(vehicleid) == 0)
		return 0;
	TDW_g_sPosX@MileageVehicle[vehicleid] =
	TDW_g_sPosY@MileageVehicle[vehicleid] =
	TDW_g_sPosZ@MileageVehicle[vehicleid] =
	TDW_g_sVehicleMileage[vehicleid] = 0.0;
	return 1;
}

#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#define DestroyVehicle TDWVH_ML@DestroyVehicle


forward OnVehicleMileageUpdate(vehicleid);
