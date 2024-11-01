#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500005
#define MAX_Q 500005

int n, q;
int tree[MAX_N][3];
int external_input[3 * MAX_N + 2];
int cell_output[MAX_N];

void update(int cell) {
    if (cell > n) return;
    
    int count_zero = 0, count_one = 0;
    for (int i = 0; i < 3; i++) {
        int input = tree[cell][i];
        if (input > n) {
            if (external_input[input] == 0) count_zero++;
            else count_one++;
        } else {
            if (cell_output[input] == 0) count_zero++;
            else count_one++;
        }
    }
    
    int new_output = (count_one > count_zero);
    if (new_output != cell_output[cell]) {
        cell_output[cell] = new_output;
        update(cell / 3);
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &tree[i][j]);
        }
    }
    
    for (int i = n + 1; i <= 3 * n + 1; i++) {
        scanf("%d", &external_input[i]);
    }
    
    for (int i = n; i >= 1; i--) {
        int count_one = 0;
        for (int j = 0; j < 3; j++) {
            int input = tree[i][j];
            if (input > n) {
                if (external_input[input] == 1) count_one++;
            } else {
                if (cell_output[input] == 1) count_one++;
            }
        }
        cell_output[i] = (count_one > 1);
    }
    
    scanf("%d", &q);
    
    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        external_input[x] = 1 - external_input[x];
        update(x / 3);
        printf("%d\n", cell_output[1]);
    }
    
    return 0;
}