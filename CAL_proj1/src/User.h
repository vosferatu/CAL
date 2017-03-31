/*
 * User.h
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#ifndef USER_H_
#define USER_H_

#include <string>
#include <stack>
#include "CPoint.h"

#define PAYPAL 0
#define CREDIT 1

class User{
	/*
	 * @brief User's name
	 */
	std::string name;

	/*
	 * @brief User's password
	 */
	std::string password;

	/*
	 * @brief User's payment method
	 */
	int pay_method;

	/*
	 * @brief User's payment number
	 */
	int pay_no;

	/**
	 * @brief Last CPoint visited;
	 */
	size_t last;
public:
	User() {
		last = 0;
		pay_no = 0;
		pay_method = 0;
	}

	/*
	 * @brief User constructor
	 */
	User(std::string cli_name, std::string cli_password, int cli_pay_method, int cli_pay_no, size_t cli_last);

	/*
	 * @brief Gets User's name
	 */
	const std::string& getName() const;

	/*
	 * @brief Gets User's payment method
	 */
	const int getPayMethod() const;

	/*
	 * @brief Gets User's payment number
	 */
	int getPayNo() const;

	/*
	 * @brief Gets User's password
	 */
	const std::string& getPassword() const;

	/*
	 * @brief Gets the index of the last visited CPoint
	 */
	size_t getLast() const;

	/*
	 * @brief User extraction operator
	 */
	friend std::ofstream& operator<<(std::ofstream& out, const User user);
};



#endif /* USER_H_ */
