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

enum class State {kEmpty, kObstacle};

// Add the ParseLine function.
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
// Add the ReadBoardFile function.
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
        return "⛰️  ";
    default:
        return "0  ";
    }
}

// Add the PrintBoard function.
void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout <<  CellString(board[i][j]) <<" ";
    }
    cout << "\n";
  }
}



int main() {

  auto board =ReadBoardFile("./tests/1.board");
  PrintBoard(board);
   
}