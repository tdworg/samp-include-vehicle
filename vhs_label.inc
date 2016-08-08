/** ======================================================================== **\
| Name:
	Vehicle Label system

| Category:
	core

| Version:
	2.0.2

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


#if defined _inc_vhs_label
	#undef _inc_vhs_label
#endif

#if defined _TDW_VEHICLE_LABEL
	#endinput
#endif

#define _TDW_VEHICLE_LABEL

#include "vehicle/detect/samp_support"
#include "vehicle/detect/streamer"
#include "vehicle/utility"
#include "vehicle/system/vehicle_label"
