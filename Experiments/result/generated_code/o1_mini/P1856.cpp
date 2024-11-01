#include <stdio.h>
#include <stdlib.h>

// Structure for Vertical Segments
typedef struct {
    int x;
    int y1;
    int y2;
} VerticalSegment;

// Structure for Horizontal Segments
typedef struct {
    int y;
    int x1;
    int x2;
} HorizontalSegment;

// Comparator for Vertical Segments: first by x, then by y1
int compare_vertical(const void *a, const void *b) {
    VerticalSegment va = *(VerticalSegment*)a;
    VerticalSegment vb = *(VerticalSegment*)b;
    if (va.x != vb.x)
        return va.x - vb.x;
    return va.y1 - vb.y1;
}

// Comparator for Horizontal Segments: first by y, then by x1
int compare_horizontal(const void *a, const void *b) {
    HorizontalSegment ha = *(HorizontalSegment*)a;
    HorizontalSegment hb = *(HorizontalSegment*)b;
    if (ha.y != hb.y)
        return ha.y - hb.y;
    return ha.x1 - hb.x1;
}

int main(){
    int N;
    scanf("%d", &N);
    VerticalSegment vertical_segs[10000];
    HorizontalSegment horizontal_segs[10000];
    int v_cnt = 0, h_cnt = 0;
    for(int i=0;i<N;i++){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        // Vertical segments
        vertical_segs[v_cnt].x = x1;
        vertical_segs[v_cnt].y1 = y1;
        vertical_segs[v_cnt].y2 = y2;
        v_cnt++;
        vertical_segs[v_cnt].x = x2;
        vertical_segs[v_cnt].y1 = y1;
        vertical_segs[v_cnt].y2 = y2;
        v_cnt++;
        // Horizontal segments
        horizontal_segs[h_cnt].y = y1;
        horizontal_segs[h_cnt].x1 = x1;
        horizontal_segs[h_cnt].x2 = x2;
        h_cnt++;
        horizontal_segs[h_cnt].y = y2;
        horizontal_segs[h_cnt].x1 = x1;
        horizontal_segs[h_cnt].x2 = x2;
        h_cnt++;
    }
    // Sort vertical segments
    qsort(vertical_segs, v_cnt, sizeof(VerticalSegment), compare_vertical);
    // Merge and sum vertical perimeter
    long long vertical_perim = 0;
    int i_v = 0;
    while(i_v < v_cnt){
        int current_x = vertical_segs[i_v].x;
        // Merge intervals at current_x
        int start = vertical_segs[i_v].y1;
        int end = vertical_segs[i_v].y2;
        i_v++;
        while(i_v < v_cnt && vertical_segs[i_v].x == current_x){
            if(vertical_segs[i_v].y1 <= end){
                if(vertical_segs[i_v].y2 > end){
                    end = vertical_segs[i_v].y2;
                }
            }
            else{
                vertical_perim += (end - start);
                start = vertical_segs[i_v].y1;
                end = vertical_segs[i_v].y2;
            }
            i_v++;
        }
        vertical_perim += (end - start);
    }
    // Sort horizontal segments
    qsort(horizontal_segs, h_cnt, sizeof(HorizontalSegment), compare_horizontal);
    // Merge and sum horizontal perimeter
    long long horizontal_perim = 0;
    int i_h = 0;
    while(i_h < h_cnt){
        int current_y = horizontal_segs[i_h].y;
        // Merge intervals at current_y
        int start = horizontal_segs[i_h].x1;
        int end = horizontal_segs[i_h].x2;
        i_h++;
        while(i_h < h_cnt && horizontal_segs[i_h].y == current_y){
            if(horizontal_segs[i_h].x1 <= end){
                if(horizontal_segs[i_h].x2 > end){
                    end = horizontal_segs[i_h].x2;
                }
            }
            else{
                horizontal_perim += (end - start);
                start = horizontal_segs[i_h].x1;
                end = horizontal_segs[i_h].x2;
            }
            i_h++;
        }
        horizontal_perim += (end - start);
    }
    printf("%lld\n", vertical_perim + horizontal_perim);
}