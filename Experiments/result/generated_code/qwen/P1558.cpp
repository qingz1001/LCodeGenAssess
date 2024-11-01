#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100005
#define MAX_T 30
#define MAX_O 100005

int main() {
    int L, T, O;
    scanf("%d %d %d", &L, &T, &O);

    int *colors = (int *)malloc(L * sizeof(int));
    for (int i = 0; i < L; i++) {
        colors[i] = 1;
    }

    for (int i = 0; i < O; i++) {
        char action[2];
        int A, B, C;
        scanf("%s %d %d", action, &A, &B);
        if (action[0] == 'C') {
            scanf("%d", &C);
            if (A > B) {
                int temp = A;
                A = B;
                B = temp;
            }
            for (int j = A - 1; j <= B - 1; j++) {
                colors[j] = C;
            }
        } else if (action[0] == 'P') {
            if (A > B) {
                int temp = A;
                A = B;
                B = temp;
            }
            int count[MAX_T + 1] = {0};
            for (int j = A - 1; j <= B - 1; j++) {
                count[colors[j]]++;
            }
            int result = 0;
            for (int j = 1; j <= T; j++) {
                if (count[j] > 0) {
                    result++;
                }
            }
            printf("%d\n", result);
        }
    }

    free(colors);
    return 0;
}