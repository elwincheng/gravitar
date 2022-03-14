#include "stdafx.h"
#include "GameInfo.h"
#include "App/AppSettings.h"
#include "App/app.h"
#include "Spaceship.h"
#include <string>

GameInfo::GameInfo() 
{
}

void GameInfo::Initialize()
{
	m_fuel = 10000;
	m_score = 10;
	m_lives = 5;
	m_lost = false;
	m_lostTime = 0.0f;
	for (int i = 5; i > 0; i--)
	{
		Spaceship ship;
		ship.Initialize(APP_VIRTUAL_WIDTH / 2 - 300 + i * 30, APP_VIRTUAL_HEIGHT - 50);
		m_spaceships.push_back(ship);
	}
}

void GameInfo::LoseLife()
{
	m_lives--;
	m_spaceships.pop_back();
}

void GameInfo::Draw() 
{
	App::Print(APP_VIRTUAL_WIDTH / 2 - 50, APP_VIRTUAL_HEIGHT - 50, "SCORE");
	App::Print(APP_VIRTUAL_WIDTH / 2 - 50, APP_VIRTUAL_HEIGHT - 100, "FUEL");

	std::string fuel = std::to_string(m_fuel);
	const char* pfuel = fuel.c_str();

	std::string score = std::to_string(m_score);
	const char* pscore = score.c_str();

	App::Print(APP_VIRTUAL_WIDTH / 2 + 100, APP_VIRTUAL_HEIGHT - 50, pscore);
	App::Print(APP_VIRTUAL_WIDTH / 2 + 100, APP_VIRTUAL_HEIGHT - 100, pfuel);

	for (int i = 0; i < m_spaceships.size(); i++)
	{
		m_spaceships[i].Draw();
	}
}
