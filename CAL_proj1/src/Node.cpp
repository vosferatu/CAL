/*
 * Node.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include "Node.h"
#include "Geography.h"
#include <string>

Node::Node(){}

Node::Node(int node_id, GeoCoordinate node_deg_coords, GeoCoordinate node_rad_coords, bool node_collection_point/*, int node_bikes, int node_places*/)
{
	ID=node_id;
	deg_coords=node_deg_coords;
	rad_coords=node_rad_coords;
	collection_point=node_collection_point;
	/*bikes=node_bikes;
	places=node_places;*/
}

bool Node::isCollectionPoint() const {
	return collection_point;
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
