#include <stdio.h>
#include <emscripten.h> // note we added the emscripten header
#include "game.cpp"

#ifdef __cplusplus
extern "C" {
#endif

int EMSCRIPTEN_KEEPALIVE get_score(int buffer[], int buffer_size) {
    Game g;
    char board[3][3];
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (buffer[i*3+j] == 1118830592) {
                board[i][j] = 'X';
            }
            if (buffer[i*3+j] == 1117650944) {
                board[i][j] = 'O';
            }
            if (buffer[i*3+j] == 1110704128) {
                board[i][j] = '-';
            }
        }
    }
    int result = g.score(board);
    return result; 
}


int EMSCRIPTEN_KEEPALIVE is_game_over(int buffer[], int buffer_size) {
    Game g;
    char board[3][3];
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (buffer[i*3+j] == 1118830592) {
                board[i][j] = 'X';
            }
            if (buffer[i*3+j] == 1117650944) {
                board[i][j] = 'O';
            }
            if (buffer[i*3+j] == 1110704128) {
                board[i][j] = '-';
            }
        }
    }
    int result = g.gameOver(board);
    return result; 
}

int EMSCRIPTEN_KEEPALIVE get_next_move(int buffer[], int buffer_size) {
    Game g;
    char board[3][3];
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (buffer[i*3+j] == 1118830592) {
                board[i][j] = 'X';
            }
            if (buffer[i*3+j] == 1117650944) {
                board[i][j] = 'O';
            }
            if (buffer[i*3+j] == 1110704128) {
                board[i][j] = '-';
            }
        }
    }
    Move AImove = g.minimax(board);
    return AImove.x*10+AImove.y;
}

#ifdef __cplusplus
}
#endif



int main(){
    //Game g;
    //char board[3][3] = { {'X', 'O', 'X'}, {'-', 'O', '-'}, {'-', 'X', '-'} };
    //Move AImove = g.minimax(board);
    //cout << AImove.x << " " << AImove.y << endl;
    return 0;
}