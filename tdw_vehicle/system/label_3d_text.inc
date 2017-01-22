/* ========================================================================== *\
	3D Text Label

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
			- CreateVehicle3DTextLabel
			- DestroyVehicle3DTextLabel
			- UpdateVehicle3DTextLabel
			- ShowVehicle3DTextLabel
			- HideVehicle3DTextLabel
			- Is3DTextLabelHidden
		Static:
			-
		Public:
			-
		Hooks:
			-
	[Callbacks]:
		-
	[Definitions]:
		- TDW_VH_DestroyLabel
		- TDW_VH_UpdateLabel
		- MAX_VEHICLE_LABEL_SIZE
	[Enumerations]:
		- E_TDW_VH_LABEL_FLAGS
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			- TDW_g_sVehicle@LabelId
			- TDW_g_sVehicle@LabelText
			- TDW_g_sVehicle@Flags
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	- streamer (optional)
\* ========================================================================== */

#if defined _inc_label_3d_text
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_label_3d_text
#endif

#if defined _TDW_VH_SYS_3D_TEXT_LABEL
	#endinput
#endif

#define _TDW_VH_SYS_3D_TEXT_LABEL

// -----------------------------------------------------------------------------
// Enumerations:

enum E_TDW_VH_LABEL_FLAGS(<<= 1)
{
	EI_VH_LABEL_HIDDEN = 1
};

// -----------------------------------------------------------------------------
// Definitions:

#if defined _TDW_VH_DETECT_STREAMER
	#define TDW_VH_DestroyLabel				DestroyDynamic3DTextLabel
	#define TDW_VH_UpdateLabel				UpdateDynamic3DTextLabelText
#else
	#define TDW_VH_DestroyLabel				Delete3DTextLabel
	#define TDW_VH_UpdateLabel				Update3DTextLabelText
#endif

#if !defined MAX_VEHICLE_LABEL_SIZE
	#define MAX_VEHICLE_LABEL_SIZE			(144)
#endif

// -----------------------------------------------------------------------------
// Static scope:

static stock
	Text3D:TDW_g_sVehicle@LabelId[MAX_VEHICLES],
	TDW_g_sVehicle@LabelText[MAX_VEHICLES][MAX_VEHICLE_LABEL_SIZE char],
	E_TDW_VH_LABEL_FLAGS:TDW_g_sVehicle@Flags[MAX_VEHICLES char];

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>CreateVehicle3DTextLabel</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock CreateVehicle3DTextLabel(vehicleid, const label[], color, Float:offset_x,
	Float:offset_y, Float:offset_z, Float:drawdistance, virtualworld,
	bool:testLos = false)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;

	new
		label_length = strlen(label);

	if (0 == _:(0 < label_length < MAX_VEHICLE_LABEL_SIZE))
		return 0;

	#if defined _TDW_VH_DETECT_STREAMER
		TDW_g_sVehicle@LabelId[vehicleid] = CreateDynamic3DTextLabel(label,
			color, offset_x, offset_y, offset_z, drawdistance, _, vehicleid,
			_:testLos, virtualworld, _, _, _);
	#else
		new Text3D:Create3DTextLabel_ret;

		#emit PUSH.s testLos
		#emit PUSH.s virtualworld
		#emit PUSH.s drawdistance
		#emit PUSH.c 0 // Float value
		#emit PUSH.c 0 // Float value
		#emit PUSH.c 0 // Float value
		#emit PUSH.s color
		#emit PUSH.s label
		#emit PUSH.c 36
		#emit SYSREQ.c Create3DTextLabel

		#emit STOR.s.pri Create3DTextLabel_ret

		#emit PUSH.s offset_z
		#emit PUSH.s offset_y
		#emit PUSH.s offset_x
		#emit PUSH.s vehicleid
		#emit PUSH.pri
		#emit PUSH.c 20
		#emit SYSREQ.c Attach3DTextLabelToVehicle

		#emit STACK 64 // (36 + 4) + (20 + 4)

		TDW_g_sVehicle@LabelId[vehicleid] = Create3DTextLabel_ret;
	#endif

	strpack(TDW_g_sVehicle@LabelText[vehicleid], label, label_length);

	TDW_g_sVehicle@Flags{vehicleid} = E_TDW_VH_LABEL_FLAGS:0;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>DestroyVehicle3DTextLabel</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock DestroyVehicle3DTextLabel(vehicleid)
{
	return IsValidVehicle(vehicleid)
		? TDW_VH_DestroyLabel(TDW_g_sVehicle@LabelId[vehicleid])
		: INVALID_VEHICLE_ID;
}

/** ------------------------------------------------------------------------ **\
<summary>UpdateVehicle3DTextLabel</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock UpdateVehicle3DTextLabel(vehicleid, const label[], color = -1,
	bool:replace_buffer = false)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;

	new
		label_length = strlen(label);

	if (0 == _:(0 < label_length < MAX_VEHICLE_LABEL_SIZE))
		return 0;

	#emit PUSH.s label
	#emit PUSH.s color

	#emit CONST.alt TDW_g_sVehicle@LabelId
	#emit LOAD.s.pri vehicleid
	#emit LIDX

	#emit PUSH.pri
	#emit PUSH.c 12
	#if defined _TDW_VH_DETECT_STREAMER
		#emit SYSREQ.c UpdateDynamic3DTextLabelText
	#else
		#emit SYSREQ.c Update3DTextLabelText
	#endif
	#emit STACK 16

	if (replace_buffer)
		strpack(TDW_g_sVehicle@LabelText[vehicleid], label, label_length);

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>ShowVehicle3DTextLabel</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock ShowVehicle3DTextLabel(vehicleid)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;

	if (TDW_g_sVehicle@Flags{vehicleid} & EI_VH_LABEL_HIDDEN) {
		UpdateVehicle3DTextLabel(vehicleid, TDW_g_sVehicle@LabelText[vehicleid],
			true);
		TDW_g_sVehicle@Flags{vehicleid} ^= EI_VH_LABEL_HIDDEN;
	}

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>HideVehicle3DTextLabel</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock HideVehicle3DTextLabel(vehicleid)
{
	if (0 == IsValidVehicle(vehicleid))
		return 0;
	if (TDW_g_sVehicle@Flags{vehicleid} & EI_VH_LABEL_HIDDEN)
		return 0;

	UpdateVehicle3DTextLabel(vehicleid, !" ", true);
	TDW_g_sVehicle@Flags{vehicleid} ^= EI_VH_LABEL_HIDDEN;

	return 1;
}

/** ------------------------------------------------------------------------ **\
<summary>Is3DTextLabelHidden</summary>
<param name="vehicleid">The ID of the vehicle</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock Is3DTextLabelHidden(vehicleid)
{
	return IsValidVehicle(vehicleid) &&
		(TDW_g_sVehicle@Flags{vehicleid} & EI_VH_LABEL_HIDDEN);
}

// -----------------------------------------------------------------------------
// Internal:

#undef TDW_VH_DestroyLabel
#undef TDW_VH_UpdateLabel
