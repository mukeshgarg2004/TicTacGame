#include "Board.h"
#include <string>
using namespace std;
class Marker;

#ifndef __PLAYER
#define __PLAYER
enum PlayerType
{
	HUMAN,
	COMPUTER
};

class IPlayer
{
public:
	void virtual placeMarker(unsigned int cellNo) =0;
	void virtual unPlaceMarker(unsigned int cellNo) =0;
	virtual Marker& getMarker() = 0;
	virtual bool IsComputer() = 0;
	virtual int getPlayeNo() = 0;

};

class Player : public IPlayer
{
	PlayerType m_type;
	string m_szName;
	int m_playerNo;
	Marker m_marker;
	IBoard& m_board;
public:
	Player(char *name, int playerNum,const PlayerType &pType,IBoard &board, const Marker &marker):m_board( board)
	{ 
		m_szName = name;
		m_playerNo = playerNum;
		m_type = pType;
		m_marker = marker;
		//m_board = board;
	}
	
	int getPlayerNo() { return m_playerNo;}
	Marker& getMarker() { return m_marker;}
	void placeMarker(unsigned int CellNo)
	{
		m_board.PlaceMarker(CellNo,m_marker);
	}
	void unPlaceMarker(unsigned int CellNo)
	{
		m_board.MakeEmpty(CellNo);

	}
	
	bool IsComputer() { return m_type == COMPUTER; }
	int getPlayeNo() { return m_playerNo;}


};
#endif