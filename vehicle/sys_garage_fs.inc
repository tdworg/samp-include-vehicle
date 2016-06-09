/** ======================================================================== **\
	Vehicle Garage system [File system]

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

/* =========================================================
 * Attention!
 * - The alpha version of the library.
 * =========================================================
 */

#if defined _TDW_VEHICLE_S_GARAGE_FS_INC_
	#endinput
#endif
#define _TDW_VEHICLE_S_GARAGE_FS_INC_

#if defined _TDW_VEHICLE_S_GARAGE_FS_INC_
	#error Use only one of the libraries: fs or sql. Include "vhs_garage.inc"
#endif

#if defined _TDW_VEHICLE_S_GARAGE_COR_INC_
static stock TDW_g_sVehicleD@Garages[TDW_MAX_GARAGES][e_TDW_VEHICLE_GARAGE];
#endif

static stock
	Garages_Garages()
{
	static const sscanf_fmt[] = !"p<|>s[24]ffffffd"; // For optimization...
	new buffer[(7 + MAX_PLAYER_NAME + 16/*float len*/ * 6) + 1],
		Float:file = fopen(!TDW_GARAGE_FILE_NAME, io_read);
	if (_:file == 0)
		return print(
			!"TDW_GARAGE: File \"" TDW_GARAGE_FILE_NAME "\" isn't exists!"
		);
	for (new i = -1; ++i < sizeof TDW_g_sVehicleD@Garages;)
	{
		fread(file, buffer);
		// parse the file..
		if (sscanf(buffer, sscanf_fmt,
			TDW_g_sVehicleD@Garages[i][ei_OwnerName],
			TDW_g_sVehicleD@Garages[i][ei_pos_x],
			TDW_g_sVehicleD@Garages[i][ei_pos_y],
			TDW_g_sVehicleD@Garages[i][ei_pos_z],
			TDW_g_sVehicleD@Garages[i][ei_rot_x],
			TDW_g_sVehicleD@Garages[i][ei_rot_y],
			TDW_g_sVehicleD@Garages[i][ei_rot_z],
			TDW_g_sVehicleD@Garages[i][ei_price]
		))
			return print(
				!"TDW_GARAGE: Parse error! File: \"" TDW_GARAGE_FILE_NAME "\""
			);
		TDW_g_sVehicleD@Garages[i][ei_door_object_id] = TDW_CreateDObject(
			TDW_GARAGE_OBJECT_DOOR_ID, TDW_g_sVehicleD@Garages[i][ei_pos_x],
			TDW_g_sVehicleD@Garages[i][ei_pos_y],
			TDW_g_sVehicleD@Garages[i][ei_pos_z],
			TDW_g_sVehicleD@Garages[i][ei_rot_x],
			TDW_g_sVehicleD@Garages[i][ei_rot_y],
			TDW_g_sVehicleD@Garages[i][ei_rot_z]
		);
		Garage_Update(i);
	}
	fclose(file);
	return 0;
}

stock
	Garage_Update(garageid)
{
	static const
		fmt_str_owned[] = TDW_GARAGE_LOCALE_OWNED,
		fmt_str_nowned[] = TDW_GARAGE_LOCALE_NOWNED;
	const
		size_owned = sizeof fmt_str_owned + (-2 + 11 /* id */) +
			(-2 + MAX_PLAYER_NAME /* player name */),
		size_nowned = sizeof fmt_str_nowned + (-2 + 11 /* price */);
	#if size_owned > size_nowned
		const size = size_owned;
	#else
		const size = size_nowned;
	#endif

	new buffer[size];
	if (TDW_g_sVehicleD@Garages[garageid][ei_OwnerName][0] == '\0')
	{
		format(buffer, sizeof buffer, fmt_str_nowned,
			TDW_g_sVehicleD@Garages[garageid][ei_price]
		);
	}
	else
	{
		format(buffer, sizeof buffer, fmt_str_owned,
			garageid, TDW_g_sVehicleD@Garages[garageid][ei_OwnerName]
		);
	}
	TDW_DestroyDLabel(TDW_g_sVehicleD@Garages[garageid][ei_label_id]);
#if _TDW_VEHICLE_STREAMER_DEFINED
	TDW_g_sVehicleD@Garages[garageid][ei_label_id] = CreateDynamic3DTextLabel(
		buffer, 0xFFFFFFFF,
		TDW_g_sVehicleD@Garages[garageid][ei_pos_x],
		TDW_g_sVehicleD@Garages[garageid][ei_pos_y],
		TDW_g_sVehicleD@Garages[garageid][ei_pos_z],
		20.0, _, _, 1, 0, _, _, _);
#else
	TDW_g_sVehicleD@Garages[garageid][ei_label_id] = Create3DTextLabel(
		buffer, 0xFFFFFFFF,
		TDW_g_sVehicleD@Garages[garageid][ei_pos_x],
		TDW_g_sVehicleD@Garages[garageid][ei_pos_y],
		TDW_g_sVehicleD@Garages[garageid][ei_pos_z],
		20.0, 0, 1);
#endif
	return 1;
}

// If you don't want to use the functions(publics), add this to your code(before
// a_samp):
// #define _TDW_VEHICLE_NOT_USE_PUBLICS

#if defined _TDW_VEHICLE_NOT_USE_PUBLICS
	public
		OnGameModeInit()
	{
		Garages_Garages();
		#if defined TDWVH@OnGameModeInit_SGRS
			return TDWVH@OnGameModeInit_SGRS();
		#else
			return 1;
		#endif
	}
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit(%0) TDWVH@OnGameModeInit_SGRS(%0)

	#if defined TDWVH@OnGameModeInit_SGRS
		forward TDWVH@OnGameModeInit_SGRS();
	#endif

	public
		OnFilterScriptInit()
	{
		Garages_Garages();
		#if defined TDWVH@OnFilterScriptInit_SGRS
			return TDWVH@OnFilterScriptInit_SGRS();
		#else
			return 1;
		#endif
	}
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit(%0) TDWVH@OnFilterScriptInit_SGRS(%0)

	#if defined TDWVH@OnFilterScriptInit_SGRS
		forward TDWVH@OnFilterScriptInit_SGRS();
	#endif
#endif