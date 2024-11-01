#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M, J;
    scanf("%d %d", &N, &M);
    scanf("%d", &J);

    int *apples = (int *)malloc(J * sizeof(int));
    for (int i = 0; i < J; i++) {
        scanf("%d", &apples[i]);
    }

    int min_moves = 0;
    int current_position = 1;

    for (int i = 0; i < J; i++) {
        int target_column = apples[i];
        if (target_column >= current_position && target_column <= current_position + M - 1) {
            // The ship already covers the target column.
        } else {
            // Calculate the minimum moves to cover the target column.
            int left_moves = target_column > current_position ? target_column - current_position : 0;
            int right_moves = target_column < current_position ? current_position - target_column : 0;
            min_moves += left_moves + right_moves;
            current_position = target_column;
        }
    }

    printf("%d\n", min_moves);

    free(apples);
    return 0;
}