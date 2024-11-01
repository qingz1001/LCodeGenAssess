#include <stdio.h>
#include <string.h>

#define MAXN 30005

int main() {
    int n, q;
    char s[MAXN];
    scanf("%d %d", &n, &q);
    scanf("%s", s);

    while (q--) {
        int i, p, k;
        scanf("%d %d %d", &i, &p, &k);

        // Calculate the cost of using the teleportation portal
        int j = p;
        while (j < n && s[i - p + j] == s[j]) j++;
        int teleport_cost = n - j;

        // Calculate the minimum cost to reach the top
        int min_cost = teleport_cost;
        if (k > i) {
            min_cost += k - i;
        } else {
            min_cost += i - k;
        }

        printf("%d\n", min_cost);
    }

    return 0;
}