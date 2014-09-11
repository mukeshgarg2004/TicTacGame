#ifndef __MARKER
#define __MARKER
class Marker
{
	char m_markerType;
public:
	Marker(){}
	Marker(char type):m_markerType(type){}
	char &getMarkerType() { return m_markerType;}
	char getOppMarkerType() { return m_markerType == 'X' ? 'O': 'X';}
};
#endif