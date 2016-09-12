/** ======================================================================== **\
	Vehicle Windows

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


#if defined _inc_vehicle_windows
	#undef _inc_vehicle_windows
#endif

#if defined _TDW_VEHICLE_U_WINDOWS
	#endinput
#endif

#define _TDW_VEHICLE_U_WINDOWS


#if !defined OpenVehicleWindow
	#define OpenVehicleWindow(%0,%1) SetVehicleWindowState(%0,%1,WINDOW_OPENED)
#endif
#if !defined CloseVehicleWindow
	#define CloseVehicleWindow(%0,%1) SetVehicleWindowState(%0,%1,WINDOW_CLOSED)
#endif
#if !defined IsVehicleWindowInState
	#define IsVehicleWindowInState(%0,%1,%2) \
		(_:(GetVehicleWindowState(%0,%1) == _:(e_TDW_WINDOW_STATE:(%2))))
#endif


enum
	e_TDW_WINDOW_STATE
{
	WINDOW_NOT_SET = -1,
	WINDOW_OPENED = 0,
	WINDOW_CLOSED
};


#if defined OnVehicleWindowUpdate
	forward OnVehicleWindowUpdate(vehicleid, e_TDW_VEHICLE_DOOR:door,
		e_TDW_WINDOW_STATE:newstate);
#endif


stock
	GetVehicleWindowState(vehicleid, door, w_states[e_TDW_VEHICLE_DOOR])
{
	if (IsValidVehicle(vehicleid) == 0)
		return INVALID_VEHICLE_ID;
	if (_:(0 < door < 3) == 0)
		return 0;
	GetVehicleParamsCarWindows(vehicleid,
		w_states[FRONT_LEFT_DOOR], w_states[FRONT_RIGHT_DOOR],
		w_states[REAR_LEFT_DOOR],  w_states[REAR_RIGHT_DOOR]
	);
	return 1;
}


stock
	SetVehicleWindowState(vehicleid, e_TDW_VEHICLE_DOOR:door,
		e_TDW_WINDOW_STATE:newstate)
{
	if (IsValidVehicle(vehicleid) == 0)
		return INVALID_VEHICLE_ID;
	if (_:(0 < door < 3) == 0)
		return 0;
	new w_states[e_TDW_VEHICLE_DOOR];
	GetVehicleParamsCarWindows(vehicleid,
		w_states[FRONT_LEFT_DOOR], w_states[FRONT_RIGHT_DOOR],
		w_states[REAR_LEFT_DOOR],  w_states[REAR_RIGHT_DOOR]
	);
#if defined OnVehicleWindowUpdate
	OnVehicleWindowUpdate(vehicleid, door, newstate);
#endif
	w_states[door] = newstate;
	SetVehicleParamsCarWindows(vehicleid,
		w_states[FRONT_LEFT_DOOR], w_states[FRONT_RIGHT_DOOR],
		w_states[REAR_LEFT_DOOR],  w_states[REAR_RIGHT_DOOR]
	);
	return 1;
}
