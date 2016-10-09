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
| vh_dstatus  | Library that adds new functions to edit the status of visual damage. |
| vh_dwos     | Contains many functions for working with doors and windows of the vehicles. Besides, this library defines new callbacks that are called when doors or windows have been updated. |
| vh_handling | Detail information about the vehicles. |
| vh_idata    | All important information about the vehicles, such as: color, spawn positions, angles, model id. |
| vh_iterator | Adds a new iterator that is used for only foreach loops. |
| vh_math     | Contains different mathematical functions. |
| vh_nplate   | Functions that are help you work with number plates of vehicles. |
| vh_odata    | Add additionally information about the vehicles, such as: interior id, paintjob id, virtualworld id, etc.. |
| vh_sadata   | Minimum information about the vehicles, such as: category, type, max. speed. |
| vh_sscanf   | It adds a new custom parameter in sscanf. |
| vh_tune     | Information about tuning components for the vehicles. |
| vh_utils    | Contains many useful functions for the vehicles. |

### Systems:
| Name        | Description |
|------------:|:------------|
| vhs_3dlabel | Creates a new 3D label for vehicles. |
| vhs_limiter | Creates speed limits for vehicles. |
| vhs_trailer | Adds new callbacks to checks on attach or detach trailer. |
| vhs_tuning  | Saves the tuning vehicles. |
