/** ======================================================================== **\
	Vehicle Utils

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

#if defined _inc_utils
	#undef _inc_utils
#endif
#if defined _TDW_VEHICLE_UTILS_INC_
	#endinput
#endif
#define _TDW_VEHICLE_UTILS_INC_

#if !defined TDW_VEHICLE_USE_DEPRECATED_COD
@__TDW_VEHICLE_UTILS__FIX();
@__TDW_VEHICLE_UTILS__FIX()
{
	#emit retn
	// The stock compiler crashes because of using sysreq.c on a native
	// function.
	UpdateVehicleDamageStatus(0, 0, 0, 0, 0);
}
#endif

stock
	DestroyAllVehicles()
{
	new count;
#if defined _TDW_VEHICLE_FOREACH_ARRAY
	foreach (new i: Vehicle)
#else
	for (
		new i
	#if defined GetVehiclePoolSize
		= GetVehiclePoolSize() + 1
	#else
		= MAX_VEHICLES
	#endif
		; --i != 0;
	)
#endif
	{
		if (DestroyVehicle(i))
			count++; // It's a feature of this function.
	}
	return count;
}

#if defined _TDW_VEHICLE_FOREACH_ARRAY
	#define CountOfValidVehicles(%0) (Iter_Count(Vehicle))
#else
	stock
		CountOfValidVehicles()
	{
		new count;
		for (
			new i
		#if defined GetVehiclePoolSize
			= GetVehiclePoolSize() + 1
		#else
			= MAX_VEHICLES
		#endif
			; --i != 0;
		)
		{
			if (IsValidVehicle(i) == 0)
				continue;
			count++;
		}
		return count;
	}
#endif

stock
	IsVehicleOccupied(vehicleid)
{
	if (IsValidVehicle(vehicleid))
	{
	#if _TDW_VEHICLE_FOREACH_DEFINED
		foreach (new i: Player)
	#else
		for (
			new i
		#if defined GetPlayerPoolSize
			= GetPlayerPoolSize() + 1
		#else
			= GetMaxPlayers()
		#endif
			; --i != -1;
		)
	#endif
		{
			if (IsPlayerInVehicle(i, vehicleid) == 0)
				continue;
			return 1;
		}
	}
	return 0;
}

stock
	IsVehicleSeatOccupied(vehicleid, seatid)
{
	if (IsValidVehicle(vehicleid))
	{
	#if _TDW_VEHICLE_FOREACH_DEFINED
		foreach (new i: Player)
	#else
		for (
			new i
		#if defined GetPlayerPoolSize
			= GetPlayerPoolSize() + 1
		#else
			= GetMaxPlayers()
		#endif
			; --i != -1;
		)
	#endif
		{
			if (IsPlayerInVehicle(i, vehicleid) == 0)
				continue;
			if (GetPlayerVehicleSeat(i) != seatid)
				continue;
			return 1;
		}
	}
	return 0;
}

stock
	GetNearestVehicleFromPoint(Float:x, Float:y, Float:z,
		Float:distance = 30.0)
{
	new Float:min_dist, vehicleid = INVALID_VEHICLE_ID;
#if defined _TDW_VEHICLE_FOREACH_ARRAY
	foreach (new i: Vehicle)
#else
	for (
		new i
	#if defined GetVehiclePoolSize
		= GetVehiclePoolSize() + 1
	#else
		= MAX_VEHICLES
	#endif
		; --i != 0;
	)
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
		return _:(point_x = point_y = point_z = 0.0); // I optimized this.
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
		return _:(x = y = z = 0.0); // I optimized this.
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
		return _:(x = y = z = 0.0); // I optimized this.
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
	new modelid, vehicle_z;
	if ((modelid = GetVehicleModel(vehicleid)) == 0)
		return _:(x = y = z = 0.0);
	GetVehicleModelInfo(modelid, VEHICLE_MODEL_INFO_SIZE, x, y, vehicle_z);
	GetVehiclePos(vehicleid, x, y, z);
	z += floatsqroot(vehicle_z);
	return 1;
}

stock
	GetVehicleMaxPassengers(modelid)
{
	static const
		vehicle_seat_data[27] =
	{
		0x21442224, 0x22422242, 0x22442424,
		0x81244412, 0x2482f221, 0x21422214,
		0x21112F82, 0x22214422, 0x24224411,
		0x42212211, 0x41112412, 0x22142422,
		0x22122442, 0x21124222, 0x12242211,
		0x22222221, 0x22211142, 0x22241882,
		0x44224422, 0x22222212, 0x44212244,
		0x21211881, 0x14144212, 0xF822224F,
		0x24441111, 0xFF242222, 0x0000F2FF
	};
	// OMG! It's very hard! But, no, it's not hard, believe me.
	// ======================================================================
	// e.g. modelid = 400
	// 1. modelid - 400 = 0
	// 2. 400 - 400 = 0
	// 3. 0 >>> 3 = 0
	// 4. 0b000 (0) & 0b111 = 0
	// 5. 0 << 2 = 0
	// 6. 0b00100001010001000010001000100100(0x21442224) >>> 0 = 0x21442224
	// 7. 0b00100001010001000010001000100100 & 0b1111 = 0b0100
	// End.
	return (
		(MIN_VEHICLE_MODEL_ID <= modelid <= MAX_VEHICLE_MODEL_ID)
		? ((vehicle_seat_data[(modelid -= MIN_VEHICLE_MODEL_ID) >>> 3] >>>
			((modelid & 0b111) << 2)) & 0b1111)
		: 0b1111
	);
}

stock
	IsValidModelForPaintjob(modelid)
{
	switch (modelid)
	{
		case 483: // 0
			return 1;
		case 575: // 1
			return 2;
		case 534, 535, 536, 558, 559, 560, 561, 562, 567, 576: // 012
			return 3;
	}
	return 0;
}

enum e_TDW_VEHICLE_DOOR
{
	FRONT_LEFT_DOOR, FRONT_RIGHT_DOOR,
	 REAR_LEFT_DOOR,  REAR_RIGHT_DOOR // applies to vehicles with 4 doors.
};

stock
	GetVehicleDoorPos(vehicletype, e_TDW_VEHICLE_DOOR:door,
		&Float:x, &Float:y, &Float:z)
{
	if (GetVehiclePos(vehicletype, x, y, z) == 0)
		return _:(x = y = z = 0.0);
	new Float:z_angle, Float:vehicle_x, Float:vehicle_y, Float:vehicle_z,
		Float:div;
	GetVehicleZAngle(vehicletype, z_angle);
	vehicletype = GetVehicleModel(vehicletype);
	switch (door)
	{
		case FRONT_LEFT_DOOR, FRONT_RIGHT_DOOR:
			GetVehicleModelInfo(vehicletype,
				VEHICLE_MODEL_INFO_FRONTSEAT,
				vehicle_x, vehicle_y, vehicle_z
			);
		case REAR_LEFT_DOOR, REAR_RIGHT_DOOR:
			GetVehicleModelInfo(vehicletype,
				VEHICLE_MODEL_INFO_REARSEAT,
				vehicle_x, vehicle_y, vehicle_z
			);
	}
	div = (_:door % 2) ? (vehicle_x) : (-vehicle_x);
	x = (floatsin((z_angle = 360 - z_angle), degrees) * vehicle_y) +
		(floatcos(z_angle, degrees) * div) + x;
	y = (floatcos(z_angle, degrees) * vehicle_y) -
		(floatsin(z_angle, degrees) * div) + y;
	z += vehicle_z;
	return 1;
}

enum e_TDW_VEHICLE_WHEEL
{
	 FRONT_LEFT,  FRONT_RIGHT,
	MIDDLE_LEFT, MIDDLE_RIGHT, // applies to vehicles with 3 axes
	  REAR_LEFT,   REAR_RIGTH
};

stock
	GetVehicleWheelPos(vehicletype, e_TDW_VEHICLE_WHEEL:wheel,
		&Float:x, &Float:y, &Float:z)
{
	if (GetVehiclePos(vehicletype, x, y, z) == 0)
		return _:(x = y = z = 0.0);
	new Float:z_angle, Float:vehicle_x, Float:vehicle_y, Float:vehicle_z,
		Float:div;
	GetVehicleZAngle(vehicletype, z_angle);
	vehicletype = GetVehicleModel(vehicletype);
	switch (wheel)
	{
		case FRONT_LEFT, FRONT_RIGHT:
			GetVehicleModelInfo(vehicletype,
				VEHICLE_MODEL_INFO_WHEELSFRONT,
				vehicle_x, vehicle_y, vehicle_z
			);
		case MIDDLE_LEFT, MIDDLE_RIGHT:
			GetVehicleModelInfo(vehicletype,
				VEHICLE_MODEL_INFO_WHEELSMID,
				vehicle_x, vehicle_y, vehicle_z
			);
		case REAR_LEFT, REAR_RIGTH:
			GetVehicleModelInfo(vehicletype,
				VEHICLE_MODEL_INFO_WHEELSREAR,
				vehicle_x, vehicle_y, vehicle_z
			);
	}
	div = (_:wheel % 2) ? (vehicle_x) : (-vehicle_x);
	x = (floatsin((z_angle = 360 - z_angle), degrees) * vehicle_y) +
		(floatcos(z_angle, degrees) * div) + x;
	y = (floatcos(z_angle, degrees) * vehicle_y) -
		(floatsin(z_angle, degrees) * div) + y;
	z = z + vehicle_z;
	return 1;
}

static stock TDW_g_sNULL;

// If you don't want to use the pp-operator "emit" in the code,
// add this to your code(before a_samp):
// #define TDW_VEHICLE_USE_DEPRECATED_COD

stock
	GetVehiclePanelsStatus(vehicleid, &front_left_panel, &front_right_panel,
		&rear_left_panel, &rear_right_panel, &windshield, &front_bumper,
		&rear_bumper)
{
	new panels;
	if (GetVehicleDamageStatus(vehicleid, panels, TDW_g_sNULL, TDW_g_sNULL,
		TDW_g_sNULL))
		return 0;
#if defined TDW_VEHICLE_USE_DEPRECATED_COD
	front_left_panel = panels & 0xF;
	front_right_panel = (panels >>> 4) & 0xF;
	rear_left_panel = (panels >>> 8) & 0xF;
	rear_right_panel = (panels >>> 12) & 0xF;
	windshield = (panels >>> 16) & 0xF;
	front_bumper = (panels >>> 20) & 0xF;
	rear_bumper = (panels >>> 24) & 0xF;
#else
	#emit const.alt     0xF
	// front_left_panel
	#emit load.s.pri    panels
	#emit and
	#emit sref.s.pri    front_left_panel
	// front_right_panel
	#emit shr.c.pri     4 // 4
	#emit and
	#emit sref.s.pri    front_right_panel
	// rear_left_panel
	#emit shr.c.pri     4 // 8
	#emit and
	#emit sref.s.pri    rear_left_panel
	// rear_right_panel
	#emit shr.c.pri     4 // 12
	#emit and
	#emit sref.s.pri    rear_right_panel
	// windshield
	#emit shr.c.pri     4 // 16
	#emit and
	#emit sref.s.pri    windshield
	// front_bumper
	#emit shr.c.pri     4 // 20
	#emit and
	#emit sref.s.pri    front_bumper
	// rear_bumper
	#emit shr.c.pri     4 // 24
	#emit and
	#emit sref.s.pri    rear_bumper
#endif
	return 1;
}

stock
	SetVehiclePanelsStatus(vehicleid, front_left_panel, front_right_panel,
		rear_left_panel, rear_right_panel, windshield, front_bumper,
		rear_bumper)
{
	new doors, lights, tires;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sNULL, doors, lights,
		tires) == 0)
		return 0;
#if defined TDW_VEHICLE_USE_DEPRECATED_COD
	UpdateVehicleDamageStatus(vehicleid,
		(front_left_panel | (front_right_panel << 4) | (rear_left_panel << 8)
			| (rear_right_panel << 12) | (windshield << 16)
			| (front_bumper << 20) | (rear_bumper << 24)),
		doors, lights, tires
	);
#else
	#emit push.s        tires // 4
	#emit push.s        lights // 8
	#emit push.s        doors // 12
	// front_left_panel
	#emit load.s.pri    front_left_panel
	// front_right_panel
	#emit load.s.alt    front_right_panel
	#emit shl.c.alt     4
	#emit or
	// rear_left_panel
	#emit load.s.alt    rear_left_panel
	#emit shl.c.alt     8
	#emit or
	// rear_right_panel
	#emit load.s.alt    rear_right_panel
	#emit shl.c.alt     12
	#emit or
	// windshield
	#emit load.s.alt    windshield
	#emit shl.c.alt     16
	#emit or
	// front_bumper
	#emit load.s.alt    front_bumper
	#emit shl.c.alt     20
	#emit or
	// rear_bumper
	#emit load.s.alt    rear_bumper
	#emit shl.c.alt     24
	#emit or
	// call the function
	#emit push.pri      // 16
	#emit push.s        vehicleid // 20
	#emit push.c        20
	#emit sysreq.c      UpdateVehicleDamageStatus
	#emit stack         24
#endif
	return 1;
}

stock
	GetVehicleDoorsStatus(vehicleid, &bonnet, &boot, &driver_door,
		&passenger_door)
{
	new doors;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sNULL, doors, TDW_g_sNULL,
		TDW_g_sNULL) == 0)
		return 0;
#if defined TDW_VEHICLE_USE_DEPRECATED_COD
	bonnet = doors & 0x7;
	boot = (doors >>> 8) & 0x7;
	driver_door = (doors >>> 16) & 0x7;
	passenger_door = (doors >>> 24) & 0x7;
#else
	#emit const.alt     0x7
	// bonnet
	#emit load.s.pri    doors
	#emit and
	#emit sref.s.pri    bonnet
	// boot
	#emit shr.c.pri     8 // 8
	#emit and
	#emit sref.s.pri    boot
	// driver_door
	#emit shr.c.pri     8 // 16
	#emit and
	#emit sref.s.pri    driver_door
	// passenger_door
	#emit shr.c.pri     8 // 24
	#emit and
	#emit sref.s.pri    passenger_door
#endif
	return 1;
}

stock
	SetVehicleDoorsStatus(vehicleid, bonnet, boot, driver_door, passenger_door)
{
	new panels, lights, tires;
	if (GetVehicleDamageStatus(vehicleid, panels, TDW_g_sNULL, lights,
		tires) == 0)
		return 0;
#if defined TDW_VEHICLE_USE_DEPRECATED_COD
	UpdateVehicleDamageStatus(vehicleid, panels,
		(bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24))
		, lights, tires
	);
#else
	#emit push.s        tires // 4
	#emit push.s        lights // 8
	// bonnet
	#emit load.s.pri    bonnet
	// boot
	#emit load.s.alt    boot
	#emit shl.c.alt     8
	#emit or
	// driver_door
	#emit load.s.alt    driver_door
	#emit shl.c.alt     16
	#emit or
	// passenger_door
	#emit load.s.alt    passenger_door
	#emit shl.c.alt     24
	#emit or
	// call the function
	#emit push.pri      // 12
	#emit push.s        panels // 16
	#emit push.s        vehicleid // 20
	#emit push.c        20
	#emit sysreq.c      UpdateVehicleDamageStatus
	#emit stack         24
#endif
	return 1;
}

stock
	GetVehicleLightsStatus(vehicleid, &light1, &light2, &light3, &light4)
{
	new lights;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sNULL, TDW_g_sNULL, lights,
		TDW_g_sNULL) == 0)
		return 0;
#if defined TDW_VEHICLE_USE_DEPRECATED_COD
	light1 = lights & 0x1;
	light2 = (lights >>> 1) & 0x1;
	light3 = (lights >>> 2) & 0x1;
	light4 = (lights >>> 3) & 0x1;
#else
	#emit const.alt     0x1
	// light1
	#emit load.s.pri    lights
	#emit and
	#emit sref.s.pri    light1
	// light2
	#emit shr.c.pri     1 // 2
	#emit and
	#emit sref.s.pri    light2
	// light3
	#emit shr.c.pri     1 // 3
	#emit and
	#emit sref.s.pri    light3
	// light4
	#emit shr.c.pri     1 // 4
	#emit and
	#emit sref.s.pri    light4
#endif
	return 1;
}

stock
	SetVehicleLightsStatus(vehicleid, light1, light2, light3, light4)
{
	new panels, doors, tires;
	if (GetVehicleDamageStatus(vehicleid, panels, doors, TDW_g_sNULL,
		tires) == 0)
		return 0;
#if defined TDW_VEHICLE_USE_DEPRECATED_COD
	UpdateVehicleDamageStatus(vehicleid, panels, doors,
		(light1 | (light2 << 1) | (light3 << 2) | (light4 << 3)),
		tires
	);
#else
	#emit push.s        tires // 4
	// light1
	#emit load.s.pri    light1
	// light2
	#emit load.s.alt    light2
	#emit shl.c.alt     1
	#emit or
	// light3
	#emit load.s.alt    light3
	#emit shl.c.alt     2
	#emit or
	// light4
	#emit load.s.alt    light4
	#emit shl.c.alt     3
	#emit or
	// call the function
	#emit push.pri      // 8
	#emit push.s        doors // 12
	#emit push.s        panels // 16
	#emit push.s        vehicleid // 20
	#emit push.c        20
	#emit sysreq.c      UpdateVehicleDamageStatus
	#emit stack         24
#endif
	return 1;
}

stock
	GetVehicleTiresStatus(vehicleid, &tire1, &tire2, &tire3, &tire4)
{
	new tires;
	if (GetVehicleDamageStatus(vehicleid, TDW_g_sNULL, TDW_g_sNULL,
		TDW_g_sNULL, tires) == 0)
		return 0;
#if defined TDW_VEHICLE_USE_DEPRECATED_COD
	tire1 = tires & 0x1;
	tire2 = (tires >>> 1) & 0x1;
	tire3 = (tires >>> 2) & 0x1;
	tire4 = (tires >>> 3) & 0x1;
#else
	#emit const.alt     0x1
	// tire1
	#emit load.pri      tires
	#emit and
	#emit sref.s.pri    tire1
	// tire2
	#emit shr.c.pri     1 // 2
	#emit and
	#emit sref.s.pri    tire2
	// tire3
	#emit shr.c.pri     1 // 3
	#emit and
	#emit sref.s.pri    tire3
	// tire4
	#emit shr.c.pri     1 // 4
	#emit and
	#emit sref.s.pri    tire4
#endif
	return 1;
}

stock
	SetVehicleTiresStatus(vehicleid, tire1, tire2, tire3, tire4)
{
	new panels, doors, lights, tires;
	if (GetVehicleDamageStatus(vehicleid, panels, doors, lights,
		TDW_g_sNULL) == 0)
		return 0;
#if defined TDW_VEHICLE_USE_DEPRECATED_COD
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights,
		(tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3))
	);
#else
	// tire1
	#emit load.s.pri    tire1
	// tire2
	#emit load.s.alt    tire2
	#emit shl.c.alt     1
	#emit or
	// tire3
	#emit load.s.alt    tire3
	#emit shl.c.alt     2
	#emit or
	// tire4
	#emit load.s.alt    tire4
	#emit shl.c.alt     3
	#emit or
	// call the function
	#emit push.pri      // 4
	#emit push.s        lights // 8
	#emit push.s        doors // 12
	#emit push.s        panels // 16
	#emit push.s        vehicleid // 20
	#emit push.c        20
	#emit sysreq.c      UpdateVehicleDamageStatus
	#emit stack         24
#endif
	return 1;
}

#if defined COLANDREAS
	stock
		IsVehicleInWater(vehicleid)
	{
		new Float:x, Float:y, Float:z;
		if (GetVehiclePos(vehicleid, x, y, z))
		{
			new Float:retx[2], Float:rety[2], Float:retz[2],
			    Float:retdist[2], modelids[2],
			    collisions = CA_RayCastMultiLine(
			    x, y, z + 0.7, x, y, z - 0.7, retx, rety, retz, retdist,
			    modelids, 2);

			if (collisions)
			{
				for (new i = -1; ++i < collisions;)
					if (modelids[i] == WATER_OBJECT)
						return 1;
			}
		}
		return 0;
	}
#endif

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
	GetPlayerFromVehicleState(vehicleid, stateid)
{
	if (IsValidVehicle(vehicleid))
	{
	#if _TDW_VEHICLE_FOREACH_DEFINED
		foreach (new i: Player)
	#else
		for(
			new i
		#if defined GetPlayerPoolSize
			= GetPlayerPoolSize() + 1
		#else
			= GetMaxPlayers()
		#endif
			; --i != -1;
		)
	#endif
		{
			if (GetPlayerVehicleID(i) == 0)
				continue;
			if(GetPlayerState(i) != stateid)
				continue;
			return i;
		}
	}
	return INVALID_PLAYER_ID;
}

#if !defined GetVehicleDriverId
	#define GetVehicleDriverId(%0) \
		GetPlayerFromVehicleState(%0, PLAYER_STATE_DRIVER)
#endif

stock
	GetPlayerFromVehicleSeat(vehicleid, seatid)
{
	if (IsValidVehicle(vehicleid))
	{
	#if _TDW_VEHICLE_FOREACH_DEFINED
		foreach (new i: Player)
	#else
		for(
			new i
		#if defined GetPlayerPoolSize
			= GetPlayerPoolSize() + 1
		#else
			= GetMaxPlayers()
		#endif
			; --i != -1;
			)
	#endif
		{
			if (GetPlayerVehicleID(i) == 0)
				continue;
			if(GetPlayerVehicleSeat(i) != seatid)
				continue;
			return i;
		}
	}
	return INVALID_PLAYER_ID;
}

enum e_TDW_DOOR_STATE
{
	DOOR_NOT_SET = -1,
	DOOR_OPENED = 0,
	DOOR_CLOSED
};

enum e_TDW_WINDOW_STATE
{
	WINDOW_NOT_SET = -1,
	WINDOW_OPENED = 0,
	WINDOW_CLOSED
};

#if defined OnVehicleWindowUpdate
forward OnVehicleWindowUpdate(vehicleid, e_TDW_VEHICLE_DOOR:door,
	e_TDW_WINDOW_STATE:newstate);
#endif
#if defined OnVehicleDoorUpdate
forward OnVehicleDoorUpdate(vehicleid, e_TDW_VEHICLE_DOOR:door,
	e_TDW_DOOR_STATE:newstate);
#endif

// This function was added in SA:MP 0.3.7 and will not work in earlier version!
#if defined GetVehicleParamsCarWindows
stock
	SetVehicleWindowState(vehicleid, e_TDW_VEHICLE_DOOR:door,
		e_TDW_WINDOW_STATE:newstate)
{
	if (IsValidVehicle(vehicleid))
	{
		if (0 < door < 3)
		{
			new w_states[e_TDW_VEHICLE_DOOR];

			GetVehicleParamsCarWindows(vehicleid,
				w_states[FRONT_LEFT_DOOR], w_states[FRONT_RIGHT_DOOR],
				w_states[REAR_LEFT_DOOR],  w_states[REAR_RIGHT_DOOR]
			);

			#if defined OnVehicleWindowUpdate
			OnVehicleWindowUpdate(vehicleid, door, newstate, w_states[door]);
			#endif

			w_states[door] = newstate;

			SetVehicleParamsCarWindows(vehicleid,
				w_states[FRONT_LEFT_DOOR], w_states[FRONT_RIGHT_DOOR],
				w_states[REAR_LEFT_DOOR],  w_states[REAR_RIGHT_DOOR]
			);
			return 1;
		}
	}
	return 0;
}
#endif

// This function was added in SA:MP 0.3.7 and will not work in earlier version!
#if defined GetVehicleParamsCarDoors
stock
	SetVehicleDoorState(vehicleid, e_TDW_VEHICLE_DOOR:door,
		e_TDW_DOOR_STATE:newstate)
{
	if (IsValidVehicle(vehicleid))
	{
		if (0 < door < 3)
		{
			new w_states[e_TDW_VEHICLE_DOOR];

			GetVehicleParamsCarDoors(vehicleid,
				w_states[FRONT_LEFT_DOOR], w_states[FRONT_RIGHT_DOOR],
				w_states[REAR_LEFT_DOOR],  w_states[REAR_RIGHT_DOOR]
			);

			#if defined OnVehicleDoorUpdate
			OnVehicleDoorUpdate(vehicleid, door, newstate, w_states[door]);
			#endif

			w_states[door] = newstate;

			SetVehicleParamsCarDoors(vehicleid,
				w_states[FRONT_LEFT_DOOR], w_states[FRONT_RIGHT_DOOR],
				w_states[REAR_LEFT_DOOR],  w_states[REAR_RIGHT_DOOR]
			);

			return 1;
		}
	}
	return 0;
}
#endif

// This function was added in SA:MP 0.3.7 and will not work in earlier version!
#if defined GetVehicleParamsCarWindows
stock
	GetVehicleWindowState(vehicleid, door, w_states[e_TDW_VEHICLE_DOOR])
{
	if (IsValidVehicle(vehicleid))
	{
		if (0 < door < 3)
		{
			GetVehicleParamsCarWindows(vehicleid,
				w_states[FRONT_LEFT_DOOR], w_states[FRONT_RIGHT_DOOR],
				w_states[REAR_LEFT_DOOR],  w_states[REAR_RIGHT_DOOR]
			);
			return 1;
		}
	}
	return 0;
}
#endif

// This function was added in SA:MP 0.3.7 and will not work in earlier version!
#if defined GetVehicleParamsCarDoors
stock
	GetVehicleDoorState(vehicleid, door, w_states[e_TDW_VEHICLE_DOOR])
{
	if (IsValidVehicle(vehicleid))
	{
		if (0 < door < 3)
		{
			GetVehicleParamsCarDoors(vehicleid,
				w_states[FRONT_LEFT_DOOR], w_states[FRONT_RIGHT_DOOR],
				w_states[REAR_LEFT_DOOR],  w_states[REAR_RIGHT_DOOR]
			);
			return 1;
		}
	}
	return 0;
}
#endif

enum e_TDW_VEHICLE_SPEED
{
	kmph,
	mph
};

stock
	Float:GetVehicleSpeedFromVelocity(Float:x, Float:y, Float:z,
		e_TDW_VEHICLE_SPEED:conv = kmph)
{
	return floatsqroot(((x * x) + (y * y)) + (z * z))
		* (conv == kmph ? 187.666667 : 116.610660);
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
		new Float:current_speed = GetVehicleSpeedFromVelocity(x, y, z, kmph),
		    Float:m = ((
		    conv == kmph ? speed : (speed * 1.609344)
		    ) + (current_speed / 100)) /
		    (current_speed / 100) / 113.8333335;
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

#if defined GetVehicleParamsCarDoors
	#if !defined OpenVehicleDoor
		#define OpenVehicleDoor(%0,%1) SetVehicleDoorState(%0,%1,DOOR_OPENED)
	#endif
	#if !defined CloseVehicleDoor
		#define CloseVehicleDoor(%0,%1) SetVehicleDoorState(%0,%1,DOOR_CLOSED)
	#endif
	#if !defined IsVehicleDoorInState
		#define IsVehicleDoorInState(%0,%1,%2) \
			(_:(GetVehicleDoorState(%0,%1) == _:(e_TDW_DOOR_STATE:(%2))))
	#endif
	#if !defined OpenVehicleWindow
		#define OpenVehicleWindow(%0,%1) SetVehicleWindowState(%0,%1, \
			WINDOW_OPENED)
	#endif
	#if !defined CloseVehicleWindow
		#define CloseVehicleWindow(%0,%1) SetVehicleWindowState(%0,%1, \
			WINDOW_CLOSED)
	#endif
	#if !defined IsVehicleWindowInState
		#define IsVehicleWindowInState(%0,%1,%2) \
			(_:(GetVehicleWindowState(%0,%1) == _:(e_TDW_WINDOW_STATE:(%2))))
	#endif
#endif
