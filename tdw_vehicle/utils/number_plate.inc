/** ======================================================================== **\
	Vehicle Number Plate

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


#if defined _inc_number_plate
	#undef _inc_number_plate
#endif

#if defined _TDW_VHLIB__NUMBER_PLATE
	#endinput
#endif

#define _TDW_VHLIB__NUMBER_PLATE

// Checks if a string is packed.
// Other information: //www.compuphase.com/pawn/String_Manipulation.pdf
#if !defined IsPackedString
	#define IsPackedString%0(%1) ((%1)[0] > 255)
#endif


static stock
	TDW_g_sNumberPlate[MAX_VEHICLES][MAX_NUMBER_PLATE_SIZE char];



native nst_SetVehicleNumberPlate(vehicleid,
	numberplate[]) = SetVehicleNumberPlate;

stock
	TDWVH_NP@SetVehicleNumberPlate(vehicleid, numberplate[])
{
	new Float:current_x, Float:current_y, Float:current_z;
	if (GetVehiclePos(vehicleid, current_x, current_y, current_z) == 0)
		return 0;
	new Float:current_z_angle, Float:current_health, cur_dstatus_panels,
		cur_dstatus_doors, cur_dstatus_lights, cur_dstatus_tires,
		i;
	new passengers[MAX_VEHICLE_PASSENGERS];
	// Get the current parameters of the vehicle.
	GetVehicleZAngle(vehicleid, current_z_angle);
	#if !defined TDW_NPLATE_NOT_SAFE_DAMAGE
	GetVehicleHealth(vehicleid, current_health);
	GetVehicleDamageStatus(vehicleid, cur_dstatus_panels, cur_dstatus_doors,
		cur_dstatus_lights, cur_dstatus_tires
	);
	#endif
	i = 0;
	GetVehicleOccupantPlayers(vehicleid, passengers);
	SetVehicleNumberPlate(vehicleid, numberplate);
	SetVehicleToRespawn(vehicleid);
	// Copy numberplate into the array.
	#if !defined TDW_NPLATE_NOT_SAFE_NUMBER
	TDW_g_sNumberPlate[vehicleid]{0} = '\0';
	strpack(TDW_g_sNumberPlate[vehicleid], numberplate);
	#endif
	// Set the old parameters to the vehicle
	SetVehiclePos(vehicleid, current_x, current_y, current_z);
	i = 0;
	do
	{
		PutPlayerInVehicle(passengers[i], vehicleid, i);
	} while(++i < sizeof passengers);
	SetVehicleZAngle(vehicleid, current_z_angle);
	#if !defined TDW_NPLATE_NOT_SAFE_DAMAGE
	SetVehicleHealth(vehicleid, current_health);
	UpdateVehicleDamageStatus(vehicleid, cur_dstatus_panels, cur_dstatus_doors,
		cur_dstatus_lights, cur_dstatus_tires
	);
	#endif
	return 1;
}

#if defined _ALS_SetVehicleNumberPlate
	#undef SetVehicleNumberPlate
#else
	#define _ALS_SetVehicleNumberPlate
#endif

#define SetVehicleNumberPlate TDWVH_NP@SetVehicleNumberPlate


stock
	SetVehicleNumberPlateRand(vehicleid, dest[MAX_NUMBER_PLATE] = !"")
{
	if (IsValidVehicle(vehicleid) == 0)
		return 0;
	static const letters[] = !"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const
		NUMBER_PLATE_SPACE_POS = 3,
		LETTER_SIZE = sizeof letters - 1;
	new i = MAX_NUMBER_PLATE;
	if (IsPackedString(dest))
	{
		while (i-- != 0)
		{
			dest{i} = ((i == NUMBER_PLATE_SPACE_POS)
				? '-'
				: letters{random(LETTER_SIZE)}
			);
			i--;
		}
	}
	else
	{
		while (i != 0)
		{
			dest[i] = ((i == NUMBER_PLATE_SPACE_POS)
				? '-'
				: letters{random(LETTER_SIZE)}
			);
			i--;
		}
	}
	return TDWVH_NP@SetVehicleNumberPlate(vehicleid, dest);
}


// //github.com/TDW-org/samp-include-string/
#if !defined _TDW_STLIB__STRING
static stock
	strcpy(dest[], const string[], dest_size = sizeof dest)
{
	return
		(IsPackedString(dest) ? (dest{0} = '\0') : (dest[0] = '\0')),
		strcat(dest, string, dest_size);
}
#endif


#if !defined TDW_NPLATE_NOT_SAFE_NUMBER
stock
	GetVehicleNumberPlate(vehicleid, dest[], bool:packed = false,
		dest_size = sizeof dest)
{
	return packed
		? strcpy(dest, TDW_g_sNumberPlate[vehicleid], dest_size)
		: strunpack(dest, TDW_g_sNumberPlate[vehicleid], dest_size);
}
#endif
