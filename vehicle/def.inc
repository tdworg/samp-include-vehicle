/** ======================================================================== **\
	Core

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

#if defined _TDW_VEHICLE_DEF_INC_
	#endinput
#endif
#define _TDW_VEHICLE_DEF_INC_

#if !defined GetVehicleDamageStatus
	#error Please, Update the SA:MP libraries.
#endif

#if !defined VEHICLE_PAINTJOB_MIN
	#define VEHICLE_PAINTJOB_MIN (0)
#endif

#if !defined VEHICLE_PAINTJOB_MAX
	#define VEHICLE_PAINTJOB_MAX (2)
#endif

#if !defined INVALID_VEHICLE_ID
	#define INVALID_VEHICLE_ID (3)
#endif

#if !defined MAX_INTERIORS
	#define MAX_INTERIORS (18)
#endif

#if !defined MAX_VEHICLE_MODEL_ID
	#define MAX_VEHICLE_MODEL_ID (611)
#endif
#if !defined MIN_VEHICLE_MODEL_ID
	#define MIN_VEHICLE_MODEL_ID (400)
#endif
#if !defined MAX_VEHICLE_MODELS
	#define MAX_VEHICLE_MODELS (MAX_VEHICLE_MODEL_ID - MIN_VEHICLE_MODEL_ID)
#endif

#if !defined IsValidVehicle
native IsValidVehicle(vehicleid);
#endif

// For foreach support.
#if !defined _TDW_VEHICLE_FOREACH_DEFINED
	#if defined TDW_VEHICLE_NOT_USE_FOREACH
		#define _TDW_VEHICLE_FOREACH_DEFINED 0
	#elseif !defined _FOREACH_LOCAL_VERSION
		#tryinclude <foreach>
		#if defined _FOREACH_LOCAL_VERSION
			#define _TDW_VEHICLE_FOREACH_DEFINED 1
		#endif
		#if !defined _FOREACH_LOCAL_VERSION
			#tryinclude "../include/foreach.inc"
			#if defined _FOREACH_LOCAL_VERSION
				#define _TDW_VEHICLE_FOREACH_DEFINED 1
			#endif
		#endif
		#if !defined _FOREACH_LOCAL_VERSION
			#tryinclude "../include/foreach2.inc"
			#if defined _FOREACH_LOCAL_VERSION
				#define _TDW_VEHICLE_FOREACH_DEFINED 1
			#endif
		#endif
		#if !defined _FOREACH_LOCAL_VERSION
			#tryinclude <foreach2>
			#if defined _FOREACH_LOCAL_VERSION
				#define _TDW_VEHICLE_FOREACH_DEFINED 1
			#endif
		#else
			#define _TDW_VEHICLE_FOREACH_DEFINED 0
		#endif
	#endif
#endif

// For streamer support.
#if !defined _TDW_VEHICLE_STREAMER_DEFINED
	#if defined TDW_VEHICLE_NOT_USE_STREAMER
		#define _TDW_VEHICLE_STREAMER_DEFINED 0
	#elseif !defined Streamer_IncludeFileVersion
		#tryinclude <streamer>
		#if defined Streamer_IncludeFileVersion
			#define _TDW_VEHICLE_STREAMER_DEFINED 1
		#else
			#tryinclude "../include/streamer.inc"
			#if defined Streamer_IncludeFileVersion
				#define _TDW_VEHICLE_STREAMER_DEFINED 1
			#else
				#define _TDW_VEHICLE_STREAMER_DEFINED 0
			#endif
		#endif
	#endif
#endif

#if !defined IS_VALID_MODEL
	#define IS_VALID_MODEL(%0)\
		(_:(MIN_VEHICLE_MODEL_ID<=(%0)<=MAX_VEHICLE_MODEL_ID))
#endif