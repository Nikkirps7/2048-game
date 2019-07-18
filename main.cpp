#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

int Board[4][4];

/* we have given direction values for s as 0, d as 1, w as 2 and a as 3.
   so if we type s the piece has to move down by one value and hence 
   dirLine for s is 1 (dirLine[0]=1),
   and as there is no change in the column for s, the dirColumn value for s is 0 (dirColumn[0]=0).
   Similarly for d the dirLine and dirColumn values are 0 and 1 respectively 
   (dirLine[1]=0 and dirColumn[1]=1), as by pressing d the piece has to move towards right.
   -1 in dirLine indicates the upward movement and -1 in dirColumn indicates movement towards left.
*/
int dirLine[] = {1, 0, -1, 0};
int dirColumn[] = {0, 1, 0, -1};

/* This function generates a random position by generating random values for line and column in the
   range [0-3]. The addPiece() function adds the value 2 to the randomly generated position using 
   generateUnoccupiedPosition().
*/
pair<int,int> generateUnoccupiedPosition(){
	int occupied = 1, line, column;
	while(occupied){
		line = rand() % 4;
		column = rand() % 4;
		if(Board[line][column]==0){
			occupied = 0;
		}
	}
	return make_pair(line,column);
}

void addPiece(){
	pair<int,int> pos = generateUnoccupiedPosition();
	Board[pos.first][pos.second] = 2;
}

void newGame(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Board[i][j] = 0;
		}
	}
	addPiece();
}

// This function prints the board.
void PrintUI(){
	system("cls");
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if(Board[i][j]==0){
				cout << setw(4) << ".";
			}
			/* setw(4) sets the size of each piece to 4 units as the maximum possible value
			   i.e 2048 has the size of 4 units. This is done to make the interface look good.
			*/
			else{
				cout << setw(4) << Board[i][j];
			}
		}
		cout<<"\n";
	}
	cout << "newgame : n, quit : q, left : a, right : d, top : w, bottom : s \n";
}

// Two pieces can be merged only when both of them are equal.
// This function checks whether the pieces follow the eligibility criteria or not.
bool canDoMove(int line, int column, int nextLine, int nextColumn){
	if(nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4
		|| (Board[line][column] != Board[nextLine][nextColumn] && Board[nextLine][nextColumn] != 0)){
		return false;
	}
	return true;
}


void applyMove(int direction){
	int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1;

	if(direction==0){
		startLine = 3;
		lineStep = -1;
	}
	if(direction==1){
		startColumn = 3;
		columnStep = -1;
	}

	int movePossible, canAddPiece = 0;

	do{
		movePossible = 0;
		for(int i = startLine; i>=0 && i<4; i += lineStep){
			for(int j = startColumn; j>=0 && j<4; j += columnStep){
				int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
				if(Board[i][j] && canDoMove(i, j, nextI, nextJ)){
					Board[nextI][nextJ] += Board[i][j];
					Board[i][j] = 0;
					movePossible = canAddPiece = 1;
				}
			}
		}
	}while(movePossible);

	if(canAddPiece){
		addPiece();
	}
}

int main()
{
	srand(time(0));
	char CommandToDir[128];
	CommandToDir['s'] = 0;
	CommandToDir['d'] = 1;
	CommandToDir['w'] = 2;
	CommandToDir['a'] = 3;

	newGame();
	while(true){
		PrintUI();
		char command;
		cin >> command;
		if(command=='n'){
			newGame();
		}
		else if(command == 'q'){
			break;
		}
		else{
			int currentDirection = CommandToDir[command];
			applyMove(currentDirection);
		}
	}
    return 0;
}