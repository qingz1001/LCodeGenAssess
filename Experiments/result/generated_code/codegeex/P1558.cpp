#include <stdio.h>
#include <string.h>

#define MAX_L 100005

int color[MAX_L];

void paint(int L, int A, int B, int C) {
    for (int i = A; i <= B; i++) {
        color[i] = C;
    }
}

int countColors(int L, int A, int B) {
    int count = 0;
    int seenColors[MAX_L] = {0};
    for (int i = A; i <= B; i++) {
        seenColors[color[i]] = 1;
    }
    for (int i = 1; i <= L; i++) {
        if (seenColors[i]) count++;
    }
    return count;
}

int main() {
    int L, T, O;
    scanf("%d%d%d", &L, &T, &O);

    for (int i = 0; i < O; i++) {
        char command[2];
        int A, B, C;
        scanf("%s%d%d", command, &A, &B);
        if (command[0] == 'C') {
            scanf("%d", &C);
            paint(L, A, B, C);
        } else if (command[0] == 'P') {
            printf("%d\n", countColors(L, A, B));
        }
    }

    return 0;
}