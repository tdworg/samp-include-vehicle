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


#if defined _inc_window_manage
	#undef _inc_window_manage
#endif

#if defined _TDW_VHLIB__WINDOW_MANAGE
	#endinput
#endif

#define _TDW_VHLIB__WINDOW_MANAGE


#if !defined OpenVehicleWindow
	// Arguments:
	// %1 - vehicleid
	// %2 - E_TDW_VEHICLE_DOOR:door
	#define OpenVehicleWindow%0(%1,%2)\
		SetVehicleWindowState(%1,%2,WINDOW_OPENED)
#endif

#if !defined CloseVehicleWindow
	// Arguments:
	// %1 - vehicleid
	// %2 - E_TDW_VEHICLE_DOOR:door
	#define CloseVehicleWindow%0(%1,%2)\
		SetVehicleWindowState(%1,%2,WINDOW_CLOSED)
#endif

#if !defined IsVehicleWindowInState
	// Arguments:
	// %1 - vehicleid
	// %2 - E_TDW_VEHICLE_DOOR:door
	// %3 - E_TDW_DOOR_STATE:state
	#define IsVehicleWindowInState%0(%1,%2,%3)\
		(_:(GetVehicleWindowState(%1,%2) == _:(E_TDW_WINDOW_STATE:(%3))))
#endif


enum
	E_TDW_WINDOW_STATE
{
	WINDOW_NOT_SET = -1,
	WINDOW_OPENED = 0,
	WINDOW_CLOSED
};


stock
	GetVehicleWindowState(vehicleid, E_TDW_VEHICLE_DOOR:door)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	if (_:(0 <= _:door < MAX_VEHICLE_DOORS) == 0)
		return 0;
	new driver, passenger, backleft, backright;
	GetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft,
		backright
	);
	// Return state of the door, which was specified when calling the function.
	switch (door)
	{
		case FRONT_LEFT_DOOR:
			return driver;
		case FRONT_RIGHT_DOOR:
			return passenger;
		case REAR_LEFT_DOOR:
			return backleft;
		case REAR_RIGHT_DOOR:
			return backright;
	}
	return 0; // For compiler!
}


// Returns true if the vehicle exists, otherwise false.
stock
	SetVehicleWindowState(vehicleid, E_TDW_VEHICLE_DOOR:door,
		E_TDW_DOOR_STATE:newstate)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	if (_:(0 <= _:door < MAX_VEHICLE_DOORS) == 0)
		return 0;
	new driver, passenger, backleft, backright;
	GetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft,
		backright
	);
	switch (door)
	{
		case FRONT_LEFT_DOOR:
			return SetVehicleParamsCarWindows(vehicleid, _:newstate, passenger,
				backleft, backright
			);
		case FRONT_RIGHT_DOOR:
			return SetVehicleParamsCarWindows(vehicleid, driver, _:newstate,
				backleft, backright
			);
		case REAR_LEFT_DOOR:
			return SetVehicleParamsCarWindows(vehicleid, driver, passenger,
				_:newstate, backright
			);
		case REAR_RIGHT_DOOR:
			return SetVehicleParamsCarWindows(vehicleid, driver, passenger,
				backleft, _:newstate
			);
	}
	return 0; // For compiler!
}
