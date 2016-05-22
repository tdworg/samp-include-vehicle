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