#ifndef __BOARD
#define __BOARD

#include "Marker.h"
#include "Cell.h"

#include <iostream>
#include <list>
#include <vector>
using namespace std;

class IBoard
{
public:
	void virtual DrawBoard() =0;
	void virtual PlaceMarker(unsigned int cellNo, Marker markerType) =0;
	void virtual MakeEmpty(unsigned int cellno) = 0;
	bool virtual isBoardFull() = 0;
	unsigned int virtual getNumLines() = 0;
	int virtual Eval(Marker &marker, unsigned int lineNo) = 0;
	virtual char getMarker(unsigned int cellNo) =0;
	virtual	bool isCellOccupied(unsigned int cellNo) = 0;
	virtual unsigned int getNumCells() = 0;
	virtual bool checkWin()=0;
};

class Board: public IBoard
{
	size_t m_numCells;
	vector<Cell*> m_cells;
public:
	Board(){}
	Board(int numCells) 
	{
		m_numCells = numCells;

		for(unsigned int i=0; i<m_numCells;i++)
		{
			char c = i+1+'0';
			Cell *cell = new Cell(c, EMPTY);
			m_cells.push_back(cell);
		}
	}

	size_t getNumCells() { return m_numCells;}
	unsigned int getNumLines() { return 8;}

	void DrawBoard() 
	{
		system("cls");
		cout << "\n\n\tTic Tac Toe\n\n";

		cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
		cout << endl;

		cout << "     |     |     " << endl;
		cout << "  " << m_cells[0]->getMarker()<< "  |  " << m_cells[1]->getMarker() << "  |  " << m_cells[2]->getMarker() << endl;

		cout << "_____|_____|_____" << endl;
		cout << "     |     |     " << endl;

		cout << "  " << m_cells[3]->getMarker() << "  |  " << m_cells[4]->getMarker() << "  |  " << m_cells[5]->getMarker() << endl;

		cout << "_____|_____|_____" << endl;
		cout << "     |     |     " << endl;

		cout << "  " << m_cells[6]->getMarker() << "  |  " << m_cells[7]->getMarker() << "  |  " << m_cells[8]->getMarker() << endl;

		cout << "     |     |     " << endl << endl;
	}

	void PlaceMarker(unsigned int cellNo, Marker markerType)
	{
		if((cellNo-1 >= 0) && (cellNo-1 <= m_numCells -1))
		{
			m_cells[cellNo-1]->Place(markerType);
		}
	}

	void virtual MakeEmpty(unsigned int cellno)
	{
		char c = cellno +'0';
		m_cells[cellno-1]->Place(Marker(c));
		m_cells[cellno-1]->setUnOccupied();
	}

	char getMarker(unsigned int cellNo)
	{
		return m_cells[cellNo-1]->getMarker();
	}

	bool isCellOccupied(unsigned int cellNo)
	{
		return m_cells[cellNo-1]->isOccupied();
	}

	bool isBoardFull()
	{
		for(unsigned int i=0; i<m_numCells;i++)
		{
			if(!m_cells[i]->isOccupied())
				return false;
		}
		return true;
	}

	int Eval(Marker &marker, unsigned int lineNo)
	{
		unsigned int i=1, j=2, k=3;

		switch(lineNo)
		{
		case 1:
			i=1;j=2;k=3;break; //row 1
		case 2:
			i=4;j=5;k=6;break; //row 2
		case 3:
			i=7;j=8;k=9;break; //row 3
		case 4:
			i=1;j=4;k=7;break; //column 1
		case 5:
			i=2;j=5;k=8;break;//column 2
		case 6:
			i=3;j=6;k=9;break;//column 3
		case 7:
			i=1;j=5;k=9;break;//diagonal 1
		case 8:
			i=3;j=5;k=7;break;//diagonal 2
		}

		int score = 0;
		char symbol = marker.getMarkerType();

		if (( getMarker(i)!= symbol && isCellOccupied(i)) ||(getMarker(j)!= symbol && isCellOccupied(j))||(getMarker(k)!= symbol && isCellOccupied(k)))
			score = 0;
		else 
			score = (getMarker(i) == symbol) + (getMarker(j) == symbol) + (getMarker(k) == symbol);
	
		symbol = marker.getOppMarkerType();
		if (score == 0)
		{
			if (( getMarker(i)!= symbol && isCellOccupied(i)) ||(getMarker(j)!= symbol && isCellOccupied(j))||(getMarker(k)!= symbol && isCellOccupied(k)))
				score = 0;
			else 
				score = -((getMarker(i) == symbol) + (getMarker(j) == symbol) + (getMarker(k) == symbol));
				
		}

		return score;
	}

	
	bool checkWin()
	{
		//check rows
		for(unsigned i = 1 ; i <= getNumCells() ; i+=3)
		{
			if(isCellOccupied(i) && isCellOccupied(i+1) && isCellOccupied(i+2))
			{
				if(getMarker(i) == getMarker(i+1) && getMarker(i+1) == getMarker(i+2))
					return true;
			}
		}

		//check column
		for(unsigned i = 1 ; i <= 3 ; i++)
		{
			if(isCellOccupied(i) && isCellOccupied(i+3) && isCellOccupied(i+6))
			{
				if(getMarker(i) == getMarker(i+3) && getMarker(i+3) == getMarker(i+6))
					return true;
			}
		}


		//check diagnoal
		if(isCellOccupied(1) && isCellOccupied(5) && isCellOccupied(9))
		{
			if(getMarker(1) == getMarker(5) && getMarker(5) == getMarker(9))
			{
				return true;
			}
		}
		else if(isCellOccupied(3) && isCellOccupied(5) && isCellOccupied(7))
		{
			if(getMarker(3) == getMarker(5) && getMarker(5) == getMarker(7))
			{
				return true;
			}
		}
		return false;
	}

	~Board()
	{
		if(!m_cells.empty())
		{
			for(unsigned int i=0; i<m_numCells;i++)
			{
				delete m_cells[i];
			}
		}
	}
};

#endif