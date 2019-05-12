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

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

// Implement the ParseLine function.
vector<State> ParseLine(string line)
{
    istringstream myline(line);
    vector<State> sv;
    char c;
    int n;
    while (myline >> n >> c && c == ',')
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
vector<vector<State>> ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
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

 int Heuristic(int x1, int y1, int x2, int y2)
 {
   return abs(x2 - x1) + abs(y2 - y1);
 }

 // implement CheckValidCell function

bool CheckValidCell(int x, int y, vector<vector<State>> &grid) {
  bool on_grid_x = (x >= 0 && x < grid.size());
  bool on_grid_y = (y >= 0 && y < grid[0].size());
  if (on_grid_x && on_grid_y)
    return grid[x][y] == State::kEmpty;
  return false;
}

 // implement AddToOpen helper function

void AddToOpen(int x, int y, int g,  int h, vector<vector<int>> &opennode,vector<vector<State>> &grid )
{
  opennode.push_back(vector<int>{x, y, g, h});
  grid[x][y] = State::kClosed;
}

//Implement  ExpandNeighbors function

void ExpandNeighbors(const vector<int> &current, int goal[2], vector<vector<int>> &openlist, vector<vector<State>> &grid) {
  // Get current node's data.
  int x = current[0];
  int y = current[1];
  int g = current[2];
 
  

// loop over neighbors
 int rows =  sizeof delta / sizeof delta[0];  
 for (int i = 0; i < rows; i++)
 {
  int x2 = x + delta[i][0];
  int y2 = y +delta[i][1];
   if (CheckValidCell(x2,y2,grid))
   {
    int g2 = g+1;
    int h2 = Heuristic(x2,y2,goal[0],goal[1]);
    AddToOpen(x2, y2, g2, h2, openlist, grid);

   }
   
 }
 
  

}

// Implement search functiom
vector<vector<State>> Search(vector<vector<State>> grid,int init[2],int goal[2] )
{
  vector<vector<int>> open {};
  int g=0;
  int x=init[0];
  int y=init[1];
  int h=Heuristic(x,y,goal[0],goal[1]);
  AddToOpen(x,y,g,h,open,grid);
  while (open.size() > 0)
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
 ExpandNeighbors(current, goal, open, grid);
  }
  
  cout<<"NO Path is Found \n";
  return std::vector<vector<State>>{};
}

// Create the CellString function
string CellString(State cell)
{
    switch (cell)
    {
    case State::kObstacle:
        return "⛰️   ";
     case State::kPath: 
        return "🚗   ";
    default:
        return "0   ";
    }
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
  TestSearch();
  TestCheckValidCell();
  TestExpandNeighbors();
  
}