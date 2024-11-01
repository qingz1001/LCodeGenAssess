#include <stdio.h>
#include <stdlib.h>

// Define possible cell values
typedef struct {
    int cell[2];
} Board;

// Function to copy board
Board copy_board(Board b) {
    Board new_b;
    new_b.cell[0] = b.cell[0];
    new_b.cell[1] = b.cell[1];
    return new_b;
}

// Function to check if two boards are equal
int boards_equal(Board a, Board b) {
    return (a.cell[0] == b.cell[0]) && (a.cell[1] == b.cell[1]);
}

// Function to perform a move and return new board and score
typedef struct {
    Board board;
    int score;
    int moved;
} MoveResult;

MoveResult perform_move(Board b, char direction) {
    MoveResult res;
    res.board = copy_board(b);
    res.score = 0;
    res.moved = 0;

    // Since n=1, m=2, only left and right have effect
    if(direction == 'L' || direction == 'R') {
        int first, second;
        if(direction == 'L') {
            first = res.board.cell[0];
            second = res.board.cell[1];
        }
        else {
            first = res.board.cell[1];
            second = res.board.cell[0];
        }

        if(first == 0 && second !=0){
            first = second;
            second = 0;
            res.moved =1;
        }

        if(first !=0 && second !=0){
            if(first == second){
                first *=2;
                res.score += first;
                second =0;
                res.moved =1;
            }
        }

        if(direction == 'L') {
            res.board.cell[0] = first;
            res.board.cell[1] = second;
        }
        else {
            res.board.cell[1] = first;
            res.board.cell[0] = second;
        }
    }

    return res;
}

int main(){
    // Initial board
    Board initial;
    initial.cell[0] = 0;
    initial.cell[1] = 0;

    // Player C places two tiles
    // Each tile can be 2 or 4, and can be placed in either cell
    int x_min = -1, x_max = -1;

    for(int first_val=2; first_val<=4; first_val+=2){
        for(int first_pos=0; first_pos<2; first_pos++){
            Board after_first = copy_board(initial);
            after_first.cell[first_pos] = first_val;
            for(int second_val=2; second_val<=4; second_val+=2){
                for(int second_pos=0; second_pos<2; second_pos++){
                    if(after_first.cell[second_pos]==0){
                        Board after_second = copy_board(after_first);
                        after_second.cell[second_pos] = second_val;

                        // Now it's M's turn
                        // Try all 4 directions
                        // But only 'L' and 'R' have effect
                        int possible_moves =0;
                        MoveResult moveL = perform_move(after_second, 'L');
                        if(moved) // Need to check if board changed
                            if(!boards_equal(after_second, moveL.board))
                                possible_moves++;

                        MoveResult moveR = perform_move(after_second, 'R');
                        if(!boards_equal(after_second, moveR.board))
                            possible_moves++;

                        // x is the number of possible moves
                        // since M will choose to make a move if possible
                        if(moveL.moved || moveR.moved){
                            if(x_min==-1 || x_min >1)
                                x_min =1;
                            if(x_max==-1 || x_max <1)
                                x_max =1;
                        }
                        else{
                            if(x_min==-1 || x_min >0)
                                x_min =0;
                            if(x_max==-1 || x_max <0)
                                x_max =0;
                        }
                    }
                }
            }
        }
    }

    // Handle case where no moves
    if(x_min==-1) x_min=0;
    if(x_max==-1) x_max=0;

    printf("%d\n%d\n", x_min, x_max);
    return 0;
}