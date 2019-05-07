#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using std::istringstream;
using std::cout;
using std::ifstream;
using std::string;
using std::vector;
using std::abs;
using std::sort;

enum class State {kEmpty, kObstacle, kClosed, kPath};

// Implement the ParseLine function.
auto ParseLine(string line)
{
    istringstream myline(line);
    vector<State> sv;
    char c;
    int n;
    while (myline>>n>>c)
    {
        if (n == 0)
        {
            sv.push_back(State::kEmpty);
        }
        else
        {
            sv.push_back(State::kObstacle);
        }
    }
    return sv;
    
}
// Implement the ReadBoardFile function.
auto ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<State>> board;
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      board.push_back(ParseLine(line));
    }
  }
  return board;
}

// Create the CellString function
string CellString(State cell)
{
    switch (cell)
    {
    case State::kObstacle:
        return "⛰️   ";
    case State::kClosed:
        return "2   ";
     case State::kPath: 
        return "🚗   ";
    default:
        return "0   ";
    }
}
//implement function to compare 2 nodes

bool Compare(const vector<int> first, const vector<int> sec)
{
  int f1,f2;
  f1=first[2]+first[3];
  f2=sec[2]+sec[3];

    return f1>f2;
  
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

// Implement Heuristic function

 int Heuristic(int x1, int x2, int y1, int y2)
 {
   return (abs(x2-x1)+abs(y2-y1));
 }

 // implement AddToOpen helper function

void AddToOpen(int &x, int &y, int &g,  int &h, vector<vector<int>> &opennode,vector<vector<State>> &grid )
{
   vector<int>  node;
   node.push_back(x);
   node.push_back(y);
   node.push_back(g);
   node.push_back(h);
   opennode.push_back(node);
   grid[x][y]=State::kClosed;
}

// Implement search functiom
vector<vector<State>> Search(vector<vector<State>> grid,int init[2],int goal[2] )
{
  vector<vector<int>> open {};
  int g=0;
  int x=init[0];
  int y=init[1];
  int h=Heuristic(init[0],goal[0],init[1],goal[1]);
  AddToOpen(x,y,g,h,open,grid);
  while (open.size()>0)
  {
    CellSort(&open);
    auto current=open.back();
    open.pop_back();
    x=current[0];
    y=current[1];
    grid[x][y] = State::kPath;

     if (x == goal[0] && y == goal[1]) {
      return grid;
    }

  }
  
  cout<<"NO Path is Found \n";
  return grid;
}
// Implement the PrintBoard function.
void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout <<  CellString(board[i][j]) <<"";
    }
    cout << "\n";
  }
}


#include "./../tests/tests.cpp"

int main() {
  int init[2]{0, 0};
  int goal[2]{4, 5};
  auto board =ReadBoardFile("./tests/1.board");
  auto solution = Search(board, init, goal);
  PrintBoard(solution);
  // Tests
  TestHeuristic();
  TestAddToOpen();
  TestCompare();
  
}