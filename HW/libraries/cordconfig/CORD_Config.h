/*
* | File      	:	CORD_Config.h
* | Author      :   Gabriel da Rocha Silva
* | Function    :   Measure distance of GPS coordinates
* | Info        :	It has two methods. The second method is accurate, it takes more time.
* 					Both methods return the distance in kilometers.
*----------------
* |	This version:   V0.1
* | Date        :   06-13-2020
* | Info        :   First version of this "library"
**/

#ifndef CORD_CONFIG_H
#define CORD_CONFIG_H

#include "Arduino.h"

double cord_dist_s(double lat_ini, double lon_ini, double lat_fin, double lon_fin);
double cord_dist_e(double lat_ini, double lon_ini, double lat_fin, double lon_fin);

#endif
