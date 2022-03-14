#pragma once
#include "Line.h"
#include <vector>
#include "Bunker.h"
#include "Spaceship.h"

class Planet
{
public:
	Planet();

	void Draw();

	void Initiialize();

	void Update(float dt);

	void SetShipPos(float posX, float posY) { m_shipPosX = posX; m_shipPosY = posY; }

	int GetNumBunkersDestroyed() { return m_bunkersDestroyed; }

	std::vector<Bunker> GetBunkers() { return m_planetBunkers; }

	void IsHit(std::vector<Bullet> bullets);

private:
	int m_bunkersDestroyed = 0;
	float m_animTime = 0.0f;
	float m_shipPosX = 0.0f;
	float m_shipPosY = 0.0f;
	float m_bunkerTime = 0.0f;
	std::vector<Line> m_planetLines;
	std::vector<Bunker> m_planetBunkers;
};

