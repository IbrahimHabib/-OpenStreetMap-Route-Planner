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

// TODO: Add the ParseLine function here.
vector<int> ParseLine(string line)
{
    istringstream myline(line);
    vector<int> sv;
    char c;
    int n;
    while (myline>>n>>c)
    {
        sv.push_back(n);
    }
    return sv;
    
}

vector<vector<int>> ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<int>> board;
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      board.push_back(ParseLine(line));
    }
  }
  return board;
}

void PrintBoard(const vector<vector<int>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << board[i][j];
    }
    cout << "\n";
  }
}
int main() {
   
  // TODO: Store the output of ReadBoardFile in the "board" variable.
  vector<vector<int>> board;
  board=ReadBoardFile("./tests/1.board");
  // TODO: Uncomment PrintBoard below to print "board".
   PrintBoard(board);
}