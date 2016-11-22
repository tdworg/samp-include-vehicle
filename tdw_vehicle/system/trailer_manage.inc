/** ======================================================================== **\
	Vehicle Trailer system

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


#if defined _inc_trailer_manage
	#undef _inc_trailer_manage
#endif

#if defined _TDW_VHSYS__TRAILER_MANAGE
	#endinput
#endif

#define _TDW_VHSYS__TRAILER_MANAGE


#if defined OnTrailerAttached
	forward OnTrailerAttached(trailerid, vehicleid);
#endif
#if defined OnTrailerDetached
	forward OnTrailerDetached(trailerid, vehicleid);
#endif

#if !defined MAX_TRAILER_UPDATE
	#define MAX_TRAILER_UPDATE (1000)
#endif


enum
	E_TM_TDW_CALLBACKS
{
	EI_CB_OnTrailerAttached,
	EI_CB_OnTrailerDetached
};


static stock
	TDW_g_sVDynamic@LastTrailerIds[MAX_VEHICLES] = {INVALID_VEHICLE_ID, ...},
	bool:TDW_g_sVDynamic@TrailerAttached[MAX_VEHICLES char],
	TDW_g_sTimerName[] = !"@_TDW_TIMER_OnTrailerUpdate",
	TDW_g_sSpecifier@ii[] = !"ii",
	E_TM_TDW_CALLBACKS:TDW_g_sCallbacks,
	TDW_g_sOnTrailerAttached[] = !"OnTrailerAttached",
	TDW_g_sOnTrailerDetached[] = !"OnTrailerDetached";



#if defined FILTERSCRIPT
	public
		OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnTrailerAttached) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnTrailerAttached;
		}
		if (funcidx(TDW_g_sOnTrailerDetached) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnTrailerDetached;
		}

		return
		#if defined TDWVH_TM@OnFilterScriptInit
			TDWVH_TM@OnFilterScriptInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVH_TM@OnFilterScriptInit

	#if defined TDWVH_TM@OnFilterScriptInit
		forward TDWVH_TM@OnFilterScriptInit();
	#endif
#else
	public
		OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnTrailerAttached) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnTrailerAttached;
		}
		if (funcidx(TDW_g_sOnTrailerDetached) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnTrailerDetached;
		}

		return
		#if defined TDWVH_TM@OnGameModeInit
			TDWVH_TM@OnGameModeInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVH_TM@OnGameModeInit

	#if defined TDWVH_TM@OnGameModeInit
		forward TDWVH_TM@OnGameModeInit();
	#endif
#endif


stock
	GetLastAttachedTrailerId(vehicleid)
{
	return (IsValidVehicle(vehicleid) == 0
		? TDW_g_sVDynamic@LastTrailerIds[vehicleid]
		: INVALID_VEHICLE_ID
	);
}


#if !defined nst_AttachTrailerToVehicle
native nst_AttachTrailerToVehicle(trailerid,vehicleid) = AttachTrailerToVehicle;
#endif

stock
	TDWVH_TM@AttachTrailerToVehicle(trailerid, vehicleid)
{
	if (IsValidVehicle(trailerid) == 0)
		return 0;
	if (IsValidVehicle(vehicleid) == 0)
		return 0;

	AttachTrailerToVehicle(trailerid, vehicleid);

	TDW_g_sVDynamic@LastTrailerIds[vehicleid] = trailerid;
	TDW_g_sVDynamic@TrailerAttached{trailerid} = true;

	if (TDW_g_sCallbacks & EI_CB_OnTrailerAttached)
	{
		CallLocalFunction(TDW_g_sOnTrailerAttached, TDW_g_sSpecifier@ii,
			trailerid, vehicleid
		);
	}

	return 1;
}

#if defined _ALS_AttachTrailerToVehicle
	#undef AttachTrailerToVehicle
#else
	#define _ALS_AttachTrailerToVehicle
#endif

#define AttachTrailerToVehicle TDWVH_TM@AttachTrailerToVehicle


#if !defined nst_DetachTrailerFromVehicle
native nst_DetachTrailerFromVehicle(vehicleid) = DetachTrailerFromVehicle;
#endif

stock
	TDWVH_TM@DetachTrailerFromVeh(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;

	new trailerid = TDW_g_sVDynamic@LastTrailerIds[vehicleid];

	if (IsValidVehicle(trailerid) == 0)
		return 0;
	if (IsTrailerAttachedToVehicle(vehicleid) == 0)
		return 0;

	DetachTrailerFromVehicle(vehicleid);

	TDW_g_sVDynamic@TrailerAttached{trailerid} = false;

	if (TDW_g_sCallbacks & EI_CB_OnTrailerDetached)
	{
		CallLocalFunction(TDW_g_sOnTrailerDetached, TDW_g_sSpecifier@ii,
			trailerid, vehicleid
		);
	}

	return 1;
}

#if defined _ALS_DetachTrailerFromVehicle
	#undef DetachTrailerFromVehicle
#else
	#define _ALS_DetachTrailerFromVehicle
#endif

#define DetachTrailerFromVehicle TDWVH_TM@DetachTrailerFromVeh


public
	OnTrailerUpdate(playerid, vehicleid /* trailerid */)
{
	if (_:TDW_g_sVDynamic@TrailerAttached{vehicleid} == 0)
	{
		new player_vehicleid = GetPlayerVehicleID(playerid);

		TDW_g_sVDynamic@TrailerAttached{vehicleid} = true;

		if (TDW_g_sCallbacks & EI_CB_OnTrailerAttached)
		{
			CallLocalFunction(TDW_g_sOnTrailerAttached, TDW_g_sSpecifier@ii,
				vehicleid, player_vehicleid
			);
		}

		SetTimerEx(TDW_g_sTimerName, MAX_TRAILER_UPDATE, false,
			TDW_g_sSpecifier@ii, vehicleid, player_vehicleid
		);
	}
	#if defined TDWVH_TM@OnTrailerUpdate
		return TDWVH_TM@OnTrailerUpdate(vehicleid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnTrailerUpdate
	#undef OnTrailerUpdate
#else
	#define _ALS_OnTrailerUpdate
#endif

#define OnTrailerUpdate TDWVH_TM@OnTrailerUpdate

#if defined TDWVH_TM@OnTrailerUpdate
forward TDWVH_TM@OnTrailerUpdate(vehicleid);
#endif


@_TDW_TIMER_OnTrailerUpdate(trailerid, vehicleid);
@_TDW_TIMER_OnTrailerUpdate(trailerid, vehicleid)
{
	if (IsTrailerAttachedToVehicle(vehicleid) == 0)
	{
		if (TDW_g_sCallbacks & EI_CB_OnTrailerDetached)
		{
			CallLocalFunction(TDW_g_sOnTrailerDetached, TDW_g_sSpecifier@ii,
				trailerid, vehicleid
			);
		}

		TDW_g_sVDynamic@TrailerAttached{vehicleid} = true;
		TDW_g_sVDynamic@LastTrailerIds[vehicleid] = trailerid;

		return 0;
	}
	return SetTimerEx(TDW_g_sTimerName, MAX_TRAILER_UPDATE, false,
		TDW_g_sSpecifier@ii, vehicleid, trailerid
	);
}
