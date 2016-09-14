/** ======================================================================== **\
	Vehicle Static Data

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


#if defined _inc_iterator
	#undef _inc_iterator
#endif

#if defined _TDW_VHLIB__ITERATOR
	#endinput
#endif

#define _TDW_VHLIB__ITERATOR

// Creates the foreach array.
#if defined _TDW_VEHICLE_FOREACH_DEFINED
	#if _TDW_VEHICLE_FOREACH_DEFINED
		#if !defined Vehicle@YSII_Ag
			new Iterator:Vehicle<MAX_VEHICLES>;
		#endif
		#if !defined _TDW_VEHICLE_FOREACH_ARRAY
			#define _TDW_VEHICLE_FOREACH_ARRAY 1
		#endif
		// The variables can't be used in the code.
		#pragma unused Vehicle@YSII_Ag, Vehicle@YSII_Cg
	#endif
#endif

stock
	DestroyVehicleSafe(vehicleid)
{
	Iter_SafeRemove(Vehicle, vehicleid, vehicleid);
	return DestroyVehicle(vehicleid);
}
