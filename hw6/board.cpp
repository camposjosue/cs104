#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];
  srand(seed);
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::~Board(){
  delete _tiles;
}

Board::Board(const Board& other){
  _tiles = new int[other.size()];
  _size = other.size();
 
  for(int i=0; i<_size; i++){
    _tiles[i] = other._tiles[i];
  }

}

Board& Board::operator=(const Board& other){
  if( this == &other){
    return *this;
  }
  _tiles = new int[other.size()];
  _size = other.size();
 
  for(int i=0; i<_size; i++){
    _tiles[i] = other._tiles[i];
  }

  return *this;
}



void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(_tiles[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  int loc;

  map<int, Board*> potential; //declaring map

  for(int i =0; i < size(); i++){
    if(_tiles[i]==0)
      loc = i;
  }

  int side = dim();

  //check if there is a move west
  if(loc % side > 0){
    Board* temp = new Board(*this);
    temp->move(_tiles[loc -1]);
    //cout<<"1111111111111"<<endl;
    potential.insert(make_pair(_tiles[loc-1], temp));

   // delete temp;

  }

  //check if there is a move east
  if((loc+1) % side != 0){
    Board* temp = new Board(*this);
    temp->move(_tiles[loc + 1]);
  //  cout<<"22222222222222"<<endl;
    potential.insert(make_pair(_tiles[loc+1], temp));

     //delete temp;


  }

  //check if there is a move north
  if(loc - side >= 0){
    Board* temp = new Board(*this);
    temp->move(_tiles[loc - dim()]);
   // cout<<"3333333333333"<<endl;
    potential.insert(make_pair(_tiles[loc-dim()], temp));

    // delete temp;

  }

  //check if there is a move south
  if(loc + side <= _size-1){
    Board* temp = new Board(*this);
    temp->move(_tiles[loc + dim()]);
    //cout<<"4444444444444"<<endl;
    potential.insert(make_pair(_tiles[loc+dim()], temp));

    // delete temp;

  }
  return potential;
}


bool Board::solved() const
{
  for(int i =0; i < _size; i++){
    
    if(_tiles[i]!= i) return false;
    // if(_tiles[i]>_tiles[i+1]){
    //   return false;  
    // }
  }

  return true;
}

bool Board::operator<(const Board& rhs) const{
  int i = 0;
  bool less_than = false;
  while(i<_size){
    if(_tiles[i]<rhs._tiles[i]){
      less_than =true;
      break;
    }
    else if(_tiles[i]>rhs._tiles[i]){
      less_than=false;
      break;
    }
    i++;
  }
  return less_than;
}

std::ostream& operator<<(std::ostream &os, const Board &b){
  for(int i = 0; i <b.size(); i++){
    if(i%b.dim() == 0){
      os<<endl;
      b.printRowBanner(os);
      os<<"|";
    }
    
    if(b[i]==0){
      os<<"  |";
    }
    if(b[i]<10 && b[i] != 0){
      os<<" "<<b[i]<<"|";
    }
    else if(b[i] != 0){
      os<<b[i]<<"|";
    }
  }
  os<<endl;
  b.printRowBanner(os);

  return os;
}

const int& Board::operator[](int loc) const 
{ 
  return _tiles[loc]; 
}

int Board::size() const 
{ 
  return _size; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
