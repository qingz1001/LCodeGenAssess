#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 200000
#define MAX_Q 200000

typedef long long ll;

ll solutions[MAX_N];
int n, q;

int compare(const void* a, const void* b) {
    return (*(ll*)a > *(ll*)b) - (*(ll*)a < *(ll*)b);
}

void parse_equation(char* eq) {
    int a, b, c;
    sscanf(eq, "%dx%*[^=]=%d", &a, &c);
    
    char* plus = strchr(eq, '+');
    char* minus = strchr(eq, '-');
    
    if (plus) {
        sscanf(plus + 1, "%d", &b);
    } else if (minus) {
        sscanf(minus + 1, "%d", &b);
        b = -b;
    } else {
        b = 0;
    }
    
    solutions[n++] = (ll)ceil((c - b) / (double)a);
}

int count_solutions(ll l, ll r) {
    ll* lower = (ll*)bsearch(&l, solutions, n, sizeof(ll), compare);
    if (!lower) {
        lower = (ll*)solutions + (lower - solutions);
        while (lower < solutions + n && *lower < l) lower++;
    }
    
    ll* upper = (ll*)bsearch(&r, solutions, n, sizeof(ll), compare);
    if (!upper) {
        upper = (ll*)solutions + (upper - solutions);
        while (upper > solutions && *upper > r) upper--;
    }
    
    return (upper >= lower) ? (int)(upper - lower + 1) : 0;
}

int main() {
    char equation[100];
    scanf("%d %d", &n, &q);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", equation);
        parse_equation(equation);
    }
    
    qsort(solutions, n, sizeof(ll), compare);
    
    ll l, r;
    for (int i = 0; i < q; i++) {
        scanf("%lld %lld", &l, &r);
        printf("%d\n", count_solutions(l, r));
    }
    
    return 0;
}