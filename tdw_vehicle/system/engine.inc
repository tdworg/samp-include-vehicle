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

enum
	E_ENGINE_TDW_CALLBACKS (<<= 1)
{
	EI_CB_EngineStateChange = 1, // OnVehicleEngineStateChange 1
	EI_CB_EngineStartFailed, // OnVehicleEngineStartFailed 2
	EI_CB_EngineStopped, // OnVehicleEngineStopped 3
	EI_CB_FuelChange, // OnVehicleFuelChange 4
	EI_CB_EngineStarted // OnVehicleEngineStarted 5
};


static stock
	TDW_g_sTimerId@Vehicle[MAX_VEHICLES] = {-1, ...},
	bool:TDW_g_sIsEngineRunning@Vehicle[MAX_VEHICLES char] = {false, ...},
	Float:TDW_g_sFuel@Vehicle[MAX_VEHICLES] = {TDW_ENGINE_DEFAULT_FUEL, ...},
	TDW_g_sLastMileage@Vehicle[MAX_VEHICLES] = {0,...},
	TDW_g_sVehicleId,
	E_ENGINE_TDW_CALLBACKS:TDW_g_sCallbacks,
	TDW_g_sOnVEngineStateChange[] = !"OnVehicleEngineStateChange",
	TDW_g_sOnVEngineStartFailed[] = !"OnVehicleEngineStartFailed",
	TDW_g_sOnVEngineStopped[] = !"OnVehicleEngineStopped",
	TDW_g_sOnVFuelChange[] = !"OnVehicleFuelChange",
	TDW_g_sOnVEngineStarted[] = !"OnVehicleEngineStarted",
	TDW_g_sSpecifier@ii[] = !"ii",
	TDW_g_sSpecifier@if[] = !"if",
	TDW_g_sSpecifier@i[] = !"i";


#if defined FILTERSCRIPT
	public
		OnFilterScriptInit()
	{
		ManualVehicleEngineAndLights();

		if (funcidx(TDW_g_sOnVEngineStateChange) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_EngineStateChange;
		}
		if (funcidx(TDW_g_sOnVEngineStartFailed) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_EngineStartFailed;
		}
		if (funcidx(TDW_g_sOnVEngineStopped) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_EngineStopped;
		}
		if (funcidx(TDW_g_sOnVFuelChange) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_FuelChange;
		}
		if (funcidx(TDW_g_sOnVEngineStarted) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_EngineStarted;
		}

		return
		#if defined TDWVHE@OnFilterScriptInit
			TDWVHE@OnFilterScriptInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVHE@OnFilterScriptInit

	#if defined TDWVHE@OnFilterScriptInit
		forward TDWVHE@OnFilterScriptInit();
	#endif
#else
	public
		OnGameModeInit()
	{
		ManualVehicleEngineAndLights();

		if (funcidx(TDW_g_sOnVEngineStateChange) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_EngineStateChange;
		}
		if (funcidx(TDW_g_sOnVEngineStartFailed) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_EngineStartFailed;
		}
		if (funcidx(TDW_g_sOnVEngineStopped) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_EngineStopped;
		}
		if (funcidx(TDW_g_sOnVFuelChange) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_FuelChange;
		}
		if (funcidx(TDW_g_sOnVEngineStarted) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_EngineStarted;
		}

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
#endif



stock
	StartVehicleEngine(vehicleid)
{
	if (TDW_g_sIsEngineRunning@Vehicle{vehicleid})
		return 0;
	if (_:(0 < TDW_g_sFuel@Vehicle[vehicleid] < FLOAT_INFINITY) == 0)
	{
		if (TDW_g_sCallbacks & EI_CB_EngineStateChange)
		{
			CallLocalFunction(TDW_g_sOnVEngineStateChange, TDW_g_sSpecifier@ii,
				vehicleid, _:ENGINE_STATE_FAILED
			);
		}

		if (TDW_g_sCallbacks & EI_CB_EngineStartFailed)
		{
			CallLocalFunction(TDW_g_sOnVEngineStartFailed, TDW_g_sSpecifier@i,
				vehicleid
			);
		}

		return 0;
	}

	#if defined TDW_ENGINE_USE_TIMER
		if (TDW_g_sTimerId@Vehicle[vehicleid] != -1)
			return 0;
		TDW_g_sTimerId@Vehicle[vehicleid] = SetTimerEx(!"@_TDW_VEHICLE_ENGINE",
			TDW_ENGINE_TIMER_INTERVAL, false, TDW_g_sSpecifier@i, vehicleid
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
	if (GetModelStaticType(modelid) == BIKE) // Bike is not a MOTORBIKE
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

	if (TDW_g_sCallbacks & EI_CB_EngineStateChange)
	{
		CallLocalFunction(TDW_g_sOnVEngineStateChange, TDW_g_sSpecifier@ii,
			vehicleid, _:ENGINE_STATE_STOPPED
		);
	}

	if (TDW_g_sCallbacks & EI_CB_EngineStopped)
	{
		CallLocalFunction(TDW_g_sOnVEngineStopped, TDW_g_sSpecifier@i,
			vehicleid
		);
	}

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
		if (GetModelStaticType(vehicletype) == BIKE)
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
		{
			StopVehicleEngine(vehicleid);
			if (TDW_g_sCallbacks & EI_CB_FuelChange)
			{
				CallLocalFunction(TDW_g_sOnVFuelChange, TDW_g_sSpecifier@if,
					vehicleid, 0.0
				);
			}
			// If the fuel is null, sets a new value in order to skip that part
			// of the code.
			TDW_g_sFuel@Vehicle[vehicleid] = FLOAT_INFINITY;
		}
		else
		{
			static mile;

			if ((mile = GetVehicleMileage(vehicleid)) >
				TDW_g_sLastMileage@Vehicle[vehicleid])
			{
				TDW_g_sFuel@Vehicle[vehicleid] -= (mile -
					TDW_g_sLastMileage@Vehicle[vehicleid]) *
					TDW_ENGINE_FLOAT_SUB;

				if (TDW_g_sCallbacks & EI_CB_FuelChange)
				{
					CallLocalFunction(TDW_g_sOnVFuelChange, TDW_g_sSpecifier@if,
						vehicleid, TDW_g_sFuel@Vehicle[vehicleid]
					);
				}

				TDW_g_sLastMileage@Vehicle[vehicleid] = mile;
			}
			else
			{
				// If the vehicle is standing stil.
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
		if (TDW_g_sCallbacks & EI_CB_EngineStateChange)
		{
			CallLocalFunction(TDW_g_sOnVEngineStateChange, TDW_g_sSpecifier@ii,
				vehicleid, _:ENGINE_STATE_FAILED
			);
		}

		if (TDW_g_sCallbacks & EI_CB_EngineStartFailed)
		{
			CallLocalFunction(TDW_g_sOnVEngineStartFailed, TDW_g_sSpecifier@i,
				vehicleid
			);
		}

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

		if (TDW_g_sCallbacks & EI_CB_EngineStateChange)
		{
			CallLocalFunction(TDW_g_sOnVEngineStateChange, TDW_g_sSpecifier@ii,
				vehicleid, _:ENGINE_STATE_STARTED
			);
		}

		if (TDW_g_sCallbacks & EI_CB_EngineStarted)
		{
			CallLocalFunction(TDW_g_sOnVEngineStarted, TDW_g_sSpecifier@i,
				vehicleid
			);
		}

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
forward OnVehicleEngineStateChange(vehicleid, E_TDW_ENGINE_STATE:engine);
forward OnVehicleEngineStartFailed(vehicleid);
forward OnVehicleEngineStarted(vehicleid);
forward OnVehicleEngineStopped(vehicleid);
forward OnVehicleFuelChange(vehicleid, Float:amount);
