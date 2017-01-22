/* ========================================================================== *\
	Core

| Description:


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
			-
		Static:
			-
		Public:
			-
		Hooks:
			-
	[Callbacks]:
		-
	[Definitions]:
		- MAX_VEHICLE_COMPONENT_ID
		- MAX_VEHICLE_COMPONENTS
		- MAX_VEHICLE_MODEL
		- MAX_VEHICLE_MODELS
		- MAX_VEHICLE_PAINTJOB
		- MIN_VEHICLE_COMPONENT_ID
		- MIN_VEHICLE_MODEL
		- MIN_VEHICLE_PAINTJOB
	[Enumerations]:
		-
	[Macros]:
		- IS_VALID_COMPONENT_ID
		- IS_VALID_MODEL
		- IS_VALID_PAINTJOB
		- IS_VALID_VEHICLEID
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			-
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_core
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_core
#endif

#if defined _TDW_VH_CORE
	#endinput
#endif

#define _TDW_VH_CORE

// -----------------------------------------------------------------------------
// Definitions:

// Paintjob
#if !defined MIN_VEHICLE_PAINTJOB
	#define MIN_VEHICLE_PAINTJOB		(0)
#endif
#if !defined MAX_VEHICLE_PAINTJOB
	#define MAX_VEHICLE_PAINTJOB		(3)
#endif

// Models
#if !defined MIN_VEHICLE_MODEL
	#define MIN_VEHICLE_MODEL			(400)
#endif
#if !defined MAX_VEHICLE_MODEL
	#define MAX_VEHICLE_MODEL			(611)
#endif
#if !defined MAX_VEHICLE_MODELS
	#define MAX_VEHICLE_MODELS			(MAX_VEHICLE_MODEL - MIN_VEHICLE_MODEL)
#endif

// Components
#if !defined MIN_VEHICLE_COMPONENT_ID
	#define MIN_VEHICLE_COMPONENT_ID	(1000)
#endif
#if !defined MAX_VEHICLE_COMPONENT_ID
	#define MAX_VEHICLE_COMPONENT_ID	(1193)
#endif
#if !defined MAX_VEHICLE_COMPONENTS
	#define MAX_VEHICLE_COMPONENTS		(MAX_VEHICLE_COMPONENT_ID - \
		MIN_VEHICLE_COMPONENT_ID)
#endif

// Number plate
#if !defined MAX_NUMBER_PLATE_SIZE
	#define MAX_NUMBER_PLATE_SIZE		(32)
#endif
#if !defined MAX_NUMBER_PLATE
	#define MAX_NUMBER_PLATE			(8)
#endif

// Passengers
#if !defined MAX_VEHICLE_PASSENGERS
	#define MAX_VEHICLE_PASSENGERS		(8)
#endif

// Doors
#if !defined MAX_VEHICLE_DOORS
	#define MAX_VEHICLE_DOORS			(4)
#endif

//
#if !defined _TDW_FOREACH_MAX_VEHICLES_
	#if defined GetVehiclePoolSize
		#define _TDW_FOREACH_MAX_VEHICLES_	(GetVehiclePoolSize() + 1)
	#else
		#define _TDW_FOREACH_MAX_VEHICLES_	(MAX_VEHICLES)
	#endif
#endif

#if !defined _TDW_FOREACH_MAX_PLAYERS_
	#if defined GetPlayerPoolSize
		#define _TDW_FOREACH_MAX_PLAYERS_	(GetPlayerPoolSize() + 1)
	#else
		#define _TDW_FOREACH_MAX_PLAYERS_	(GetMaxPlayers())
	#endif
#endif

// -----------------------------------------------------------------------------
// Macros:

// Paintjob
#if !defined IS_VALID_PAINTJOB
	#define IS_VALID_PAINTJOB%0(%1)		_:(MIN_VEHICLE_PAINTJOB <= \
		(%1) <= MAX_VEHICLE_PAINTJOB)
#endif

// Models
#if !defined IS_VALID_MODEL
	#define IS_VALID_MODEL%0(%1)		_:(MIN_VEHICLE_MODEL <= \
		(%1) <= MAX_VEHICLE_MODEL)
#endif

// Components
#if !defined IS_VALID_COMPONENT_ID
	#define IS_VALID_COMPONENT_ID%0(%1)	_:(MIN_VEHICLE_COMPONENT_ID <= \
		(%1) <= MAX_VEHICLE_COMPONENT_ID)
#endif

// Vehicleid
#if !defined IS_VALID_VEHICLEID
	#define IS_VALID_VEHICLEID%0(%1) _:(0 < (%1) < MAX_VEHICLES)
#endif

// -----------------------------------------------------------------------------
// Natives:

#if !defined IsValidVehicle
	// This function is not defined in SA:MP library.
	native IsValidVehicle(vehicleid);
#endif
