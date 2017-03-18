/*
 * Road.cpp
 *
 *  Created on: 14/03/2017
 *      Author: bmsp2
 */

#include "Road.h"

#include <string>

Road::Road(int number_ID, std::string street_name, bool two_way_street){
	id=number_ID;
	name=street_name;
	two_way=two_way_street;
}


int Road::getId() const {
	return id;
}

const std::string& Road::getName() const {
	return name;
}

bool Road::isTwoWay() const {
	return two_way;
}

