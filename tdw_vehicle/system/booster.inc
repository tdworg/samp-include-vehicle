/** ======================================================================== **\
	Vehicle Booste Speed system

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


#if defined _inc_booster
	#undef _inc_booster
#endif

#if defined _TDW_VHSYS__BOOSTER
	#endinput
#endif

#define _TDW_VHSYS__BOOSTER


#if !defined _TDW_BOOSTER_SPEED_UPDATE
	#define _TDW_BOOSTER_SPEED_UPDATE (450)
#else
	#assert (0 <= _TDW_BOOSTER_SPEED_UPDATE)
#endif

#if !defined _TDW_BOOSTER_MIN_SPEED
	#define _TDW_BOOSTER_MIN_SPEED (5.0)
#else
	#assert (0 <= _TDW_BOOSTER_MIN_SPEED)
#else

#if !defined _TDW_BOOSTER_BOOST_SPEED
	#define _TDW_BOOSTER_BOOST_SPEED (10.0)
#endif

#if !defined _TDW_BOOSTER_INACCURACY
	#define _TDW_BOOSTER_INACCURACY (0.15)
#endif

static stock const
	TDW_g_sTimerName[] = !"@_TDW_BOOSTER_SPEED_UPDATE";


public
	OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
	{
		if (GetModelStaticType(modelid) == CAR)
		{
			@_TDW_BOOSTER_SPEED_UPDATE(playerid);
		}
	}
	return
	#if defined TDWVHB@OnPlayerStateChange
		TDWVHB@OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		1;
	#endif
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVHB@OnPlayerStateChange

#if defined TDWVHB@OnPlayerStateChange
	forward TDWVHB@OnPlayerStateChange(playerid, newstate, oldstate);
#endif


@_TDW_BOOSTER_SPEED_UPDATE(playerid);
@_TDW_BOOSTER_SPEED_UPDATE(playerid)
{
	static vehicleid;

	if ((vehicleid = GetPlayerVehicleID(playerid)) == 0)
		return 0;

	static
		Float:old_angle,
		Float:cur_angle,
		keys,
		___, // Temporary variable
		Float:angle_tmp,
		Float:speed;

	GetVehicleZAngle(vehicleid, cur_angle);
	GetPlayerKeys(playerid, keys, ___, ___);

	if (keys & KEY_SPRINT)
	{
		old_angle = floatround(floatabs(floatadd(old_angle,
			_TDW_BOOSTER_INACCURACY
		)));
		angle_tmp = floatround(floatabs(cur_angle));

		if (_:(old_angle > angle_tmp || old_angle < angle_tmp) == 0)
		{
			speed = GetVehicleSpeed(vehicleid);

			if (_:(speed < _TDW_BOOSTER_MIN_SPEED ||
				IsVehicleDirection(vehicleid)) == 0)
				SetVehicleSpeed(vehicleid, speed + _TDW_BOOSTER_BOOST_SPEED);
		}
	}

	old_angle = cur_angle;

	return
		SetTimerEx(TDW_g_sTimerName, _TDW_BOOSTER_SPEED_UPDATE, false, !"i",
			playerid
		);
}
