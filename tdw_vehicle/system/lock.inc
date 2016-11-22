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


public
	OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (IsVehicleLocked(vehicleid))
	{
		#if defined OnPlayerTryingEnterVehicle
			if (OnPlayerTryingEnterVehicle(playerid, vehicleid) == 0)
			{
				ClearAnimations(playerid, 1);
			}
		#endif
	}
	return
	#if defined TDWVHE@OnPlayerEnterVehicle
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
	#if defined TDWVHE@OnPlayerStateChange
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


#if defined OnPlayerTryingEnterVehicle
	forward OnPlayerTryingEnterVehicle(playerid, vehicleid);
#endif
