/* ========================================================================== *\
	Pawn call fix

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
			- @__TDW_VEHICLE_CALL_EMIT_FIX__@
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

#if defined _inc_pawncallfix
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_pawncallfix
#endif

#if defined _TDW_VH_PAWNCALLFIX
	#endinput
#endif

#define _TDW_VH_PAWNCALLFIX

// -----------------------------------------------------------------------------
// Functions:

@__TDW_VEHICLE_CALL_EMIT_FIX__@();
@__TDW_VEHICLE_CALL_EMIT_FIX__@()
{
	#emit RETN
	static null_string[] = !" ";
	// The stock compiler crashes because of using sysreq.c on a native
	// function.
	DestroyVehicle(0);
	SetVehicleNumberPlate(0, null_string);
	Create3DTextLabel(null_string, 0, 0.0, 0.0, 0.0, 0.0, 0, 0);
	Attach3DTextLabelToVehicle(Text3D:0, 0, 0.0, 0.0, 0.0);
	#if defined _TDW_VH_DETECT_STREAMER
		UpdateDynamic3DTextLabelText(Text3D:0, 0, null_string);
	#else
		Update3DTextLabelText(Text3D:0, 0, null_string);
	#endif
}
