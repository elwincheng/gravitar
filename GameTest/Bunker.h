#pragma once
#include <vector>
#include "Bullet.h"
#include "Line.h"
class Bunker
{
public:
	Bunker(float posX, float posY);

	void SetShipPos(float posX, float posY) { m_shipPosX = posX; m_shipPosY = posY; }

	std::vector<Bullet> GetBullets() { return m_bullets; }

	void Update(float dt);

	void Fire();

	void Draw();

	bool IsHit(float posX, float posY);

private:
	float m_posX = 0.0f;
	float m_posY = 0.0f;
	float m_shipPosX = 0.0f;
	float m_shipPosY = 0.0f;
	float m_animTime = 0.0f;
	float m_lastFire = 0.0f;
	std::vector<Bullet> m_bullets;
	std::vector<Line> m_bunkerLines;
};

