#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string loadFileAsString(std::string file)
{
	std::ifstream f(file);
	std::stringstream s;
	s << f.rdbuf();

	return s.str();
}