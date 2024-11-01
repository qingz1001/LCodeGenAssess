#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 16
#define MAX_COLORS 20
#define MAX_STATE (1<<16)
#define INF 255

struct Rect {
    int y1, x1, y2, x2, c;
} rects[MAX_N];

int main(){
    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d %d %d %d %d", &rects[i].y1, &rects[i].x1, &rects[i].y2, &rects[i].x2, &rects[i].c);
    }
    
    // Compute dependencies
    unsigned short dep[MAX_N];
    for(int i=0; i<N; i++) dep[i] = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(i == j) continue;
            if(rects[j].y2 == rects[i].y1){
                if(rects[j].x1 < rects[i].x2 && rects[j].x2 > rects[i].x1){
                    dep[i] |= (1<<j);
                }
            }
        }
    }
    
    // Compute mask per color
    unsigned short mask_per_color[MAX_COLORS+1];
    for(int c=0; c<=MAX_COLORS; c++) mask_per_color[c] = 0;
    for(int i=0; i<N; i++){
        if(rects[i].c >=1 && rects[i].c <= MAX_COLORS){
            mask_per_color[rects[i].c] |= (1<<i);
        }
    }
    
    // Initialize visited
    unsigned char visited_states[MAX_STATE];
    for(int i=0; i<(1<<N); i++) visited_states[i] = INF;
    visited_states[0] = 0;
    
    // Initialize queue
    unsigned int queue_arr[MAX_STATE];
    int head =0, tail=0;
    queue_arr[tail++] = 0;
    
    while(head < tail){
        unsigned int current = queue_arr[head++];
        unsigned char current_steps = visited_states[current];
        if(current == ((1<<N)-1)){
            break;
        }
        // Iterate through all colors
        for(int C=1; C<=MAX_COLORS; C++){
            unsigned int ready =0;
            for(int i=0; i<N; i++){
                if(rects[i].c == C && !(current & (1<<i)) && ((dep[i] & ~current) ==0)){
                    ready |= (1<<i);
                }
            }
            if(ready){
                unsigned int new_state = current | ready;
                if(visited_states[new_state] > current_steps +1){
                    visited_states[new_state] = current_steps +1;
                    queue_arr[tail++] = new_state;
                }
            }
        }
    }
    
    unsigned int full = (1<<N)-1;
    printf("%d\n", visited_states[full]);
    return 0;
}