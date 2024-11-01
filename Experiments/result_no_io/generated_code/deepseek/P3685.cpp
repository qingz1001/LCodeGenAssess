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
        hint_len[i] = 0;
        while (scanf("%d", &num) && num != 0) {
            hints[i][hint_len[i]++] = num;
        }
    }
}

int is_valid_sequence(int *sequence, int len) {
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < len; j++) {
            if (sequence[j] == hints[i][found]) {
                found++;
                if (found == hint_len[i]) break;
            }
        }
        if (found != hint_len[i]) return 0;
    }
    return 1;
}

void generate_sequences(int *sequence, int len, int *used) {
    if (len >= min_length) return;
    if (is_valid_sequence(sequence, len)) {
        min_length = len;
        return;
    }
    for (int i = 1; i <= 9; i++) {
        if (!used[i]) {
            used[i] = 1;
            sequence[len] = i;
            generate_sequences(sequence, len + 1, used);
            used[i] = 0;
        }
    }
}

int main() {
    read_input();
    int sequence[MAX_LEN];
    int used[10] = {0};
    generate_sequences(sequence, 0, used);
    if (min_length == MAX_LEN) {
        printf("-1\n");
    } else {
        printf("%d\n", min_length);
    }
    return 0;
}