#pragma once
#include <vector>
#include "Spaceship.h"
class GameInfo
{
public:
	GameInfo();
	void Initialize();
	void Draw();
	void LoseLife();
	void SetFuel(int fuel) { m_fuel = fuel; }
	void SetScore(int score) { m_score = score; }
	int GetFuel() { return m_fuel; }
	int GetLives() { return m_lives; }
	int GetScore() { return m_score; }
	void SetGameLost(bool state) { m_lost = state; }
	bool GetGameLost() { return m_lost; }
	void SetLives(int lives) { m_lives = lives; }
	void Update(float dt) { m_lostTime += dt; }
	float GetLostTime() { return m_lostTime; }
private:
	int m_score = 0;
	int m_fuel = 10000;
	int m_lives = 5;
	bool m_lost = false;
	float m_lostTime = 0.0f;
	std::vector<Spaceship> m_spaceships;
};

