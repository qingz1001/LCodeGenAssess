#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-9

typedef struct {
    double r_win;
    double b_win;
} Prob;

Prob multiply(Prob a, Prob b) {
    Prob result;
    result.r_win = a.r_win * b.r_win + a.b_win * b.q_win;
    result.b_win = a.r_win * b.p_win + a.b_win * (1 - b.q_win);
    return result;
}

double expected_wins(int n, int m, char type[], Prob p[], int operations[][2]) {
    Prob current_prob = {p[0].r_win, 1 - p[0].r_win};
    
    for (int i = 0; i < m; ++i) {
        if (operations[i][0] == 0) {
            current_prob = multiply(current_prob, p[operations[i][1]]);
        } else {
            // If the operation is delete, we need to reverse the effect of the last add operation
            // This is a simplified approach and may not be accurate due to floating-point precision issues
            // For simplicity, we assume the last add operation was valid and directly apply its inverse
            current_prob = multiply(current_prob, (Prob){1 / p[operations[i][1]].r_win, 1 / (1 - p[operations[i][1]].r_win)});
        }
    }
    
    return current_prob.r_win * (n - 1) + current_prob.b_win;
}

int main() {
    int n, m;
    char type[10];
    scanf("%d %d %s", &n, &m, type);
    
    Prob p[n];
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            scanf("%lf", &p[i].r_win);
            p[i].b_win = 1 - p[i].r_win;
        } else {
            scanf("%lf %lf", &p[i].r_win, &p[i].q_win);
            p[i].b_win = 1 - p[i].r_win;
        }
    }
    
    int operations[m][2];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &operations[i][0], &operations[i][1]);
        --operations[i][1]; // Adjusting for 0-based index
    }
    
    for (int i = 0; i < m; ++i) {
        printf("%.4f\n", expected_wins(n, i + 1, type, p, operations));
    }
    
    return 0;
}