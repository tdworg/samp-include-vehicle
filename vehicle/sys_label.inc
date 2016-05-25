/** ======================================================================== **\
	Vehicle Label system

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

#if defined _TDW_VEHICLE_S_LABEL_INC_
	#endinput
#endif
#define _TDW_VEHICLE_S_LABEL_INC_

#define TDW_MAX_LABEL_SIZE (256)

static stock
	Text3D:TDW_g_sVehicleD@LabelId[MAX_VEHICLES],
	TDW_g_sVehicleD@Buffer[MAX_VEHICLES][TDW_MAX_LABEL_SIZE char];

stock
	CreateVehicle3DTextLabel(vehicleid, const label[], color, Float:offset_x,
		Float:offset_y, Float:offset_z, Float:drawdistance, virtualworld,
		bool:testLos = false
#if _TDW_VEHICLE_STREAMER_DEFINED
		, interiorid = -1, streamdistance = STREAMER_3D_TEXT_LABEL_SD
#endif
		, label_length = sizeof label
	)
{
	if (label[0] == '\0')
		return 0;
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	if (TDW_MAX_LABEL_SIZE <= label)
		return 0;

	TDW_g_sVehicleD@LabelId[vehicleid]
	#if _TDW_VEHICLE_STREAMER_DEFINED
	= CreateDynamic3DTextLabel(label, color, offset_x, offset_y, offset_z,
		drawdistance, _, vehicleid, _:testlos, virtualworld, interiorid,
		streamdistance
	);
	#else
	= Create3DTextLabel(label, color, 0.0, 0.0, 0.0, drawdistance,
		virtualworld, _:testlos
	);
	Attach3DTextLabelToVehicle(TDW_g_sVehicleD@LabelId[vehicleid],
		vehicleid, offset_x, offset_y, offset_z
	);
	#endif

	strpack(TDW_g_sVehicleD@Buffer, label);
	return 1;
}

stock
	DestroyVehicle3DTextLabel(vehicleid)
{
	if (IsValidVehicle(vehicleid))
	{
		#if _TDW_VEHICLE_STREAMER_DEFINED
		DestroyDynamic3DTextLabel(TDW_g_sVehicleD@LabelId[vehicleid]);
		#else
		Delete3DTextLabel(TDW_g_sVehicleD@LabelId[vehicleid]);
		#endif
	}
	return 0;
}

stock
	UpdateVehicle3DTextLabel(vehicleid, const label[], bool:replace = true,
		color = -1)
{
	if (label[0] == '\0')
		return 0;
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	if (TDW_MAX_LABEL_SIZE <= label)
		return 0;

	#if _TDW_VEHICLE_STREAMER_DEFINED
	UpdateDynamic3DTextLabelText(TDW_g_sVehicleD@LabelId[vehicleid], color,
		label
	);
	#else
	Update3DTextLabelText(TDW_g_sVehicleD@LabelId[vehicleid], color, label);
	#endif

	if (replace)
		strpack(TDW_g_sVehicleD@Buffer, label);
	return 1;
}

#if !defined ShowVehicle3DTextLabel
stock
	ShowVehicle3DTextLabel(vehicleid)
{
	return UpdateVehicle3DTextLabel(vehicleid,
		TDW_g_sVehicleD@Buffer[vehicleid], false
	);
}
#endif

#if !defined HideVehicle3DTextLabel
	// If text[] is empty, the server/clients next to the text might crash!
	#define HideVehicle3DTextLabel(%0)\
		UpdateVehicle3DTextLabel(%0, !" ", false)
#endif