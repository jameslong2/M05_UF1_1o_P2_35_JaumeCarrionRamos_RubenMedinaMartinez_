#pragma once
#include "ConsoleUtils.h"
#include "Map.h"
#include "TimeManager.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

class Enemy
{

private:
	COORD direction;
	COORD position;
	COORD spawn;
	char character = 'X';
	float powerup_countdown = 0;
	const float powerup_countdown_time = 15;
	ConsoleUtils::CONSOLE_COLOR foreground = ConsoleUtils::CONSOLE_COLOR::DARK_RED;
	ConsoleUtils::CONSOLE_COLOR background = ConsoleUtils::CONSOLE_COLOR::DARK_RED;

	ConsoleUtils::CONSOLE_COLOR foreground_powerup = ConsoleUtils::CONSOLE_COLOR::CYAN;
	ConsoleUtils::CONSOLE_COLOR background_powerup = ConsoleUtils::CONSOLE_COLOR::CYAN;

	ConsoleUtils::CONSOLE_COLOR foreground_attack = ConsoleUtils::CONSOLE_COLOR::DARK_RED;
	ConsoleUtils::CONSOLE_COLOR background_attack = ConsoleUtils::CONSOLE_COLOR::DARK_RED;

	void RandomDirection();
public:
	enum ENEMY_STATE { ENEMY_NONE, ENEMY_KILLED, ENEMY_DEAD };
	Enemy();
	Enemy(COORD _spawn);
	ENEMY_STATE Update(Map* _map, COORD _player);


	void Draw();
	void PowerUPicked();

};


