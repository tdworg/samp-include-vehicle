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