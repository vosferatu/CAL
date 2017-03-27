/*
 * Geography.cpp
 *
 *  Created on: 14/03/2017
 *      Author: bmsp2
 */

#include "Geography.h"

GeoCoordinate::GeoCoordinate() : lat {0}, lon {0} {};

GeoCoordinate::GeoCoordinate(long latitude, long longitude){
	lat=latitude;
	lon=longitude;
}

long GeoCoordinate::getLon() const {
	return lon;
}

long GeoCoordinate::getLat() const {
	return lat;
}

int GeoCoordinate::getDistanceFromLatLonInKm(const GeoCoordinate place) {
		int R = 6371; // Radius of the earth in km
		float a = sin((place.getLat() - lat) / 2)
												* sin((place.getLat() - lat) / 2)
												+ cos(lat) * cos(place.getLat())
												* sin((place.getLon() - lon) / 2)
												* sin((place.getLon() - lon) / 2);
		float c = 2 * atan2(sqrt(a), sqrt(1 - a));
		float d = R * c; // Distance in km
		return d;
	}
