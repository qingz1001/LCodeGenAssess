#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x1, y1, x2, y2;
} Segment;

int main(){
    int N;
    long long S;
    scanf("%d %lld", &N, &S);
    Segment* segments = (Segment*)malloc(N * sizeof(Segment));
    for(int i=0;i<N;i++) {
        scanf("%lld %lld %lld %lld", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }
    long long current_x = S;
    long long current_y = 1e18;
    while(1){
        long long max_y = -1e18;
        int chosen = -1;
        double intersect_y;
        for(int i=0;i<N;i++){
            Segment s = segments[i];
            // Check if current_x is between s.x1 and s.x2
            if(s.x1 == s.x2){
                // Vertical segment, skip as drop would not follow it
                continue;
            }
            long long minx = s.x1 < s.x2 ? s.x1 : s.x2;
            long long maxx_seg = s.x1 > s.x2 ? s.x1 : s.x2;
            if(current_x <= minx || current_x >= maxx_seg){
                continue;
            }
            // Calculate y at current_x
            double t = (double)(current_x - s.x1) / (double)(s.x2 - s.x1);
            double y = s.y1 + t * (s.y2 - s.y1);
            if(y >= current_y){
                continue;
            }
            if(y > max_y){
                max_y = y;
                chosen = i;
                intersect_y = y;
            }
        }
        if(chosen == -1){
            break;
        }
        // Move to lower end of the chosen segment
        Segment s = segments[chosen];
        if(s.y1 < s.y2){
            current_x = s.x1;
            current_y = s.y1;
        }
        else{
            current_x = s.x2;
            current_y = s.y2;
        }
    }
    printf("%lld", current_x);
    free(segments);
    return 0;
}