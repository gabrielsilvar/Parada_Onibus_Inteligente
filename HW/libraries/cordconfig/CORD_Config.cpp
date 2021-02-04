/*
* | File      	:	CORD_Config.cpp
* | Author      :   Gabriel da Rocha Silva
* | Function    :   Measure distance of GPS coordinates
* | Info        :	It has two methods. The second method is accurate, it takes more time.
* 					The codes return the distance in kilometers. 
*----------------
* |	This version:   V0.1
* | Date        :   06-13-2020
* | Info        :   First version of this "library" codes.
**/

#include "CORD_Config.h"

double cord_dist_s(double lat_ini, double lon_ini, double lat_fin, double lon_fin){
	float deglen = 110.25;
	double x = lat_fin - lat_ini;
	double y = (lon_fin - lon_ini)*cos(lat_ini);
  
	double dist = deglen*sqrt(x*x + y*y);

	return dist; //Returns in Km
}

double cord_dist_e(double lat_ini, double lon_ini, double lat_fin, double lon_fin){
	double d2r = 0.017453292519943295769236;

	double dlong = (lon_fin - lon_ini) * d2r;
	double dlat = (lat_fin - lat_ini) * d2r;

	double temp_sin = sin(dlat/2.0);
	double temp_cos = cos(lat_ini * d2r);
	double temp_sin2 = sin(dlong/2.0);

	double a = (temp_sin * temp_sin) + (temp_cos * temp_cos) * (temp_sin2 * temp_sin2);
	double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

	return 6368.1 * c; //Returns in Km
}
