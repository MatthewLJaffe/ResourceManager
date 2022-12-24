#pragma once
#include <SDL.h>
#include <string>
#include <Vector>
#include <sstream>
using namespace std;


namespace utils
{
    float hireTimeInSeconds();
	vector<string> split(const string& s, char delim);
}