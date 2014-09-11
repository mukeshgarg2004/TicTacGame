#include "Game.h"
#include <iostream>
#include <memory>
using namespace std;   //Using standard namespace

void main()
{
	//inititialze the game board, there are 9 cells in a game
	unique_ptr<IBoard> board(new Board(9));
	unique_ptr<IHeuristic> h(new MinMaxHeuristic());
	unique_ptr<IGame> newGame(new Game(*board,*h,2));

	char name1[256]={0}, name2[256]={0};

	cout<<"Enter Type of Play "<<endl;
	cout<<"Enter 1 for:" << "Human Vs Human"<<endl;
	cout<<"Enter 2 for:" << "Computer Vs Human"<<endl;
	cout<<"Enter 3 for:" << "Computer Vs Computer"<<endl;

	int gameType = 1;
	cin>> gameType;

	int player1Type,player2Type;

	switch(gameType)
	{
	case 1:
		player1Type=player2Type = 0;
		break;
	case 2:
		player1Type=1;
		player2Type = 0;
		break;
	case 3:
		player1Type=player2Type = 1;
		break;

	default:
		{
			cout<<"Please enter valid Play Type"<<endl;
			return;
		}
	}

	//initialize the players, there are  2 players default
	cout << "Enter Player 1's Name"<< name1<<endl;
	cin>>name1;
	unique_ptr<IPlayer> player1(new Player(name1,0,PlayerType(player1Type),*board,Marker('X')));

	cout << "Enter Player 2's Name"<< name2<<endl;
	cin>>name2;
	unique_ptr<IPlayer> player2(new Player(name2,1,PlayerType(player2Type),*board,Marker('O')));

	newGame->AddPlayer(*player1);
	newGame->AddPlayer(*player2);
	newGame->Play();
   }