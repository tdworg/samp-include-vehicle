/* ========================================================================== *\
	Iterator Array

| Description:
	Create the iterator. Add new functions.

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

| Metadata:
	[Functions]:
		Stock:
			- DestroyVehicleSafe
		Static:
			-
		Public:
			-
		Hooks:
			-
	[Callbacks]:
		-
	[Definitions]:
		-
	[Enumerations]:
		-
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			- Vehicle
		Static scope:
			-
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	- foreach, or YSI with y_iterator (optional)
\* ========================================================================== */

#if defined _inc_iterator_array
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_iterator_array
#endif

#if defined _TDW_VH_ITERATOR_ARRAY
	#endinput
#endif

#define _TDW_VH_ITERATOR_ARRAY

// -----------------------------------------------------------------------------
// Definitions:

#if !defined _TDW_VH_DETECT_FOREACH
	#endinput
#endif

#if !defined Vehicle@YSII_Ag
	// Create the iterator.
	new Iterator:Vehicle<MAX_VEHICLES>;
	// Remove the warning messages.
	//
	// foreach generate names with tags.
	#pragma unused Vehicle@YSII_Ag, Vehicle@YSII_Cg
#endif

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>DestroyVehicleSafe</summary>
<param name="&vehicleid">The ID of the vehicle (ref)</param>
<returns>
	-
</returns>
<remarks>
	Delete the ID of the vehicle from the iterator.
</remarks>
\** ------------------------------------------------------------------------ **/

stock DestroyVehicleSafe(&vehicleid)
{
	Iter_SafeRemove(Vehicle, vehicleid, vehicleid);
	return DestroyVehicle(vehicleid);
}
