#include "shell.h"


using namespace starkey;
using namespace std;


namespace starkey
{
	shell::shell(ALLEGRO_BITMAP* initial_bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy, int angle) :sprite(initial_bitmap, world_width, world_height, initial_x, initial_y, initial_vx, initial_vy)
	{
		currentAngle = angle;

		initialVX = initial_vx * std::cos(currentAngle * PI / 180);
		initialVY = initial_vy * std::sin(currentAngle * PI / 180);
		groundExplosion = al_load_bitmap("explosion2.png");
		tankExplosion = al_load_bitmap("explosion4.png");
	}

	void shell::draw(ALLEGRO_DISPLAY *display)
	{		
		if (hitGround == true && explosionOver == false)
		{
			al_draw_bitmap(groundExplosion, currentX - 90, currentY - 100, 0);
		}
		else if (tankGame->GetCurrentGameState() == TankGame::HIT_TARGET)
		{
			al_draw_bitmap(groundExplosion, currentX - 90, currentY - 100, 0);
		}
		else if (explosionOver == false)
		{
			al_draw_rotated_bitmap(currentBitmap, 50, 0, currentX, currentY, currentAngle * PI / 180, 0); //I planed to rotate rocket in flight, but ran out of time :-(.
		}
	}

	//I tried to get the physics working with the formulas you provided, but failed. 
	//I substituted another method that I hope is acceptable, even though I'm not sure it's accurate.
	void shell::advance_by_time(double dt)
	{
		//Used a static to store culmative time
		static double dta, dtExplosion;
		if (inverseFlight == false)
		{
			
			dta = dta + dt;
			if (hitGround == false)
			{
				dtExplosion = 0;
				currentVX = initialVX + 0 * dta;
				currentVY = initialVY + EARTHGRAVITY * dta;

				currentX = 150 + ((initialVX * dta) + (.5 * 0) * (dta * dta));
				currentY = 1020 - ((initialVY * dta) + (.5 * EARTHGRAVITY) * (dta * dta));
			}
			else
			{
				if (dtExplosion == 0)
				{
					dtExplosion = dta;
				}

				if (dta - dtExplosion > .5)
				{
					explosionOver = true;
					readyToDispose = true;
					dta = 0;
					dtExplosion = 0;

					if (tankGame->GetCurrentPlayer() == TankGame::PLAYER_1)
					{
						tankGame->SetCurrentPlayer(TankGame::PLAYER_2);
					}
					else
					{
						tankGame->SetCurrentPlayer(TankGame::PLAYER_1);
					}
				}
			}
		}
		else
		{			
			dta = dta + dt;
			if (hitGround == false)
			{
				dtExplosion = 0;
				currentVX = initialVX + 0 * dta;
				currentVY = initialVY + EARTHGRAVITY * dta;

				currentX = 1810 - ((initialVX * dta) + (.5 * 0) * (dta * dta));
				currentY = 1020 - ((initialVY * dta) + (.5 * EARTHGRAVITY) * (dta * dta));
			}
			else
			{
				if (dtExplosion == 0)
				{
					dtExplosion = dta;
				}

				if (dta - dtExplosion > .5)
				{
					explosionOver = true;
					readyToDispose = true;
					dta = 0;
					dtExplosion = 0;

					if (tankGame->GetCurrentPlayer() == TankGame::PLAYER_1)
					{
						tankGame->SetCurrentPlayer(TankGame::PLAYER_2);
					}
					else
					{
						tankGame->SetCurrentPlayer(TankGame::PLAYER_1);
					}
				}
			}
		}
		

		if (currentY > 1060 && dta > 1)
		{
			hitGround = true;		
		}
	}

	bool shell::isShellReadyToDispose() const
	{
		return readyToDispose;
	}

	void shell::SetGame(TankGame *game)
	{
		tankGame = game;
	}
		
	void shell::InverseFlight(bool flight)
	{
		inverseFlight = flight;
	}

	shell::~shell()
	{
		al_destroy_bitmap(groundExplosion);
		al_destroy_bitmap(tankExplosion);		
	}
}
