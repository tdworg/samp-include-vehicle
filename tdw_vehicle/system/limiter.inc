/** ======================================================================== **\
	Vehicle Limiter system

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


#if defined _inc_limiter
	#undef _inc_limiter
#endif

#if defined _TDW_VHSYS__LIMITER
	#endinput
#endif

#define _TDW_VHSYS__LIMITER


#if !defined TDW_LIMITER_TIMER_INTERVAL
	#define TDW_LIMITER_TIMER_INTERVAL (450)
#endif

enum
	E_LIMITER_TDW_CALLBACKS (<<= 1)
{
	EI_CB_OnPlayerReachSpeedLimit = 1
};

static stock
	Float:TDW_g_sVehiclesWithLimit[MAX_VEHICLES] = {Float:-1, ...},
	TDW_g_sTimerName[] = !"@_TDW_TIMER_@_LIMITER_",
	TDW_g_sSpecifier@ii[] = !"ii",
	E_LIMITER_TDW_CALLBACKS:TDW_g_sCallbacks,
	TDW_g_sOnPlayerReachSpeedLimit[] = !"OnPlayerReachSpeedLimit";


#if defined FILTERSCRIPT
	public
		OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnPlayerReachSpeedLimit) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnPlayerReachSpeedLimit;
		}

		return
		#if defined TDWVH_L@OnFilterScriptInit
			TDWVH_L@OnFilterScriptInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVH_L@OnFilterScriptInit

	#if defined TDWVH_L@OnFilterScriptInit
		forward TDWVH_L@OnFilterScriptInit();
	#endif
#else
	public
		OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnPlayerReachSpeedLimit) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnPlayerReachSpeedLimit;
		}

		return
		#if defined TDWVH_L@OnGameModeInit
			TDWVH_L@OnGameModeInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVH_L@OnGameModeInit

	#if defined TDWVH_L@OnGameModeInit
		forward TDWVH_L@OnGameModeInit();
	#endif
#endif


stock
	Float:GetVehicleLimit(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0.0;
	return TDW_g_sVehiclesWithLimit[vehicleid];
}


stock
	SetVehicleLimit(vehicleid, Float:limit_value)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	TDW_g_sVehiclesWithLimit[vehicleid] = limit_value;
	return 1;
}



public
	OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
	{
		SetTimerEx(TDW_g_sTimerName, TDW_LIMITER_TIMER_INTERVAL, false,
			TDW_g_sSpecifier@ii, GetPlayerVehicleID(playerid), playerid
		);
	}

	#if defined TDWVH_L@OnPlayerStateChange
		return TDWVH_L@OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVH_L@OnPlayerStateChange

#if defined TDWVH_L@OnPlayerStateChange
	forward TDWVH_L@OnPlayerStateChange(playerid, newstate, oldstate);
#endif


@_TDW_TIMER_@_LIMITER_(vehicleid, playerid);
@_TDW_TIMER_@_LIMITER_(vehicleid, playerid)
{
	static Float:speed;

	if ((speed = GetVehicleSpeed(vehicleid)) >
		TDW_g_sVehiclesWithLimit[vehicleid])
	{
		SetVehicleSpeed(vehicleid, TDW_g_sVehiclesWithLimit[vehicleid]);

		if (TDW_g_sCallbacks & EI_CB_OnPlayerReachSpeedLimit)
		{
			CallLocalFunction(TDW_g_sOnPlayerReachSpeedLimit, !"iif",
				vehicleid, playerid, speed
			);
		}
	}

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return 0;

	return
		SetTimerEx(TDW_g_sTimerName, TDW_LIMITER_TIMER_INTERVAL, false,
			TDW_g_sSpecifier@ii, vehicleid, playerid
		);
}


forward OnPlayerReachSpeedLimit(vehicleid, playerid, Float:speed);
