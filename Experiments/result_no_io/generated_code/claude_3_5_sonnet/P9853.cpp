#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200000
#define MAX_Q 200000

typedef long long ll;

typedef struct {
    ll x;
    int count;
} Solution;

int compare(const void* a, const void* b) {
    return ((Solution*)a)->x - ((Solution*)b)->x;
}

Solution solutions[MAX_N];
int solutionCount = 0;

void addSolution(ll x) {
    int i;
    for (i = 0; i < solutionCount; i++) {
        if (solutions[i].x == x) {
            solutions[i].count++;
            return;
        }
    }
    solutions[solutionCount].x = x;
    solutions[solutionCount].count = 1;
    solutionCount++;
}

int countSolutions(ll L, ll R) {
    int i, count = 0;
    for (i = 0; i < solutionCount; i++) {
        if (solutions[i].x >= L && solutions[i].x <= R) {
            count++;
        }
        if (solutions[i].x > R) break;
    }
    return count;
}

int main() {
    int n, Q, i;
    char equation[100];
    ll a, b, c, x;

    scanf("%d %d", &n, &Q);

    for (i = 0; i < n; i++) {
        scanf("%s", equation);
        sscanf(equation, "%lldx%lld=%lld", &a, &b, &c);
        if (a > 0) {
            x = (c - b) / a;
            if (x > 0 && a * x + b == c) {
                addSolution(x);
            }
        } else {
            x = (b - c) / (-a);
            if (x > 0 && -a * x + b == c) {
                addSolution(x);
            }
        }
    }

    qsort(solutions, solutionCount, sizeof(Solution), compare);

    ll L, R;
    for (i = 0; i < Q; i++) {
        scanf("%lld %lld", &L, &R);
        printf("%d\n", countSolutions(L, R));
    }

    return 0;
}