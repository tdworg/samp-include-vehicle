/** ======================================================================== **\
| Name:
	Support

| Category:
	core

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


#if defined _inc_samp_support
	#undef _inc_samp_support
#endif

#if defined _TDW_VEHICLE_SUPPORT
	#endinput
#endif

#define _TDW_VEHICLE_SUPPORT


#include <a_samp>

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