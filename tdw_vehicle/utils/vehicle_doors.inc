/** ======================================================================== **\
	Vehicle Doors

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


#if defined _inc_vehicle_doors
	#undef _inc_vehicle_doors
#endif

#if defined _TDW_VEHICLE_U_DOORS
	#endinput
#endif

#define _TDW_VEHICLE_U_DOORS


#if !defined MAX_VEHICLE_DOORS
	#define MAX_VEHICLE_DOORS (4)
#endif


#if !defined OpenVehicleDoor
	#define OpenVehicleDoor(%0,%1) SetVehicleDoorState(%0, %1, DOOR_OPENED)
#endif
#if !defined CloseVehicleDoor
	#define CloseVehicleDoor(%0,%1) SetVehicleDoorState(%0, %1, DOOR_CLOSED)
#endif
#if !defined IsVehicleDoorInState
	#define IsVehicleDoorInState(%0,%1,%2) \
		(_:(GetVehicleDoorState(%0,%1) == _:(e_TDW_DOOR_STATE:(%2))))
#endif


enum
	e_TDW_VEHICLE_DOOR
{
	FRONT_LEFT_DOOR, FRONT_RIGHT_DOOR,
	 REAR_LEFT_DOOR,  REAR_RIGHT_DOOR // applies to vehicles with 4 doors.
};

enum
	e_TDW_DOOR_STATE
{
	DOOR_NOT_SET = -1,
	DOOR_OPENED = 0,
	DOOR_CLOSED
};


#if defined OnVehicleDoorUpdate
	forward OnVehicleDoorUpdate(vehicleid, e_TDW_VEHICLE_DOOR:door,
		e_TDW_DOOR_STATE:newstate);
#endif


stock
	GetVehicleDoorState(vehicleid, door, d_states[e_TDW_VEHICLE_DOOR])
{
	if (IsValidVehicle(vehicleid) == 0)
		return INVALID_VEHICLE_ID;
	if (_:(0 < door < 3) == 0)
		return 0;
	GetVehicleParamsCarDoors(vehicleid,
		d_states[FRONT_LEFT_DOOR], d_states[FRONT_RIGHT_DOOR],
		d_states[REAR_LEFT_DOOR],  d_states[REAR_RIGHT_DOOR]
	);
	return 1;
}


stock
	SetVehicleDoorState(vehicleid, e_TDW_VEHICLE_DOOR:door,
		e_TDW_DOOR_STATE:newstate)
{
	if (IsValidVehicle(vehicleid) == 0)
		return INVALID_VEHICLE_ID;
	if (_:(0 < door < 3) == 0)
		return 0;
	new d_states[e_TDW_VEHICLE_DOOR];
	GetVehicleParamsCarDoors(vehicleid,
		d_states[FRONT_LEFT_DOOR], d_states[FRONT_RIGHT_DOOR],
		d_states[REAR_LEFT_DOOR],  d_states[REAR_RIGHT_DOOR]
	);
#if defined OnVehicleDoorUpdate
	OnVehicleDoorUpdate(vehicleid, door, newstate);
#endif
	d_states[door] = newstate;
	SetVehicleParamsCarDoors(vehicleid,
		d_states[FRONT_LEFT_DOOR], d_states[FRONT_RIGHT_DOOR],
		d_states[REAR_LEFT_DOOR],  d_states[REAR_RIGHT_DOOR]
	);
	return 1;
}


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
