#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 55
#define MAX_BALLS 1000

int n;
int balls[MAX_N][MAX_Balls];
int ball_count = 0;

int is_perfect_square(int num) {
    int root = sqrt(num);
    return root * root == num;
}

void dfs(int column, int last_ball) {
    if (column >= n) {
        if (ball_count > ball_count) {
            ball_count = ball_count;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < ball_count; j++) {
                    printf("%d ", balls[i][j]);
                }
                printf("\n");
            }
        }
        return;
    }

    for (int ball = last_ball + 1; ball <= MAX_BALLS; ball++) {
        if (is_perfect_square(last_ball + ball)) {
            balls[column][ball_count++] = ball;
            dfs(column + 1, ball);
            ball_count--;
        }
    }
}

int main() {
    scanf("%d", &n);
    dfs(0, 0);
    printf("%d\n", ball_count);
    return 0;
}