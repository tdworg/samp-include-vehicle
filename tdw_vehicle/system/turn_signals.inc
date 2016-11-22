/** ======================================================================== **\
	Vehicle Turn signals system

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


#if defined _inc_turn_signals
	#undef _inc_turn_signals
#endif

#if defined _TDW_VHSYS__TURN_SIGNALS
	#endinput
#endif

#define _TDW_VHSYS__TURN_SIGNALS


#if !defined TDW_SIGNAL_OBJECT_ID
	#define TDW_SIGNAL_OBJECT_ID (19294)
#endif


enum
	E_TDW_TURN_SIGNAL_STATE(<<= 1)
{
	EI_TURN_SIGNAL_LEFT = 1,
	EI_TURN_SIGNAL_RIGHT,
	EI_TURN_SIGNAL_BOTH = EI_TURN_SIGNAL_LEFT | EI_TURN_SIGNAL_RIGHT
};

enum
	E_TDW_TURN_SIGNAL_OBJECT_IDS
{
	EI_TURN_SIGNAL_FRONT_LEFT,
	EI_TURN_SIGNAL_FRONT_RIGHT,
	EI_TURN_SIGNAL_BACK_LEFT,
	EI_TURN_SIGNAL_BACK_RIGHT
};


static stock
	TDW_g_sVehicleObjects[MAX_VEHICLES][E_TDW_TURN_SIGNAL_OBJECT_IDS];


stock
	AddVehicleTurnSignals(vehicleid, E_TDW_TURN_SIGNAL_STATE:turn_signal)
{
	new vehicle_model;
	if ((vehicle_model = GetVehicleModel(vehicleid)) == 0)
		return 0;
	if (GetModelStaticType(vehicle_model) != CAR)
		return 0;

	new
		Float:x,
		Float:y,
		Float:z;

	GetVehicleModelInfo(vehicle_model, VEHICLE_MODEL_INFO_SIZE, x, y, z);

	if (turn_signal & EI_TURN_SIGNAL_LEFT)
	{
		TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_FRONT_LEFT] =
			CreateObject(
			TDW_SIGNAL_OBJECT_ID,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, // Rotations
			0.0 // DrawDistance
		);
		TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_BACK_LEFT] =
			CreateObject(
			TDW_SIGNAL_OBJECT_ID,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, // Rotations
			0.0 // DrawDistance
		);
		AttachObjectToVehicle(
			TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_FRONT_LEFT],
			vehicleid,
			-x / 2.23, y / 2.23, 0.1, // Offsets
			0.0, 0.0, 0.0 // Rotations
		);
		AttachObjectToVehicle(
			TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_BACK_LEFT],
			vehicleid,
			-x / 2.23, -y / 2.23, 0.1, // Offsets
			0.0, 0.0, 0.0 // Rotations
		);
	}
	if (turn_signal & EI_TURN_SIGNAL_RIGHT)
	{
		TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_FRONT_RIGHT] =
			CreateObject(
			TDW_SIGNAL_OBJECT_ID,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, // Rotations
			0.0 // DrawDistance
		);
		TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_BACK_RIGHT] =
			CreateObject(
			TDW_SIGNAL_OBJECT_ID,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, // Rotations
			0.0 // DrawDistance
		);
		AttachObjectToVehicle(
			TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_FRONT_RIGHT],
			vehicleid,
			x / 2.23, y / 2.23, 0.1, // Offsets
			0.0, 0.0, 0.0 // Rotations
		);
		AttachObjectToVehicle(
			TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_BACK_RIGHT],
			vehicleid,
			x / 2.23, -y / 2.23, 0.1, // Offsets
			0.0, 0.0, 0.0 // Rotations
		);
	}
	return 1;
}


stock
	DeleteVehicleTurnSignals(vehicleid, E_TDW_TURN_SIGNAL_STATE:turn_signal)
{
	new vehicle_model;
	if ((vehicle_model = GetVehicleModel(vehicleid)) == 0)
		return 0;
	if (GetModelStaticType(vehicle_model) != CAR)
		return 0;

	if (turn_signal & EI_TURN_SIGNAL_LEFT)
	{
		DestroyObject(
			TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_FRONT_LEFT]
		);
		DestroyObject(
			TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_BACK_LEFT]
		);
	}
	if (turn_signal & EI_TURN_SIGNAL_RIGHT)
	{
		DestroyObject(
			TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_FRONT_RIGHT]
		);
		DestroyObject(
			TDW_g_sVehicleObjects[vehicleid][EI_TURN_SIGNAL_BACK_RIGHT]
		);
	}
	return 1;
}
