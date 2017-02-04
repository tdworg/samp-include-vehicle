/* ========================================================================== *\
	Math

| Description:
	Mathematical functions for finding the positions.

| License:
	Copyright (c) 2016-2017 Double V

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

| Metadata:
	[Functions]:
		Stock:
			- GetNearestVehicleFromPoint
			- GetVehicleOffsetFromPos
			- GetVehicleBootPos
			- GetVehicleBonnetPos
			- GetVehicleRoofPos
			- IsVehicleInRangeOfPoint
			- GetVehicleSpeedFromVelocity
			- GetVehicleSpeed
			- SetVehicleSpeed
			- IsVehicleUpsideDown
			- GetVehicleVelocityDirection
		Static:
			-
		Public:
			-
		Hooks:
			-
	[Callbacks]:
		-
	[Definitions]:
		- FLOAT_INFINITY
	[Enumerations]:
		- E_TDW_MATH_VEHICLE_SPEED_TYPE
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			-
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_vmath
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_vmath
#endif

#if defined _TDW_VH_MATH
	#endinput
#endif

#define _TDW_VH_MATH

#include "tdw_vehicle"

// -----------------------------------------------------------------------------
// Definitions:

#if !defined FLOAT_INFINITY
	#define FLOAT_INFINITY					(Float:0x7F800000)
#endif

// -----------------------------------------------------------------------------
// Enumerations:

enum E_TDW_MATH_VEHICLE_SPEED_TYPE
{
	EI_MATH_SPEED_KMPH, // kilometers per hour
	EI_MATH_SPEED_MPH // miles per hour
};

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>GetNearestVehicleFromPoint</summary>
<param name="Float:x">The X map coordinate.</param>
<param name="Float:y">The Y map coordinate.</param>
<param name="Float:z">The Z map coordinate.</param>
<param name="Float:distance">The distance</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetNearestVehicleFromPoint(Float:x, Float:y, Float:z,
	Float:distance = 30.0)
{
	new
		Float:min_dist,
		vehicleid = INVALID_VEHICLE_ID;
	#pragma tabsize 0
	#if defined _TDW_VH_DETECT_FOREACH
		foreach (new i: Vehicle)
	#else
		for (new i = _TDW_FOREACH_MAX_VEHICLES_; --i != 0;)
	#endif
	{
		if ((min_dist = GetVehicleDistanceFromPoint(i, x, y, z)) <= distance) {
			vehicleid = i;
			distance = min_dist;
		}
	}
	#pragma tabsize 4
	return vehicleid;
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleOffsetFromPos</summary>
<param name="vehicleid"></param>
<param name="Float:point_x"></param>
<param name="Float:point_y"></param>
<param name="Float:point_z"></param>
<param name="&Float:offset_x"></param>
<param name="&Float:offset_y"></param>
<param name="&Float:offset_z"></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleOffsetFromPos(vehicleid, Float:point_x, Float:point_y,
	Float:point_z, &Float:offset_x, &Float:offset_y, &Float:offset_z)
{
	new
		Float:x,
		Float:y,
		Float:z;

	if (0 == GetVehiclePos(vehicleid, x, y, z))
		return _:(point_x = point_y = point_z = 0.0); // return 0

	offset_x = floatsub(point_x, x);
	offset_y = floatsub(point_y, y);
	offset_z = floatsub(point_z, z);

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleBootPos</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleBootPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new
		Float:angle,
		Float:distance;

	if (0 == GetVehicleZAngle(vehicleid, angle))
		return _:(x = y = z = 0.0); // return 0

	GetVehicleModelInfo(
		GetVehicleModel(vehicleid),
		VEHICLE_MODEL_INFO_SIZE,
		x, distance, z
	);

	distance = floatadd(floatdiv(distance, 2.0), 0.1);

	GetVehiclePos(vehicleid, x, y, z);

	x = floatadd(x, floatmul(distance, floatsin(floatadd(-angle, 180.0),
		degrees)));
	y = floatadd(y, floatmul(distance, floatcos(floatadd(-angle, 180.0),
		degrees)));

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleBonnetPos</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleBonnetPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new
		Float:angle,
		Float:distance;

	if (0 == GetVehicleZAngle(vehicleid, angle))
		return _:(x = y = z = 0.0); // return 0

	GetVehicleModelInfo(
		GetVehicleModel(vehicleid),
		VEHICLE_MODEL_INFO_SIZE,
		x, distance, z
	);

	distance = floatadd(floatdiv(distance, 2.0), 0.1);

	GetVehiclePos(vehicleid, x, y, z);

	x = floatsub(x, floatmul(distance, floatsin(floatadd(-angle, 180.0),
		degrees)));
	y = floatsub(y, floatmul(distance, floatsin(floatadd(-angle, 180.0),
		degrees)));

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleRoofPos</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleRoofPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new
		modelid,
		Float:vehicle_z;

	if (0 == (modelid = GetVehicleModel(vehicleid)))
		return _:(x = y = z = 0.0); // return 0

	GetVehicleModelInfo(modelid, VEHICLE_MODEL_INFO_SIZE, x, y, vehicle_z);
	GetVehiclePos(vehicleid, x, y, z);

	z = floatadd(z, floatsqroot(vehicle_z));

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>IsVehicleInRangeOfPoint</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock IsVehicleInRangeOfPoint(vehicleid, Float:range, Float:x, Float:y, Float:z)
{
	new
		Float:vehicle_x,
		Float:vehicle_y,
		Float:vehicle_z;

	if (0 == GetVehiclePos(vehicleid, vehicle_x, vehicle_y, vehicle_z))
		return 0;

	x = floatsub(x, vehicle_x);
	y = floatsub(y, vehicle_y);
	z = floatsub(z, vehicle_z);

	return VectorSize(x, y, z) < floatpower(range, 2);
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleSpeedFromVelocity</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock Float:GetVehicleSpeedFromVelocity(Float:x, Float:y, Float:z,
	E_TDW_MATH_VEHICLE_SPEED_TYPE:type = EI_MATH_SPEED_KMPH)
{
	return floatmul(VectorSize(x, y, z), (type == EI_MATH_SPEED_KMPH
		? 180.0
		: 111.846814));
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleSpeed</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock Float:GetVehicleSpeed(vehicleid,
	E_TDW_MATH_VEHICLE_SPEED_TYPE:type = EI_MATH_SPEED_KMPH)
{
	new
		Float:x,
		Float:y,
		Float:z;

	return GetVehicleVelocity(vehicleid, x, y, z)
		? GetVehicleSpeedFromVelocity(x, y, z, type)
		: FLOAT_INFINITY;
}

/** ------------------------------------------------------------------------ **\
<summary>SetVehicleSpeed</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetVehicleSpeed(vehicleid, Float:speed,
	E_TDW_MATH_VEHICLE_SPEED_TYPE:type = EI_MATH_SPEED_KMPH)
{
	new
		Float:x,
		Float:y,
		Float:z;

	if (GetVehicleVelocity(vehicleid, x, y, z))
	{
		new
			Float:angle;

		GetVehicleVelocity(vehicleid, x, y, z);
		GetVehicleZAngle(vehicleid, angle);

		switch (type)
		{
			case EI_MATH_SPEED_KMPH:
				speed = floatdiv(speed, 180.0);
			case EI_MATH_SPEED_MPH:
				speed = floatdiv(speed, 111.846814);
		}

		x = floatmul(speed, floatsin(-angle, degrees));
		y = floatmul(speed, floatcos(-angle, degrees));

		SetVehicleVelocity(vehicleid, x, y, z);
	}
	return 0;
}

/** ------------------------------------------------------------------------ **\
<summary>IsVehicleUpsideDown</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock IsVehicleUpsideDown(vehicleid)
{
	new
		Float:x,
		Float:y,
		Float:z,
		Float:w;

	if (0 == GetVehicleRotationQuat(vehicleid, w, x, y, z))
		return 0;

	new
		Float:angle = atan2(((y * z) + (w * x)) * 2.0,
			(w * w) - (x * x) - (y * y) + (z * z));

	return ((angle > 90.0) || (angle < -90.0));
}

/** ------------------------------------------------------------------------ **\
<summary>GetVehicleVelocityDirection</summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetVehicleVelocityDirection(vehicleid, &Float:direction)
{
	new
		Float:x,
		Float:y,
		Float:z;

	if (0 == GetVehicleVelocity(vehicleid, x, y, z))
		return 0;

	if (x < 0.0) {
		if (y > 0.0)
			direction = atan(floatabs(floatdiv(x, y)));
		else if (y <= 0.0)
			direction = floatadd(atan(floatdiv(y, x)), 90.0);
	} else if (x > 0) {
		if (y < 0.0)
			direction = floatadd(atan(floatabs(floatdiv(x, y))), 180.0);
		else if (y >= 0.0)
			direction = floatadd(atan(floatdiv(y, x)), 270.0);
	} else if (x == 0) {
		if (y > 0.0)
			direction = 0.0;
		else if (y < 0.0)
			direction = 180.0;
	}

	return 1;
}
