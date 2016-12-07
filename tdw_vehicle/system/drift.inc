/** ======================================================================== **\
	Vehicle Drift system

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


#if defined _inc_drift
	#undef _inc_drift
#endif

#if defined _TDW_VHSYS__DRIFT
	#endinput
#endif

#define _TDW_VHSYS__DRIFT


static stock
	TDW_g_sOnPlayerVehicleDrift[]= !"OnPlayerVehicleDrift",
	TDW_g_sCallbacks;


@_TDW_VEHICLE_DRIFT(playerid, vehicleid);
@_TDW_VEHICLE_DRIFT(playerid, vehicleid)
{
	static
		Float:speed,
		Float:direction,
		Float:drift_angle,
		Float:z_angle,
		bool:is_player_drifting[MAX_PLAYERS char];
	if (GetVehicleVelocityDirection(vehicleid, direction) == 0)
		return 0;
	speed = GetVehicleSpeed(vehicleid);
	if (speed > 5.0)
	{
		GetVehicleZAngle(vehicleid, z_angle);
		drift_angle = floatabs(floatsub(direction, z_angle));
		if (drift_angle >= 180.0)
			drift_angle = floatsub(360.0, drift_angle);
		static bool:is_drifting;
		is_drifting = is_player_drifting{playerid};
		if (15.0 < drift_angle < 80.0)
		{
			if (_:is_drifting == 0)
			{
				CallLocalFunction(TDW_g_sOnPlayerVehicleDrift, !"iif", playerid,
					vehicleid, drift_angle
				);
			}
		}
		if (_:is_drifting != 0)
			is_player_drifting{playerid} = false;
	}
	return SetTimerEx(!"@_TDW_VEHICLE_DRIFT", 250, false, !"ii", playerid,
		vehicleid
	);
}


public
	OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if (GetModelStaticType(GetVehicleModel(vehicleid)) == CAR)
		{
			if (TDW_g_sCallbacks & 1)
			{
				@_TDW_VEHICLE_DRIFT(playerid, vehicleid);
			}
		}
	}
	return
	#if defined TDWVHD@OnPlayerStateChange
		TDWVHD@OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		1;
	#endif
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVHD@OnPlayerStateChange

#if defined TDWVHD@OnPlayerStateChange
	forward TDWVHD@OnPlayerStateChange(playerid, newstate, oldstate);
#endif


#if defined FILTERSCRIPT
	public
		OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnPlayerVehicleDrift) != -1)
		{
			TDW_g_sCallbacks |= 1;
		}
		return
		#if defined TDWVHD@OnFilterScriptInit
			TDWVHD@OnFilterScriptInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVHD@OnFilterScriptInit

	#if defined TDWVHD@OnFilterScriptInit
		forward TDWVHD@OnFilterScriptInit();
	#endif
#else
	public
		OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnPlayerVehicleDrift) != -1)
		{
			TDW_g_sCallbacks |= 1;
		}
		return
		#if defined TDWVHD@OnGameModeInit
			TDWVHD@OnGameModeInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVHD@OnGameModeInit

	#if defined TDWVHD@OnGameModeInit
		forward TDWVHD@OnGameModeInit();
	#endif
#endif


forward OnPlayerVehicleDrift(playerid, vehicleid, Float:drift_angle);
