/** ======================================================================== **\
| Name:
	Vehicle sscanf

| Category:
	utils

| Version:
	2.0.1

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


#if defined _inc_vehicle_sscanf
	#undef _inc_vehicle_sscanf
#endif

#if defined _TDW_VEHICLE_U_SSCANF
	#endinput
#endif

#define _TDW_VEHICLE_U_SSCANF

SSCANF:vehicleid(string[])
{
	if ('0' <= string[0] <= '9')
	{
		new ret = strval(string);
		if (1 <= ret <= MAX_VEHICLES - 1)
		{
			if (IsValidVehicle(vehicleid))
			{
				return ret;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}