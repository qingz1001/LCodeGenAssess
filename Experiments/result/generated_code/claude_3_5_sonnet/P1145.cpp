#include <stdio.h>
#include <stdbool.h>

#define MAX_K 14

bool simulate(int k, int m) {
    int people[2 * MAX_K] = {0};  // 0代表好人，1代表坏人
    int n = 2 * k;
    for (int i = k; i < n; i++) {
        people[i] = 1;
    }
    
    int count = 0, killed = 0, pos = 0;
    while (killed < k) {
        if (people[pos] != -1) {
            count++;
            if (count == m) {
                if (people[pos] == 0) {
                    return false;
                }
                people[pos] = -1;
                killed++;
                count = 0;
            }
        }
        pos = (pos + 1) % n;
    }
    return true;
}

int main() {
    int k;
    scanf("%d", &k);
    
    int m = k + 1;
    while (!simulate(k, m)) {
        m++;
    }
    
    printf("%d\n", m);
    return 0;
}