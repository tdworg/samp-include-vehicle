/** ======================================================================== **\
	Vehicle Engine system

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


#if defined _inc_engine
	#undef _inc_engine
#endif

#if defined _TDW_VHSYS__ENGINE
	#endinput
#endif

#define _TDW_VHSYS__ENGINE


#if !defined TDW_ENGINE_TIMER_INTERVAL
	#define TDW_ENGINE_TIMER_INTERVAL (1000)
#endif

#if !defined TDW_ENGINE_FLOAT_SUB
	#define TDW_ENGINE_FLOAT_SUB (0.125)
#endif

enum
	E_TDW_ENGINE_STATE
{
	ENGINE_STATE_NONE,
	ENGINE_STATE_FAILED,
	ENGINE_STATE_STARTED,
	ENGINE_STATE_STOPPED
};


static stock
	TDW_g_sTimerId@Vehicle[MAX_VEHICLES] = {-1, ...},
	bool:TDW_g_sIsEngineRunning@Vehicle[MAX_VEHICLES char] = {false, ...},
	Float:TDW_g_sFuel@Vehicle[MAX_VEHICLES] = {1000.0, ...},
	TDW_g_sLastMileage@Vehicle[MAX_VEHICLES] = {0,...};


stock
	StartVehicleEngine(vehicleid)
{
	#if defined TDW_ENGINE_USE_TIMER
		if (TDW_g_sTimerId@Vehicle[vehicleid] != -1)
			return 0;
		TDW_g_sTimerId@Vehicle[vehicleid] = SetTimerEx(!"@_TDW_VEHICLE_ENGINE",
			TDW_ENGINE_TIMER_INTERVAL, false, !"i", vehicleid
		);
	#else
		@_TDW_VEHICLE_ENGINE(vehicleid);
	#endif
	return 1;
}


@_TDW_VEHICLE_ENGINE(vehicleid);
@_TDW_VEHICLE_ENGINE(vehicleid)
{
	new Float:health;

	if (GetVehicleHealth(vehicleid, health) == 0)
		return 0;
	if (TDW_g_sIsEngineRunning@Vehicle{vehicleid})
		return 0;

	new percent = floatround(health, floatround_round) / 10;

	if (random(100 + 1) >= percent)
	{
		#if defined OnVehicleEngineStateChange
			OnVehicleEngineStateChange(vehicleid, ENGINE_STATE_FAILED);
		#endif
		#if defined OnVehicleEngineStartFailed
			OnVehicleEngineStartFailed(vehicleid);
		#endif

		TDW_g_sIsEngineRunning@Vehicle{vehicleid} = false;
	}
	else
	{
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet,
			boot, objective
		);
		SetVehicleParamsEx(vehicleid, true, lights, alarm, doors,
			bonnet, boot, objective
		);

		#if defined OnVehicleEngineStateChange
			OnVehicleEngineStateChange(vehicleid, ENGINE_STATE_STARTED);
		#endif
		#if defined OnVehicleEngineStarted
			OnVehicleEngineStarted(vehicleid);
		#endif

		TDW_g_sIsEngineRunning@Vehicle{vehicleid} = true;
	}

	TDW_g_sTimerId@Vehicle[vehicleid] = -1;

	return 1;
}


stock
	StopVehicleEngine(vehicleid)
{
	new timerid = TDW_g_sTimerId@Vehicle[vehicleid];

	if (timerid != -1)
		KillTimer(timerid);

	if (_:TDW_g_sIsEngineRunning@Vehicle{vehicleid} == 0)
		return 0;

	new engine, lights, alarm, doors, bonnet, boot, objective;

	if (GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet,
		boot, objective) == 0)
		return 0;

	SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors,
		bonnet, boot, objective
	);

	TDW_g_sIsEngineRunning@Vehicle{vehicleid} = false;

	#if defined OnVehicleEngineStateChange
		OnVehicleEngineStateChange(vehicleid, ENGINE_STATE_STOPPED);
	#endif
	#if defined OnVehicleEngineStopped
		OnVehicleEngineStopped(vehicleid);
	#endif

	return 1;
}


stock
	IsVehicleEngineRunning(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	return TDW_g_sIsEngineRunning@Vehicle{vehicleid};
}

stock
	GetVehicleFuel(vehicleid)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	return TDW_g_sFuel@Vehicle[vehicleid];
}

stock
	SetVehicleFuel(vehicleid, amount)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	TDW_g_sFuel@Vehicle[vehicleid] = amount;
	return 1;
}


public
	OnVehicleMileageUpdate(vehicleid)
{
	if (TDW_g_sFuel@Vehicle[vehicleid] <= 0.0)
	{
		StopVehicleEngine(vehicleid);
	}
	else
	{
		static mile;
		if ((mile = GetVehicleMileage(vehicleid)) >
			TDW_g_sLastMileage@Vehicle[vehicleid])
		{
			TDW_g_sLastMileage@Vehicle[vehicleid] = mile;
			TDW_g_sFuel@Vehicle[vehicleid] -= TDW_ENGINE_FLOAT_SUB;
		}
	}
	return
	#if defined TDWVHE@OnVehicleMileageUpdate
		TDWVHE@OnVehicleMileageUpdate(vehicleid);
	#else
		1;
	#endif
}

#if defined _ALS_OnVehicleMileageUpdate
	#undef OnVehicleMileageUpdate
#else
	#define _ALS_OnVehicleMileageUpdate
#endif

#define OnVehicleMileageUpdate TDWVHE@OnVehicleMileageUpdate

#if defined TDWVHE@OnVehicleMileageUpdate
	forward TDWVHE@OnVehicleMileageUpdate(vehicleid);
#endif


public
	OnVehicleSpawn(vehicleid)
{
	if (TDW_g_sFuel@Vehicle[vehicleid] != 0.0)
	{
		StopVehicleEngine(vehicleid);
	}
	return
	#if defined TDWVHE@OnVehicleSpawn
		TDWVHE@OnVehicleSpawn(vehicleid);
	#else
		1;
	#endif
}

#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif

#define OnVehicleSpawn TDWVHE@OnVehicleSpawn

#if defined TDWVHE@OnVehicleSpawn
	forward TDWVHE@OnVehicleSpawn(vehicleid);
#endif

#if defined OnVehicleEngineStateChange
forward OnVehicleEngineStateChange(vehicleid, E_TDW_ENGINE_STATE:engine);
#endif

#if defined OnVehicleEngineStartFailed
forward OnVehicleEngineStartFailed(vehicleid);
#endif

#if defined OnVehicleEngineStarted
forward OnVehicleEngineStarted(vehicleid);
#endif

#if defined OnVehicleEngineStopped
forward OnVehicleEngineStopped(vehicleid);
#endif
