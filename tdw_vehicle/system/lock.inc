/** ======================================================================== **\
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


#if defined _inc_lock
	#undef _inc_lock
#endif

#if defined _TDW_VHSYS__LOCK
	#endinput
#endif

#define _TDW_VHSYS__LOCK


enum
	E_LOCK_TDW_CALLBACKS (<<= 1)
{
	EI_CB_PlayerTryingEnterVehicle = 1
};


static stock
	TDW_g_sOnPlTryingEnterVehicle[] = !"OnPlayerTryingEnterVehicle",
	E_LOCK_TDW_CALLBACKS:TDW_g_sCallbacks,
	TDW_g_sSpecifier@ii[] = !"ii";



#if defined FILTERSCRIPT
	public
		OnFilterScriptInit()
	{

		if (funcidx(TDW_g_sOnPlTryingEnterVehicle) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_PlayerTryingEnterVehicle;
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

		if (funcidx(TDW_g_sOnPlTryingEnterVehicle) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_PlayerTryingEnterVehicle;
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


public
	OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (IsVehicleLocked(vehicleid))
	{
		if (TDW_g_sCallbacks & EI_CB_PlayerTryingEnterVehicle)
		{
			if (CallLocalFunction(TDW_g_sOnPlTryingEnterVehicle,
				TDW_g_sSpecifier@ii, playerid, vehicleid) == 0)
			{
				ClearAnimations(playerid, 1);
			}
		}
	}
	return
	#if defined TDWVHL@OnPlayerEnterVehicle
		TDWVHL@OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		1;
	#endif
}

#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif

#define OnPlayerEnterVehicle TDWVHL@OnPlayerEnterVehicle

#if defined TDWVHL@OnPlayerEnterVehicle
	forward TDWVHL@OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif


public
	OnPlayerStateChange(playerid, newstate, oldstate)
{
	switch (newstate)
	{
		case PLAYER_STATE_PASSENGER, PLAYER_STATE_DRIVER:
		{
			if (IsVehicleLocked(GetPlayerVehicleID(playerid)))
			{
				RemovePlayerFromVehicle(playerid);
				ClearAnimations(playerid, 1);
			}
		}
	}
	return
	#if defined TDWVHL@OnPlayerStateChange
		TDWVHL@OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		1;
	#endif
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVHL@OnPlayerStateChange

#if defined TDWVHL@OnPlayerStateChange
	forward TDWVHL@OnPlayerStateChange(playerid, newstate, oldstate);
#endif


forward OnPlayerTryingEnterVehicle(playerid, vehicleid);
