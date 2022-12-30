#pragma once
#include <SDL.h>
#include <string>
#include <Vector>
#include <sstream>
#include <cmath>
using namespace std;


namespace utils
{
    float hireTimeInSeconds();
	vector<string> split(const string& s, char delim);
	bool inRect(float p_x, float p_y, float r_x, float r_y, float r_w, float r_h);
	float lerp(float a, float b, float t);
}