#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 16

int n;
char order[MAX_N];
char train[MAX_N];
char track[2][MAX_N];
int pos[MAX_N];

void init() {
    for (int i = 0; i < 2; i++) {
        memset(track[i], 0, sizeof(track[i]));
    }
}

void move_train(char h, char from, char to) {
    printf("%c %c %c\n", h, from, to);
    if (from == 'B' || from == 'C') {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (track[from - 'B'][i] == h) {
                idx = i;
                break;
            }
        }
        memmove(&track[from - 'B'][idx], &track[from - 'B'][idx + 1], (n - idx - 1) * sizeof(char));
    } else if (from == 'D') {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (train[i] == h) {
                idx = i;
                break;
            }
        }
        memmove(&train[idx], &train[idx + 1], (n - idx - 1) * sizeof(char));
    }
    track[to - 'B'][pos[h - 'a']] = h;
    pos[h - 'a']++;
}

int main() {
    scanf("%d %s", &n, order);
    for (int i = 0; i < n; i++) {
        train[i] = order[i];
        pos[order[i] - 'a'] = i;
    }

    init();

    for (int i = 0; i < n; i++) {
        char h = order[i];
        if (h == 'a') {
            move_train('a', 'A', 'B');
        } else if (h == 'b') {
            move_train('b', 'A', 'C');
        } else if (h == 'c') {
            move_train('c', 'B', 'C');
        } else if (h == 'd') {
            move_train('d', 'C', 'D');
        }
    }

    for (int i = 0; i < n; i++) {
        if (train[i] != order[i]) {
            printf("NO\n");
            return 0;
        }
    }

    printf("\n");
    return 0;
}