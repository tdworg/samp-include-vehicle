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
	GetVehicleVelocityDirection(vehicleid, &Float:direction)
{
	static
		Float:x,
		Float:y,
		Float:z;
	if (GetVehicleVelocity(vehicleid, x, y, z) == 0)
		return 0;
	if (x < 0.0)
	{
		if (y > 0.0)
			direction = atan(floatabs(floatdiv(x, y)));
		else if (y <= 0.0)
			direction = floatadd(atan(floatdiv(y, x)), 90.0);
	}
	else if (x > 0)
	{
		if (y < 0.0)
			direction = floatadd(atan(floatabs(floatdiv(x, y))), 180.0);
		else if (y >= 0.0)
			direction = floatadd(atan(floatdiv(y, x)), 270.0);
	}
	else if (x == 0)
	{
		if (y > 0.0)
			direction = 0.0;
		else if (y < 0.0)
			direction = 180.0;
	}
	return 1;
}



@_TDW_VEHICLE_DRIFT(vehicleid);
@_TDW_VEHICLE_DRIFT(vehicleid)
{
	static
		Float:speed,
		Float:direction,
		Float:drift_angle,
		Float:z_angle;
	if (GetVehicleVelocityDirection(vehicleid, direction) == 0)
		return 0;
	speed = GetVehicleSpeed(vehicleid);
	if (speed > 2.0)
	{
		GetVehicleZAngle(vehicleid, z_angle);
		drift_angle = floatabs(floatsub(direction, z_angle));
		if (drift_angle >= 180.0)
			drift_angle = floatsub(360.0, drift_angle);
		if (15.0 < drift_angle < 80.0)
		{
			if (25.0 < drift_angle < 70.0)
			{
				SendClientMessageToAll(0xffffffff, "Nice! 25.0 || 70.0");
			}
			else if (35.0 < drift_angle < 45.0)
			{
				SendClientMessageToAll(0xffffffff, "Nice! 35.0 || 45.0");
			}
			else
			{
				SendClientMessageToAll(0xffffffff, "Nice! 15.0 || 80.0");
			}
		}
	}
	return SetTimerEx(!"@_TDW_VEHICLE_DRIFT", 250, false, !"i", vehicleid);
}


public
	OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if (GetModelStaticType(GetVehicleModel(vehicleid)) == CAR)
		{
			@_TDW_VEHICLE_DRIFT(vehicleid);
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
