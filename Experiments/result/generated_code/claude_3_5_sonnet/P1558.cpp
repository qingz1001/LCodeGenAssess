#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 100005
#define MAX_T 31

int L, T, O;
int color[MAX_L];
int last_change[MAX_L];
int last_color[MAX_L];

void update(int left, int right, int c, int time) {
    if (left > right) {
        int temp = left;
        left = right;
        right = temp;
    }
    for (int i = left; i <= right; i++) {
        if (last_change[i] < time) {
            last_change[i] = time;
            last_color[i] = c;
        }
    }
}

int query(int left, int right, int time) {
    if (left > right) {
        int temp = left;
        left = right;
        right = temp;
    }
    int count = 0;
    int colors[MAX_T] = {0};
    for (int i = left; i <= right; i++) {
        int c = (last_change[i] > 0) ? last_color[i] : color[i];
        if (!colors[c]) {
            colors[c] = 1;
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d", &L, &T, &O);
    
    memset(color, 1, sizeof(color));
    memset(last_change, 0, sizeof(last_change));
    memset(last_color, 0, sizeof(last_color));

    char op;
    int a, b, c;
    for (int i = 1; i <= O; i++) {
        scanf(" %c", &op);
        if (op == 'C') {
            scanf("%d %d %d", &a, &b, &c);
            update(a, b, c, i);
        } else if (op == 'P') {
            scanf("%d %d", &a, &b);
            printf("%d\n", query(a, b, i));
        }
    }

    return 0;
}