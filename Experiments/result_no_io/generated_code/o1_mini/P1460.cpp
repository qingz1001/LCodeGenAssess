#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V 25
#define MAX_G 15

int main(){
    int v;
    scanf("%d", &v);
    int required[MAX_V];
    for(int i=0;i<v;i++) scanf("%d", &required[i]);
    int g;
    scanf("%d", &g);
    int feeds[MAX_G][MAX_V];
    for(int i=0;i<g;i++) {
        for(int j=0;j<v;j++) scanf("%d", &feeds[i][j]);
    }
    int min_p = g+1;
    int best_set = 0;
    for(int mask=1; mask<(1<<g); mask++){
        int count = 0;
        for(int i=0;i<g;i++) if(mask & (1<<i)) count++;
        if(count > min_p) continue;
        int valid = 1;
        int total[MAX_V];
        memset(total, 0, sizeof(total));
        for(int i=0;i<g;i++) if(mask & (1<<i)){
            for(int j=0;j<v;j++) total[j] += feeds[i][j];
        }
        for(int j=0;j<v;j++) if(total[j] < required[j]){
            valid = 0;
            break;
        }
        if(valid){
            if(count < min_p){
                min_p = count;
                best_set = mask;
            }
            else if(count == min_p){
                // Compare lex order
                int better = 0;
                for(int i=0;i<g;i++){
                    int bit1 = (best_set & (1<<i)) ? 1 : 0;
                    int bit2 = (mask & (1<<i)) ? 1 : 0;
                    if(bit1 < bit2){
                        better = 1;
                        break;
                    }
                    else if(bit1 > bit2){
                        break;
                    }
                }
                if(better){
                    best_set = mask;
                }
            }
        }
    }
    printf("%d", min_p);
    for(int i=0;i<g;i++) if(best_set & (1<<i)) printf(" %d", i+1);
    printf("\n");
    return 0;
}