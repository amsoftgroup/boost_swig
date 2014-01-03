#pragma once

#include "HelloWorld.h"
#include "../boost_swig/logger.h"

int main(int argc, char* argv[])
{
	//client_ptr = Singleton::instance();
	logger *l1 = logger::instance();
	logger *l2 = logger::instance();
	//logger l;
	//l.set_api("57");
	//l.write_settings();


	//l.write_settings();
	return 0;

};
