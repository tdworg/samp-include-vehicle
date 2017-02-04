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
#include <tdw_vmath>

new TDW_gVehicleId;

public OnFilterScriptInit()
{
	TDW_gVehicleId = CreateVehicle(400, 12.5, 10.5, 4.2, 0.0, 0, 0, -1, 0);
	TDW_gVehicleId = CreateVehicle(400, 12.5, 10.5, 4.2, 0.0, 0, 0, -1, 0);
	TDW_gVehicleId = CreateVehicle(400, 12.5, 10.5, 4.2, 0.0, 0, 0, -1, 0);
	TDW_gVehicleId = CreateVehicle(400, 12.5, 10.5, 4.2, 0.0, 0, 0, -1, 0);

	printf("GetNearestVehicleFromPoint      %d", GetNearestVehicleFromPoint(12.5, 10.5, 4.2));
	new Float:offset_x, Float:offset_y, Float:offset_z;

	GetVehicleOffsetFromPos(TDW_gVehicleId, 14.5, 10.5, 3.5, offset_x, offset_y, offset_z);
	printf("GetVehicleOffsetFromPos         %f %f %f", offset_x, offset_y, offset_z);

	GetVehicleBootPos(TDW_gVehicleId, offset_x, offset_y, offset_z);
	printf("GetVehicleBootPos               %f %f %f", offset_x, offset_y, offset_z);

	GetVehicleBonnetPos(TDW_gVehicleId, offset_x, offset_y, offset_z);
	printf("GetVehicleBonnetPos             %f %f %f", offset_x, offset_y, offset_z);

	GetVehicleRoofPos(TDW_gVehicleId, offset_x, offset_y, offset_z);
	printf("GetVehicleRoofPos               %f %f %f", offset_x, offset_y, offset_z);

	printf("IsVehicleInRangeOfPoint         %d", IsVehicleInRangeOfPoint(TDW_gVehicleId, 10.0, 12.5, 10.5, 4.2));

	printf("GetVehicleSpeed                 %f", GetVehicleSpeed(TDW_gVehicleId));
	printf("SetVehicleSpeed                 %d", SetVehicleSpeed(TDW_gVehicleId, 100.0));

	printf("IsVehicleUpsideDown             %d", IsVehicleUpsideDown(TDW_gVehicleId));
	GetVehicleVelocityDirection(TDW_gVehicleId, offset_x);
	printf("GetVehicleVelocityDirection     %f", offset_x);
}
