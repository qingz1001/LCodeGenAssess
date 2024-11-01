#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLOR 1000001
#define MAX_SEGMENTS 200000
#define MAX_TEMP 100000

typedef struct Segment {
    int id;
    int color;
    int prev; // Previous segment id
    int next; // Next segment id
    int color_prev; // Previous in color list
    int color_next; // Next in color list
} Segment;

Segment segments[MAX_SEGMENTS];
int color_head_list[MAX_COLOR];
int color_tail_list[MAX_COLOR];
int total_segments = 0;

int temp_segments[MAX_TEMP];
int temp_count = 0;

// Function to remove a segment from its color list
void remove_from_color(int seg, int color){
    if(segments[seg].color_prev != -1){
        segments[segments[seg].color_prev].color_next = segments[seg].color_next;
    }
    else{
        color_head_list[color] = segments[seg].color_next;
    }
    if(segments[seg].color_next != -1){
        segments[segments[seg].color_next].color_prev = segments[seg].color_prev;
    }
    else{
        color_tail_list[color] = segments[seg].color_prev;
    }
    segments[seg].color_prev = -1;
    segments[seg].color_next = -1;
}

// Function to add a segment to a color list
void add_to_color(int seg, int color){
    segments[seg].color_next = color_head_list[color];
    segments[seg].color_prev = -1;
    if(color_head_list[color] != -1){
        segments[color_head_list[color]].color_prev = seg;
    }
    color_head_list[color] = seg;
    if(color_tail_list[color] == -1){
        color_tail_list[color] = seg;
    }
}

// Function to collect all segments of a color into temp_segments
int collect_color_segments(int color){
    temp_count = 0;
    int seg = color_head_list[color];
    while(seg != -1){
        temp_segments[temp_count++] = seg;
        seg = segments[seg].color_next;
    }
    return temp_count;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a;
    // Initialize color lists
    for(int i=0;i<=1000000;i++){
        color_head_list[i] = -1;
        color_tail_list[i] = -1;
    }
    // Read the first color and initialize first segment
    scanf("%d", &a);
    segments[0].id = 0;
    segments[0].color = a;
    segments[0].prev = -1;
    segments[0].next = -1;
    segments[0].color_prev = -1;
    segments[0].color_next = color_head_list[a];
    if(color_head_list[a] != -1){
        segments[color_head_list[a]].color_prev = 0;
    }
    color_head_list[a] = 0;
    if(color_tail_list[a] == -1){
        color_tail_list[a] = 0;
    }
    total_segments = 1;
    int last_seg = 0;
    int num_segments = 1;
    for(int i=2;i<=n;i++){
        int current;
        scanf("%d", &current);
        if(current != segments[last_seg].color){
            // Create new segment
            segments[num_segments].id = num_segments;
            segments[num_segments].color = current;
            segments[num_segments].prev = last_seg;
            segments[num_segments].next = -1;
            // Link the previous segment
            segments[last_seg].next = num_segments;
            // Add to color list
            segments[num_segments].color_prev = -1;
            segments[num_segments].color_next = color_head_list[current];
            if(color_head_list[current] != -1){
                segments[color_head_list[current]].color_prev = num_segments;
            }
            color_head_list[current] = num_segments;
            if(color_tail_list[current] == -1){
                color_tail_list[current] = num_segments;
            }
            last_seg = num_segments;
            num_segments++;
            total_segments++;
        }
        else{
            // Extend the current segment, do nothing
        }
    }
    // Process operations
    for(int i=0;i<m;i++){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int x, y;
            scanf("%d %d", &x, &y);
            if(x == y) continue;
            // Collect all segments with color x
            int count = collect_color_segments(x);
            // Clear color x's list
            color_head_list[x] = -1;
            color_tail_list[x] = -1;
            for(int j=0; j<count; j++){
                int s = temp_segments[j];
                if(segments[s].color != x) continue;
                // Change color to y
                segments[s].color = y;
                // Add to y's color list
                add_to_color(s, y);
                // Try to merge with previous segment
                if(segments[s].prev != -1 && segments[segments[s].prev].color == y){
                    int p = segments[s].prev;
                    // Merge p and s
                    segments[p].next = segments[s].next;
                    if(segments[s].next != -1){
                        segments[segments[s].next].prev = p;
                    }
                    // Remove s from y's list
                    remove_from_color(s, y);
                    total_segments--;
                    s = p;
                }
                // Try to merge with next segment
                if(segments[s].next != -1 && segments[segments[s].next].color == y){
                    int n_seg = segments[s].next;
                    // Merge s and n_seg
                    segments[s].next = segments[n_seg].next;
                    if(segments[n_seg].next != -1){
                        segments[segments[n_seg].next].prev = s;
                    }
                    // Remove n_seg from y's list
                    remove_from_color(n_seg, y);
                    total_segments--;
                }
            }
        }
        else if(op == 2){
            printf("%d\n", total_segments);
        }
    }
    return 0;
}