#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned long long mask1;
    unsigned long long mask2;
} Mask;

int main(){
    int M, n;
    long long k;
    scanf("%d %d %lld", &M, &n, &k);
    
    int wx[M+1], wy[M+1];
    for(int i=1;i<=M;i++) scanf("%d %d", &wx[i], &wy[i]);
    
    int bx[n+1], by[n+1];
    for(int i=1;i<=n;i++) scanf("%d %d", &bx[i], &by[i]);
    
    Mask bomb[n+1];
    for(int i=1;i<=n;i++){
        bomb[i].mask1 = 0;
        bomb[i].mask2 = 0;
        for(int j=1;j<=M;j++){
            long long dx = (long long)(bx[i]) - (long long)(wx[j]);
            long long dy = (long long)(by[i]) - (long long)(wy[j]);
            if(dx*dx + dy*dy <= (long long)k*k){
                if(j-1 < 64){
                    bomb[i].mask1 |= (1ULL << (j-1));
                }
                else{
                    bomb[i].mask2 |= (1ULL << (j-1-64));
                }
            }
        }
    }
    
    // Weapons to cover: weapons2..M
    unsigned long long full_mask1 = 0, full_mask2 = 0;
    for(int j=2; j<=M; j++){
        if(j-1 < 64){
            full_mask1 |= (1ULL << (j-1));
        }
        else{
            full_mask2 |= (1ULL << (j-1-64));
        }
    }
    
    int min_x = n+1;
    for(int first=1; first<=n; first++){
        // Check if bomb[first] covers weapon1
        if(!( (bomb[first].mask1 & 1ULL) )){
            continue;
        }
        // Remaining to cover
        unsigned long long rem1 = full_mask1;
        unsigned long long rem2 = full_mask2;
        // Remove what's covered by first bomb
        if(1 < 64){
            rem1 &= ~(bomb[first].mask1);
        }
        else{
            rem2 &= ~(bomb[first].mask2);
        }
        // Greedy set cover
        int count =0;
        int used[n+1];
        memset(used, 0, sizeof(used));
        used[first] =1;
        while(rem1 || rem2){
            int best = -1;
            int best_cnt = -1;
            for(int i=1;i<=n;i++) if(!used[i]){
                // Count how many can be covered
                unsigned long long covered1 = bomb[i].mask1 & rem1;
                unsigned long long covered2 = bomb[i].mask2 & rem2;
                int cnt = __builtin_popcountll(covered1) + __builtin_popcountll(covered2);
                if(cnt > best_cnt){
                    best_cnt = cnt;
                    best = i;
                }
            }
            if(best==-1 || best_cnt==0){
                break;
            }
            used[best]=1;
            count++;
            rem1 &= ~(bomb[best].mask1);
            rem2 &= ~(bomb[best].mask2);
        }
        // Check if all covered
        if(rem1==0 && rem2==0){
            if(count +1 < min_x) min_x = count +1;
        }
    }
    printf("%d\n", min_x);
}