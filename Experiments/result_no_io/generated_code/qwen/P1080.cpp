#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n;
int a, b;
int left[MAXN], right[MAXN];

long long calculate_reward(int pos) {
    long long product = 1;
    for (int i = 0; i < pos; i++) {
        product *= left[i];
    }
    return product / right[pos];
}

int main() {
    scanf("%d", &n);
    scanf("%d %d", &a, &b);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &left[i], &right[i]);
    }

    int max_reward = -1;
    for (int i = 0; i < n; i++) {
        int reward = calculate_reward(i);
        if (reward > max_reward) {
            max_reward = reward;
        }
    }

    printf("%d\n", max_reward);

    return 0;
}