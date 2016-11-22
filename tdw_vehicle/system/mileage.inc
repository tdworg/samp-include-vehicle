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

enum
	E_MILEAGE_TDW_CALLBACKS
{
	EI_CB_OnVehicleMileageUpdate // OnVehicleMileageUpdate 1
};

static stock
	Float:TDW_g_sVehicleMileage[MAX_VEHICLES],
	TDW_g_sVehicleTimerName[] = !"@__TDW_TIMER_MILEAGE",
	Float:TDW_g_sPosX@MileageVehicle[MAX_VEHICLES],
	Float:TDW_g_sPosY@MileageVehicle[MAX_VEHICLES],
	Float:TDW_g_sPosZ@MileageVehicle[MAX_VEHICLES],
	TDW_g_sOnVehicleMileageUpdate[] = !"OnVehicleMileageUpdate",
	E_MILEAGE_TDW_CALLBACKS:TDW_g_sCallbacks,
	TDW_g_sSpecifier@i[] = !"i";




#if defined FILTERSCRIPT
	public
		OnFilterScriptInit()
	{

		if (funcidx(TDW_g_sOnVehicleMileageUpdate) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnVehicleMileageUpdate;
		}

		return
		#if defined TDWVHL@OnFilterScriptInit
			TDWVHL@OnFilterScriptInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVHL@OnFilterScriptInit

	#if defined TDWVHL@OnFilterScriptInit
		forward TDWVHL@OnFilterScriptInit();
	#endif
#else
	public
		OnGameModeInit()
	{

		if (funcidx(TDW_g_sOnVehicleMileageUpdate) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnVehicleMileageUpdate;
		}

		return
		#if defined TDWVHL@OnGameModeInit
			TDWVHL@OnGameModeInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVHL@OnGameModeInit

	#if defined TDWVHL@OnGameModeInit
		forward TDWVHL@OnGameModeInit();
	#endif
#endif


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

	if (TDW_g_sCallbacks & EI_CB_OnVehicleMileageUpdate)
	{
		CallLocalFunction(TDW_g_sOnVehicleMileageUpdate, TDW_g_sSpecifier@i,
			vehicleid
		);
	}

	return SetTimerEx(TDW_g_sVehicleTimerName, TDW_MILEAGE_UPDATE, false,
		TDW_g_sSpecifier@i, vehicleid
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
			TDW_g_sSpecifier@i, vehicleid
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


#if !defined nst_SetVehiclePos
native nst_SetVehiclePos(vehicleid, Float:x, Float:y, Float:z) = SetVehiclePos;
#endif

stock
	TDWVH_ML@SetVehiclePos(vehicleid, Float:x, Float:y, Float:z)
{
	if (SetVehiclePos(vehicleid, x, y, z) == 0)
		return 0;

	TDW_g_sPosX@MileageVehicle[vehicleid] = x;
	TDW_g_sPosY@MileageVehicle[vehicleid] = y;
	TDW_g_sPosZ@MileageVehicle[vehicleid] = z;
	return 1;
}

#if defined _ALS_SetVehiclePos
	#undef SetVehiclePos
#else
	#define _ALS_SetVehiclePos
#endif

#define SetVehiclePos TDWVH_ML@SetVehiclePos


forward OnVehicleMileageUpdate(vehicleid);
