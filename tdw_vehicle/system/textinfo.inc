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


#if defined _inc_textinfo
	#undef _inc_textinfo
#endif

#if defined _TDW_VHSYS__TEXTINFO
	#endinput
#endif

#define _TDW_VHSYS__TEXTINFO

const MAX_CHARS = 1000 / 100 + (10*2) + 1;

static stock
	TDW_g_sVehicleId,
	TDW_g_sBuffer[MAX_CHARS + 1],
	Float:TDW_g_sOldHealth[MAX_VEHICLES] = {1000.0, ...};

#if !defined nst_AddStaticVehicle
native nst_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2) = AddStaticVehicle;
#endif

stock
	TDWVH_TI@AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2)
{
	if ((TDW_g_sVehicleId = AddStaticVehicle(modelid, spawn_x, spawn_y, spawn_z,
		z_angle, color1, color2)) != INVALID_VEHICLE_ID)
	{
		ComputeVehicleTextHealth(TDW_g_sVehicleId, TDW_g_sBuffer);
		CreateVehicle3DTextLabel(TDW_g_sVehicleId, TDW_g_sBuffer, 0xFFFFFFFF,
			0.0, 0.0, 0.0, // offset
			40.0, -1, false
		);
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif

#define AddStaticVehicle TDWVH_TI@AddStaticVehicle


#if !defined nst_AddStaticVehicleEx
native nst_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
	Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren
	) = AddStaticVehicleEx;
#endif

stock
	TDWVH_TI@AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y,
		Float:spawn_z, Float:z_angle, color1, color2, respawn_delay,
		addsiren = 0)
{
	if ((TDW_g_sVehicleId = AddStaticVehicleEx(modelid, spawn_x, spawn_y,
		spawn_z, z_angle, color1, color2, respawn_delay, addsiren)
		) != INVALID_VEHICLE_ID)
	{
		ComputeVehicleTextHealth(TDW_g_sVehicleId, TDW_g_sBuffer);
		CreateVehicle3DTextLabel(TDW_g_sVehicleId, TDW_g_sBuffer, 0xFFFFFFFF,
			0.0, 0.0, 0.0, // offset
			40.0, -1, false
		);
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif

#define AddStaticVehicleEx TDWVH_TI@AddStaticVehicleEx


#if !defined nst_CreateVehicle
native nst_CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation,
	color1, color2, respawn_delay, addsiren) = CreateVehicle;
#endif

stock
	TDWVH_TI@CreateVehicle(vehicletype, Float:x, Float:y, Float:z,
		Float:rotation, color1, color2, respawn_delay, addsiren = 0)
{
	if ((TDW_g_sVehicleId = CreateVehicle(vehicletype, x, y, z, rotation,
		color1, color2, respawn_delay, addsiren)) != INVALID_VEHICLE_ID)
	{
		ComputeVehicleTextHealth(TDW_g_sVehicleId, TDW_g_sBuffer);
		CreateVehicle3DTextLabel(TDW_g_sVehicleId, TDW_g_sBuffer, 0xFFFFFFFF,
			0.0, 0.0, 0.0, // offset
			40.0, -1, false
		);
	}
	return TDW_g_sVehicleId;
}

#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif

#define CreateVehicle TDWVH_TI@CreateVehicle


static stock
	ComputeVehicleTextHealth(vehicleid, dest[], size = sizeof dest)
{
	new Float:health;
	if (GetVehicleHealth(vehicleid, health) == 0)
		return 0;
	health = Float:clamp(_:health, _:0.0, _:1000.0);
	goto no_init;
	new buffer@green[10+1],
		buffer@red[10+1];
	no_init:
	new
		Float:r = 1000.0 - health,
		green = floatround(health / 100.0),
		red = floatround(r / 100.0),
		i;
	while (i != green) buffer@green[i++] = '|';
	buffer@green[i] = '\0';
	i = 0;
	while (i != red) buffer@red[i++] = '|';
	buffer@red[i] = '\0';
	format(dest, size, "{FF00FF}%s{FFFF00}%s", buffer@green, buffer@red);
	return 1;
}


public
	OnPlayerUpdate(playerid)
{
	static vehicleid;
	if ((vehicleid = GetPlayerVehicleID(playerid)) != 0)
	{
		static Float:health;
		GetVehicleHealth(vehicleid, health);
		TDW_g_sOldHealth[vehicleid] = health;
		ComputeVehicleTextHealth(vehicleid, TDW_g_sBuffer);
		UpdateVehicle3DTextLabel(vehicleid, TDW_g_sBuffer, true);
	}
}

