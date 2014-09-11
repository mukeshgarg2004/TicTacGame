#ifndef __GAME
#define __GAME
#include "Marker.h"
#include "Cell.h"
#include "Player.h"
#include "Board.h"
#include <vector>
#include "Heuristic.h"
using namespace std;

//class Board;
//class Player;

enum GameState
{
	START,
	IN_PROGRESS,
	WIN,
	DRAW
};

class IGame
{
public:
	virtual void AddPlayer(IPlayer &p) = 0;
	virtual void DrawBoard()= 0;
	virtual void init()= 0;
	virtual bool checkWin()= 0;
	virtual bool checkDraw()= 0;
	virtual void Play()= 0;
	virtual IPlayer& getCurrentPlayer(int playerNo)= 0;
	virtual int HumanPlay(IPlayer &currPlayer)= 0;
	virtual int ComputerPlay (IBoard& b, IPlayer& p, int &nBestPos,unsigned int depth)= 0;
	virtual IPlayer& getOpponent(unsigned int playerNo)= 0;
};

class Game : public IGame
{
	IBoard &m_board;
	unsigned int m_depth;
	vector<IPlayer*> m_players;
	GameState currentState;
	IHeuristic &hHeuristicFunction;

public:
	Game(IBoard &board,IHeuristic &h,unsigned int d):m_board(board),currentState(START),hHeuristicFunction(h),m_depth(d){}
	void AddPlayer(IPlayer &p) { m_players.push_back(&p);}
	void DrawBoard();
	void init();
	bool checkWin() {return m_board.checkWin();}
	bool checkDraw() 
	{
		if(m_board.isBoardFull())
			return true;
		return false;
	}
	void Play();
	IPlayer& getCurrentPlayer(int playerNo){ return *m_players[playerNo];}
	int HumanPlay(IPlayer &currPlayer);
	int ComputerPlay (IBoard& b, IPlayer& p, int &nBestPos,unsigned int depth);
	IPlayer& getOpponent(unsigned int playerNo)
	{
		playerNo = (playerNo + 1) % 2; 
		return getCurrentPlayer(playerNo);
	}
};

#endif