/*
 * Node.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include "Node.h"
#include "Geography.h"
#include <string>

Node::Node(long long node_id, GeoCoordinate node_deg_coords, GeoCoordinate node_rad_coords)
{
	ID=node_id;
	deg_coords=node_deg_coords;
	rad_coords=node_rad_coords;
}

const GeoCoordinate Node::getDegCoords(){
	return deg_coords;
}

const GeoCoordinate Node::getRadCoords(){
	return rad_coords;
}

long long Node::getId() const {
	return ID;
}

bool Node::operator==(const Node& n1) const{
	return ID==n1.getId();
}
