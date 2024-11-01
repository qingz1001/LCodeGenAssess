#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEG 200005
#define MAX_COLOR 1000005

typedef struct Segment {
    int color;
    int prev;
    int next;
    int color_prev;
    int color_next;
} Segment;

Segment segments[MAX_SEG];
int seg_cnt = 0;

// Color list heads
int color_head[MAX_COLOR];
int color_tail[MAX_COLOR];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    
    // Initialize segments
    int current_color = a[0];
    segments[seg_cnt].color = current_color;
    segments[seg_cnt].prev = -1;
    segments[seg_cnt].next = -1;
    segments[seg_cnt].color_prev = -1;
    segments[seg_cnt].color_next = -1;
    // Add to color list
    color_head[current_color] = seg_cnt;
    color_tail[current_color] = seg_cnt;
    seg_cnt++;
    for(int i=1;i<n;i++){
        if(a[i] != current_color){
            // New segment
            segments[seg_cnt].color = a[i];
            segments[seg_cnt].prev = seg_cnt-1;
            segments[seg_cnt-1].next = seg_cnt;
            segments[seg_cnt].next = -1;
            segments[seg_cnt].color_prev = color_tail[a[i]];
            segments[seg_cnt].color_next = -1;
            if(color_tail[a[i]] != -1){
                segments[color_tail[a[i]]].color_next = seg_cnt;
            }
            else{
                color_head[a[i]] = seg_cnt;
            }
            color_tail[a[i]] = seg_cnt;
            seg_cnt++;
            current_color = a[i];
        }
    }
    
    // Initialize total segments
    int total_segments = seg_cnt;
    
    for(int i=0;i<m;i++){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int x, y;
            scanf("%d %d", &x, &y);
            if(x == y) continue;
            int s = color_head[x];
            while(s != -1){
                int next_s = segments[s].color_next;
                // Change color from x to y
                // Remove from color x list
                if(segments[s].color_prev != -1){
                    segments[segments[s].color_prev].color_next = segments[s].color_next;
                }
                else{
                    color_head[x] = segments[s].color_next;
                }
                if(segments[s].color_next != -1){
                    segments[segments[s].color_next].color_prev = segments[s].color_prev;
                }
                else{
                    color_tail[x] = segments[s].color_prev;
                }
                // Add to color y list
                segments[s].color_prev = color_tail[y];
                segments[s].color_next = -1;
                if(color_tail[y] != -1){
                    segments[color_tail[y]].color_next = s;
                }
                else{
                    color_head[y] = s;
                }
                color_tail[y] = s;
                segments[s].color = y;
                
                // Try to merge with previous
                if(segments[s].prev != -1 && segments[segments[s].prev].color == y){
                    int prev = segments[s].prev;
                    // Merge prev and s
                    segments[prev].next = segments[s].next;
                    if(segments[s].next != -1){
                        segments[segments[s].next].prev = prev;
                    }
                    // Remove s from color y list
                    if(segments[s].color_prev != -1){
                        segments[segments[s].color_prev].color_next = segments[s].color_next;
                    }
                    else{
                        color_head[y] = segments[s].color_next;
                    }
                    if(segments[s].color_next != -1){
                        segments[segments[s].color_next].color_prev = segments[s].color_prev;
                    }
                    else{
                        color_tail[y] = segments[s].color_prev;
                    }
                    total_segments--;
                    s = prev;
                }
                // Try to merge with next
                if(segments[s].next != -1 && segments[segments[s].next].color == y){
                    int nxt = segments[s].next;
                    // Merge s and nxt
                    segments[s].next = segments[nxt].next;
                    if(segments[nxt].next != -1){
                        segments[segments[nxt].next].prev = s;
                    }
                    // Remove nxt from color y list
                    if(segments[nxt].color_prev != -1){
                        segments[segments[nxt].color_prev].color_next = segments[nxt].color_next;
                    }
                    else{
                        color_head[y] = segments[nxt].color_next;
                    }
                    if(segments[nxt].color_next != -1){
                        segments[segments[nxt].color_next].color_prev = segments[nxt].color_prev;
                    }
                    else{
                        color_tail[y] = segments[nxt].color_prev;
                    }
                    total_segments--;
                }
                s = next_s;
            }
        }
        else if(op == 2){
            printf("%d\n", total_segments);
        }
    }
    return 0;
}