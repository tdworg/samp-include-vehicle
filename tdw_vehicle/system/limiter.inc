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
	#define TDW_LIMITER_TIMER_INTERVAL (250)
#endif


static stock
	Float:TDW_g_sVehiclesWithLimit[MAX_VEHICLES];


stock
	Float:GetVehicleLimit(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
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
		SetTimerEx(!"@_TDW_TIMER_@_LIMITER_", TDW_LIMITER_TIMER_INTERVAL,
			false, !"ii", GetPlayerVehicleID(playerid), playerid
		);
	}
	#if defined TDWVH@OnPlayerStateChange
	return TDWVH@OnPlayerStateChange(playerid, newstate, oldstate);
	#else
	return 1;
	#endif
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange(%0) TDWVH@OnPlayerStateChange(%0)

#if defined TDWVH@OnPlayerStateChange
forward TDWVH@OnPlayerStateChange(playerid, newstate, oldstate);
#endif


forward @_TDW_TIMER_@_LIMITER_(vehicleid, playerid);
@_TDW_TIMER_@_LIMITER_(vehicleid, playerid)
{
	if (GetVehicleSpeed(vehicleid) > TDW_g_sVehiclesWithLimit[vehicleid])
	{
		SetVehicleSpeed(vehicleid, TDW_g_sVehiclesWithLimit[vehicleid]);
	}
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return 0;
	return SetTimerEx(!"@_TDW_TIMER_@_LIMITER_", TDW_LIMITER_TIMER_INTERVAL,
		false, !"ii", vehicleid, playerid
	);
}
