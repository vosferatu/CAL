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

long GeoCoordinate::getDistance(GeoCoordinate gc1){
	/*
	 * TODO: Introduzir f�rmula que permita calcular dist�ncia entre duas coordenadas geogr�ficas
	 */
	return gc1.lat;//for now
}
