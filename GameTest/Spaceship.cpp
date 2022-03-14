#include "stdafx.h"
#include "Spaceship.h"
#include "Line.h"
#include "App/AppSettings.h"
#include "Bullet.h"
#include "App/app.h"

Spaceship::Spaceship()
{
}

void Spaceship::Initialize(float posX = APP_VIRTUAL_WIDTH / 2.0f, float posY =APP_VIRTUAL_HEIGHT / 2.0f)
{
	m_angle = PI / 2.0f;
	m_posX = posX;
	m_posY = posY;
	m_velX = 0;
	m_velY = 0;
	m_accelX = 0;
	m_accelY = 0;
	m_isExplode = 0;
	Line base(-10, -10, 10, -10, 0, 0, 1, m_posX, m_posY);
	Line left(-10, -10, 0, 10, 0, 0, 1, m_posX, m_posY);
	Line right(10, -10, 0, 10, 0, 0, 1, m_posX, m_posY);
	m_ship.clear();
	m_ship.push_back(base);
	m_ship.push_back(left);
	m_ship.push_back(right);	
}

void Spaceship::FireBullet() 
{
	m_lastFire = 0;
	Bullet bullet(m_posX, m_posY, 2, cosf(m_angle), sinf(m_angle), 0, 0, 1, 200);
	m_bullets.push_back(bullet);
}

bool Spaceship::IsHit(std::vector<Bullet> bullets) 
{
	for (int i = 0; i < bullets.size(); i++)
	{
		float posX, posY;
		bullets[i].GetPos(posX, posY);
		if (m_posX - 10 <= posX && posX <= m_posX + 10 && m_posY - 10 <= posY && posY <= m_posY + 10)
		{
			return true;
		}
	}
	return false;
	
}

void Spaceship::Update(float dt) 
{
	m_animTime = dt / 1000.0f;

	if (m_isExplode)
	{
		if (m_explodeTime > 2000)
		{
			m_explodeTime = 0;
			m_isExplode = false;
			Initialize();
		}
		m_velX = 0;
		m_velY = 0;
		m_accelX = 0;
		m_accelY = 0;
		for (int i = 0; i < m_ship.size(); i++)
		{
			float sx, sy, ex, ey;
			m_ship[i].GetPoints(sx, sy, ex, ey);
			float x = (ex - sx) / 2;
			float y = (ey - sy) / 2;
			m_ship[i].SetPos(x, y);
			m_ship[i].Rotate(4);
		}
		m_explodeTime += dt;
	}

	if (m_isAccelerate) 
	{
		m_accelX = m_acceleration * cosf(m_angle);
		m_accelY = -10.0f + m_acceleration * sin(m_angle);
	}
	else 
	{
		m_accelX = 0.0f;
		m_accelY = -10.0f;
	}
	m_velX += m_accelX * m_animTime;
	m_velY += m_accelY * m_animTime;

	m_lastFire += dt;


	//m_velY -= m_animTime * m_acceleration;
	m_posX = m_posX + m_velX * m_animTime;
	m_posY = m_posY + m_velY * m_animTime;

	if (m_posX > APP_VIRTUAL_WIDTH)
	{
		m_posX = APP_VIRTUAL_WIDTH;
		m_velX = 0;
	}
	if (m_posX < 0)
	{
		m_posX = 0;
		m_velX = 0;
	}
	if (m_posY > APP_VIRTUAL_HEIGHT)
	{
		m_posY = APP_VIRTUAL_HEIGHT;
		m_velY = 0;
	}
	if (m_posY < 0)
	{
		m_posY = 0;
		m_velY = 0;
	}
	for (int i = 0; i < m_ship.size(); i++) 
	{
		m_ship[i].SetPos(m_posX, m_posY);
		m_ship[i].Update(dt);
	}
	for (int i = 0; i < m_bullets.size(); i++) 
	{
		m_bullets[i].Update(dt);
		if (m_bullets[i].GetLifeTime() > 2.0f) 
		{
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}

void Spaceship::Rotate(float thetaDot)
{
	for (int i = 0; i < m_ship.size(); i++) 
	{
		m_ship[i].Rotate(thetaDot);
	}
	m_angle += m_animTime * thetaDot;

}

void Spaceship::Draw()
{
	for (int i = 0; i < m_ship.size(); i++) 
	{
		m_ship[i].Draw();
	}
	for (int i = 0; i < m_bullets.size(); i++) 
	{
		m_bullets[i].Draw();
	}
}
