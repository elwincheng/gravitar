#include "stdafx.h"
#include "Bullet.h"
#include "App/AppSettings.h"

Bullet::Bullet(float posX, float posY, float radius, float iHat, float jHat, float r, float g, float b, float vel) : m_posX(posX), m_posY(posY), m_radius(radius), m_iHat(iHat), m_jHat(jHat), m_velocity(vel)
{
	for (float i = 0.0f; i < 360.0f; i++) 
	{
		float ex = m_radius * cosf(i * PI / 180.0f);
		float ey = m_radius * sinf(i * PI / 180.0f);
		Line line(0, 0, ex, ey, r, g, b, m_posX, m_posY);
		m_bullet.push_back(line);
	}
}


void Bullet::Draw()
{
	for (int i = 0; i < m_bullet.size(); i++) 
	{
		m_bullet[i].Draw();
	}
}

void Bullet::Update(float dt)
{
	m_animTime = dt / 1000.0f;
	m_lifeTime += m_animTime;
	m_posX += m_velocity * m_iHat * m_animTime;
	m_posY += m_velocity * m_jHat * m_animTime;
	for (int i = 0; i < m_bullet.size(); i++) 
	{
		m_bullet[i].SetPos(m_posX, m_posY);
	}
}

