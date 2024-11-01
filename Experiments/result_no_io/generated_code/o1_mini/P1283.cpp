#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned short ushort;
typedef unsigned int uint;

#define MAX_N 16
#define MAX_STATE (1<<16)
#define MAX_COLOR 20

int main(){
    int N;
    scanf("%d", &N);
    struct Rectangle {
        int y1, x1, y2, x2, c;
    } rect[MAX_N];
    
    for(int i=0;i<N;i++) {
        scanf("%d %d %d %d %d", &rect[i].y1, &rect[i].x1, &rect[i].y2, &rect[i].x2, &rect[i].c);
    }
    
    ushort dep[MAX_N];
    memset(dep, 0, sizeof(dep));
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(i == j) continue;
            if(rect[j].y2 == rect[i].y1 && rect[j].x1 < rect[i].x2 && rect[j].x2 > rect[i].x1){
                dep[i] |= (1<<j);
            }
        }
    }
    
    unsigned char visited[MAX_STATE];
    memset(visited, 255, sizeof(visited));
    visited[0] = 0;
    
    ushort queue[MAX_STATE];
    int head=0, tail=1;
    queue[0] = 0;
    
    ushort full = (N == 16) ? 0xFFFF : ((1<<N) -1);
    
    while(head < tail){
        ushort current = queue[head];
        int step = visited[current];
        if(current == full){
            printf("%d\n", step);
            return 0;
        }
        
        // Determine ready rectangles
        ushort ready = 0;
        for(int i=0;i<N;i++) {
            if( !(current & (1<<i)) && ((current & dep[i]) == dep[i])){
                ready |= (1<<i);
            }
        }
        
        // Group ready by color
        ushort color_ready[MAX_COLOR+1];
        memset(color_ready, 0, sizeof(color_ready));
        for(int i=0;i<N;i++) {
            if(ready & (1<<i)){
                int c = rect[i].c;
                color_ready[c] |= (1<<i);
            }
        }
        
        // Try each color
        for(int c=1;c<=MAX_COLOR;c++) {
            if(color_ready[c]){
                ushort new_state = current | color_ready[c];
                if(visited[new_state] == 255){
                    visited[new_state] = step +1;
                    queue[tail++] = new_state;
                }
            }
        }
        head++;
    }
    return 0;
}