#ifndef __CELL
#define __CELL
class Marker;

enum CellState
{
	EMPTY,
	OCCUPIED
};
class Cell
{
	Marker m_marker;
	CellState m_state;
public:
	Cell(char num, CellState state):m_state(state),m_marker(num){}

	void Place(Marker &marker)
	{
		m_marker = marker;
		setState(OCCUPIED);
	}
	void setUnOccupied() { setState(EMPTY);}
	bool isOccupied() { return m_state == OCCUPIED ?  true: false;}
	
	void setState(CellState state){ m_state = state;}
	char getMarker() { return m_marker.getMarkerType();}
};
#endif