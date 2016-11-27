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


#if defined _inc_radar
	#undef _inc_radar
#endif

#if defined _TDW_VHLIB__RADAR
	#endinput
#endif

#define _TDW_VHLIB__RADAR


// -----------------------------------------------------------------------------
// Default constant
// -----------------------------------------------------------------------------

#if !defined TDW_RADAR_MAX_RADARS
	#define TDW_RADAR_MAX_RADARS (500)
#endif

#if !defined TDW_RADAR_TIMER_COUNT
	#define TDW_RADAR_TIMER_COUNT (350)
#endif

#if !defined TDW_RADAR_MAX_DISTANCE
	#define TDW_RADAR_MAX_DISTANCE (10.0)
#endif

#if !defined TDW_RADAR_MIN_DISTANCE
	#define TDW_RADAR_MIN_DISTANCE (0.0)
#endif

#if _TDW_VEHICLE_STREAMER_DEFINED
	#define RRCreateObject CreateDynamicObject
	#define RRGetObjectPos GetDynamicObjectPos
	#define RRGetObjectRot GetDynamicObjectRot
#else
	#define RRCreateObject CreateObject
	#define RRGetObjectPos GetObjectPos
	#define RRGetObjectRot GetObjectRot
#endif

enum
	E_TDW_RADAR
{
	EI_RADAR_OBJECT_ID,
	EI_RADAR_TIMER_ID,
	Float:EI_RADAR_POS_X,
	Float:EI_RADAR_POS_Y,
	Float:EI_RADAR_POS_Z,
	Float:EI_RADAR_DISTANCE,
	Float:EI_RADAR_MAX_SPEED
};

enum
	E_TDW_RADAR_CALLBACKS (<<= 1)
{
	EI_CB_OnVehicleRadarDetect = 1
};

// -----------------------------------------------------------------------------
// Vars
// -----------------------------------------------------------------------------

static stock
	TDW_g_sRadar@Data[TDW_RADAR_MAX_RADARS][E_TDW_RADAR],
	TDW_g_sRadar@Id,
	TDW_g_sSpecifier@i[] = !"i",
	TDW_g_sRadar@TimerName[] = !"@_TDW_RADAR_TIMER",
	E_TDW_RADAR_CALLBACKS:TDW_g_sCallbacks = E_TDW_RADAR_CALLBACKS:0,
	TDW_g_sOnVehicleRadarDetect[] = !"OnVehicleRadarDetect",
	TDW_g_sRadar@PlayerInStream[MAX_PLAYERS char];


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

stock
	CreateRadar(Float:x, Float:y, Float:z, Float:rX, Float:rY, Float:rZ,
		Float:distance, Float:max_speed)
{
	TDW_g_sRadar@Id = Radar_GetUnusedSlot();
	if (TDW_g_sRadar@Id != INVALID_OBJECT_ID)
	{
		TDW_g_sRadar@Data[TDW_g_sRadar@Id][EI_RADAR_OBJECT_ID] = RRCreateObject(
			18880, x, y, z, rX, rY, rZ + 180.0
		);
		if (TDW_g_sCallbacks & EI_CB_OnVehicleRadarDetect)
		{
			TDW_g_sRadar@Data[TDW_g_sRadar@Id][EI_RADAR_MAX_SPEED] = max_speed;
			TDW_g_sRadar@Data[TDW_g_sRadar@Id][EI_RADAR_DISTANCE] = distance;
			TDW_g_sRadar@Data[TDW_g_sRadar@Id][EI_RADAR_TIMER_ID] = SetTimerEx(
				TDW_g_sRadar@TimerName, TDW_RADAR_TIMER_COUNT, false,
				TDW_g_sSpecifier@i, TDW_g_sRadar@Id
			);
		}
	}
	return TDW_g_sRadar@Id;
}


stock
	DestroyRadar(radarid)
{
	if (IsValidRadar(radarid) == 0)
		return 0;
	DestroyObject(objectid);
	TDW_g_sRadar@Data[radarid][EI_RADAR_OBJECT_ID] = 0;
	KillTimer(TDW_g_sRadar@Data[radarid][EI_RADAR_TIMER_ID]);
	return 1;
}


stock
	SetRadarMaxDistance(radarid, Float:distance)
{
	if (IsValidRadar(radarid) == 0)
		return 0;
	TDW_g_sRadar@Data[radarid][EI_RADAR_DISTANCE] = clamp(distance,
		TDW_RADAR_MIN_DISTANCE,
		TDW_RADAR_MAX_DISTANCE
	);
	return 1;
}


stock
	Float:GetRadarMaxDistance(radarid)
{
	if (IsValidRadar(radarid) == 0)
		return 0;
	return TDW_g_sRadar@Data[radarid][EI_RADAR_DISTANCE];
}


stock
	IsValidRadar(radarid)
{
	if (_:(0 <= radarid <= TDW_RADAR_MAX_RADARS) == 0)
		return 0;
	static objectid;
	if ((objectid = TDW_g_sRadar@Data[radarid][EI_RADAR_OBJECT_ID]) == 0)
		return 0;
	return 1;
}


stock
	SetRadarMaxSpeed(radarid, Float:speed)
{
	if (IsValidRadar(radarid) == 0)
		return 0;
	TDW_g_sRadar@Data[radarid][EI_RADAR_MAX_SPEED] = speed;
	return 1;
}


stock
	Float:GetRadarMaxSpeed(radarid)
{
	if (IsValidRadar(radarid) == 0)
		return 0;
	return TDW_g_sRadar@Data[radarid][EI_RADAR_MAX_SPEED];
}


stock
	IsPlayerInAnyVehicleInRadarArea(playerid)
{
	return TDW_g_sRadar@PlayerInStream{playerid};
}

// -----------------------------------------------------------------------------
// Internal
// -----------------------------------------------------------------------------

@_TDW_RADAR_TIMER(radarid);
@_TDW_RADAR_TIMER(radarid)
{
	static
		Float:x,
		Float:y,
		Float:z,
		objectid,
		Float:__, // It contains a useless value.
		Float:z_rot,
		Float:speed,
		Float:distance,
		vehicleid;

	objectid = TDW_g_sRadar@Data[radarid][EI_RADAR_OBJECT_ID];

	RRGetObjectPos(objectid, x, y, z);
	RRGetObjectRot(objectid, __, __, z_rot);

	distance = TDW_g_sRadar@Data[radarid][EI_RADAR_DISTANCE];

	x += (distance + 2.0) * (floatsin(-z_rot + 90.0 + 45.0, degrees));
	y += (distance + 2.0) * (floatcos(-z_rot + 90.0 + 45.0, degrees));

	foreach (new i: Player)
	{
		if (IsPlayerInAnyVehicle(i) == 0)
			continue;

		if (IsPlayerInRangeOfPoint(i, distance, x, y, z) == 0)
		{
			if (_:TDW_g_sRadar@PlayerInStream{i} != 0)
				TDW_g_sRadar@PlayerInStream{i} = false;
			continue;
		}

		vehicleid  = GetPlayerVehicleID(i);
		speed = GetVehicleSpeed(vehicleid);

		if (_:TDW_g_sRadar@PlayerInStream{i} == 0)
			TDW_g_sRadar@PlayerInStream{i} = true;

		if (speed >= TDW_g_sRadar@Data[radarid][EI_RADAR_MAX_SPEED])
		{
			CallLocalFunction(TDW_g_sOnVehicleRadarDetect, !"iiif", i,
				vehicleid, radarid, speed
			);
		}
	}

	TDW_g_sRadar@Data[radarid][EI_RADAR_TIMER_ID] = SetTimerEx(
		TDW_g_sRadar@TimerName, TDW_RADAR_TIMER_COUNT, false,
		TDW_g_sSpecifier@i, radarid
	);

	return 0;
}


static stock
	Radar_GetUnusedSlot()
{
	new i;
	do
	{
		if (TDW_g_sRadar@Data[i][EI_RADAR_OBJECT_ID] != 0)
			continue;
		return i;
	}
	while (++i != TDW_RADAR_MAX_RADARS);
	return INVALID_OBJECT_ID;
}


#if defined FILTERSCRIPT
	public
		OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnVehicleRadarDetect) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnVehicleRadarDetect;
		}

		return
		#if defined TDWVHR@OnFilterScriptInit
			TDWVHR@OnFilterScriptInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVHR@OnFilterScriptInit

	#if defined TDWVHR@OnFilterScriptInit
		forward TDWVHR@OnFilterScriptInit();
	#endif
#else
	public
		OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnVehicleRadarDetect) != -1)
		{
			TDW_g_sCallbacks |= EI_CB_OnVehicleRadarDetect;
		}

		return
		#if defined TDWVHR@OnGameModeInit
			TDWVHR@OnGameModeInit();
		#else
			1;
		#endif
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVHR@OnGameModeInit

	#if defined TDWVHR@OnGameModeInit
		forward TDWVHR@OnGameModeInit();
	#endif
#endif


forward OnVehicleRadarDetect(playerid, vehicleid, radarid, Float:speed);
