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
	float lat;
	/*
	 * @brief floatitude
	 */
	float lon;
	/*
	 * @brief Altitude
	 */
	//float alt;
public:
	/*
	 * @brief GeoCoordinate default constructor
	 */
	GeoCoordinate();
	/*
	 * @brief Creates a GeoCoordinate
	 */
	GeoCoordinate(float latitude, float floatitude);

	/*
	 * @brief Returns the latitude
	 */
	float getLat() const;

	/*
	 * @brief Returns the floatitude
	 */
	float getLon() const;
};

#endif /* GEOGRAPHY_H_ */
