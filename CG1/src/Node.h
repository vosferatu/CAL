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
	/*
	 * @brief Node's ID
	 */
	int ID;
	/*
	 * @brief Node's name
	 */
	std::string name;
	/*
	 * @brief Node's geographic coordinates
	 */
	GeoCoordinate coords;
	/*
	 * @brief Node's available bikes
	 */
	int bikes;
	/*
	 * @brief Node's available parking places
	 */
	int places;
public:
	/*
	 * @brief Constructs a Node
	 */
	Node(int node_id, std::string node_name, GeoCoordinate node_coords, int node_bikes, int node_places);
	/*
	 * @brief Gets the number of available bikes
	 */
	int getBikes() const;
	/*
	 * @brief Gets the Node's geographic coordinates
	 */
	const GeoCoordinate getCoords();
	/*
	 * @brief Gets the Node's ID
	 */
	int getId() const;
	/*
	 * @brief Gets the Node's name
	 */
	const std::string& getName() const;
	/*
	 * @brief Gets the number of available parking places
	 */
	int getPlaces() const;
};


#endif /* NODE_H_ */
