#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef unsigned long long ull;

int n, m;
ull adj[MAX];
int best_size = 0;
ull best_set[2] = {0, 0};
int current_size = 0;
ull current_set[2] = {0, 0};

// Order nodes from n-1 downto 0 for lex largest
int order[MAX];
int ord_size = 0;

void copy_best() {
    best_size = current_size;
    best_set[0] = current_set[0];
    best_set[1] = current_set[1];
}

void backtrack(int idx, int remaining) {
    if (current_size + remaining < best_size)
        return;
    if (idx == ord_size) {
        if (current_size > best_size) {
            copy_best();
        } else if (current_size == best_size) {
            if (current_set[1] > best_set[1] || (current_set[1] == best_set[1] && current_set[0] > best_set[0])) {
                copy_best();
            }
        }
        return;
    }
    int u = order[idx];
    // Try to include u
    int conflict = 0;
    if (u < 64) conflict = (current_set[0] & adj[u]) != 0;
    else conflict = (current_set[1] & adj[u]) != 0;
    if (!conflict) {
        // Include u
        if (u < 64) current_set[0] |= (1ULL << u);
        else current_set[1] |= (1ULL << (u - 64));
        current_size++;
        backtrack(idx + 1, remaining -1);
        // Backtrack
        if (u < 64) current_set[0] ^= (1ULL << u);
        else current_set[1] ^= (1ULL << (u - 64));
        current_size--;
    }
    // Exclude u
    backtrack(idx + 1, remaining -1);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) adj[i] = 0;
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        u--, v--;
        adj[u] |= (1ULL << v);
        adj[v] |= (1ULL << u);
    }
    // Order nodes from n-1 downto 0
    for(int i=0;i<n;i++) order[i] = n-1-i;
    ord_size = n;
    backtrack(0, n);
    printf("%d\n", best_size);
    int result[MAX];
    for(int i=0;i<n;i++) result[i] = 0;
    for(int i=0;i<n;i++) {
        if (i < 64) {
            if (best_set[0] & (1ULL << i)) result[i] = 1;
        }
        else {
            if (best_set[1] & (1ULL << (i - 64))) result[i] = 1;
        }
    }
    for(int i=0;i<n;i++) printf("%d%c", result[i], i<n-1?' ':'\n');
}