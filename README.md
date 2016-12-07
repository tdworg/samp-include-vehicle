# TDW Vehicle Library

### About the library
Collection of missing libraries for vehicles in SA:MP.

### Installation
1. Download library.
2. All files move into folder `pawno/includes`. But, you can use the flag `-i<path>` to specify an alternative path.
3. Include it:
```PAWN
#include <a_samp> // standart SAMP library
#include <vh_utils>
```

### Libraries:
| Name        | Description |
|------------:|:------------|
| [vh_dstatus](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/utils/damage_status.inc)  | Library that adds new functions to edit the status of visual damage. |
| [vh_dwos](https://github.com/TDW-org/samp-include-vehicle/blob/master/vh_dwos.inc)     | Contains many functions for working with doors and windows of the vehicles. Besides, this library defines new callbacks that are called when doors or windows have been updated. |
| [vh_handling](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/data/gtasa_handling.inc) | Detail information about the vehicles. |
| [vh_idata](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/data/important_data.inc)    | All important information about the vehicles, such as: color, spawn positions, angles, model id. |
| [vh_iterator](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/data/iterator.inc) | Adds a new iterator that is used for only foreach loops. |
| [vh_math](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/utils/math_functions.inc)     | Contains different mathematical functions. |
| [vh_nplate](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/utils/number_plate.inc)   | Functions that are help you work with number plates of vehicles. |
| [vh_odata](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/data/other_data.inc)    | Add additionally information about the vehicles, such as: interior id, paintjob id, virtualworld id, etc.. |
| [vh_sadata](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/data/gtasa_data.inc)   | Minimum information about the vehicles, such as: category, type, max. speed. |
| [vh_sscanf](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/utils/sscanf_custom_parameter.inc)   | It adds a new custom parameter in sscanf. |
| [vh_tune](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/data/tuning_data.inc)     | Information about tuning components for the vehicles. |
| [vh_utils](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/utils/useful_functions.inc)    | Contains many useful functions for the vehicles. |
| [vh_lock](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/data/lock.inc)    | Contains many useful functions to lock/unlock the vehicles. |

### Systems:
| Name        | Description |
|------------:|:------------|
| [vhs_3dlabel](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/3dtext_label.inc) | Creates a new 3D label for vehicles. |
| [vhs_limiter](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/limiter.inc) | Creates speed limits for vehicles. |
| [vhs_trailer](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/trailer_manage.inc) | Adds new callbacks to checks on attach or detach trailer. |
| [vhs_tuning](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/tuning_manage.inc)  | Saves the tuning vehicles. |
| [vhs_mileage](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/mileage.inc) | Calculates mileage of the vehicle. |
| [vhs_neon](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/neon.inc) | Adds new functions for working with neon. |
| [vhs_policelights](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/police_lights.inc) | Adds new functions for working with police lights. |
| [vhs_signals](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/turn_signals.inc) | Adds turn signals |
| [vhs_engine](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/engine.inc) | Helps you to manage with the engine and fuel systems |
| [vhs_lock](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/lock.inc)    | Wrapper of vh_lock library that adds all the functionality in the game. |
| [vhs_radar](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/radar.inc)    | Adds the radars |
| [vhs_booster](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/booster.inc)    | Boost forward for vehicles. |
| [vhs_drift](https://github.com/TDW-org/samp-include-vehicle/blob/master/tdw_vehicle/system/drift.inc)    | Drift!!! |
