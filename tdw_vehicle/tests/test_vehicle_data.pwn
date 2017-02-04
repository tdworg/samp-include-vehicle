/* ========================================================================== *\
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
\* ========================================================================== */

#define FILTERSCRIPT

#include <a_samp>

#include <tdw_vdata>
#include <tdw_vdetail>

new TDW_gVehicleId;

public OnFilterScriptInit()
{
	TDW_gVehicleId = AddStaticVehicle(400, 12.5, 10.5, 4.2, 0.0, 0, 0);
	DestroyVehicle(TDW_gVehicleId);
	TDW_gVehicleId = CreateVehicle(400, 12.5, 10.5, 4.2, 0.0, 0, 0, -1, 0);

	new
		color1,
		color2;

	GetVehicleColor(TDW_gVehicleId, color1, color2);
	printf("VehicleId: %d; Color1: %d; Color2: %d", TDW_gVehicleId, color1,
		color2);

	SetVehicleColor(TDW_gVehicleId, 0xFF, 0);
	GetVehicleColor(TDW_gVehicleId, color1, color2);
	printf("VehicleId: %d; Color1: %d; Color2: %d", TDW_gVehicleId, color1,
		color2);

	new paintjobid = GetVehiclePaintjobId(TDW_gVehicleId);
	printf("VehicleId: %d; PaintjobId: %d", TDW_gVehicleId, paintjobid);
	SetVehiclePaintjobId(TDW_gVehicleId, 1);
	paintjobid = GetVehiclePaintjobId(TDW_gVehicleId);
	printf("VehicleId: %d; PaintjobId: %d", TDW_gVehicleId, paintjobid);
}
