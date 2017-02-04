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
#include <tdw_vutils>

new TDW_gVehicleId;

public OnFilterScriptInit()
{
	TDW_gVehicleId = CreateVehicle(400, 12.5, 10.5, 4.2, 0.0, 0, 0, -1, 0);

	printf("GetNumberOfValidVehicles  %d", GetNumberOfValidVehicles());
	printf("IsVehicleOccupied         %d", IsVehicleOccupied(TDW_gVehicleId));
	printf("IsVehicleSeatOccupied     %d", IsVehicleSeatOccupied(TDW_gVehicleId, 0));
	printf("GetVehicleMaxPassengers   %d", GetVehicleMaxPassengers(GetVehicleModel(TDW_gVehicleId)));
	printf("GetVehicleDoorsCount      %d", GetVehicleDoorsCount(GetVehicleModel(TDW_gVehicleId)));
	printf("IsValidModelForPaintjob   %d", IsValidModelForPaintjob(GetVehicleModel(TDW_gVehicleId)));
	printf("GetVehicleOccupant        %d", GetVehicleOccupant(TDW_gVehicleId, 0));
	printf("IsVehicleMoving           %d", IsVehicleMoving(TDW_gVehicleId));

	DestroyVehicles();

	printf("GetNumberOfValidVehicles  %d", GetNumberOfValidVehicles());
}
