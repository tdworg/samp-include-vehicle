/** ======================================================================== **\
| Name:
	Vehicle Iterator data

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


#if defined _inc_vh_iterator
	#undef _inc_vh_iterator
#endif

#if defined _TDW_VEHICLE_ITERATOR
	#endinput
#endif

#define _TDW_VEHICLE_ITERATOR

#include "vehicle/detect/foreach"
#include "vehicle/utility"
#include "vehicle/data/vehicle_iterator"
#include "vehicle/data/vehicle_static_data"