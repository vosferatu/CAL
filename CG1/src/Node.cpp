/*
 * Node.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include "Node.h"
#include "Geography.h"
#include <string>

Node::Node(int node_id, GeoCoordinate node_deg_coords, GeoCoordinate node_rad_coords/*, int node_bikes, int node_places*/)
{
	ID=node_id;
	deg_coords=node_deg_coords;
	rad_coords=node_rad_coords;
	/*bikes=node_bikes;
	places=node_places;*/
}

/*int Node::getPlaces() const {
	return places;
}

int Node::getBikes() const {
	return bikes;
}*/

const GeoCoordinate Node::getDegCoords(){
	return deg_coords;
}

const GeoCoordinate Node::getRadCoords(){
	return rad_coords;
}

int Node::getId() const {
	return ID;
}
