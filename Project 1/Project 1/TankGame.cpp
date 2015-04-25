#include "TankGame.h"

using namespace starkey;

namespace starkey
{

	TankGame::TankGame()
	{
		CurrentPlayer = PLAYER_1;
	}

	TankGame::GameState TankGame::GetCurrentGameState()
	{
		return CurrentGameState;
	}

	TankGame::Players TankGame::GetCurrentPlayer()
	{
		return CurrentPlayer;
	}

	void TankGame::SetGameState(GameState currentState)
	{
		CurrentGameState = currentState;
	}

	void TankGame::SetCurrentPlayer(Players currentPlayer)
	{
		CurrentPlayer = currentPlayer;
	}

	void TankGame::Play()
	{
		switch (CurrentPlayer)
		{
		case PLAYER_1:
			CurrentPlayer = PLAYER_2;
			break;

		case PLAYER_2:
			CurrentPlayer = PLAYER_1;
			break;
		}

		switch (CurrentGameState)
		{
			case WAITING_TO_FIRE:

				break;

			case FIRED:

				break;

			case HIT_TARGET:
				gameOver = true;
				break;
		}
	}

	bool TankGame::IsGameOver()
	{
		return gameOver;
	}

	TankGame::Players TankGame::GetWinner()
	{
		return GetCurrentPlayer();
	}

	TankGame::~TankGame()
	{
	}

}