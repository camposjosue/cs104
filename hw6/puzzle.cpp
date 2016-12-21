#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"
#include "heap.h"

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }
  
  Board* game = new Board(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

  int boardSize = game->size();

  PuzzleHeuristic* heur = NULL;


  if(atoi(argv[4])==1){
  	heur = new PuzzleOutOfPlaceHeuristic();
  }
  else if(atoi(argv[4])==0){
  	heur = new PuzzleBFSHeuristic();

  }
  else if(atoi(argv[4])==2){
  	heur = new PuzzleManhattanHeuristic();
  }

  int command;
  cout<< *game;

  cout<<"Enter a tile you wish to move, 0 to quit, or -1 for Hint";
  cout<<endl;

  cin>>command;

  while(command<-1 || command> boardSize){
  	cout<<"Command Invalid"<<endl;
  	cin>>command;
  }

  while(command != 0){
  	if(command == -1){
  		PuzzleSolver solveMe(*game, heur);

  		solveMe.run();

  		std::deque<int> solutions = solveMe.getSolution();

  		cout<<"Try this sequence: "<<endl;

  		for(unsigned int i=0; i<solutions.size(); i++){
  			cout<<solutions[i]<<" ";
  			//solutions.pop_front();
  		}
  		cout<<endl;
  		cout<<"Expansions: "<<solveMe.getNumExpansions();
  	}

  	else{
  		game->move(command);
  	}

  	cout<<*game;

  	if(!game->solved()){
  		cout<<"Enter a tile you wish to move, 0 to quit, or -1 for Hint";
  		cout<<endl;

  		cin>>command;

  		while(command<-1 || command> boardSize){
  			cout<<"Command Invalid"<<endl;
  			cin>>command;
  		}
  	}
  
  	else{
  		cout<<"Solved"<<endl;
  		break;
  	}

  }
  	


  delete heur;
  delete game;








  return 0;
}
