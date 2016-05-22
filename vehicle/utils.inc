#if defined _TDW_VEHICLE_UTILS_INC_
	#endinput
#endif
#define _TDW_VEHICLE_UTILS_INC_

stock
	DestroyAllVehicles()
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
		if (DestroyVehicle(i) == 0)
			continue;
		count++; // It's a feature of this function.
	}
	return count;
}

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

stock
	IsVehicleOccupied(vehicleid)
{
	if (IsValidVehicle(vehicleid))
	{
		for (
			new i
		#if defined GetPlayerPoolSize
			= GetPlayerPoolSize() + 1
		#else
			= GetMaxPlayers()
		#endif
			; --i != -1;
		)
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
		for (
			new i
		#if defined GetPlayerPoolSize
			= GetPlayerPoolSize() + 1
		#else
			= GetMaxPlayers()
		#endif
			; --i != -1;
		)
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
		: 0
	);
}