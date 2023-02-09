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
	/// <summary>
	/// splits string into vector of strings based on delimeter
	/// </summary>
	/// <param name="s">string to split</param>
	/// <param name="delim"></param>
	vector<string> split(const string& s, char delim);
	/// <summary>
	/// determines if x, y point is inside rect
	/// </summary>
	/// <param name="p_x"></param>
	/// <param name="p_y"></param>
	/// <param name="r_x"></param>
	/// <param name="r_y"></param>
	/// <param name="r_w"></param>
	/// <param name="r_h"></param>
	/// <returns>true if point is inside rect false otherwise</returns>
	bool inRect(float p_x, float p_y, float r_x, float r_y, float r_w, float r_h);
	/// <summary>
	/// returns a random float between the upper and lower bound
	/// </summary>
	float randomFloat(float lower, float upper);
	/// <summary>
	/// linear interpolation funciton
	/// </summary>
	float lerp(float a, float b, float t); 
	/// <summary>
	/// determines if there is overlap between the two boxes
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="w1"></param>
	/// <param name="h1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	/// <param name="w2"></param>
	/// <param name="h2"></param>
	/// <returns></returns>
	bool boxCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
	/// <summary>
	/// rounds float and statically casts to nearest integer
	/// </summary>
	int roundFloat(float f);
}