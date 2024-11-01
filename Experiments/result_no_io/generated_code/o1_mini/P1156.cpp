#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int T;
    int F;
    int H;
} Garbage;

int compare(const void *a, const void *b) {
    Garbage *ga = (Garbage *)a;
    Garbage *gb = (Garbage *)b;
    if (ga->T != gb->T)
        return ga->T - gb->T;
    return 0;
}

int main(){
    int D, G;
    scanf("%d %d", &D, &G);
    Garbage garbages[G];
    for(int i=0;i<G;i++){
        scanf("%d %d %d", &garbages[i].T, &garbages[i].F, &garbages[i].H);
    }
    qsort(garbages, G, sizeof(Garbage), compare);
    
    int current[D+1];
    for(int i=0;i<=D;i++) current[i] = -1;
    current[0] = 10;
    
    int next_h[D+1];
    for(int i=0;i<=D;i++) next_h[i] = -1;
    
    int best_escape_time = 1000000000;
    int last_time = 0;
    
    for(int i=0;i<G;i++){
        int T = garbages[i].T;
        int F = garbages[i].F;
        int H = garbages[i].H;
        int delta_t = T - last_time;
        
        for(int h=0; h<=D; h++){
            if(current[h] == -1) continue;
            int v = current[h] - delta_t;
            if(v <= 0) continue;
            
            // Choice 1: Stack
            int new_h = h + H;
            if(new_h >= D){
                if(T < best_escape_time){
                    best_escape_time = T;
                }
            }
            else{
                if(next_h[new_h] < v){
                    next_h[new_h] = v;
                }
            }
            
            // Choice 2: Eat
            int new_v_eat = v + F;
            if(next_h[h] < new_v_eat){
                next_h[h] = new_v_eat;
            }
        }
        
        // Update current and reset next_h
        for(int h=0; h<=D; h++){
            current[h] = next_h[h];
            next_h[h] = -1;
        }
        last_time = T;
    }
    
    // Check for escape
    if(best_escape_time < 1000000000){
        printf("%d\n", best_escape_time);
    }
    else{
        // Calculate max survival time
        int max_survival = 0;
        for(int h=0; h<=D; h++){
            if(current[h] != -1){
                int survival = last_time + current[h];
                if(survival > max_survival){
                    max_survival = survival;
                }
            }
        }
        printf("%d\n", max_survival);
    }
    
    return 0;
}