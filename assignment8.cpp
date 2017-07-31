#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <stdexcept>

using namespace std;

const int NUMROWS = 7;// CAN BE CHANGED FOR DIFFERENT GAME PLAY
const int NUMCOLS = 10;// CAN BE CHANGED FOR DIFFERENT GAME PLAY
const int TAILLENGTH = 15;// CAN BE CHANGED FOR DIFFERENT GAME PLAY

struct _cell
{
    char marker;
    int moveNumber;
};

void initBoard (_cell (&board)[NUMROWS][NUMCOLS]){
    for (int i=0; i<NUMROWS; ++i){
        for (int j=0; j<NUMCOLS; ++j){
            board[i][j].marker='_';
            board[i][j].moveNumber=0;
        }
    }
}

void placePiece (_cell (&board)[NUMROWS][NUMCOLS], int& x, int& y, char symbol, int (move)){
    board[x][y].marker=symbol;
}


void showBoard (_cell (board)[NUMROWS][NUMCOLS], int (move)){
    for (int i=0; i<NUMROWS; ++i){
        for (int j=0; j<NUMCOLS; ++j){
            cout<<board[i][j].marker<<" ";
        }
        cout<<endl;
    }
}


void clearTail (_cell (&board)[NUMROWS][NUMCOLS], int move){
    for (int a=0; a<NUMROWS;++a){
        for (int b=0; b<NUMCOLS;++b){
            if ((board[a][b].moveNumber<=move-TAILLENGTH)&&(board[a][b].marker!='X')&&(board[a][b].marker!='U')){
                board[a][b].moveNumber=0;
                board[a][b].marker='_';
            }
        }
    }
}


void movePlayer (_cell (&board)[NUMROWS][NUMCOLS], int& x, int& y, int move){

    char input;
    board[x][y].marker='u';
    board[x][y].moveNumber=move;

    int b;

    cout<<"Enter direction (N/S/E/W): ";
    cin>>input;

    switch (input){
        case 'W':
            --y;
            break;
        case 'E':
            ++y;
            break;
        case 'S':
            ++x;
            break;
        case 'N':
            --x;
            break;
    }

    if ((x<NUMROWS)&&(x>=0)&&(y<NUMCOLS)&&(y>=0)&&(board[x][y].marker!='X')&&(board[x][y].marker!='x')&&(board[x][y].marker!='u')){
        board[x][y].marker='U';
    }
    else if ((x>=NUMROWS)||(y>=NUMCOLS)||(x<0)||(y<0)){
        cout<<"YOU FELL OFF THE BOARD!"<<endl;
        throw runtime_error("lose");
    }
    else {
        throw runtime_error("lose");
    }
}



void moveOpponent (_cell (&board)[NUMROWS][NUMCOLS], int& x, int& y, int move){
    srand(time(0));
    board[x][y].marker='x';
    board[x][y].moveNumber=move;

    int a;
    int i=0;
    int b=0;
    a=rand()%4;

    while (true){
        if (i>=4){
            clearTail(board,move);
            throw runtime_error("win");

        }
        if (b){
            break;
        }

        switch (a%4){
            case 0:
                if ((y-1<0)||(board[x][y-1].marker=='U')||(board[x][y-1].marker=='u')||(board[x][y-1].marker=='x')){
                    ++a;
                    ++i;
                }
                else{
                    --y;
                    ++b;
                }
                break;				
	

            case 1:
                if ((y+1>=NUMCOLS)||(board[x][y+1].marker=='U')||(board[x][y+1].marker=='u')||(board[x][y+1].marker=='x')){

                    ++a;
                    ++i;
                }
                else{
                    ++y;
                    ++b;

                }           
				break;

            case 2:
                if ((x+1>=NUMROWS)||(board[x+1][y].marker=='U')||(board[x+1][y].marker=='u')||(board[x+1][y].marker=='x')){
                    ++a;
                    ++i;
                }
                else{
                    ++x;
                    ++b;
                }           
				break;
				
            case 3:
                if ((x-1<0)||(board[x-1][y].marker=='U')||(board[x-1][y].marker=='u')||(board[x-1][y].marker=='x')){
                    ++a;
                    ++i;
                }
                else{
                    --x;
                    ++b;

                }           
				break;
        }
    }

    

    if (b){

        board[x][y].marker='X';
        clearTail(board,move);
    }

}



void processException (runtime_error excpt, bool& win) {

    string apple=excpt.what();

    if (apple=="win"){
        win=true;
    }
    else {
        win=false;
    }
}



int main() {
srand((unsigned int)time(NULL));
int uRow = 0, uCol = 0;
int oRow = NUMROWS - 1, oCol = NUMCOLS - 1;
bool win = true;
int move = 0;
_cell board[NUMROWS][NUMCOLS];
initBoard(board);
placePiece(board, uRow, uCol, 'U', move);
placePiece(board, oRow, oCol, 'X', move);
showBoard(board, move);
while (true) {
move++;
try {
movePlayer(board, uRow, uCol, move);
moveOpponent(board, oRow, oCol, move);
showBoard(board, move);
}
catch (runtime_error &excpt) {
processException(excpt, win);
break;
}
}
showBoard(board, move);
if (win)
cout << "*** YOU WIN! ***" << endl;
else
cout << "*** YOU LOSE! ***" << endl;
string tmp; getline(cin, tmp); // optional
}

