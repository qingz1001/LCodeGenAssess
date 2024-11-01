#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x, y;
} Wormhole;

int n;
Wormhole wormholes[12];
int pair_map[12];
int used[12];
int count_result = 0;

int compare(const void* a, const void* b){
    Wormhole* wa = (Wormhole*)a;
    Wormhole* wb = (Wormhole*)b;
    if (wa->y != wb->y)
        return wa->y - wb->y;
    return wa->x - wb->x;
}

int has_cycle(int to[]){
    for(int i=0;i<n;i++){
        int slow = i, fast = i;
        while(1){
            slow = to[slow];
            if(slow == -1) break;
            fast = to[fast];
            if(fast == -1) break;
            fast = to[fast];
            if(fast == -1) break;
            if(slow == fast){
                return 1;
            }
        }
    }
    return 0;
}

void backtrack(int first){
    if(first >= n){
        int next_map[12];
        for(int i=0;i<n;i++) next_map[i] = -1;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(wormholes[j].y == wormholes[i].y && wormholes[j].x > wormholes[i].x){
                    if(next_map[i] == -1 || wormholes[j].x < wormholes[next_map[i]].x){
                        next_map[i] = j;
                    }
                }
            }
        }
        int to_map[12];
        for(int i=0;i<n;i++){
            if(pair_map[i] != -1){
                to_map[i] = next_map[pair_map[i]];
                if(to_map[i]==-1) to_map[i] = -1;
            }
            else{
                to_map[i] = -1;
            }
        }
        if(has_cycle(to_map)){
            count_result++;
        }
        return;
    }
    if(used[first]){
        backtrack(first+1);
        return;
    }
    used[first] = 1;
    for(int j=first+1;j<n;j++){
        if(!used[j]){
            used[j] = 1;
            pair_map[first] = j;
            pair_map[j] = first;
            backtrack(first+1);
            pair_map[first] = -1;
            pair_map[j] = -1;
            used[j] = 0;
        }
    }
    used[first] = 0;
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        scanf("%lld %lld", &wormholes[i].x, &wormholes[i].y);
        pair_map[i] = -1;
        used[i] = 0;
    }
    qsort(wormholes, n, sizeof(Wormhole), compare);
    backtrack(0);
    printf("%d\n", count_result);
    return 0;
}