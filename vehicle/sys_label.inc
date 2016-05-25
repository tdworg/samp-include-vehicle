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

static stock
	Text3D:TDW_g_sVehicleD@LabelId[MAX_VEHICLES];

stock
		bool:testLos = false
#if _TDW_VEHICLE_STREAMER_DEFINED
		, interiorid = -1, streamdistance = 100.0
#endif
	)
{
	if (label[0] == '\0')
		return 0;
	if (IsValidVehicle(vehicleid) == 0)
		return 0;

	TDW_g_sVehicleD@LabelId[vehicleid]
	#if _TDW_VEHICLE_STREAMER_DEFINED
		drawdistance, _, vehicleid, _:testlos, virtualworld, interiorid,
		streamdistance
	);
	#else
	= Create3DTextLabel(label, color, 0.0, 0.0, 0.0, drawdistance,
		virtualworld, _:testlos
	);
	Attach3DTextLabelToVehicle(TDW_g_sVehicleD@LabelId[vehicleid],
	);
	#endif
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
	UpdateVehicle3DTextLabel(vehicleid, const label[], color = -1)
{
	if (label[0] == '\0')
		return 0;
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	#if _TDW_VEHICLE_STREAMER_DEFINED
	UpdateDynamic3DTextLabelText(TDW_g_sVehicleD@LabelId[vehicleid], color,
		label
	);
	#else
	Update3DTextLabelText(TDW_g_sVehicleD@LabelId[vehicleid], color, label);
	#endif
	return 1;
}