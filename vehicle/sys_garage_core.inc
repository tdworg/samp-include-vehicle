/** ======================================================================== **\
	Vehicle Garage system [--Core--]

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

/* =========================================================
 * Attention!
 * - The alpha version of the library.
 * =========================================================
 */

#if defined _TDW_VEHICLE_S_GARAGE_COR_INC_
	#endinput
#endif
#define _TDW_VEHICLE_S_GARAGE_COR_INC_

#if _TDW_VEHICLE_SSCANF_DEFINED == 0
	#error Download sscanf2.inc or sscanf3.inc
#endif

enum e_TDW_VEHICLE_GARAGE
{
	ei_OwnerName[MAX_PLAYER_NAME + 1], // [tag] + name + '\0'
	Float:ei_pos_x,
	Float:ei_pos_y,
	Float:ei_pos_z,
	Float:ei_rot_x,
	Float:ei_rot_y,
	Float:ei_rot_z,
	ei_price,
	// --
	ei_door_object_id,
	Text3D:ei_label_id
};

#if _TDW_VEHICLE_STREAMER_DEFINED
	#define TDW_CreateDObject CreateDynamicObject
	#define TDW_DestroyDLabel DestroyDynamic3DTextLabel
#else
	#define TDW_CreateDObject CreateObject
	#define TDW_DestroyDLabel Destroy3DTextLabel
#endif

#if !defined TDW_GARAGE_FILE_NAME
	#define TDW_GARAGE_FILE_NAME "tdw_garages.inc"
#endif

#if !defined TDW_GARAGE_LOCALE_OWNED
	#define TDW_GARAGE_LOCALE_OWNED "{444444}Garage ¹%d\nOwner: {FFFFFF}%s"
#endif

#if !defined TDW_GARAGE_LOCALE_NOWNED
	#define TDW_GARAGE_LOCALE_NOWNED "{444444}The garage sale.\nPrice: %d"
#endif

#if !defined TDW_GARAGE_OBJECT_DOOR_ID
	#define TDW_GARAGE_OBJECT_DOOR_ID (17951)
#else
	#assert (-1 < TDW_GARAGE_OBJECT_DOOR_ID < 20000)
#endif