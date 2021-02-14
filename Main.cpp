#include <iostream>
#include "console.h"
#include "grid.h"
#include "vector.h"
using namespace std;


struct puzzlepiece {
    string sides[4];
    int orientation;
};

bool nextlocal(int x, int width) {
    if(x < width - 1) {
        return true;
    }
    return false;
}


string getSide(puzzlepiece piece, int side) {
    int num = piece.orientation;
    return piece.sides[(num + side - 1) % 4];
}

bool checkMove(Grid<puzzlepiece> puzzle, puzzlepiece piece, int x, int y) {
    if(x > 0) {
        string side1 = getSide(puzzle[x - 1][y], 1);
        string side2 = getSide(piece, 3);
        if(side1[0] != side2[0]) {
            return false;
        }
        if(side1[1] != side2[1]) {
            return false;
        }
    }
    if(y > 0) {
        string side1 = getSide(puzzle[x][y - 1], 1);
        string side2 = getSide(piece, 0);
        if(side1[0] != side2[0]) {
            return false;
        }
        if(side1[1] != side2[1]) {
            return false;
        }
    }
    return true;
}

bool solvePuzzle(Grid<puzzlepiece>& puzzle, Vector<puzzlepiece>& pieces, int x, int y){

    if(y == puzzle.numRows()) {
        return true;
    }

    for(int i = 0; i < pieces.size(); i++){
        puzzlepiece temp = pieces[i];

        if(temp.orientation != 0) {
            continue;
        }

        int curr_x = x;
        int curr_y = y;

        if(nextlocal(x, puzzle.numCols())) {
            x ++;
        } else {
            y ++;
            x = 0;
        }

        for(int j = 1; j <= 4; j++){
            temp.orientation = j;
            if(checkMove(puzzle, temp, curr_x, curr_y)){
                puzzle[curr_x][curr_y] = temp;
                if(solvePuzzle(puzzle, pieces, x, y)) {
                    return true;
                } else {
                    temp.orientation = 0;
                }
            }
        }
    }

    return false;
}

Grid<puzzlepiece> findSoln(Vector<puzzlepiece> pieces, int width) {
    Grid<puzzlepiece> soln(3, 3);
    solvePuzzle(soln, pieces, 0, 0);
    return soln;
}

int main() {
    string pieces[9][4] = {
            {"dl", "zr", "er", "el"},
            {"zl", "dl", "tr", "er"},
            {"dl", "tr", "el", "zl"},
            {"zr", "tr", "el", "dr"},
            {"tr", "zr", "dr", "er"},
            {"dl", "zl", "tl", "er"},
            {"tl", "zr", "dl", "er"},
            {"zl", "dr", "tl", "zr"},
            {"tl", "zl", "dl", "er"}};


    Vector<puzzlepiece> allpieces;
    for(int i = 0; i < 9; i++) {
        puzzlepiece piece;
        for(string str: pieces[i]){
            piece.sides[i] = str;
        }
        piece.orientation = 0;
    }

    findSoln(allpieces, 3);
    return 0;
}




