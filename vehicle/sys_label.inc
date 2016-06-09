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

#if _TDW_VEHICLE_STREAMER_DEFINED
	#define VehicleSLabelDestroy(%0) DestroyDynamic3DTextLabel(%0)
	#define VehicleSLabelUpdate(%0) UpdateDynamic3DTextLabelText(%0)
#else
	#define VehicleSLabelDestroy(%0) Delete3DTextLabel(%0)
	#define VehicleSLabelUpdate(%0) Update3DTextLabelText(%0)
#endif

static stock
	Text3D:TDW_g_sVehicleD@LabelId[MAX_VEHICLES],
	TDW_g_sVehicleD@Buffer[MAX_VEHICLES][TDW_MAX_LABEL_SIZE char];

stock
#if _TDW_VEHICLE_STREAMER_DEFINED
	CreateVehicle3DTextLabel(vehicleid, const label[], color, Float:offset_x,
		Float:offset_y, Float:offset_z, Float:drawdistance, virtualworld,
		bool:testLos = false
		, interiorid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD
		, label_length = sizeof label
	)
#else
	CreateVehicle3DTextLabel(vehicleid, const label[], color, Float:offset_x,
		Float:offset_y, Float:offset_z, Float:drawdistance, virtualworld,
		bool:testLos = false
		, label_length = sizeof label
	)
#endif
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
		VehicleSLabelDestroy(TDW_g_sVehicleD@LabelId[vehicleid]);
	}
	return 0;
}

enum e_UPD_TLABEL
{
	REPLACE_LABEL,
	NON_REPLACE_LABEL
};

stock
	UpdateVehicle3DTextLabel(vehicleid, const label[], e_UPD_TLABEL:replace =
		NON_REPLACE_LABEL, color = -1)
{
	if (label[0] == '\0')
		return 0;
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	if (TDW_MAX_LABEL_SIZE <= label)
		return 0;

	VehicleSLabelUpdate(TDW_g_sVehicleD@LabelId[vehicleid], color, label);

	if (replace)
		strpack(TDW_g_sVehicleD@Buffer, label);
	return 1;
}

#if !defined ShowVehicle3DTextLabel
stock
	ShowVehicle3DTextLabel(vehicleid)
{
	return UpdateVehicle3DTextLabel(vehicleid,
		TDW_g_sVehicleD@Buffer[vehicleid], NON_REPLACE_LABEL
	);
}
#endif

#if !defined HideVehicle3DTextLabel
	static stock const TDW_g_sVehicleS@Space[] = !" ";
	// If text[] is empty, the server/clients next to the text might crash!
	#define HideVehicle3DTextLabel(%0)\
		UpdateVehicle3DTextLabel(%0, TDW_g_sVehicleS@Space, NON_REPLACE_LABEL)
#endif

#undef VehicleSLabelDestroy
#undef VehicleSLabelUpdate