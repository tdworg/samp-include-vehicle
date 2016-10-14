/** ======================================================================== **\
	Vehicle Geometry

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


#if defined _inc_math_functions
	#undef _inc_math_functions
#endif

#if defined _TDW_VHLIB__MATH_FUNCTIONS
	#endinput
#endif

#define _TDW_VHLIB__MATH_FUNCTIONS

enum
	e_TDW_VEHICLE_SPEED
{
	kmph,
	mph
};


stock
	GetNearestVehicleFromPoint(Float:x, Float:y, Float:z, Float:distance = 30.0)
{
	new Float:min_dist, vehicleid = INVALID_VEHICLE_ID;
#if _TDW_VEHICLE_FOREACH_DEFINED
	foreach (new i: Vehicle)
#else
	for (new i = _TDW_FOREACH_MAX_VEHICLES_; --i != 0;)
#endif
	{
		if ((min_dist = GetVehicleDistanceFromPoint(i, x, y, z)) <= distance)
			vehicleid = i;
	}
	return vehicleid;
}


stock
	GetVehicleOffsetFromPos(vehicleid, Float:point_x, Float:point_y,
		Float:point_z, &Float:offset_x, &Float:offset_y, &Float:offset_z)
{
	new Float:x, Float:y, Float:z;
	if (GetVehiclePos(vehicleid, x, y, z) == 0)
		return _:(point_x = point_y = point_z = 0.0);
	offset_x = (point_x - x);
	offset_y = (point_y - y);
	offset_z = (point_z - z);
	return 1;
}


stock
	GetVehicleBootPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new Float:angle, Float:distance;
	if (GetVehicleZAngle(vehicleid, angle) == 0)
		return _:(x = y = z = 0.0);
	GetVehicleModelInfo(
		GetVehicleModel(vehicleid),
		VEHICLE_MODEL_INFO_SIZE,
		x, distance, z
	);
	dist = dist / 2 + 0.1;
	GetVehiclePos(vehicleid, x, y, z);
	x += (dist * floatsin(-angle + 180, degrees));
	y += (dist * floatcos(-angle + 180, degrees));
	return 1;
}


stock
	GetVehicleBonnetPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new Float:angle, Float:distance;
	if (GetVehicleZAngle(vehicleid, angle) == 0)
		return _:(x = y = z = 0.0);
	GetVehicleModelInfo(
		GetVehicleModel(vehicleid),
		VEHICLE_MODEL_INFO_SIZE,
		x, distance, z
	);
	dist = dist / 2 + 0.1;
	GetVehiclePos(vehicleid, x, y, z);
	x -= (dist * floatsin(-angle + 180, degrees));
	y -= (dist * floatcos(-angle + 180, degrees));
	return 1;
}


stock
	GetVehicleRoofPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new modelid, Float:vehicle_z;
	if ((modelid = GetVehicleModel(vehicleid)) == 0)
		return _:(x = y = z = 0.0);
	GetVehicleModelInfo(modelid, VEHICLE_MODEL_INFO_SIZE, x, y, vehicle_z);
	GetVehiclePos(vehicleid, x, y, z);
	z += floatsqroot(vehicle_z);
	return 1;
}


stock
	IsVehicleInRangeOfPoint(vehicleid, Float:range, Float:x, Float:y, Float:z)
{
	new Float:vehicle_x, Float:vehicle_y, Float:vehicle_z;
	return (
		GetVehiclePos(vehicleid, vehicle_x, vehicle_y, vehicle_z)
		? (
			((x -= vehicle_x) * x) +
			((y -= vehicle_y) * y) +
			((z -= vehicle_z) * z)
		) < (range * range)
		: 0
	);
}


stock
	Float:GetVehicleSpeedFromVelocity(Float:x, Float:y, Float:z,
		e_TDW_VEHICLE_SPEED:conv = kmph)
{
	return VectorSize(x, y, z) * (conv == kmph ? 180.0 : 111.846814);
}


stock
	Float:GetVehicleSpeed(vehicleid, e_TDW_VEHICLE_SPEED:conv = kmph)
{
	new Float:x, Float:y, Float:z;
	return (
		GetVehicleVelocity(vehicleid, x, y, z)
		? GetVehicleSpeedFromVelocity(x, y, z, conv)
		: -1.0
	);
}


stock
	SetVehicleSpeed(vehicleid, Float:speed, e_TDW_VEHICLE_SPEED:conv = kmph)
{
	new Float:x, Float:y, Float:z;
	if (GetVehicleVelocity(vehicleid, x, y, z))
	{
		new Float:c = VectorSize(x, y, z) * (conv == kmph ? 180.0 : 111.846814),
			Float:m = speed / c;
		SetVehicleVelocity(vehicleid, x * m, y * m, z * m);
	}
	return 0;
}

// Idk where I copied it, but the function is optimized by me.
stock
	IsVehicleUpsideDown(vehicleid)
{
	new Float:x, Float:y, Float:z, Float:w;
	if (GetVehicleRotationQuat(vehicleid, w, x, y, z) == 0)
		return INVALID_VEHICLE_ID;
	new Float:angle = atan2(((y * z) + (w * x)) * 2.0,
		(w * w) - (x * x) - (y * y) + (z * z));
	return ((angle > 90.0) || (angle < -90.0));
}


stock
	GetVehicleNearPlayers(vehicleid, playerlist[], Float:distance,
		size = sizeof playerlist)
{
	new Float:x, Float:y, Float:z;
	if (GetVehiclePos(vehicleid, x, y, z) == 0)
		return INVALID_VEHICLE_ID;
	new array_index, i;
#if _TDW_VEHICLE_FOREACH_DEFINED
	foreach(i : Player)
#else
	for(i
	#if defined GetPlayerPoolSize
		= GetPlayerPoolSize() + 1
	#else
		= MAX_PLAYERS
	#endif
		; i != -1; --i
	)
	if (IsPlayerConnected(i) == 0 || IsPlayerNPC(i))
		continue;
	else
#endif
	{
		if (IsPlayerInRangeOfPoint(i, distance, x, y, z))
		{
			if (array_index >= size)
				break;
			else playerlist[array_index++] = i;
		}
	}
	if (array_index != 0)
		playerlist[array_index] = INVALID_VEHICLE_ID;
	return 1;
}
