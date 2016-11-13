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


#if !defined TDW_ENGINE_DEFAULT_FUEL
	#define TDW_ENGINE_DEFAULT_FUEL (1000.0) // Liter
#else
	#assert (0.0 <= TDW_ENGINE_DEFAULT_FUEL < FLOAT_INFINITY)
#endif

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
	Float:TDW_g_sFuel@Vehicle[MAX_VEHICLES] = {TDW_ENGINE_DEFAULT_FUEL, ...},
	TDW_g_sLastMileage@Vehicle[MAX_VEHICLES] = {0,...},
	TDW_g_sVehicleId;



stock
	StartVehicleEngine(vehicleid)
{
	if (TDW_g_sIsEngineRunning@Vehicle{vehicleid})
		return 0;
	if (_:(0 < TDW_g_sFuel@Vehicle[vehicleid] < FLOAT_INFINITY) == 0)
	{
		#if defined OnVehicleEngineStateChange
			OnVehicleEngineStateChange(vehicleid, ENGINE_STATE_FAILED);
		#endif

		#if defined OnVehicleEngineStartFailed
			OnVehicleEngineStartFailed(vehicleid);
		#endif

		return 0;
	}

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


stock
	StopVehicleEngine(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if (modelid == 0)
		return 0;
	if (_:TDW_g_sIsEngineRunning@Vehicle{vehicleid} == 0)
		return 0;
	if (GetModelStaticType(modelid) == BIKE)
		return 0;

	new timerid = TDW_g_sTimerId@Vehicle[vehicleid];

	if (timerid != -1)
		KillTimer(timerid);

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


// Reserve AddStaticVehicle
#if !defined nst_AddStaticVehicle
native nst_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2) = AddStaticVehicle;
#endif

stock
	TDWVH_EH@AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2)
{
	if ((TDW_g_sVehicleId = AddStaticVehicle(modelid, spawn_x, spawn_y, spawn_z,
		z_angle, color1, color2)) != INVALID_VEHICLE_ID)
	{
		if (GetModelStaticType(modelid) == BIKE)
		{
			TDW_g_sFuel@Vehicle[TDW_g_sVehicleId] = FLOAT_INFINITY;
		}
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif

#define AddStaticVehicle TDWVH_EH@AddStaticVehicle


// Reserve AddStaticVehicleEx
#if !defined nst_AddStaticVehicleEx
native nst_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren
	) = AddStaticVehicleEx;
#endif

stock
	TDWVH_EH@AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2, respawn_delay,
		addsiren = 0)
{
	if ((TDW_g_sVehicleId = AddStaticVehicleEx(modelid, spawn_x, spawn_y,
		spawn_z, z_angle, color1, color2, respawn_delay, addsiren)
		) != INVALID_VEHICLE_ID)
	{
		if (GetModelStaticType(modelid) == BIKE)
		{
			TDW_g_sFuel@Vehicle[TDW_g_sVehicleId] = FLOAT_INFINITY;
		}
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif

#define AddStaticVehicleEx TDWVH_EH@AddStaticVehicleEx


// Reserve CreateVehicle
#if !defined nst_CreateVehicle
native nst_CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation,
	color1, color2, respawn_delay, addsiren) = CreateVehicle;
#endif

stock
	TDWVH_EH@CreateVehicle(vehicletype, Float:x, Float:y, Float:z,
		Float:rotation, color1, color2, respawn_delay, addsiren = 0)
{
	if ((TDW_g_sVehicleId = CreateVehicle(vehicletype, x, y, z, rotation,
		color1, color2, respawn_delay, addsiren)) != INVALID_VEHICLE_ID)
	{
		if (GetModelStaticType(modelid) == BIKE)
		{
			TDW_g_sFuel@Vehicle[TDW_g_sVehicleId] = FLOAT_INFINITY;
		}
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif

#define CreateVehicle TDWVH_EH@CreateVehicle


// Hooked functions
public
	OnVehicleMileageUpdate(vehicleid)
{
	static Float:fuel;

	if ((fuel = TDW_g_sFuel@Vehicle[vehicleid]) != FLOAT_INFINITY)
	{
		if (_:TDW_g_sIsEngineRunning@Vehicle{vehicleid} == 0)
			return 0;

		if (fuel <= 0.0)
			StopVehicleEngine(vehicleid);
		else
		{
			static mile;

			if ((mile = GetVehicleMileage(vehicleid)) >
				TDW_g_sLastMileage@Vehicle[vehicleid])
			{
				#if defined OnVehicleFuelChange
					OnVehicleFuelChange(vehicleid, (
						TDW_g_sFuel@Vehicle[vehicleid] -= (mile -
						TDW_g_sLastMileage@Vehicle[vehicleid]) *
						TDW_ENGINE_FLOAT_SUB)
					);
				#else
					TDW_g_sFuel@Vehicle[vehicleid] -= (mile -
						TDW_g_sLastMileage@Vehicle[vehicleid]) *
						TDW_ENGINE_FLOAT_SUB;
				#endif
				TDW_g_sLastMileage@Vehicle[vehicleid] = mile;
			}
			else
			{
				TDW_g_sFuel@Vehicle[vehicleid] -= TDW_ENGINE_FLOAT_SUB;
			}
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
	OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if (GetModelStaticType(GetVehicleModel(vehicleid)) == BIKE)
		{
			new engine, lights, alarm, doors, bonnet, boot, objective;

			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors,
				bonnet, boot, objective
			);

			SetVehicleParamsEx(vehicleid, 1, lights, alarm,
				doors, bonnet, boot, objective
			);
		}
	}
	return
	#if defined TDWVHE@OnPlayerStateChange
		TDWVHE@OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		1;
	#endif
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange TDWVHE@OnPlayerStateChange

#if defined TDWVHE@OnPlayerStateChange
	forward TDWVHE@OnPlayerStateChange(playerid, newstate, oldstate);
#endif


public
	OnGameModeInit()
{
	ManualVehicleEngineAndLights();
	return
	#if defined TDWVHE@OnGameModeInit
		TDWVHE@OnGameModeInit();
	#else
		1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit TDWVHE@OnGameModeInit

#if defined TDWVHE@OnGameModeInit
	forward TDWVHE@OnGameModeInit();
#endif


// The timer to start the vehicle's engine
@_TDW_VEHICLE_ENGINE(vehicleid);
@_TDW_VEHICLE_ENGINE(vehicleid)
{
	new Float:health;

	if (GetVehicleHealth(vehicleid, health) == 0)
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


// Access functions
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
	SetVehicleFuel(vehicleid, Float:amount)
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	TDW_g_sFuel@Vehicle[vehicleid] = amount;
	return 1;
}


// Declare callbacks
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

#if defined OnVehicleFuelChange
forward OnVehicleFuelChange(vehicleid, Float:amount);
#endif
