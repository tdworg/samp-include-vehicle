/** ======================================================================== **\
	Vehicle Additionally

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


#if defined _inc_useful_functions
	#undef _inc_useful_functions
#endif

#if defined _TDW_VHLIB__USEFUL_FUNCTIONS
	#endinput
#endif

#define _TDW_VHLIB__USEFUL_FUNCTIONS


enum e_TDW_VEHICLE_WHEEL
{
	 FRONT_LEFT,  FRONT_RIGHT,
	MIDDLE_LEFT, MIDDLE_RIGHT, // applies to vehicles with 3 axes
	  REAR_LEFT,   REAR_RIGTH
};


stock
	DestroyAllVehicles(...)
{
	const BYTES_PER_CELL = cellbits / charbits;
	new count, number_arg;
	// Get a number of the variadic arguments
	#emit load.s.pri 8
	#emit stor.s.pri number_arg
	// Checks if the number of the variadic arguments is more zero.
	if (number_arg != 0)
	{
		new arg_start, arg_end, ret;
		// Get the current frame pointer.
		#emit lctrl 5 // get the current frame
		#emit add.c 12 // offset
		#emit stor.s.pri arg_start
		// Get a pointer to the last argument.
		#emit load.s.alt number_arg
		#emit add
		#emit stor.s.pri arg_end
		do
		{
			// Get the value from the pointer
			#emit load.i
			// Push it!
			#emit push.pri
			#emit push.c 4
			#emit sysreq.c DestroyVehicle
			#emit stack 8
			// Get the return value from the called function.
			#emit stor.s.pri ret
			if (ret)
				count++;
			arg_end -= BYTES_PER_CELL;
			#emit load.s.pri arg_end
		}
		while (arg_end > arg_start);
	}
	else
	{
		#if defined _TDW_VEHICLE_FOREACH_ARRAY
		foreach (new i: Vehicle)
		#else
		for (new i = _TDW_FOREACH_MAX_VEHICLES_; --i != 0;)
		#endif
		{
			if (DestroyVehicle(i))
				count++;
		}
	}
	return count;
}


#if defined _TDW_VEHICLE_FOREACH_ARRAY
	// Foreach already contains an implementation of this function.
	#define CountOfValidVehicles(%0) (Iter_Count(Vehicle))
#else
	stock
		CountOfValidVehicles()
	{
		new count;
		for (new i = _TDW_FOREACH_MAX_VEHICLES_; --i != 0;)
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
		for (new i = _TDW_FOREACH_MAX_PLAYERS_; --i != -1;)
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
		for (new i = _TDW_FOREACH_MAX_PLAYERS_; --i != -1;)
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
	GetVehicleMaxPassengers(modelid)
{
	static const
		vehicle_seat_data[MAX_VEHICLE_MODELS char] =
	{
		4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2,
		4, 4, 2, 2, 2, 1, 4, 4, 4, 2, 1, 7, 1, 2, 2, 0, 2, 7, 4, 2,
		4, 1, 2, 2, 2, 4, 1, 2, 1, 0, 0, 2, 1, 1, 1, 2, 2, 2, 4, 4,
		2, 2, 2, 2, 1, 1, 4, 4, 2, 2, 4, 2, 1, 1, 2, 2, 1, 2, 2, 4,
		2, 1, 4, 3, 1, 1, 1, 4, 2, 2, 4, 2, 4, 1, 2, 2, 2, 4, 4, 2,
		2, 1, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 7, 7, 1,
		4, 2, 2, 2, 2, 2, 4, 4, 2, 2, 4, 4, 2, 1, 2, 2, 2, 2, 2, 2,
		4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1, 2, 2, 1, 2, 4,
		4, 2, 4, 1, 0, 4, 2, 2, 2, 2, 0, 0, 7, 2, 2, 1, 4, 4, 4, 2,
		2, 2, 2, 2, 4, 2, 0, 0, 0, 4, 0, 0
	};
	return (
		IS_VALID_MODEL(modelid)
		? (vehicle_seat_data{modelid - MIN_VEHICLE_MODEL})
		: 0
	);
}


stock
	GetVehicleDoorsCount(modelid)
{
	static const
		vehicle_door_data[MAX_VEHICLE_MODELS char] =
	{
		4, 2, 2, 2, 4, 4, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 4, 4,
		2, 2, 0, 1, 4, 2, 2, 0, 0, 0, 0, 2, 2, 0, 2, 0, 4, 0, 2, 0, 2, 2,
		2, 4, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 4, 2, 0, 0, 0, 0, 0, 0,
		4, 4, 0, 2, 4, 0, 0, 0, 2, 2, 1, 2, 2, 4, 0, 0, 2, 2, 0, 0, 0, 4,
		4, 2, 4, 2, 4, 0, 0, 2, 2, 4, 2, 2, 2, 0, 0, 0, 0, 2, 2, 4, 2, 0,
		0, 2, 0, 0, 2, 2, 4, 2, 2, 0, 1, 0, 0, 0, 2, 2, 2, 2, 2, 4, 0, 0,
		0, 0, 2, 2, 0, 0, 0, 0, 4, 2, 2, 2, 2, 2, 4, 4, 0, 2, 4, 4, 2, 0,
		2, 0, 2, 2, 2, 2, 4, 4, 2, 2, 0, 2, 4, 0, 0, 0, 0, 0, 0, 2, 2, 0,
		2, 0, 2, 4, 4, 0, 2, 2, 0, 4, 0, 2, 2, 2, 0, 0, 0, 2, 0, 0, 4, 4,
		4, 2, 2, 0, 2, 2, 4, 2, 0, 0, 0, 2, 0, 0
	};
	return (
		IS_VALID_MODEL(modelid)
		? (vehicle_door_data{modelid - MIN_VEHICLE_MODEL})
		: 0
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


stock
	GetVehicleWheelPos(vehicletype, e_TDW_VEHICLE_WHEEL:wheel,
		&Float:x, &Float:y, &Float:z)
{
	if (GetVehiclePos(vehicletype, x, y, z) == 0)
		return _:(x = y = z = 0.0); // return 0

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


#if defined COLANDREAS
	stock
		IsVehicleInWater(vehicleid)
	{
		new Float:x, Float:y, Float:z;
		if (GetVehiclePos(vehicleid, x, y, z))
		{
			new Float:retx[2], Float:rety[2], Float:retz[2],
				Float:retdist[2], modelids[2];
			new collisions = CA_RayCastMultiLine(
				x, y, z + 0.7, x, y, z - 0.7, retx, rety, retz, retdist,
				modelids, 2);
			if (collisions)
				for (new i = -1; ++i < collisions;)
					if (modelids[i] == WATER_OBJECT)
						return 1;
		}
		return 0;
	}
#endif


stock
	GetPlayerFromVehicleState(vehicleid, stateid)
{
	if (IsValidVehicle(vehicleid))
	{
		#if _TDW_VEHICLE_FOREACH_DEFINED
		foreach (new i: Player)
		#else
		for (new i = _TDW_FOREACH_MAX_PLAYERS_; --i != -1;)
		#endif
		{
			if (GetPlayerVehicleID(i) != vehicleid)
				continue;
			if (GetPlayerState(i) != stateid)
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
	GetVehicleOccupant(vehicleid, seatid = 0)
{
	if (IsValidVehicle(vehicleid))
	{
		#if _TDW_VEHICLE_FOREACH_DEFINED
		foreach (new i: Player)
		#else
		for (new i = _TDW_FOREACH_MAX_PLAYERS_; --i != -1;)
		#endif
		{
			if (GetPlayerVehicleID(i) != vehicleid)
				continue;
			if (GetPlayerVehicleSeat(i) != seatid)
				continue;
			return i;
		}
	}
	return INVALID_PLAYER_ID;
}


stock
	GetVehicleOccupantPlayers(vehicleid, playerlist[],
		size = sizeof playerlist)
{
	if (IsValidVehicle(vehicleid))
	{
		new array_index, i;
		#if _TDW_VEHICLE_FOREACH_DEFINED
		foreach(i : Player)
		#else
		for (i = _TDW_FOREACH_MAX_PLAYERS_; --i != -1;)
		if (IsPlayerNPC(i))
			continue;
		else
		#endif
		{
			if (GetPlayerVehicleID(i) != vehicleid)
				continue;
			if (array_index >= size)
				break;
			else playerlist[array_index++] = i;
		}
		if (array_index != 0)
		{
			playerlist[array_index] = INVALID_VEHICLE_ID;
			return 1;
		}
	}
	return 0;
}


stock
	IsVehicleMoving(vehicleid)
{
	new Float:x, Float:y, Float:z;
	if (GetVehicleVelocity(vehicleid, x, y, z) != 0)
	{
		if (floatcmp(x, 0.0) == 0 && floatcmp(y, 0.0) == 0 &&
			floatcmp(z, 0.0) == 0)
			return 1;
	}
	return 0;
}


stock
	IsVehicleDirection(vehicleid)
{
	new Float:x, Float:y, Float:z;
	if (GetVehicleVelocity(vehicleid, x, y, z))
	{
		new Float:z_angle;
		GetVehicleZAngle(vehicleid, z_angle);
		if (z_angle < 90.0)
			if (x > 0.0 && y < 0.0)
				return 1;
		else if (z_angle < 180.0)
			if (x > 0.0 && y > 0.0)
				return 1;
		else if (z_angle < 270.0)
			if (x < 0.0 && y > 0.0)
				return 1;
		else
			if (x < 0.0 && y < 0.0)
				return 1;
	}
	return 0;
}
