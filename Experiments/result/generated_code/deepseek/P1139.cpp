#include <stdio.h>
#include <string.h>

#define MAX_N 15

typedef struct {
    char train;
    char from;
    char to;
} Operation;

int n;
char target[MAX_N + 1];
char A[MAX_N + 1];
char B[MAX_N + 1];
char C[MAX_N + 1];
Operation operations[MAX_N * 3];
int op_count;

int is_possible(int a_index, int b_index, int c_index, int d_index) {
    if (d_index == n) {
        return 1;
    }

    if (a_index < n && A[a_index] == target[d_index]) {
        operations[op_count++] = (Operation){A[a_index], 'A', 'D'};
        if (is_possible(a_index + 1, b_index, c_index, d_index + 1)) {
            return 1;
        }
        op_count--;
    }

    if (b_index > 0 && B[b_index - 1] == target[d_index]) {
        operations[op_count++] = (Operation){B[b_index - 1], 'B', 'D'};
        if (is_possible(a_index, b_index - 1, c_index, d_index + 1)) {
            return 1;
        }
        op_count--;
    }

    if (c_index > 0 && C[c_index - 1] == target[d_index]) {
        operations[op_count++] = (Operation){C[c_index - 1], 'C', 'D'};
        if (is_possible(a_index, b_index, c_index - 1, d_index + 1)) {
            return 1;
        }
        op_count--;
    }

    if (a_index < n) {
        operations[op_count++] = (Operation){A[a_index], 'A', 'B'};
        if (is_possible(a_index + 1, b_index + 1, c_index, d_index)) {
            return 1;
        }
        op_count--;
    }

    if (a_index < n) {
        operations[op_count++] = (Operation){A[a_index], 'A', 'C'};
        if (is_possible(a_index + 1, b_index, c_index + 1, d_index)) {
            return 1;
        }
        op_count--;
    }

    if (b_index > 0) {
        operations[op_count++] = (Operation){B[b_index - 1], 'B', 'C'};
        if (is_possible(a_index, b_index - 1, c_index + 1, d_index)) {
            return 1;
        }
        op_count--;
    }

    if (c_index > 0) {
        operations[op_count++] = (Operation){C[c_index - 1], 'C', 'B'};
        if (is_possible(a_index, b_index + 1, c_index - 1, d_index)) {
            return 1;
        }
        op_count--;
    }

    return 0;
}

int main() {
    scanf("%d", &n);
    scanf("%s", target);

    for (int i = 0; i < n; i++) {
        A[i] = 'a' + i;
    }
    A[n] = '\0';

    op_count = 0;
    if (is_possible(0, 0, 0, 0)) {
        for (int i = 0; i < op_count; i++) {
            printf("%c %c %c\n", operations[i].train, operations[i].from, operations[i].to);
        }
    } else {
        printf("NO\n");
    }

    return 0;
}