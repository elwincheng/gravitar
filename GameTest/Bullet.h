#pragma once
#include "Line.h"
#include <vector>
class Bullet
{
public:
	Bullet(float posX, float posY, float radius, float iHat, float jHat, float r, float g, float b, float vel);
	void Draw();

	void Update(float dt);

	float GetLifeTime() { return m_lifeTime;  }

	void GetPos(float& x, float& y) { x = m_posX, y = m_posY; }


private:
	float m_posX = 0.0f;
	float m_posY = 0.0f;
	float m_radius = 0.0f;
	float m_velX = 0.0f;
	float m_velY = 0.0f;
	float m_iHat = 0.0f;
	float m_jHat = 0.0f;
	float m_velocity = 500.0f;
	float m_animTime = 0.0f;
	float m_lifeTime = 0.0f;
	std::vector<Line> m_bullet;
};

