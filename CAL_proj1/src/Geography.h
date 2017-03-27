/*
 * Geography.h
 *
 *  Created on: 14/03/2017
 *      Author: bmsp2
 */

#ifndef GEOGRAPHY_H_
#define GEOGRAPHY_H_

#include <math.h>

class GeoCoordinate{
	/*
	 * @brief Latitude
	 */
	long lat;
	/*
	 * @brief Longitude
	 */
	long lon;
	/*
	 * @brief Altitude
	 */
	//long alt;
public:
	/*
	 * @brief GeoCoordinate default constructor
	 */
	GeoCoordinate();
	/*
	 * @brief Creates a GeoCoordinate
	 */
	GeoCoordinate(long latitude, long longitude);

	/*
	 * @brief Returns the latitude
	 */
	long getLat() const;

	/*
	 * @brief Returns the longitude
	 */
	long getLon() const;

	/*
	 * @brief Returns the distance between two places
	 * @param place Place to compare
	 */
	int getDistanceFromLatLonInKm(const GeoCoordinate place);
};

#endif /* GEOGRAPHY_H_ */
