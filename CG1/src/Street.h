/*
 * Street.h
 *
 *  Created on: 14/03/2017
 *      Author: bmsp2
 */

#ifndef STREET_H_
#define STREET_H_

#include <string.h>

class Street{
	/*
	 *	@brief Street's unique ID
	 */
	int id;
	/*
	 *	@brief Street's name
	 */
	std::string name;
	/*
	 *	@brief If it allows vehicles to travel in both directions
	 */
	bool two_way;
public:
	/*
	 * @brief Creates a Street
	 */
	Street(int number_ID, std::string street_name, bool two_way_street);
	/*
	 * @brief Returns the ID
	 */
	int getId() const;
	/*
	 * @brief Returns the name
	 */
	const std::string& getName() const;
	/*
	 * @brief Returns true if street is 'two-way'
	 */
	bool isTwoWay() const;
};



#endif /* SRC_STREET_H_ */
