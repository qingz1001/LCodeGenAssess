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
        if (apples[i] >= current_position && apples[i] < current_position + M) {
            continue;
        } else {
            int moves_to_left = apples[i] - current_position;
            int moves_to_right = current_position + M - apples[i];
            min_moves += moves_to_left > moves_to_right ? moves_to_right : moves_to_left;
            current_position = apples[i];
        }
    }

    printf("%d\n", min_moves);

    free(apples);
    return 0;
}