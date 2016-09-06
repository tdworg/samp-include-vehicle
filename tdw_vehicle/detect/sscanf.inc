/** ======================================================================== **\
| Name:
	Sscanf support

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


#if defined _inc_sscanf
	#undef _inc_sscanf
#endif

#if defined _TDW_VEHICLE_SSCANF
	#endinput
#endif

#define _TDW_VEHICLE_SSCANF


#if !defined _TDW_VEHICLE_SSCANF_DEFINED
	// You can define this constant to disable the sscanf2/3 library.
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
