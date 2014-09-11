//#include<StdAfx.h>      //Important if you are using Microsoft Visual Studio
#include "Game.h"
#include <iostream>
#include <limits.h>
using namespace std;   //Using standard namespace

void Game::init()
{
}

void Game::DrawBoard() 
{
	m_board.DrawBoard();
}

int Game::HumanPlay(IPlayer &currPlayer)
{
	int cellNo;
	
	cout << "Player " << currPlayer.getPlayeNo() + 1 << ", enter a cell number:  ";
    cin >> cellNo;

    if (!m_board.isCellOccupied(cellNo))
	{
		currPlayer.placeMarker(cellNo);
		return 0;
	}
    else
    {
        cout<<"Cell is already Occupied, please select another cell ";

        cin.ignore();
        cin.get();
    }
	return -1;
}

int Game::ComputerPlay (IBoard& b, IPlayer& p, int &nBestPos,unsigned int depth)
{
	int nBestScore =  p.IsComputer()? INT_MIN : INT_MAX; 

	if (depth == 0)
	{
		nBestScore =  hHeuristicFunction.Evaluate(b,p);
		return nBestScore;
	}

	for (unsigned int i = 1; i<= b.getNumCells() ; i++)
	{
		if (!b.isCellOccupied(i))
		{
			p.placeMarker(i);
			int nCurrentSocre = ComputerPlay(b, getOpponent(p.getPlayeNo()),nBestPos,depth-1);
				
			if (((nCurrentSocre > nBestScore) && p.IsComputer()) || ((nCurrentSocre < nBestScore) && !p.IsComputer()) )
			{
				nBestScore = nCurrentSocre;
				nBestPos = i;
			}
			p.unPlaceMarker(i);

		}
	}
	return nBestScore;
}

void Game::Play()
{
	int playeNo = 0,prevPlayNo;

	do
	{
		DrawBoard();

		IPlayer &currPlayer = getCurrentPlayer(playeNo);

		if (!currPlayer.IsComputer())
		{
			if(HumanPlay(currPlayer) == -1)
				continue;
		}
		else
		{
			int nBestPos = -1;
			ComputerPlay(m_board,currPlayer,nBestPos,m_depth);

			if(nBestPos != -1)
				currPlayer.placeMarker(nBestPos);
		}
		prevPlayNo = playeNo;

		playeNo = (playeNo + 1) % 2;
		currentState = IN_PROGRESS;
	}
	while (!checkWin() && !checkDraw());

	DrawBoard();

    if(checkWin())
	{
		currentState = WIN;
		cout<<"==>\aPlayer "<<getCurrentPlayer(prevPlayNo).getPlayeNo() + 1<<" win ";
	}
    else if(checkDraw())
	{
		currentState = DRAW;;
        cout<<"==>\aGame draw";
	}

    cin.ignore();
    cin.get();

}

