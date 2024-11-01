#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 2000005

int N, K;
int diff[MAXM];
int pos;

void add(int l, int r) {
    diff[l]++;
    diff[r+1]--;
}

int main() {
    scanf("%d %d", &N, &K);
    
    memset(diff, 0, sizeof(diff));
    pos = 1000000;
    
    for(int i = 0; i < N; i++) {
        int x;
        char dir[2];
        scanf("%d %s", &x, dir);
        
        int new_pos;
        if(dir[0] == 'L') {
            new_pos = pos - x;
            add(new_pos + 1000000, pos + 1000000);
        } else {
            new_pos = pos + x;
            add(pos + 1000000, new_pos + 1000000);
        }
        pos = new_pos;
    }
    
    int sum = 0, ans = 0;
    for(int i = 0; i < MAXM; i++) {
        sum += diff[i];
        if(sum >= K) ans++;
    }
    
    printf("%d\n", ans);
    
    return 0;
}