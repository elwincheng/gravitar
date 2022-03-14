//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <vector>
#include <string>
//------------------------------------------------------------------------
#include "app\app.h"
#include "App\AppSettings.h"
//------------------------------------------------------------------------
#include "Spaceship.h"
#include "Bunker.h"
#include "Planet.h"
#include "GameInfo.h"
//------------------------------------------------------------------------
Spaceship ship;
Planet planet;
GameInfo gameInfo;

//------------------------------------------------------------------------
/* This challenge was fun. Thank you. I learned a lot. */

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	planet.Initiialize();
	ship.Initialize(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_WIDTH / 2.0f);
	gameInfo.Initialize();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	float posX, posY;
	ship.GetPos(posX, posY);
	planet.SetShipPos(posX, posY);
	planet.Update(deltaTime);

	// Check if planet bunker is hit by ship's bullets
	planet.IsHit(ship.GetBullets());
	gameInfo.SetScore(planet.GetNumBunkersDestroyed() * 1000);
	std::vector<Bunker> bunkers = planet.GetBunkers();
	// Check if ship is hit by bunkers

	if (gameInfo.GetFuel() <= 0)
	{
		gameInfo.SetLives(0);
	}

	if (gameInfo.GetLives() <= 0) 
	{
		gameInfo.SetGameLost(true);
	}

	if (gameInfo.GetGameLost())
	{
		gameInfo.Update(deltaTime);
		if (gameInfo.GetLostTime() > 2500 && App::IsKeyPressed(' '))
		{
			gameInfo.Initialize();
			planet.Initiialize();
			ship.Initialize(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_WIDTH / 2.0f);
		}
		return;
	}


	for (int i = 0; i < bunkers.size(); i++) {
		if (ship.IsHit(bunkers[i].GetBullets()))
		{
			if (!ship.getExplode())
			{
				App::PlaySound(".\\Sounds\\short_explosion.wav");
				ship.Explode();
				gameInfo.LoseLife();
			}
		}
	}
	if (posY <= 110)
	{
		if (!ship.getExplode())
		{
			App::PlaySound(".\\Sounds\\short_explosion.wav");
			ship.Explode();
			gameInfo.LoseLife();
		}
	}

	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		ship.Rotate(-6);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		ship.Rotate(6);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		ship.Accelerate(true);
		gameInfo.SetFuel(gameInfo.GetFuel() - 1);
	}
	else {
		ship.Accelerate(false);
	}

	if (App::IsKeyPressed(' ')) 
	{
		if (ship.getLastFire() >= 200) 
		{
			App::PlaySound(".\\Sounds\\long_laser.wav");
			ship.FireBullet();
			gameInfo.SetFuel(gameInfo.GetFuel() - 25);

		}

	}
	ship.Update(deltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	//------------------------------------------------------------------------
	if (gameInfo.GetGameLost())
	{
		std::string score = std::to_string(gameInfo.GetScore());
		const char* pscore = score.c_str();

		App::Print(APP_VIRTUAL_WIDTH / 2 - 60, APP_VIRTUAL_HEIGHT / 2 + 50, "YOU LOST!", 1, 0, 0);

		App::Print(APP_VIRTUAL_WIDTH / 2 - 100, APP_VIRTUAL_HEIGHT / 2, "TOTAL SCORE:");
		App::Print(APP_VIRTUAL_WIDTH / 2 + 50, APP_VIRTUAL_HEIGHT / 2, pscore, 0, 0, 1);

		App::Print(APP_VIRTUAL_WIDTH / 2 - 130, APP_VIRTUAL_HEIGHT / 2 - 50, "PRESS 'SPACE' TO RESTART", 0, 1, 0);
		return;
	}
	ship.Draw();
	planet.Draw();
	gameInfo.Draw();
	//------------------------------------------------------------------------

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
}