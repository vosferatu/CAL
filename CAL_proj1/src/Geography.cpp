/*
 * Geography.cpp
 *
 *  Created on: 14/03/2017
 *      Author: bmsp2
 */

#include "Geography.h"

GeoCoordinate::GeoCoordinate() : lat {0}, lon {0} {};

GeoCoordinate::GeoCoordinate(float latitude, float floatitude){
	lat=latitude;
	lon=floatitude;
}

float GeoCoordinate::getLon() const {
	return lon;
}

float GeoCoordinate::getLat() const {
	return lat;
}

int GeoCoordinate::getDistanceFromLatLon(const GeoCoordinate place) {
		int R = 6371000;
		float a = sin((place.getLat() - lat) / 2)
												* sin((place.getLat() - lat) / 2)
												+ cos(lat) * cos(place.getLat())
												* sin((place.getLon() - lon) / 2)
												* sin((place.getLon() - lon) / 2);
		float c = 2 * atan2(sqrt(a), sqrt(1 - a));
		float d = R * c;
		return d;
	}

float GeoCoordinate::latMin=FLT_MAX;
float GeoCoordinate::latMax=FLT_MIN;
float GeoCoordinate::lonMin=FLT_MAX;
float GeoCoordinate::lonMax=FLT_MIN;
