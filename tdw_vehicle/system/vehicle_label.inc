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


#if defined _inc_vehicle_label
	#undef _inc_vehicle_label
#endif

#if defined _TDW_VEHICLE_S_LABEL
	#endinput
#endif

#define _TDW_VEHICLE_S_LABEL


#if _TDW_VEHICLE_STREAMER_DEFINED
	#define TDW_VEHICLE_DESTROY_LABEL(%0) DestroyDynamic3DTextLabel(%0)
	#define TDW_VEHICLE_UPDATE_LABEL(%0) UpdateDynamic3DTextLabel(%0)
#else
	#define TDW_VEHICLE_DESTROY_LABEL(%0) Delete3DTextLabel(%0)
	#define TDW_VEHICLE_UPDATE_LABEL(%0) Update3DTextLabelText(%0)
#endif

#if !defined MAX_VEHICLE_LABEL_SIZE
	#define MAX_VEHICLE_LABEL_SIZE (144)
#endif


static stock
	Text3D:TDW_g_sVDynamic@LabelIds[MAX_VEHICLES],
	TDW_g_sVDynamic@LabelTexts[MAX_VEHICLES][MAX_VEHICLE_LABEL_SIZE char];


stock
#if _TDW_VEHICLE_STREAMER_DEFINED
	CreateVehicle3DTextLabel(vehicleid, const label[], color, Float:offset_x,
		Float:offset_y, Float:offset_z, Float:drawdistance, virtualworld,
		bool:testLos = false, interiorid = -1,
		Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD,
		label_length = sizeof label
	)
#else
	CreateVehicle3DTextLabel(vehicleid, const label[], color, Float:offset_x,
		Float:offset_y, Float:offset_z, Float:drawdistance, virtualworld,
		bool:testLos = false, label_length = sizeof label
	)
#endif
{
	if (label[0] == '\0')
		return 0;
	if (IsValidVehicle(vehicleid) == 0)
		return INVALID_VEHICLE_ID;
	if (MAX_VEHICLE_LABEL_SIZE <= label)
		return 0;
	TDW_g_sVDynamic@LabelIds[vehicleid]
#if _TDW_VEHICLE_STREAMER_DEFINED
	= CreateDynamic3DTextLabel(label, color, offset_x, offset_y, offset_z,
		drawdistance, _, vehicleid, _:testlos, virtualworld, interiorid,
		streamdistance
	);
#else
	= Create3DTextLabel(label, color, 0.0, 0.0, 0.0, drawdistance,
		virtualworld, _:testlos
	);
	Attach3DTextLabelToVehicle(TDW_g_sVDynamic@LabelIds[vehicleid],
		vehicleid, offset_x, offset_y, offset_z
	);
#endif
	strpack(TDW_g_sVDynamic@LabelTexts[vehicleid], label, label_length);
	return 1;
}


stock
	DestroyVehicle3DTextLabel(vehicleid)
{
	return (IsValidVehicle(vehicleid)
		? TDW_VEHICLE_DESTROY_LABEL(TDW_g_sVDynamic@LabelIds[vehicleid])
		: INVALID_VEHICLE_ID
	);
}


stock
	UpdateVehicle3DTextLabel(vehicleid, const label[], bool:replace = false,
		color = -1)
{
	if (label[0] == '\0')
		return 0;
	if (IsValidVehicle(vehicleid) == 0)
		return INVALID_VEHICLE_ID;
	if (MAX_VEHICLE_LABEL_SIZE <= label)
		return 0;
	TDW_VEHICLE_UPDATE_LABEL(TDW_g_sVDynamic@LabelIds[vehicleid], color, label);
	if (replace)
		strpack(TDW_g_sVDynamic@LabelTexts[vehicleid], label);
	return 1;
}


stock
	ShowVehicle3DTextLabel(vehicleid)
{
	return UpdateVehicle3DTextLabel(vehicleid,
		TDW_g_sVDynamic@LabelTexts[vehicleid], false
	);
}


#undef TDW_VEHICLE_DESTROY_LABEL
#undef TDW_VEHICLE_UPDATE_LABEL
