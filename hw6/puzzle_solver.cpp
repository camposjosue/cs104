 #include "puzzle_solver.h"
#include "heap.h"

 PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph) : _b(b) {
 	//_b=b;
 	_ph=ph;
 	_expansions = -1;
 }

  // Destructor
 PuzzleSolver::~PuzzleSolver(){

 }

  // Run the A* search and builds the solution and tracks
  // the number of expansions
  void PuzzleSolver::run(){
  	PuzzleMoveScoreComp comp;
  	PuzzleMoveBoardComp comp2;
  	PuzzleMoveSet closedList(comp2);

  	Heap<PuzzleMove*, PuzzleMoveScoreComp> openlist(2, comp);

  	PuzzleMove* something = new PuzzleMove(&_b);
  	something->h = _ph->compute(_b);
  	closedList.insert(something);
  	openlist.push(something);

  	//bool solved;

  	//_expansions=0;

  	while(!openlist.empty() && something->b->solved() == false){
  		//Board* theBoard = something->b;
		something = openlist.top();
  		openlist.pop();
  		
  	
			map<int, Board*> nextMoves = something->b->potentialMoves();

			for(map<int, Board*>::iterator it = nextMoves.begin(); it != nextMoves.end(); ++it){
				PuzzleMove* temp= new PuzzleMove(it->first, it->second, something);
				temp->h = _ph->compute(*it->second);

				set<PuzzleMove*, PuzzleMoveScoreComp>:: iterator it2 = closedList.find(temp);

				if(it2 == closedList.end()){
				// cout<<"*******************************************************************"<<endl;
				// cout<<"WHILE: "<<fun<<" "<<fun<<" "<<fun<<endl;
				// cout<<it->first;
				// cout<<*(it->second)<<endl;
				// cout<<"###################################################"<<endl;
					openlist.push(temp);
					closedList.insert(temp);
					_expansions++;
				}
				else{
					delete temp;
				}
			}
  
  	}
  	//if(){
  		//_solution.push_front->something->tileMove;
  			while(something-> prev != NULL){
  				_solution.push_front(something->tileMove);
  				something = something->prev;
  			}
  			//break;
  		//}
  	
  		// delete something;
  		// set<PuzzleMove*, PuzzleMoveScoreComp>:: iterator it3;
  		// for(it3 = closedList.begin(); it3!= closedList.end(); ++it3){
  		// 	closedList.erase(it3);
  		// }

		


  }

  // Return the solution deque
  std::deque<int> PuzzleSolver::getSolution(){
  	return _solution;
  }

  // Return how many expansions were performed in the search
  int PuzzleSolver::getNumExpansions(){
  	return _expansions;
  }