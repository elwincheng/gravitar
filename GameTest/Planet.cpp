#include "stdafx.h"
#include "Planet.h"
#include "Line.h"
#include "App/AppSettings.h"
#include "Spaceship.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "App/app.h"

Planet::Planet()
{
	srand(time(NULL));
}

void Planet::Initiialize()
{
	m_bunkersDestroyed = 0;

	Line line(0, 100, APP_VIRTUAL_WIDTH, 100, 0, 1, 0, 0, 0);
	Bunker bunker1(100, 110);
	Bunker bunker2(200, 110);
	Bunker bunker3(400, 110);

	m_planetLines.clear();
	m_planetBunkers.clear();

	m_planetLines.push_back(line);
	m_planetBunkers.push_back(bunker1);
	m_planetBunkers.push_back(bunker2);
	m_planetBunkers.push_back(bunker3);

}


void Planet::Update(float dt)
{
	m_animTime = dt / 1000.0f;
	m_bunkerTime += dt;
	if (m_bunkerTime > 5000)
	{
		m_bunkerTime = 0;
		int x = rand() % APP_VIRTUAL_WIDTH;
		Bunker bunker(x, 110);
		m_planetBunkers.push_back(bunker);
	}

	for (int i = 0; i < m_planetBunkers.size(); i++)
	{
		m_planetBunkers[i].Update(dt);
		m_planetBunkers[i].SetShipPos(m_shipPosX, m_shipPosY);
	}

	for (int i = 0; i < m_planetBunkers.size(); i++)
	{
		m_planetBunkers[i].Fire();
	}

}

void Planet::IsHit(std::vector<Bullet> bullets)
{
	for (int i = 0; i < m_planetBunkers.size(); i++)
	{
		for (int j = 0; j < bullets.size(); j++) 
		{
			float x, y;
			bullets[j].GetPos(x, y);
			if (m_planetBunkers[i].IsHit(x, y))
			{
				App::PlaySound(".\\Sounds\\short_explosion.wav");
				m_bunkersDestroyed++;
				m_planetBunkers.erase(m_planetBunkers.begin() + i);
				i--;
				break;
			}

		}
	}
}

void Planet::Draw()
{
	for (int i = 0; i < m_planetLines.size(); i++)
	{
		m_planetLines[i].Draw();
	}

	for (int i = 0; i < m_planetBunkers.size(); i++)
	{
		m_planetBunkers[i].Draw();
	}

}
