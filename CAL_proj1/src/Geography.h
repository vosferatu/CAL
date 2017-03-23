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
};

#endif /* GEOGRAPHY_H_ */
