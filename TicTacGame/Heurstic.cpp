#include "Heuristic.h"

int MinMaxHeuristic::Evaluate(IBoard &board, IPlayer &player)
{
	int dHeuristicVal = 0;
	
	for (unsigned int i=1;i<=board.getNumLines();i++)
	{
		int dEval = board.Eval(player.getMarker(),i);

		if(dEval >= 0)
			dHeuristicVal += 1 * (int)pow(10,dEval);
		else
		{
			dEval *= -1;
			dHeuristicVal += -1 * (int)pow(10,dEval);
		}
	}

	return dHeuristicVal;
}