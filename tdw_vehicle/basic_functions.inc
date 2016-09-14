/** ======================================================================== **\
	Utility

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


#if defined _inc_basic_functions
	#undef _inc_basic_functions
#endif

#if defined _TDW_VHLIB__BASIC_FUNCTIONS
	#endinput
#endif

#define _TDW_VHLIB__BASIC_FUNCTIONS


#if !defined MIN_VEHICLE_PAINTJOB
	#define MIN_VEHICLE_PAINTJOB (0)
#endif
#if !defined MAX_VEHICLE_PAINTJOB
	#define MAX_VEHICLE_PAINTJOB (3)
#endif
#if !defined IS_PAINTJOB_VALID
	#define IS_PAINTJOB_VALID(%0) \
		(MIN_VEHICLE_PAINTJOB <= (%0) <= MAX_VEHICLE_PAINTJOB)
#endif

// Model limits
#if !defined MAX_VEHICLE_MODEL
	#define MAX_VEHICLE_MODEL (611)
#endif
#if !defined MIN_VEHICLE_MODEL
	#define MIN_VEHICLE_MODEL (400)
#endif
#if !defined MAX_VEHICLE_MODELS
	#define MAX_VEHICLE_MODELS (MAX_VEHICLE_MODEL - MIN_VEHICLE_MODEL)
#endif
#if !defined IS_VALID_MODEL
	#define IS_VALID_MODEL(%0) (MIN_VEHICLE_MODEL <= (%0) <= MAX_VEHICLE_MODEL)
#endif

#if !defined _TDW_DEBUG && defined _DEBUG
	#define _TDW_DEBUG 1
#else
	#define _TDW_DEBUG 0
#endif

#if !defined MAX_VEHICLE_PASSENGERS
	#define MAX_VEHICLE_PASSENGERS (8)
#endif

#if !defined IsValidVehicle
	native IsValidVehicle(vehicleid);
#endif

#if !defined _TDW_FOREACH_MAX_VEHICLES_
	#if defined GetVehiclePoolSize
		#define _TDW_FOREACH_MAX_VEHICLES_ (GetVehiclePoolSize() + 1)
	#else
		#define _TDW_FOREACH_MAX_VEHICLES_ (MAX_VEHICLES)
	#endif
#endif

#if !defined _TDW_FOREACH_MAX_PLAYERS_
	#if defined GetPlayerPoolSize
		#define _TDW_FOREACH_MAX_PLAYERS_ (GetPlayerPoolSize() + 1)
	#else
		#define _TDW_FOREACH_MAX_PLAYERS_ (GetMaxPlayers())
	#endif
#endif
