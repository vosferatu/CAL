/*
 * CPoint.h
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#ifndef CPOINT_H_
#define CPOINT_H_

#include "Node.h"
#include <fstream>
#include <string>

class CPoint{
	/**
	 * @brief CPoint's name
	 */
	std::string name;
	/**
	 * @brief CPoint's available bikes
	 */
	int bikes;
	/**
	 * @brief CPoint's available parking places
	 */
	int places;
	/**
	 * @brief Pointer to the correspondent node
	 */
	Node* col_node;
	/**
	 * @brief CPoint's altitude
	 */
	double altitude;
	/**
	 * @brief CPoint's distance
	 */
	int distance;
public:
	CPoint();
	/**
	* @brief CPoint constructor;
	*/
	CPoint(std::string name_cpoint, int bikes_cpoint, int places_cpoint, Node* col_node_cpoint, double altitude_cpoint);
	/**
	 * @brief Gets the number of available bikes
	 * @return Number of available bikes
	 */
	int getBikes() const;

	/**
	 * @brief Gets the number of available parking places
	 * @return Number of available parking places
	 */
	int getPlaces() const;

	/**
	 * @brief Gets the Collection Node
	 * @return Collection Node
	 */
	Node* getColNode() const;

	/**
	 * @brief Gets CPoint's name
	 * @return CPoint's name
	 */
	const std::string& getName() const;

	/**
	 * @brief Gets CPoint's distance
	 * @return CPoint's distance
	 */
	int getDistance() const;

	/**
	 * @brief Alters CPoint's distance to a new distance
	 * @param nDistance new distance
	 */
	void setDistance(int nDistance);
	/**
	 * @brief Gets CPoint's altitude
	 * @return CPoint's altitude
	 */
	double getAltitude() const;

	/**
	 * @brief Rent a bike from this CPoint
	 */
	void rentBike();

	/**
	 * @brief Return a bike from this CPoint
	 */
	void returnBike();

	/**
	 * @brief CPoint extraction operator
	 */
	friend std::ofstream& operator<<(std::ofstream& out, const CPoint& point);
};

#endif
