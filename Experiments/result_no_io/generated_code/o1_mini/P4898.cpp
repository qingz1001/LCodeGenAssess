#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
} Seat;

int main(){
    int H, W, Q;
    scanf("%d %d %d", &H, &W, &Q);
    int HW = H * W;
    Seat *contestants = (Seat*)malloc(sizeof(Seat)*HW);
    for(int i=0;i<HW;i++){
        scanf("%d %d", &contestants[i].row, &contestants[i].col);
    }
    // To keep track of which contestant is at each seat
    int *seat_map = (int*)malloc(sizeof(int)*H*W);
    for(int i=0;i<HW;i++){
        int pos = contestants[i].row * W + contestants[i].col;
        seat_map[pos] = i;
    }
    for(int i=0;i<Q;i++){
        int A, B;
        scanf("%d %d", &A, &B);
        // Swap seats of contestant A and B
        int posA = contestants[A].row * W + contestants[A].col;
        int posB = contestants[B].row * W + contestants[B].col;
        // Update seat_map
        seat_map[posA] = B;
        seat_map[posB] = A;
        // Swap the row and column in contestants array
        int tmp_row = contestants[A].row;
        int tmp_col = contestants[A].col;
        contestants[A].row = contestants[B].row;
        contestants[A].col = contestants[B].col;
        contestants[B].row = tmp_row;
        contestants[B].col = tmp_col;
        // Compute 美妙度
        // TODO: Implement the counting of beautiful rectangles
        // For now, output 0
        printf("0\n");
    }
    free(contestants);
    free(seat_map);
    return 0;
}