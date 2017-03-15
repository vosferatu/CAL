/*
 * Node.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include <Node.h>

Node::Node(int node_id, std::string node_name, GeoCoordinate node_coords, int node_bikes, int node_places)
{
	ID=node_id;
	name=node_name;
	coords=node_coords;
	bikes=node_bikes;
	places=node_places;
}

int Node::getPlaces() const {
	return places;
}

int Node::getBikes() const {
	return bikes;
}

const GeoCoordinate& Node::getCoords(){
	return coords;
}

int Node::getId() const {
	return ID;
}

const std::string& Node::getName() const {
	return name;
}
