/*
 * Node.h
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#ifndef NODE_H_
#define NODE_H_

#include "Geography.h"
#include <string>

class Node{
	
	/**
	 * @brief Node's ID
	 */
	long long ID;
	
	/**
	 * @brief Node's degrees geographic coordinates
	 */
	GeoCoordinate deg_coords;
	
	/**
	 * @brief Node's radians geographic coordinates
	 */
	GeoCoordinate rad_coords;
public:
	
	/**
	* @brief Node default constructor
	*/
	Node();
	
	/**
	 * @brief Constructs a Node
	 */
	Node(long long node_id, GeoCoordinate node_deg_coords, GeoCoordinate node_rad_coords);
	
	/**
	 * @brief Gets the Node's geographic degrees coordinates
	 */
	const GeoCoordinate getDegCoords();
	
	/**
	 * @brief Gets the Node's geographic radians coordinates
	 */
	const GeoCoordinate getRadCoords();
	
	/**
	 * @brief Gets the Node's ID
	 */
	long long getId() const;

	/**
	 * @brief Node equals comparison
	 */
	bool operator==(const Node& n1) const;
};

#endif /* NODE_H_ */
