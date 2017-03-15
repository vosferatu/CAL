/*
 * Client.cpp
 *
 *  Created on: 15/03/2017
 *      Author: bmsp2
 */

#include "Client.h"

Client::Client(std::string cli_name,int cli_pay_method,int cli_pay_no){
	name=cli_name;
	pay_method=cli_pay_method;
	pay_no=cli_pay_no;
}

const std::string& Client::getName() const {
	return name;
}

const int Client::getPayMethod() const {
	return pay_method;
}

int Client::getPayNo() const {
	return pay_no;
}
