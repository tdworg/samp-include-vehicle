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

#if defined _inc_def
	#undef _inc_def
#endif
#if defined _TDW_VEHICLE_DEF_INC_
	#endinput
#endif
#define _TDW_VEHICLE_DEF_INC_

#define _TDW_SAMP_INC_VERSION_037     0x037
// #define _TDW_SAMP_INC_VERSION_03zR4   0x03f111
// #define _TDW_SAMP_INC_VERSION_03zR2_2 0x03f110
#define _TDW_SAMP_INC_VERSION_03z     0x03f100
#define _TDW_SAMP_INC_VERSION_03x 0x03f0
#define _TDW_SAMP_INC_VERSION_03e 0x03e
#define _TDW_SAMP_INC_VERSION_03d 0x03d
// #define _TDW_SAMP_INC_VERSION_03cR4 0x03c111
// #define _TDW_SAMP_INC_VERSION_03cR3 0x03c110
#define _TDW_SAMP_INC_VERSION_03c 0x03c
#define _TDW_SAMP_INC_VERSION_03b 0x03b
#define _TDW_SAMP_INC_VERSION_03a 0x03a

// 0.3a
#if defined GetVehicleVelocity || defined Attach3DTextLabelToVehicle
	// 0.3.7
	#if defined GetVehiclePoolSize || defined OnVehicleSirenStateChange
		#define _TDW_SAMP_INCLUDE_VERSION _TDW_SAMP_INC_VERSION_037
	// 0.3z
	#elseif defined OnTrailerUpdate || defined GetPlayerLastShotVectors
		#define _TDW_SAMP_INCLUDE_VERSION _TDW_SAMP_INC_VERSION_03z
	// 0.3x
	#elseif defined TextDrawSetPreviewVehCol || defined TextDrawSetPreviewModel
		#define _TDW_SAMP_INCLUDE_VERSION _TDW_SAMP_INC_VERSION_03x
	// 0.3e
	#elseif defined GetVehicleModelInfo || defined AttachPlayerObjectToVehicle
		#define _TDW_SAMP_INCLUDE_VERSION _TDW_SAMP_INC_VERSION_03e
	// 0.3d
	#elseif defined RemoveBuildingForPlayer || defined OnPlayerTakeDamage
		#define _TDW_SAMP_INCLUDE_VERSION _TDW_SAMP_INC_VERSION_03d
	// 0.3c
	#elseif defined SetVehicleNumberPlate || defined GetPlayerSurfingObjectID 
		#define _TDW_SAMP_INCLUDE_VERSION _TDW_SAMP_INC_VERSION_03c
	// 0.3b
	#elseif defined GetVehicleRotationQuat || defined SetVehicleAngularVelocity
		#define _TDW_SAMP_INCLUDE_VERSION _TDW_SAMP_INC_VERSION_03b
	#else
		#define _TDW_SAMP_INCLUDE_VERSION _TDW_SAMP_INC_VERSION_03a
	#endif
#else
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

		#define _FOREACH_NO_TEST

		#tryinclude <foreach>
		#if defined _FOREACH_LOCAL_VERSION
			#define _TDW_VEHICLE_FOREACH_DEFINED 1
		#else
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

// For sscanf2/3 support
#if !defined _TDW_VEHICLE_SSCANF_DEFINED
	#if defined TDW_VEHICLE_NOT_USE_SSCANF
		#define _TDW_VEHICLE_SSCANF_DEFINED 0
	#elseif !defined sscanf
		#tryinclude <sscanf2>
		#if defined sscanf
			#define _TDW_VEHICLE_SSCANF_DEFINED 1
		#else
			#if !defined sscanf
				#tryinclude "../include/sscanf2"
				#if defined sscanf
					#define _TDW_VEHICLE_SSCANF_DEFINED 1
				#endif
			#endif
			#if !defined sscanf
				#tryinclude "../include/sscanf3"
				#if defined sscanf
					#define _TDW_VEHICLE_SSCANF_DEFINED 1
				#endif
			#endif
			#if !defined sscanf
				#tryinclude <sscanf3>
				#if defined sscanf
					#define _TDW_VEHICLE_SSCANF_DEFINED 1
				#endif
			#else
				#define _TDW_VEHICLE_SSCANF_DEFINED 0
			#endif
		#endif
	#endif
#endif

#if !defined IS_VALID_MODEL
	#define IS_VALID_MODEL(%0)\
		(_:(MIN_VEHICLE_MODEL_ID<=(%0)<=MAX_VEHICLE_MODEL_ID))
#endif

#if defined _DEBUG
	#define _TDW_DEBUG_ 1
#else
	#define _TDW_DEBUG_ 0
#endif