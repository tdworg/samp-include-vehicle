/* ========================================================================== *\
	Speed Radar Controller (SRC)

| Description:


| License:
	Copyright (c) 2016-2017 Double V

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

| Metadata:
	[Functions]:
		Stock:
			- CreateRadar
			- DestroyRadar
			- SetRadarMaxDistance
			- GetRadarMaxDistance
			- IsValidRadar
			- SetRadarMaxSpeed
			- GetRadarMaxSpeed
		Static:
			- Radar_GetUnusedSlot
		Public:
			- @_TDW_RADAR_TIMER
			- OnGameModeInit
			- OnFilterScriptInit
		Hooks:
			-
	[Callbacks]:
		- TDWVH_RADAR@OnGameModeInit
		- TDWVH_RADAR@OnFilterScriptInit
		- OnVehicleRadarDetect
	[Definitions]:
		- TDW_RADAR_MAX_RADARS
		- TDW_RADAR_TIMER_COUNT
		- TDW_RADAR_MAX_DISTANCE
		- TDW_RADAR_MIN_DISTANCE
		- TDW_SRC_CreateObject
		- TDW_SRC_GetObjectPos
		- TDW_SRC_GetObjectRot
	[Enumerations]:
		- E_TDW_VH_RADAR
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			- TDW_g_sRadar@Data
			- TDW_g_sRadar@Id
			- TDW_g_sSpecifier@i
			- TDW_g_sRadar@TimerName
			- TDW_g_sCallbacks
			- TDW_g_sOnVehicleRadarDetect
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	- streamer (optional)
	- foreach (optional)
\* ========================================================================== */

#if defined _inc_speed_radar_controller
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_speed_radar_controller
#endif

#if defined _TDW_VH_SYS_SRC // (S)peed (R)adar (C)ontroller
	#endinput
#endif

#define _TDW_VH_SYS_SRC

// -----------------------------------------------------------------------------
// Definitions:

#if !defined TDW_RADAR_MAX_RADARS
	#define TDW_RADAR_MAX_RADARS				(500)
#endif

#if !defined TDW_RADAR_TIMER_COUNT
	#define TDW_RADAR_TIMER_COUNT				(350)
#endif

#if !defined TDW_RADAR_MAX_DISTANCE
	#define TDW_RADAR_MAX_DISTANCE				(10.0)
#endif

#if !defined TDW_RADAR_MIN_DISTANCE
	#define TDW_RADAR_MIN_DISTANCE				(0.0)
#endif

#if defined _TDW_VH_DETECT_STREAMER
	#define TDW_SRC_CreateObject				CreateDynamicObject
	#define TDW_SRC_GetObjectPos				GetDynamicObjectPos
	#define TDW_SRC_GetObjectRot				GetDynamicObjectRot
#else
	#define TDW_SRC_CreateObject				CreateObject
	#define TDW_SRC_GetObjectPos				GetObjectPos
	#define TDW_SRC_GetObjectRot				GetObjectRot
#endif

// -----------------------------------------------------------------------------
// Enumerations:

enum E_TDW_VH_RADAR
{
	EI_RADAR_OBJECT_ID,
	EI_RADAR_TIMER_ID,
	Float:EI_RADAR_POS_X,
	Float:EI_RADAR_POS_Y,
	Float:EI_RADAR_POS_Z,
	Float:EI_RADAR_DISTANCE,
	Float:EI_RADAR_MAX_SPEED
};

// -----------------------------------------------------------------------------
// Static scope:

static stock
	TDW_g_sRadar@Data[TDW_RADAR_MAX_RADARS][E_TDW_VH_RADAR],
	TDW_g_sRadar@Id,
	TDW_g_sSpecifier@i[] = !"i",
	TDW_g_sRadar@TimerName[] = !"@_TDW_RADAR_TIMER",
	TDW_g_sCallbacks = 0,
	TDW_g_sOnVehicleRadarDetect[] = !"OnVehicleRadarDetect";
	// TDW_g_sRadar@PlayerInStream[MAX_PLAYERS char];

// -----------------------------------------------------------------------------
// Hooks:

// OnFilterScriptInit / OnGameModeInit hook
#if defined FILTERSCRIPT
	#if defined TDWVH_RADAR@OnFilterScriptInit
		forward TDWVH_RADAR@OnFilterScriptInit();
	#endif

	public OnFilterScriptInit()
	{
		if (funcidx(TDW_g_sOnVehicleRadarDetect) != -1)
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_RADAR@OnFilterScriptInit
			TDWVH_RADAR@OnFilterScriptInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit TDWVH_RADAR@OnFilterScriptInit
#else
	#if defined TDWVH_RADAR@OnGameModeInit
		forward TDWVH_RADAR@OnGameModeInit();
	#endif

	public OnGameModeInit()
	{
		if (funcidx(TDW_g_sOnVehicleRadarDetect) != -1)
			TDW_g_sCallbacks |= 1;

		#if defined TDWVH_RADAR@OnGameModeInit
			TDWVH_RADAR@OnGameModeInit();
		#endif

		return 1;
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit TDWVH_RADAR@OnGameModeInit
#endif

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>CreateRadar</summary>
<param name="radarid">The ID of the radar</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock CreateRadar(Float:x, Float:y, Float:z, Float:rX, Float:rY, Float:rZ,
	Float:distance, Float:max_speed)
{
	TDW_g_sRadar@Id = Radar_GetUnusedSlot();

	if (TDW_g_sRadar@Id != INVALID_OBJECT_ID) {
		TDW_g_sRadar@Data[TDW_g_sRadar@Id][EI_RADAR_OBJECT_ID] =
			TDW_SRC_CreateObject(18880, x, y, z, rX, rY, floatadd(rZ, 180.0));

		if (TDW_g_sCallbacks & 1) {
			TDW_g_sRadar@Data[TDW_g_sRadar@Id][EI_RADAR_MAX_SPEED] = max_speed;
			TDW_g_sRadar@Data[TDW_g_sRadar@Id][EI_RADAR_DISTANCE] = distance;
			TDW_g_sRadar@Data[TDW_g_sRadar@Id][EI_RADAR_TIMER_ID] = SetTimerEx(
				TDW_g_sRadar@TimerName, TDW_RADAR_TIMER_COUNT, false,
				TDW_g_sSpecifier@i, TDW_g_sRadar@Id);
		}
	}

	return TDW_g_sRadar@Id;
}

/** ------------------------------------------------------------------------ **\
<summary>DestroyRadar</summary>
<param name="radarid">The ID of the radar</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock DestroyRadar(radarid)
{
	if (0 == IsValidRadar(radarid))
		return 0;

	DestroyObject(objectid);
	TDW_g_sRadar@Data[radarid][EI_RADAR_OBJECT_ID] = 0;
	KillTimer(TDW_g_sRadar@Data[radarid][EI_RADAR_TIMER_ID]);

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>SetRadarMaxDistance</summary>
<param name="radarid">The ID of the radar</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetRadarMaxDistance(radarid, Float:distance)
{
	if (0 == IsValidRadar(radarid))
		return 0;
	TDW_g_sRadar@Data[radarid][EI_RADAR_DISTANCE] = clamp(distance,
		TDW_RADAR_MIN_DISTANCE, TDW_RADAR_MAX_DISTANCE);
	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>GetRadarMaxDistance</summary>
<param name="radarid">The ID of the radar</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock Float:GetRadarMaxDistance(radarid)
{
	if (0 == IsValidRadar(radarid))
		return 0;

	return TDW_g_sRadar@Data[radarid][EI_RADAR_DISTANCE];
}

/** ------------------------------------------------------------------------ **\
<summary>IsValidRadar</summary>
<param name="radarid">The ID of the radar</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock IsValidRadar(radarid)
{
	if (0 == _:(0 <= radarid <= TDW_RADAR_MAX_RADARS))
		return 0;

	static objectid;

	if (0 == (objectid = TDW_g_sRadar@Data[radarid][EI_RADAR_OBJECT_ID]))
		return 0;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>SetRadarMaxSpeed</summary>
<param name="radarid">The ID of the radar</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock SetRadarMaxSpeed(radarid, Float:speed)
{
	if (0 == IsValidRadar(radarid))
		return 0;

	TDW_g_sRadar@Data[radarid][EI_RADAR_MAX_SPEED] = speed;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>GetRadarMaxSpeed</summary>
<param name="radarid">The ID of the radar</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock Float:GetRadarMaxSpeed(radarid)
{
	if (0 == IsValidRadar(radarid))
		return 0.0;

	return TDW_g_sRadar@Data[radarid][EI_RADAR_MAX_SPEED];
}

// -----------------------------------------------------------------------------
// Internal:

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

	TDW_SRC_GetObjectPos(objectid, x, y, z);
	TDW_SRC_GetObjectRot(objectid, __, __, z_rot);

	distance = TDW_g_sRadar@Data[radarid][EI_RADAR_DISTANCE];

	x = floatadd(x, floatmul(floatadd(distance, 2.0), floatsin(floatadd(-z_rot,
		135.0), degrees)));
	y = floatadd(y, floatmul(floatadd(distance, 2.0), floatcos(floatadd(-z_rot,
		135.0), degrees)));

	#if defined _TDW_VH_DETECT_FOREACH
		foreach (new i: Player)
	#else
		for (new i = _TDW_FOREACH_MAX_PLAYERS_; --i != 0;)
	#endif
	{
		if (IsPlayerInAnyVehicle(i) == 0)
			continue;

		vehicleid  = GetPlayerVehicleID(i);
		speed = GetVehicleSpeed(vehicleid);

		if (speed >= TDW_g_sRadar@Data[radarid][EI_RADAR_MAX_SPEED])
			CallLocalFunction(TDW_g_sOnVehicleRadarDetect, !"iiif", i,
				vehicleid, radarid, speed);
	}
	#pragma tabsize 0
	TDW_g_sRadar@Data[radarid][EI_RADAR_TIMER_ID] = SetTimerEx(
		TDW_g_sRadar@TimerName, TDW_RADAR_TIMER_COUNT, false,
		TDW_g_sSpecifier@i, radarid);
	#pragma tabsize 4
	return 0;
}

static stock Radar_GetUnusedSlot()
{
	new i;

	do {
		if (TDW_g_sRadar@Data[i][EI_RADAR_OBJECT_ID] == 0)
			return i;
	} while (++i != TDW_RADAR_MAX_RADARS);

	return INVALID_OBJECT_ID;
}

// -----------------------------------------------------------------------------
// Forwards:

forward OnVehicleRadarDetect(playerid, vehicleid, radarid, Float:speed);

// -----------------------------------------------------------------------------
// Internal:

#undef TDW_SRC_CreateObject
#undef TDW_SRC_GetObjectPos
#undef TDW_SRC_GetObjectRot
