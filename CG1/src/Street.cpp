/*
 * Street.cpp
 *
 *  Created on: 14/03/2017
 *      Author: bmsp2
 */

#include "Street.h"
#include <string>

Street::Street(int number_ID, std::string street_name, bool two_way_street){
	id=number_ID;
	name=street_name;
	two_way=two_way_street;
}


int Street::getId() const {
	return id;
}

const std::string& Street::getName() const {
	return name;
}

bool Street::isTwoWay() const {
	return two_way;
}

