#include "stdafx.h"
#include "Bunker.h"
#include "Line.h"
#include "Bullet.h"

Bunker::Bunker(float posX, float posY) : m_posX(posX), m_posY(posY)
{
	Line base(-10, 0, 10, 0, 1, 0, 0, m_posX, m_posY);
	Line left(-10, 0, -20, -10, 1, 0, 0, m_posX, m_posY);
	Line right(10, 0, 20, -10, 1, 0, 0, m_posX, m_posY);
	m_bunkerLines.push_back(base);
	m_bunkerLines.push_back(left);
	m_bunkerLines.push_back(right);
}

void Bunker::Draw()
{
	for (int i = 0; i < m_bunkerLines.size(); i++) {
		m_bunkerLines[i].Draw();
	}
	for (int i = 0; i < m_bullets.size(); i++) {
		m_bullets[i].Draw();
	}
}

bool Bunker::IsHit(float posX, float posY)
{
	return m_posX - 20 <= posX && posX <= m_posX + 20 && m_posY - 20 <= posY && posY <= m_posY;
}

void Bunker::Fire()
{
	if (m_lastFire < 500) return;
	m_lastFire = 0;
	float hyp = sqrtf(powf(m_shipPosX - m_posX, 2) + powf(m_shipPosY - m_posY,  2));
	float iHat = (m_shipPosX - m_posX) / hyp;
	float jHat = (m_shipPosY - m_posY) / hyp;

	Bullet bullet(m_posX, m_posY, 2, iHat, jHat, 1, 0, 0, 200);
	m_bullets.push_back(bullet);
}

void Bunker::Update(float dt)
{

	m_animTime = dt / 1000.0f;
	m_lastFire += dt;
	for (int i = 0; i < m_bullets.size(); i++) {
		m_bullets[i].Update(dt);
		if (m_bullets[i].GetLifeTime() > 1.0f) {
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
	Fire();
}
