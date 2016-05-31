/** ======================================================================== **\
	Vehicle Surfing system

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

#if defined _TDW_VEHICLE_S_SURFING_INC_
	#endinput
#endif
#define _TDW_VEHICLE_S_SURFING_INC_

#if !defined TDW_MAX_TIMER_INTERVAL
	#define TDW_MAX_TIMER_INTERVAL (300)
#endif

static stock
	TDW_g_sVehicleD@TimerId[MAX_PLAYERS] = {-1, ...},
	TDW_g_sVehicleD@AllowedModels[MAX_VEHICLE_MODELS + 1];

stock
	VehicleSurfing_Construct(playerid)
{
	TDW_g_sVehicleD@TimerId[playerid] = SetTimerEx(!"@_TDW_VSS____Update",
		TDW_MAX_TIMER_INTERVAL, true, !"i", playerid);
	return;
}

stock
	VehicleSurfing_Destruct(playerid)
{
	if (TDW_g_sVehicleD@TimerId[playerid] != -1)
	{
		KillTimer(TDW_g_sVehicleD@TimerId[playerid]);
	}
	return 0;
}

stock
	VehicleSurfing_SetAllowModel(modelid, bool:value)
{
	if (_:(MIN_VEHICLE_MODEL_ID <= modeldid <= MAX_VEHICLE_MODEL_ID) == 0)
		return 0;
	TDW_g_sVehicleD@AllowedModels[modelid - MIN_VEHICLE_MODEL_ID] = _:value;
	return 1;
}

// Timer
@_TDW_VSS____Update(playerid);
@_TDW_VSS____Update(playerid)
{
	static vehicleid;
	if ((vehicleid = GetPlayerSurfingVehicleID(playerid)) !=
		INVALID_VEHICLE_ID)
	{
		if (TDW_g_sVehicleD@AllowedModels[GetVehicleModel(vehicleid) -
			MIN_VEHICLE_MODEL_ID] == 0)
		{
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			// GetVehicleBootPos(vehicleid, x, y, z);
			SetPlayerPos(playerid, x, y, z + 3.5);
		}
	}
	return 0;
}