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
		= GetVehiclePoolSize()
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
		= GetVehiclePoolSize()
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
		= GetVehiclePoolSize()
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