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
	float randomFloat(float lower, float upper);
	float lerp(float a, float b, float t); 
	bool boxCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
	int roundFloat(float f);
}