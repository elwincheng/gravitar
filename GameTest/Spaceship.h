#pragma once
#include <vector>
#include <queue>
#include "Line.h"
#include "App/AppSettings.h"
#include "Bullet.h"

class Spaceship
{
public:
	Spaceship();

	void GetPos(float& x, float& y) { x = m_posX; y = m_posY; }

	void SetPos(float x, float y) { m_posX = x; m_posY = y; }

	void SetVel(float vx, float vy) { m_velX = vx; m_velY = vy; }
	
	void Initialize(float posX, float posY);

	float getLastFire() { return m_lastFire; }

	void Accelerate(bool isAccelerate) { m_isAccelerate = isAccelerate; }

	void Explode() { m_isExplode = true; }

	bool getExplode() { return m_isExplode; }

	void Update(float dt);

	void Rotate(float thetaDot);

	std::vector<Bullet> GetBullets() { return m_bullets; }

	void FireBullet();

	void Draw();

	bool IsHit(std::vector<Bullet> bullets);

private:
	float m_posX = 0.0f;
	float m_posY = 0.0f;
	float m_animTime = 0.0F;
	float m_angle = PI / 2.0f;
	float m_velX = 0.0f;
	float m_velY = 0.0f;
	float m_accelX = 0.0f;
	float m_accelY = 0.0f;
	float m_fueld = 0.0f;
	float m_lastFire = 0.0f;
	float m_explodeTime = 0.0f;
	bool m_isExplode = false;
	bool m_isAccelerate = false;
	float m_acceleration = 100.0f;
	std::vector<Line> m_ship;
	std::vector<Bullet> m_bullets;

};

