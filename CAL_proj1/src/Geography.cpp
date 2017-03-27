/*
 * Geography.cpp
 *
 *  Created on: 14/03/2017
 *      Author: bmsp2
 */

#include "Geography.h"

GeoCoordinate::GeoCoordinate() : lat {0}, lon {0} {};

GeoCoordinate::GeoCoordinate(float latitude, float longitude){
	lat=latitude;
	lon=longitude;
}

float GeoCoordinate::getLon() const {
	return lon;
}

float GeoCoordinate::getLat() const {
	return lat;
}
