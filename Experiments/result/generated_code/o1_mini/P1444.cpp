#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long long x, y;
} Wormhole;

int n;
Wormhole wormholes[12];
int pairings[12];
int nextRight[12];
long long countCycles = 0;

int cmp(const void *a, const void *b){
    Wormhole *wa = (Wormhole *)a;
    Wormhole *wb = (Wormhole *)b;
    if (wa->x != wb->x)
        return (wa->x < wb->x) ? -1 : 1;
    if (wa->y != wb->y)
        return (wa->y < wb->y) ? -1 : 1;
    return 0;
}

bool hasCycle(){
    for(int i=0;i<n;i++){
        int start = i;
        int current = i;
        for(int step=0; step<n; step++){
            // Move to next on right
            if(nextRight[current] == -1){
                break;
            }
            current = pairings[nextRight[current]];
            if(current == -1){
                break;
            }
        }
        if(current != -1 && current == start){
            return true;
        }
    }
    return false;
}

void backtrack(int first){
    while(first < n && pairings[first] != -1){
        first++;
    }
    if(first == n){
        if(hasCycle()){
            countCycles++;
        }
        return;
    }
    for(int i=first+1;i<n;i++){
        if(pairings[i]==-1){
            pairings[first]=i;
            pairings[i]=first;
            backtrack(first+1);
            pairings[first]=-1;
            pairings[i]=-1;
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%lld %lld", &wormholes[i].x, &wormholes[i].y);
    }
    qsort(wormholes, n, sizeof(Wormhole), cmp);
    for(int i=0;i<n;i++){
        nextRight[i]=-1;
        long long min = 1e18;
        for(int j=0;j<n;j++){
            if(wormholes[j].y == wormholes[i].y && wormholes[j].x > wormholes[i].x){
                if(wormholes[j].x - wormholes[i].x < min){
                    min = wormholes[j].x - wormholes[i].x;
                    nextRight[i]=j;
                }
            }
        }
    }
    for(int i=0;i<n;i++) pairings[i]=-1;
    backtrack(0);
    printf("%lld\n", countCycles);
    return 0;
}