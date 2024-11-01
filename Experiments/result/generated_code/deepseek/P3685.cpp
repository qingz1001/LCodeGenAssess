#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10
#define MAX_LEN 100

int n;
int hints[MAX_N][MAX_LEN];
int hint_len[MAX_N];
int min_length = MAX_LEN;

void read_input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int num;
        int len = 0;
        while (scanf("%d", &num) && num != 0) {
            hints[i][len++] = num;
        }
        hint_len[i] = len;
    }
}

int is_valid(int *sequence, int seq_len) {
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < seq_len; j++) {
            if (sequence[j] == hints[i][found]) {
                found++;
                if (found == hint_len[i]) break;
            }
        }
        if (found != hint_len[i]) return 0;
    }
    return 1;
}

void dfs(int *sequence, int seq_len, int *used) {
    if (seq_len >= min_length) return;
    if (is_valid(sequence, seq_len)) {
        min_length = seq_len;
        return;
    }
    for (int i = 1; i <= 9; i++) {
        if (!used[i]) {
            used[i] = 1;
            sequence[seq_len] = i;
            dfs(sequence, seq_len + 1, used);
            used[i] = 0;
        }
    }
}

int main() {
    read_input();
    int sequence[MAX_LEN];
    int used[10] = {0};
    dfs(sequence, 0, used);
    if (min_length == MAX_LEN) {
        printf("-1\n");
    } else {
        printf("%d\n", min_length);
    }
    return 0;
}