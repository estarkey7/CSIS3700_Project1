#include "world.h"
#include "allegro5/allegro.h"



using namespace starkey;
namespace starkey
{
	world::world(ALLEGRO_DISPLAY *display, std::size_t window_width, std::size_t window_height)
	{

		windowWidth = window_width;
		windowHeight = window_height;
		

		//Create fonts
		scoreBoardFont = al_load_ttf_font("TOSCA___.ttf", 72,0);
		statsFont = al_load_ttf_font("DigitaldreamFat.ttf", 35, 0);
				
		//Create Sprites		
		createPlayers();
		createWorldBackground();
		createScoreStats();
		

	}

	

	void world::advance_by_time(double dt)
	{
		for (int x = 0; x < world::worldsSprites.size(); x++)
		{
			worldsSprites[x]->advance_by_time(dt);
		}
	}

	void world::draw(ALLEGRO_DISPLAY *display)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(backgroundImage, 0.0, 0.0, 0);
		createScoreStats();

		for (int x = 0; x < worldsSprites.size(); x++)
		{
			worldsSprites[x]->draw(display);
		}
	}

	void world::createPlayers()
	{
		playerImage = al_load_bitmap("Tank.png");
		game = new TankGame();
		Player1 = new tank(playerImage, 1920, 1080, 5, 1020, 0, 0, 1);
		Player2 = new tank(playerImage, 1920, 1080, 1800, 1020, 0, 0, 2);
		Player1->addEnemies(Player2); //I am doing this to get the reference of the enemy tank to the shell. I tried to get a reference to the world in tank, but I got a circular reference.
		Player2->addEnemies(Player1); //This is Player1 reference.
		Player1->SetGame(game); //Update
		Player2->SetGame(game);

		Player2->flipHorizontal(true);
		worldsSprites.push_back(Player1);
		worldsSprites.push_back(Player2);
	}

	
	void world::createWorldBackground()
	{
		backgroundImage = al_load_bitmap("background-2.jpg");
	}
	void world::createScoreStats()
	{				
			playerStream.str("");
			turretAngleStream.str("");
			shellVelocityStream.str("");

			playerStream.clear();
			turretAngleStream.clear();
			shellVelocityStream.clear();

			if (game->GetCurrentPlayer() == TankGame::PLAYER_1)
			{
				currentPlayer = 1;
			}
			else
			{
				currentPlayer = 2;
			}
				
			playerStream << "Player: " << currentPlayer;
			player = playerStream.str();

			turretAngleStream << "Angle: " << getPlayer(currentPlayer)->GetTurretAngle() << "   " << "Velocity: " << getPlayer(currentPlayer)->GetShellVelocity();
			angle = turretAngleStream.str();
					
			al_draw_text(scoreBoardFont, al_map_rgb(0, 0, 0), 1920 / 2, 1080 * .025, ALLEGRO_ALIGN_CENTER, "Tank Killer");
			al_draw_text(statsFont, al_map_rgb(0, 0, 0), 1920 / 2, 1080 * .1, ALLEGRO_ALIGN_CENTER, player.c_str());
			al_draw_text(statsFont, al_map_rgb(0, 0, 0), 1920 / 2, 1080 * .15, ALLEGRO_ALIGN_CENTER, angle.c_str());

			if (game->GetCurrentGameState() == TankGame::HIT_TARGET)
			{
				playerStream.str("");
				playerStream.clear();
				playerStream << "Player: " << currentPlayer << " Wins!!";
				player = playerStream.str();
				al_draw_text(scoreBoardFont, al_map_rgb(0, 0, 0), 1920 / 2, 1080 * .25, ALLEGRO_ALIGN_CENTER, "Game Over");
				al_draw_text(statsFont, al_map_rgb(0, 0, 0), 1920 / 2, 1080 * .35, ALLEGRO_ALIGN_CENTER, player.c_str());
			}
		
	}

	//Random number generator create random numbers inclusive of min and max args.
	float world::randomGenerator(float min, float max)
	{
		static int previous = 0;
		float answer;
		answer = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
		return answer;
	}

	tank * world::getPlayer(int x)
	{
		if (x == 1)
		{
			currentPlayer = 1;
			return Player1;
		}
		else if (x == 2)
		{
			currentPlayer = 2;
			return Player2;
		}
	}

	void world::IncreaseAngle()
	{
		if (game->GetCurrentGameState() != TankGame::HIT_TARGET)
		{
			if (game->GetCurrentPlayer() == TankGame::PLAYER_1)
			{
				Player1->RaiseTurret();
			}
			else
			{
				Player2->RaiseTurret();
			}
		}
		
	}

	void world::ReduceAngle()
	{
		if (game->GetCurrentGameState() != TankGame::HIT_TARGET)
		{
			if (game->GetCurrentPlayer() == TankGame::PLAYER_1)
			{
				Player1->LowerTurret();
			}
			else
			{
				Player2->LowerTurret();
			}
		}
		
	}

	void world::IncreaseVelocity()
	{
		if (game->GetCurrentGameState() != TankGame::HIT_TARGET)
		{
			if (game->GetCurrentPlayer() == TankGame::PLAYER_1)
			{
				Player1->IncreaseShellVelocity();
			}
			else
			{
				Player2->IncreaseShellVelocity();
			}
		}
		
	}

	void world::ReduceVelocity()
	{
		if (game->GetCurrentGameState() != TankGame::HIT_TARGET)
		{
			if (game->GetCurrentPlayer() == TankGame::PLAYER_1)
			{
				Player1->ReduceShellVelocity();
			}
			else
			{
				Player2->ReduceShellVelocity();
			}
		}
		
	}

	void world::Fire()
	{
		if (game->GetCurrentGameState() != TankGame::HIT_TARGET)
		{
			if (game->GetCurrentPlayer() == TankGame::PLAYER_1)
			{
				Player1->FireShell();
			}
			else
			{
				Player2->FireShell();
			}
			game->SetGameState(TankGame::FIRED);
		}
		
	}



	world::~world()
	{
		worldsSprites.clear();		
		
	}
}