#include "pch.h"
#include <iostream>
#define MAP_SIZE 3

using namespace std;



class Game {
public:
	void PlayGame() {
		while (playAgain == 'y')
		{
			currentgame = 1;
			GenerateMap();
		
			while (currentgame == 1)
			{
				//Montre la carte
				ShowMap();
				//Switch de joueur
				/* Si c'était le tour de joueur1, changer pour joueur 2, sinon inverse*/
				ChangePlayer();
				//Choisit la position où il veut jouer
				SetNewPosition();

				CheckWin();
			}
			cout << "Play Again? y/n" << endl;
			cin >> playAgain;

		}


	}

	void GenerateMap() {

		for (int i = 0; i < MAP_SIZE; i++)
		{
			for (int j = 0; j < MAP_SIZE; j++)
			{
				map[i][j] = '_';
			}
		}
		currentgame = 1;
	}

	void ShowMap() {
		for (int i = 0; i < MAP_SIZE; i++)
		{
			for (int j = 0; j < MAP_SIZE; j++)
			{
				cout << map[i][j];
			}
			cout << endl;
		}

	}

	void SetNewPosition() {
		//Player Turn
		int row(0), column(0);
		bool correct = 0;
		while (correct == 0) {
			cout << "In what row and column would you like to play?" << endl;
			cout << "Row : ";
			cin >> row;
			cout << "Column : "; map[row][column] == player2;
			cin >> column;
			if (column > 3 || row > 3 || column < 1 || row < 1|| map[row-1][column-1] == player1 || map[row-1][column-1] == player2)
				cout << "Sorry, impossible to do such a thing!";
			else
				correct = 1;
		}
		row -= 1;
		column -= 1;
		map[row][column] = currentPlayer;



	}

	void CheckWin() {
		if (map[0][0] == currentPlayer && map[0][1] == currentPlayer && map[0][2] == currentPlayer)
		{
			if (currentPlayer == player2)
			{
				cout << "Player 2 Wins!" << endl;
				currentgame = 0;
			}
			else
			{
				cout << "Player 1 Wins!" << endl;
				currentgame = 0;
			}
		}

		else if (map[1][0] == currentPlayer && map[1][1] == currentPlayer && map[1][2] == currentPlayer)
		{
			if (currentPlayer == player2)
			{
				cout << "Player 2 Wins!" << endl;
				currentgame = 0;
			}
			else
			{
				cout << "Player 1 Wins!" << endl;
				currentgame = 0;
			}
		}

		else if (map[2][0] == currentPlayer && map[2][1] == currentPlayer && map[2][2] == currentPlayer)
		{
			if (currentPlayer == player2)
			{
				cout << "Player 2 Wins!" << endl;
				currentgame = 0;
			}
			else
			{
				cout << "Player 1 Wins!" << endl;
				currentgame = 0;
			}
		}

		else if (map[0][0] == currentPlayer && map[1][0] == currentPlayer && map[2][0] == currentPlayer)
		{
			if (currentPlayer == player2)
			{
				cout << "Player 2 Wins!" << endl;
				currentgame = 0;
			}
			else
			{
				cout << "Player 1 Wins!" << endl;
				currentgame = 0;
			}
		}

		else if (map[0][1] == currentPlayer && map[1][1] == currentPlayer && map[2][1] == currentPlayer)
		{
			if (currentPlayer == player2)
			{
				cout << "Player 2 Wins!" << endl;
				currentgame = 0;
			}
			else
			{
				cout << "Player 1 Wins!" << endl;
				currentgame = 0;
			}
		}


		else if (map[0][2] == currentPlayer && map[1][2] == currentPlayer && map[2][2] == currentPlayer)
		{
			if (currentPlayer == player2)
			{
				cout << "Player 2 Wins!" << endl;
				currentgame = 0;
			}
			else
			{
				cout << "Player 1 Wins!" << endl;
				currentgame = 0;
			}
		}


		else if (map[0][0] == currentPlayer && map[1][1] == currentPlayer && map[2][2] == currentPlayer)
		{
			if (currentPlayer == player2)
			{
				cout << "Player 2 Wins!" << endl;
				currentgame = 0;
			}
			else
			{
				cout << "Player 1 Wins!" << endl;
				currentgame = 0;
			}
		}

		else if (map[2][0] == currentPlayer && map[1][1] == currentPlayer && map[0][2] == currentPlayer)
		{
			if (currentPlayer == player2)
			{
				cout << "Player 2 Wins!" << endl;
				currentgame = 0;
			}
			else
			{
				cout << "Player 1 Wins!" << endl;
				currentgame = 0;
			}
		}

		else if (map[0][0] != '_' && map[0][1] != '_' && map[0][2] != '_' && map[1][0] != '_' && map[1][1] != '_' && map[1][2] != '_' && map[2][0] != '_' && map[2][1] != '_' && map[2][2] != '_')
		{
			cout << "draw" << endl;
			currentgame = 0;
		}
	}



	void ChangePlayer() {
		if (currentPlayer == player2)
		{
			currentPlayer = player1;
			cout << "Player 1's turn" << endl;
		}
		else
		{
			currentPlayer = player2;
			cout << "Player 2's turn" << endl;
		}
	}




private:
	char map[MAP_SIZE][MAP_SIZE] = { {} };
	char player1 = 'X', player2 = 'O', currentPlayer = player2;
	char playAgain = 'y';
	bool currentgame = 1;


};






int main()
{
	Game newGame;
	newGame.PlayGame();


}
