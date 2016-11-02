/** ======================================================================== **\
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


#if defined _inc_neon
	#undef _inc_neon
#endif

#if defined _TDW_VHSYS__NEON
	#endinput
#endif

#define _TDW_VHSYS__NEON


enum
	E_TDW_NEON_COLOR
{
	// objects
	NEON_COLOR_RED = 18647,
	NEON_COLOR_BLUE,
	NEON_COLOR_GREEN,
	NEON_COLOR_YELLOW,
	NEON_COLOR_PINK,
	NEON_COLOR_WHITE
};

enum
	E_TDW_NEON_OBJECTS
{
	EI_NEON_LEFT_ID,
	EI_NEON_RIGHT_ID
};


static stock
	TDW_g_sNeon[MAX_VEHICLES][E_TDW_NEON_OBJECTS],
	bool:TDW_g_sIsNeonAttached[MAX_VEHICLES char];


stock
	AddNeonToVehicle(vehicleid, E_TDW_NEON_COLOR:color)
{
	new vehicle_model;
	if ((vehicle_model = GetVehicleModel(vehicleid)) == 0)
		return 0;
	if (GetModelStaticType(vehicle_model) != CAR)
		return 0;
	new Float:size_x, Float:size_y, Float:size_z;
	GetVehicleModelInfo(vehicle_model, VEHICLE_MODEL_INFO_SIZE, size_x, size_y,
		size_z
	);
	new objectid;
	const Float:OFFSET_Z = -0.6;
	objectid = TDW_g_sNeon[vehicleid][EI_NEON_LEFT_ID] = CreateObject(_:color,
		0.0, 0.0, 0.0, // Positions
		0.0, 0.0, 0.0, // Rotations
		0.0 // Draw distance
	);
	AttachObjectToVehicle(objectid, vehicleid,
		-size_x / 2.8, 0.0, OFFSET_Z, // Positions
		0.0, 0.0, 0.0 // Rotations
	);
	objectid = TDW_g_sNeon[vehicleid][EI_NEON_RIGHT_ID] = CreateObject(_:color,
		0.0, 0.0, 0.0, // Positions
		0.0, 0.0, 0.0, // Rotations
		0.0 // Draw distance
	);
	AttachObjectToVehicle(objectid, vehicleid,
		size_x / 2.8, 0.0, OFFSET_Z, // Positions
		0.0, 0.0, 0.0 // Rotations
	);
	TDW_g_sIsNeonAttached{vehicleid} = true;
	return 1;
}


stock
	RemoveNeonFromVehicle(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	if (_:TDW_g_sIsNeonAttached{vehicleid} == 0)
	{
		DestroyObject(TDW_g_sNeon[vehicleid][EI_NEON_LEFT_ID]);
		DestroyObject(TDW_g_sNeon[vehicleid][EI_NEON_RIGHT_ID]);
		TDW_g_sIsNeonAttached{vehicleid} = false;
	}
	return 1;
}


public
	OnVehicleDeath(vehicleid, killerid)
{
	RemoveNeonFromVehicle(vehicleid);
	#if defined TDWHNE@OnVehicleDeath
	return TDWHNE@OnVehicleDeath(vehicleid, killerid);
	#else
	return 1;
	#endif
}
#if defined _ALS_OnVehicleDeath
	#undef OnVehicleDeath
#else
	#define _ALS_OnVehicleDeath
#endif

#define OnVehicleDeath TDWHNE@OnVehicleDeath

#if defined TDWHNE@OnVehicleDeath
forward OnVehicleDeath(vehicleid, killerid);
#endif
