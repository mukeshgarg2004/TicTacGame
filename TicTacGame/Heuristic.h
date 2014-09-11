#include "Board.h"
#include "Player.h"

class IHeuristic
{
public:
	int virtual Evaluate(IBoard &, IPlayer &) = 0; 
};

class MinMaxHeuristic: public IHeuristic
{
public:
	int Evaluate(IBoard &board, IPlayer &player);
};