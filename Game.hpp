#pragma once
#include "Entity.hpp"
#include <vector>
#include <future>
#include <thread>
class Game
{
public:
	void init();
	Game(const Game&) = delete;
	static Game& Instance();
	void RemoveEntity(Entity* entity);
	void AddEntity(Entity* entity);
private:
	void update();
	Game();
	~Game();
	std::vector<Entity*> entities;
	std::future<std::string> inputFuture;
	bool gameRunning;
};