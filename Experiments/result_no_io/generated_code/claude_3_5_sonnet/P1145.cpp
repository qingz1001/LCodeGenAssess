#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_K 13

bool simulate(int k, int m) {
    int n = 2 * k;
    bool alive[MAX_K * 2];
    memset(alive, true, sizeof(alive));
    int good_alive = k, bad_alive = k;
    int current = 0;
    
    while (good_alive > 0 && bad_alive > 0) {
        int count = 0;
        while (count < m) {
            if (alive[current]) {
                count++;
            }
            if (count == m) {
                alive[current] = false;
                if (current < k) {
                    good_alive--;
                } else {
                    bad_alive--;
                }
            }
            current = (current + 1) % n;
        }
    }
    
    return bad_alive == 0;
}

int find_minimum_m(int k) {
    int m = 1;
    while (!simulate(k, m)) {
        m++;
    }
    return m;
}

int main() {
    int k;
    scanf("%d", &k);
    int result = find_minimum_m(k);
    printf("%d\n", result);
    return 0;
}