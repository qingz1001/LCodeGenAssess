#include <stdio.h>
#include <string.h>

#define MAXN 30005

int n, q;
char s[MAXN];

void solve(int i, int p, int k) {
    int cost = 0;
    
    // Teleportation spell
    int j = p;
    while (j < n && s[i] == s[j]) {
        j++;
    }
    cost += n - j;
    i = j;
    
    // Move to the top of the mountain
    while (i != k) {
        if (i > k) {
            i--;
        } else {
            i++;
        }
        cost++;
    }
    
    printf("%d\n", cost);
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", s);
    
    for (int t = 0; t < q; t++) {
        int i, p, k;
        scanf("%d %d %d", &i, &p, &k);
        solve(i, p, k);
    }
    
    return 0;
}