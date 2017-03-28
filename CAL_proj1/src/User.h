/*
 * User.h
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#ifndef USER_H_
#define USER_H_

#include <string>

#define PAYPAL 0
#define CREDIT 1

class User{
	/*
	 * @brief Client's name
	 */
	std::string name;
	/*
	 * @brief Client's payment method
	 */
	int pay_method;
	/*
	 * @brief Client's payment number
	 */
	int pay_no;
public:
	User() {
	}

	/*
	 * @brief Client constructor
	 */
	User(std::string cli_name, int cli_pay_method,int cli_pay_no);

	/*
	 * @brief Gets Client's name
	 */
	const std::string& getName() const;

	/*
	 * @brief Gets Client's payment method
	 */
	const int getPayMethod() const;

	/*
	 * @brief Gets Client's payment number
	 */
	int getPayNo() const;
};



#endif /* USER_H_ */
