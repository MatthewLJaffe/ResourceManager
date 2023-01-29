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

//detects is box 1 is inside box 2 or if box 2 is inside box 1
bool utils::boxCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	return (((x1 - w1/2 > x2 - w2/2 && x1 - w1/2 < x2 + w2/2) || (x1 + w1/2 > x2 - w2/2 && x1 + w1/2 < x2 + w2/2)) || 
			((x2 - w2/2 > x1 - w1/2 && x2 - w2/2 < x1 + w1/2) || (x2 + w2/2 > x1 - w1/2 && x2 + w2/2 < x1 + w1/2))) &&
			(((y1 - h1/2 > y2 - h2/2 && y1 - h1/2 < y2 + h2/2) || (y1 + h1/2 > y2 - h2/2 && y1 + h1/2 < y2 + h2/2)) ||
			((y2 - h2/2 > y1 - h1/2 && y2 - h2/2 < y1 + h1/2) || (y2 + h2/2 > y1 - h1/2 && y2 + h2/2 < y1 + h1/2)));
}

int utils::roundFloat(float f)
{
	return static_cast<int>(std::round(f));
}