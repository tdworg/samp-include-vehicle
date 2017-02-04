/* ========================================================================== *\
	GTA San Andreas Vehicle Data

| Description:
	The data about the vehicles, such as: name, type, max velocity, category.

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
			- GetModelStaticSpeed
			- GetModelStaticIdFromName
			- GetModelStaticNameFromId
			- GetModelStaticCategory
			- GetModelStaticType
		Static:
			-
		Public:
			-
		Hooks:
			-
	[Callbacks]:
		-
	[Definitions]:
		-
	[Enumerations]:
		- E_TDW_VEHICLE_SA_CATEGORY
		- E_TDW_VEHICLE_SA_TYPE
	[Macros]:
		-
	[Tags]:
		-
	[Variables]:
		Global scope:
			-
		Static scope:
			- TDW_g_sVehicleSpeed
			- TDW_g_sVehicleNames
			- TDW_g_sVehicleCategory
	[Natives]:
		-
	[Operators]:
		-
| Dependencies:
	-
\* ========================================================================== */

#if defined _inc_tdw_vsa_data
	// I remove this constant because the compiler automatically generates it.
	//   github.com/Zeex/pawn/issues/107
	#undef _inc_tdw_vsa_data
#endif

#if defined _TDW_VH_GTASA_DATA
	#endinput
#endif

#define _TDW_VH_GTASA_DATA

#include "tdw_vehicle"

// -----------------------------------------------------------------------------
// Enumerations:

enum E_TDW_VEHICLE_SA_CATEGORY
{
	OFF_ROAD,
	SALOONS,
	SPORT,
	INDUSTRIAL,
	STATION_WAGONS,
	UNIQUE,
	PUBLIC_SERVICE,
	LOWRIDERS,
	RADIOC,
	HELICOPTERS,
	BOATS,
	TRAILERS,
	AIRPLANE,
	CONVERTIBLES,
	BIKES
};

enum E_TDW_VEHICLE_SA_TYPE
{
	CAR,
	HELICOPTE,
	BOAT,
	TRAILER,
	MOTORBIKE,
	TRAIN,
	PLANE,
	BIKE,
	RC
};

// -----------------------------------------------------------------------------
// Static scope:

static stock const
	TDW_g_sVehicleSpeed[MAX_VEHICLE_MODELS + 1] =
{
	160, 160, 200, 120, 150, 165, 110, 170, 110, 180, 160, 240, 160, 160, 140,
	230, 155, 200, 150, 160, 180, 180, 165, 145, 170, 200, 200, 170, 170, 200,
	190, 130,  80, 180, 200, 120, 160, 160, 160, 160, 160,  75, 150, 150, 110,
	165, 280, 200, 190, 150, 120, 240, 190, 190, 190, 140, 160, 160, 165, 160,
	200, 190, 190, 190,  75,  75, 160, 160, 190, 200, 170, 160, 190, 190, 160,
	160, 200, 200, 150, 165, 200, 120, 150, 120, 190, 160, 100, 200, 200, 170,
	170, 160, 160, 190, 220, 170, 200, 200, 140, 140, 160,  75, 220, 220, 160,
	170, 230, 165, 140, 120, 140, 200, 200, 200, 120, 120, 165, 165, 160, 330,
	330, 190, 190, 190, 110, 160, 160, 160, 170, 160,  60,  70, 140, 200, 160,
	160, 160, 110, 110, 150, 160, 230, 160, 165, 170, 160, 160, 160, 200, 160,
	160, 165, 160, 200, 170, 180, 110, 110, 200, 200, 200, 200, 200, 200,  75,
	200, 160, 160, 170, 110, 110,  90,  60, 110,  60, 160, 160, 200, 110, 160,
	165, 190, 160, 170, 120, 165, 190, 200, 140, 200, 110, 120, 200, 200,  60,
	190, 200, 200, 200, 160, 165, 110, 200, 200, 160, 165, 160, 160, 160, 140,
	160, 160
},
	TDW_g_sVehicleNames[MAX_VEHICLE_MODELS + 1][] =
{
	!"Landstalker", !"Bravura", !"Buffalo", !"Linerunner", !"Perenniel",
	!"Sentinel", !"Dumper", !"Firetruck", !"Trashmaster", !"Stretch",
	!"Manana", !"Infernus", !"Voodoo", !"Pony", !"Mule", !"Cheetah",
	!"Ambulance", !"Leviathan", !"Moonbeam", !"Esperanto", !"Taxi",
	!"Washington", !"Bobcat", !"Mr Whoopee", !"BF Injection", !"Hunter",
	!"Premier", !"Enforcer", !"Securicar", !"Banshee", !"Predator", !"Bus",
	!"Rhino", !"Barracks", !"Hotknife", !"Article Trailer", !"Previon",
	!"Coach", !"Cabbie", !"Stallion", !"Rumpo", !"RC Bandit", !"Romero",
	!"Packer", !"Monster", !"Admiral", !"Squallo", !"Seasparrow", !"Pizzaboy",
	!"Tram", !"Article Trailer 2", !"Turismo", !"Speeder", !"Reefer",
	!"Tropic", !"Flatbed", !"Yankee", !"Caddy", !"Solair",
	!"Topfun Van (Berkley's RC)", !"Skimmer", !"PCJ-600", !"Faggio",
	!"Freeway", !"RC Baron", !"RC Raider", !"Glendale", !"Oceanic", !"Sanchez",
	!"Sparrow", !"Patriot", !"Quad", !"Coastguard", !"Dinghy", !"Hermes",
	!"Sabre", !"Rustler", !"ZR-350", !"Walton", !"Regina", !"Comet", !"BMX",
	!"Burrito", !"Camper", !"Marquis", !"Baggage", !"Dozer", !"Maverick",
	!"SAN News Maverick", !"Rancher", !"FBI Rancher", !"Virgo", !"Greenwood",
	!"Jetmax", !"Hotring Racer", !"Sandking", !"Blista Compact",
	!"Police Maverick", !"Boxville", !"Benson", !"Mesa", !"RC Goblin",
	!"Hotring Racer", !"Hotring Racer", !"Bloodring Banger", !"Rancher",
	!"Super GT", !"Elegant", !"Journey", !"Bike", !"Mountain Bike", !"Beagle",
	!"Cropduster", !"Stuntplane", !"Tanker", !"Roadtrain", !"Nebula",
	!"Majestic", !"Buccaneer", !"Shamal", !"Hydra", !"FCR-900", !"NRG-500",
	!"HPV1000", !"Cement Truck", !"Towtruck", !"Fortune", !"Cadrona",
	!"FBI Truck", !"Willard", !"Forklift", !"Tractor", !"Combine Harvester",
	!"Feltzer", !"Remington", !"Slamvan", !"Blade", !"Freight (Train)",
	!"Brownstreak (Train)", !"Vortex", !"Vincent", !"Bullet", !"Clover",
	!"Sadler", !"Firetruck LA", !"Hustler", !"Intruder", !"Primo", !"Cargobob",
	!"Tampa", !"Sunrise", !"Merit", !"Utility Van", !"Nevada", !"Yosemite",
	!"Windsor", !"Monster \"A\"", !"Monster \"B\"", !"Uranus", !"Jester",
	!"Sultan", !"Stratum", !"Elegy", !"Raindance", !"RC Tiger", !"Flash",
	!"Tahoma", !"Savanna", !"Bandito", !"Freight Flat Trailer (Train)",
	!"Streak Trailer (Train)", !"Kart", !"Mower", !"Dune", !"Sweeper",
	!"Broadway", !"Tornado", !"AT400", !"DFT-30", !"Huntley", !"Stafford",
	!"BF-400", !"Newsvan", !"Tug", !"Petrol Trailer", !"Emperor", !"Wayfarer",
	!"Euros", !"Hotdog", !"Club", !"Freight Box Trailer (Train)",
	!"Article Trailer 3", !"Andromada", !"Dodo", !"RC Cam", !"Launch",
	!"Police Car (LSPD)", !"Police Car (SFPD)", !"Police Car (LVPD)",
	!"Police Ranger", !"Picador", !"S.W.A.T.", !"Alpha", !"Phoenix",
	!"Glendale Shit", !"Sadler Shit", !"Baggage Trailer \"A\"",
	!"Baggage Trailer \"B\"", !"Tug Stairs Trailer", !"Boxville",
	!"Farm Trailer", !"Utility Trailer"
},
	E_TDW_VEHICLE_SA_CATEGORY:TDW_g_sVehicleCategory[MAX_VEHICLE_MODELS + 1] =
{
	OFF_ROAD,       SALOONS,        SPORT,          INDUSTRIAL,
	STATION_WAGONS, SALOONS,        UNIQUE,         PUBLIC_SERVICE,
	INDUSTRIAL,     UNIQUE,         SALOONS,        SPORT,
	LOWRIDERS,      INDUSTRIAL,     INDUSTRIAL,     SPORT,
	PUBLIC_SERVICE, HELICOPTERS,    STATION_WAGONS, SALOONS,
	PUBLIC_SERVICE, SALOONS,        INDUSTRIAL,     UNIQUE,
	OFF_ROAD,       HELICOPTERS,    SALOONS,        PUBLIC_SERVICE,
	UNIQUE,         SPORT,          BOATS,          PUBLIC_SERVICE,
	PUBLIC_SERVICE, PUBLIC_SERVICE, UNIQUE,         TRAILERS,
	SALOONS,        PUBLIC_SERVICE, PUBLIC_SERVICE, CONVERTIBLES,
	INDUSTRIAL,     RADIOC,         UNIQUE,         INDUSTRIAL,
	OFF_ROAD,       SALOONS,        BOATS,          HELICOPTERS,
	BIKES,          UNIQUE,         TRAILERS,       SPORT,
	BOATS,          BOATS,          BOATS,          INDUSTRIAL,
	INDUSTRIAL,     UNIQUE,         STATION_WAGONS, INDUSTRIAL,
	AIRPLANE,       BIKES,          BIKES,          BIKES,
	RADIOC,         RADIOC,         SALOONS,        SALOONS,
	BIKES,          HELICOPTERS,    OFF_ROAD,       BIKES,
	BOATS,          BOATS,          SALOONS,        SPORT,
	AIRPLANE,       SPORT,          INDUSTRIAL,     STATION_WAGONS,
	CONVERTIBLES,   BIKES,          INDUSTRIAL,     UNIQUE,
	BOATS,          UNIQUE,         UNIQUE,         HELICOPTERS,
	HELICOPTERS,    OFF_ROAD,       PUBLIC_SERVICE, SALOONS,
	SALOONS,        BOATS,          SPORT,          OFF_ROAD,
	SPORT,          HELICOPTERS,    INDUSTRIAL,     INDUSTRIAL,
	OFF_ROAD,       RADIOC,         SPORT,          SPORT,
	SALOONS,        OFF_ROAD,       SPORT,          SALOONS,
	UNIQUE,         BIKES,          BIKES,          AIRPLANE,
	AIRPLANE,       AIRPLANE,       INDUSTRIAL,     INDUSTRIAL,
	SALOONS,        SALOONS,        SALOONS,        AIRPLANE,
	AIRPLANE,       BIKES,          BIKES,          PUBLIC_SERVICE,
	INDUSTRIAL,     UNIQUE,         SALOONS,        SALOONS,
	PUBLIC_SERVICE, SALOONS,        UNIQUE,         INDUSTRIAL,
	UNIQUE,         CONVERTIBLES,   LOWRIDERS,      LOWRIDERS,
	LOWRIDERS,      UNIQUE,         UNIQUE,         UNIQUE,
	SALOONS,        SPORT,          SALOONS,        INDUSTRIAL,
	PUBLIC_SERVICE, UNIQUE,         SALOONS,        SALOONS,
	HELICOPTERS,    SALOONS,        SALOONS,        SALOONS,
	INDUSTRIAL,     AIRPLANE,       INDUSTRIAL,     CONVERTIBLES,
	OFF_ROAD,       OFF_ROAD,       SPORT,          SPORT,
	SALOONS,        STATION_WAGONS, SALOONS,        HELICOPTERS,
	RADIOC,         SPORT,          LOWRIDERS,      LOWRIDERS,
	OFF_ROAD,       TRAILERS,       TRAILERS,       UNIQUE,
	UNIQUE,         OFF_ROAD,       UNIQUE,         LOWRIDERS,
	LOWRIDERS,      AIRPLANE,       INDUSTRIAL,     OFF_ROAD,
	SALOONS,        BIKES,          INDUSTRIAL,     UNIQUE,
	TRAILERS,       SALOONS,        BIKES,          SPORT,
	UNIQUE,         SPORT,          TRAILERS,       TRAILERS,
	AIRPLANE,       AIRPLANE,       RADIOC,         BOATS,
	PUBLIC_SERVICE, PUBLIC_SERVICE, PUBLIC_SERVICE, PUBLIC_SERVICE,
	INDUSTRIAL,     PUBLIC_SERVICE, SPORT,          SPORT,
	SALOONS,        INDUSTRIAL,     TRAILERS,       TRAILERS,
	TRAILERS,       INDUSTRIAL,     TRAILERS,       TRAILERS
},
	E_TDW_VEHICLE_SA_TYPE:TDW_g_sVehicleType[MAX_VEHICLE_MODELS + 1] =
{
	CAR,       CAR,       CAR,       CAR,       CAR,       CAR,       CAR,
	CAR,       CAR,       CAR,       CAR,       CAR,       CAR,       CAR,
	CAR,       CAR,       CAR,       HELICOPTE, CAR,       CAR,       CAR,
	CAR,       CAR,       CAR,       CAR,       HELICOPTE, CAR,       CAR,
	CAR,       CAR,       BOAT,      CAR,       CAR,       CAR,       CAR,
	TRAILER,   CAR,       CAR,       CAR,       CAR,       CAR,       RC,
	CAR,       CAR,       CAR,       CAR,       BOAT,      HELICOPTE, MOTORBIKE,
	TRAIN,     TRAILER,   CAR,       BOAT,      BOAT,      BOAT,      CAR,
	CAR,       CAR,       CAR,       CAR,       PLANE,     MOTORBIKE, MOTORBIKE,
	MOTORBIKE, RC,        RC,        CAR,       CAR,       MOTORBIKE, CAR,
	CAR,       CAR,       BOAT,      BOAT,      CAR,       CAR,       PLANE,
	CAR,       CAR,       CAR,       CAR,       BIKE,      CAR,       CAR,
	BOAT,      CAR,       CAR,       HELICOPTE, HELICOPTE, CAR,       CAR,
	CAR,       CAR,       BOAT,      CAR,       CAR,       CAR,       HELICOPTE,
	CAR,       CAR,       CAR,       RC,        CAR,       CAR,       CAR,
	CAR,       CAR,       CAR,       CAR,       BIKE,      BIKE,      PLANE,
	PLANE,     PLANE,     CAR,       CAR,       CAR,       CAR,       CAR,
	PLANE,     PLANE,     MOTORBIKE, MOTORBIKE, MOTORBIKE, CAR,       CAR,
	CAR,       CAR,       CAR,       CAR,       CAR,       CAR,       CAR,
	CAR,       CAR,       CAR,       CAR,       TRAIN,     TRAIN,     CAR,
	CAR,       CAR,       CAR,       CAR,       CAR,       CAR,       CAR,
	CAR,       HELICOPTE, CAR,       CAR,       CAR,       CAR,       PLANE,
	CAR,       CAR,       CAR,       CAR,       CAR,       CAR,       CAR,
	CAR,       CAR,       HELICOPTE, RC,        CAR,       CAR,       CAR,
	CAR,       TRAIN,     TRAIN,     RC,        CAR,       CAR,       CAR,
	CAR,       CAR,       PLANE,     CAR,       CAR,       CAR,       MOTORBIKE,
	CAR,       CAR,       TRAILER,   CAR,       MOTORBIKE, CAR,       CAR,
	CAR,       TRAIN,     TRAILER,   PLANE,     PLANE,     RC,        BOAT,
	CAR,       CAR,       CAR,       CAR,       CAR,       CAR,       CAR,
	CAR,       CAR,       CAR,       TRAILER,   TRAILER,   TRAILER,   CAR,
	TRAILER,   TRAILER
};

// -----------------------------------------------------------------------------
// Functions:

/** ------------------------------------------------------------------------ **\
<summary>GetModelStaticSpeed</summary>
<param name="modelid">The model id</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetModelStaticSpeed(modelid)
{
	if (0 == IS_VALID_MODEL(modelid))
		return -1;
	return TDW_g_sVehicleSpeed[modelid - MIN_VEHICLE_MODEL];
}

/** ------------------------------------------------------------------------ **\
<summary>GetModelStaticIdFromName</summary>
<param name="const name[]">The model name</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock
	GetModelStaticIdFromName(const name[])
{
	for (new i = sizeof TDW_g_sVehicleNames; --i != 0;) {
		if (strcmp(name, TDW_g_sVehicleNames[i], true) != 0)
			continue;
		return i + MIN_VEHICLE_MODEL;
	}
	return 0;
}

/** ------------------------------------------------------------------------ **\
<summary>GetModelStaticNameFromId</summary>
<param name="modelid">The model id</param>
<param name="name[]">An array into which to store the name</param>
<param name="name_size">The length of the string that should be stored</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock GetModelStaticNameFromId(modelid, name[], name_size = sizeof name)
{
	if (0 == IS_VALID_MODEL(modelid))
		return _:(name[0] = '\0'); // return 0
	name[0] = '\0';
	return strunpack(name, TDW_g_sVehicleNames[modelid - MIN_VEHICLE_MODEL],
		name_size);
}

/** ------------------------------------------------------------------------ **\
<summary>GetModelStaticCategory</summary>
<param name="modelid">The model id</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock E_TDW_VEHICLE_SA_CATEGORY:GetModelStaticCategory(modelid)
{
	if (0 == IS_VALID_MODEL(modelid))
		return E_TDW_VEHICLE_SA_CATEGORY:-1;
	return TDW_g_sVehicleCategory[modelid - MIN_VEHICLE_MODEL];
}

/** ------------------------------------------------------------------------ **\
<summary>GetModelStaticType</summary>
<param name="modelid">The model id</param>
<returns>
	-
</returns>
<remarks>
</remarks>
\** ------------------------------------------------------------------------ **/

stock E_TDW_VEHICLE_SA_TYPE:GetModelStaticType(modelid)
{
	if (0 == IS_VALID_MODEL(modelid))
		return E_TDW_VEHICLE_SA_TYPE:-1;
	return TDW_g_sVehicleType[modelid - MIN_VEHICLE_MODEL];
}
