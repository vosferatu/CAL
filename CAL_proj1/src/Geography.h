/*
 * Geography.h
 *
 *  Created on: 14/03/2017
 *      Author: bmsp2
 */

#ifndef GEOGRAPHY_H_
#define GEOGRAPHY_H_

#include <math.h>
#include <cfloat>

class GeoCoordinate{
	/**
	 * @brief Latitude
	 */
	float lat;
	/**
	 * @brief Longitude
	 */
	float lon;
public:
	/**
	* @brief Longitude Minimum
	*/
	static float lonMin;

	/**
	* @brief Longitude Maximum
	*/
	static float lonMax;
	
	/**
	* @brief Latitude Minimum
	*/
	static float latMin;
	
	/**
	* @brief Latitude Maximum
	*/
	static float latMax;
	
	/**
	 * @brief GeoCoordinate default constructor
	 */
	GeoCoordinate();
	
	/**
	 * @brief Creates a GeoCoordinate
	 */
	GeoCoordinate(float latitude, float longitude);

	/**
	 * @brief Returns the latitude
	 */
	float getLat() const;

	/**
	 * @brief Returns the longitude
	 */
	float getLon() const;

	/**
	 * @brief Returns the distance between two places
	 * @param place Place to compare
	 */
	int getDistanceFromLatLon(const GeoCoordinate place);
};

#endif /* GEOGRAPHY_H_ */
