#include "puzzle_heur.h"
#include <cmath>
#include <stdlib.h>


int PuzzleManhattanHeuristic::compute(const Board& b){
	int total = 0;

	int iRow, iCol, row, col;
	for(int i = 0; i < b.size(); i++){
		if(b[i]!=0 && b[i]!=i){
			iRow= i / b.dim();
			iCol= i % b.dim();

			row= b[i] / b.dim();
			col= b[i] % b.dim();

			total += abs(iRow-row);
			total += abs(iCol-col);

		}

		// int temp = abs(i-b[i]);
		// total += temp/ b.dim();
		// total += temp% b.dim();
	}

	return total;
}


int PuzzleOutOfPlaceHeuristic::compute(const Board& b){
	int total=0;
	for(int i = 0; i<b.size(); i++){
		if(b[i]!=i && b[i]!=0){
			total++;
		}
	}
	return total;
	
}

int PuzzleBFSHeuristic::compute(const Board& b){

	return 0;
}