/** ======================================================================== **\
	Support

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

#if defined _TDW_VHLIB__SAMP_SUPPORT
	#endinput
#endif

#define _TDW_VHLIB__SAMP_SUPPORT

//
// All SA:MP versions
//
#define _TDW_SAMP_LIB_VERSION__037 (0x00_03_70_00)
#define _TDW_SAMP_LIB_VERSION__03z (0x00_03_5A_00)
#define _TDW_SAMP_LIB_VERSION__03x (0x00_03_58_00)
#define _TDW_SAMP_LIB_VERSION__03e (0x00_03_45_00)
#define _TDW_SAMP_LIB_VERSION__03d (0x00_03_44_00)
#define _TDW_SAMP_LIB_VERSION__03c (0x00_03_43_00)
#define _TDW_SAMP_LIB_VERSION__03b (0x00_03_42_00)
#define _TDW_SAMP_LIB_VERSION__03a (0x00_03_41_00)

// Detect current library version
#if defined GetVehiclePoolSize || defined OnVehicleSirenStateChange
	#define _TDW_SAMP_CURRENT_VERSION_LIB _TDW_SAMP_LIB_VERSION__037
#elseif defined OnTrailerUpdate || defined GetPlayerLastShotVectors
	#define _TDW_SAMP_CURRENT_VERSION_LIB _TDW_SAMP_LIB_VERSION__03z
#elseif defined TextDrawSetPreviewVehCol || defined TextDrawSetPreviewModel
	#define _TDW_SAMP_CURRENT_VERSION_LIB _TDW_SAMP_LIB_VERSION__03x
#elseif defined GetVehicleModelInfo || defined AttachPlayerObjectToVehicle
	#define _TDW_SAMP_CURRENT_VERSION_LIB _TDW_SAMP_LIB_VERSION__03e
#elseif defined RemoveBuildingForPlayer || defined OnPlayerTakeDamage
	#define _TDW_SAMP_CURRENT_VERSION_LIB _TDW_SAMP_LIB_VERSION__03d
#elseif defined SetVehicleNumberPlate || defined GetPlayerSurfingObjectID
	#define _TDW_SAMP_CURRENT_VERSION_LIB _TDW_SAMP_LIB_VERSION__03c
#elseif defined GetVehicleRotationQuat || defined SetVehicleAngularVelocity
	#define _TDW_SAMP_CURRENT_VERSION_LIB _TDW_SAMP_LIB_VERSION__03b
#elseif defined GetVehicleVelocity || defined Attach3DTextLabelToVehicle
	#define _TDW_SAMP_CURRENT_VERSION_LIB _TDW_SAMP_LIB_VERSION__03a
#else
	#error Ops
#endif

#define _TDW_SAMP_SUPPORT: _TDW_SAMP_S0:_TDW_SAMP_S1:
#define _TDW_SAMP_S0:_TDW_SAMP_S1:%1.%2||| _TDW_SAMP_SUPPORT:%1%2|||
#define _TDW_SAMP_S1:%1||| _TDW_SAMP_VALUE:%1|||

#define _TDW_SAMP_VALUE:%1||| _TDW_SAMP_LIB_VERSION__%1

#if !defined IS_VERSION
	#define IS_VERSION%0(%1) \
		_:_TDW_SAMP_SUPPORT:%1||| <= _TDW_SAMP_CURRENT_VERSION_LIB
#endif
