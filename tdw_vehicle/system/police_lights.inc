/** ======================================================================== **\
	Vehicle Police Lights system

| Bugs:
-1 - If the status is zero or one, but the player has not updated the status of
the sirens.

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


#if defined _inc_police_lights
	#undef _inc_police_lights
#endif

#if defined _TDW_VHSYS__POLICE_LIGHTS
	#endinput
#endif

#define _TDW_VHSYS__POLICE_LIGHTS


static stock
	TDW_g_sPLVehicle[MAX_VEHICLES];


stock
	UpdatePoliceLights(vehicleid)
{
	new modelid;
	if ((modelid = GetVehicleModel(vehicleid)) == 0)
		return 0;
	if (GetModelStaticType(modelid) != CAR)
		return 0;
	new siren_state;
	if ((siren_state = GetVehicleParamsSirenState(vehicleid)) == -1)
		return 0;
	new objectid, Float:size_x, Float:size_y, Float:size_z,
		object_model = siren_state ? 19420 : 19419;
	GetVehicleModelInfo(modelid, VEHICLE_MODEL_INFO_SIZE, size_x, size_y,
		size_z
	);
	if ((objectid = TDW_g_sPLVehicle[vehicleid]))
		DestroyObject(objectid);
	objectid = TDW_g_sPLVehicle[vehicleid] = CreateObject(object_model,
		0.0, 0.0, 0.0, // Positions
		0.0, 0.0, 0.0, // Rotations
		0.0
	);
	AttachObjectToVehicle(objectid, vehicleid,
		0.0, 0.0, size_z / 2.0, // Positions
		0.0, 0.0, 0.0 // Rotations
	);
	return 1;
}


stock
	RemovePoliceLights(vehicleid)
{
	if (IsValidVehicle(vehicleid))
		return 0;
	new objectid;
	if ((objectid = TDW_g_sPLVehicle[vehicleid]))
		DestroyObject(objectid);
	return 1;
}
