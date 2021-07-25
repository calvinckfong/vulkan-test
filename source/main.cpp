/*
 * main.cpp
 *
 *  Created on: 2021年7月10日
 *      Author: calvin.fong
 */

#include "vkobject.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main()
{
	VKObject app;

	try {
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


