#include "Utils.hpp"

float utils::hireTimeInSeconds()
{
    float t = SDL_GetTicks();
    t *= 0.001f;
    return t;
}

vector<string> utils::split(const string& s, char delim)
{
	istringstream iss(s);
	string item;
	vector<string> elems;
	while (getline(iss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

bool utils::inRect(float p_x, float p_y, float r_x, float r_y, float r_w, float r_h)
{
	return p_x >= r_x && p_x <= r_x + r_w && p_y >= r_y && p_y <= r_y + r_h;
}

float utils::lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

float utils::randomFloat(float lower, float upper)
{
	return lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upper - lower)));
}
