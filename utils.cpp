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
