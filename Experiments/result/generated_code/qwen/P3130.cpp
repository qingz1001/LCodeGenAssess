#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000
#define MAX_Q 100000

int n, q;
int haybales[MAX_N];
int min_haybales[MAX_N];

void update(int start, int end, int value) {
    for (int i = start - 1; i <= end - 1; i++) {
        haybales[i] += value;
        min_haybales[i] = haybales[i];
    }
}

int query_min(int start, int end) {
    int min_val = haybales[start - 1];
    for (int i = start; i <= end - 1; i++) {
        if (min_haybales[i] < min_val) {
            min_val = min_haybales[i];
        }
    }
    return min_val;
}

long long query_sum(int start, int end) {
    long long sum = 0;
    for (int i = start - 1; i <= end - 1; i++) {
        sum += haybales[i];
    }
    return sum;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &haybales[i]);
        min_haybales[i] = haybales[i];
    }

    char type[2];
    int a, b, c;
    for (int i = 0; i < q; i++) {
        scanf("%s", type);
        scanf("%d %d", &a, &b);
        if (type[0] == 'M') {
            printf("%d\n", query_min(a, b));
        } else if (type[0] == 'P') {
            scanf("%d", &c);
            update(a, b, c);
        } else if (type[0] == 'S') {
            printf("%lld\n", query_sum(a, b));
        }
    }

    return 0;
}