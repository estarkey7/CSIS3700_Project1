#ifndef TANKGAME_H
#define TANKGAME_H


namespace starkey
{
	class TankGame
	{
		public:
			TankGame();
			enum GameState
			{
				WAITING_TO_FIRE,
				FIRED,
				HIT_TARGET,
				END_GAME
			};

			enum Players
			{
				PLAYER_1,
				PLAYER_2
			};
						

			GameState GetCurrentGameState();
			Players GetCurrentPlayer();
			void SetGameState(GameState currentState);
			void SetCurrentPlayer(Players currentPlayer);
			void Play();
			void Fire();
			bool IsGameOver();
			Players GetWinner();
			virtual ~TankGame();

	protected:
		GameState CurrentGameState;
		Players CurrentPlayer;
		bool gameOver = false;
		

	};
}
#endif

