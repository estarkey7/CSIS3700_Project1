#include "tank.h"


using namespace std;
using namespace starkey;

namespace starkey
{
	tank::tank(ALLEGRO_BITMAP *bitmap, std::size_t world_width, std::size_t world_height, float initial_x, float initial_y, float initial_vx, float initial_vy, int ID) : vehicle(bitmap, world_width, world_height, initial_x, initial_y, initial_vx, initial_vy)
	{
		tankID = ID;
		turretImage = al_load_bitmap("turret.png");
		shellImage = al_load_bitmap("missle2.png");
		destroyedTankImage = al_load_bitmap("destroyedTank.png");
		destroyedTurretImage = al_load_bitmap("destroyedTurret.png");
		enemies = new vector<tank*>();
	}

	void tank::advance_by_time(double dt)
	{
		if (firedShell != NULL && tankGame->GetCurrentGameState() == TankGame::FIRED)
		{
			firedShell->advance_by_time(dt);
			firedShell->NotifyObservers(firedShell->GetCurrentX(), firedShell->GetCurrentY(), 18, 18);

			if (firedShell->isShellReadyToDispose() == true)
			{
				tankGame->SetGameState(TankGame::WAITING_TO_FIRE);				
				delete firedShell; //Dispose of Shell.
				firedShell = NULL;
			}
		}
		
	}

	void tank::RaiseTurret()
	{
		if (turretAngle < 90)
		{
			turretAngle++;
		}
	}

	void tank::LowerTurret()
	{
		if (turretAngle > 0)
		{
			turretAngle--;
		}
	}

	void tank::IncreaseShellVelocity()
	{
		if (shellVelocity < 10000)
		{
			shellVelocity += 5;
		}
	}

	void tank::ReduceShellVelocity()
	{
		if (shellVelocity > 0)
		{
			shellVelocity -= 5;
		}
	}


	//Fire tank shell routine creates a dynamic shell object and registers all the enemy tanks with its bounding box using the observer pattern.
	void tank::FireShell()
	{
		if (tankGame != NULL && tankGame->GetCurrentGameState() != TankGame::FIRED)
		{
			if (flipImageHorizontal == false)
			{
				tankGame->SetGameState(TankGame::FIRED);
				firedShell = new shell(shellImage, worldWidth, worldHeight, currentX, 1020, shellVelocity, shellVelocity, turretAngle);
				firedShell->SetGame(tankGame);
			}
			else
			{
				tankGame->SetGameState(TankGame::FIRED);
				firedShell = new shell(shellImage, worldWidth, worldHeight, currentX, 1020, shellVelocity, shellVelocity, turretAngle);
				firedShell->InverseFlight(true);
				firedShell->SetGame(tankGame);
			}
			
			
			//Register each enemy with the shell that is fired. Using the Observable pattern.
			for (int x = 0; x < enemies->size(); x++)
			{
				firedShell->RegisterObserver(enemies->at(x));
			}
		}
		

	}

	//Allegro draw routine
	void tank::draw(ALLEGRO_DISPLAY *display)
	{
		sprite::draw(display);				
		

		if (flipImageHorizontal == true)
		{			
			al_draw_rotated_bitmap(turretImage, 50, 0, currentX + 30, currentY + 10, turretAngle * PI / 180, ALLEGRO_FLIP_HORIZONTAL);//Angle to Radians conversion for rotation.			
		}
		else
		{			
			al_draw_rotated_bitmap(turretImage, 0, 0, currentX + 80, currentY + 10, -turretAngle * PI / 180, 0);		
		}

		//Draw the shell if it was fired
		if (tankGame != NULL && firedShell != NULL && tankGame->GetCurrentGameState() == TankGame::FIRED)
		{
			firedShell->draw(display);
		}

	}

	int tank::GetTurretAngle()
	{
		return turretAngle;
	}

	float tank::GetShellVelocity()
	{
		return shellVelocity;
	}

	//Add enemies to the tank so they can be registered with the subject.
	void tank::addEnemies(tank *enemy)
	{
		enemies->push_back(enemy);
	}

	void tank::SetGame(TankGame *game)
	{
		tankGame = game;
	}

	//Observer function which supplies the subject bounding box for hit detection.
	//We only have one enemy, but if the game needed more, this would handle it detection easily for all the objects.
	void tank::Update(int x, int y, int height, int width)
	{
		if ((x > currentX + 110 - 1) || (y > currentY + 42 - 1) || (currentX > x + height - 1) || (currentY > y + width - 1))
		{
						
		}
		else
		{
			//I'm hit!!!
			tankGame->SetGameState(TankGame::HIT_TARGET);
			currentBitmap = destroyedTankImage;
			turretImage = destroyedTurretImage;
		}
	}


	tank::~tank()
	{
		al_destroy_bitmap(turretImage);
		al_destroy_bitmap(shellImage);
		al_destroy_bitmap(destroyedTankImage);
		enemies->clear();
		delete enemies;

		if (firedShell != NULL)
		{
			delete firedShell;
		}
	}

	
}
