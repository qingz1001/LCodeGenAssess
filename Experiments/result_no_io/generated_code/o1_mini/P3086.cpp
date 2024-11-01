#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 300

int main(){
    int N;
    scanf("%d", &N);
    char grid[MAXN+2][MAXN+2];
    for(int i=0;i<N;i++) {
        scanf("%s", grid[i]);
    }
    
    // Precompute prefix sums for each row
    int prefix[MAXN][MAXN+1];
    for(int i=0;i<N;i++){
        prefix[i][0] = 0;
        for(int j=0; j<N; j++){
            prefix[i][j+1] = prefix[i][j] + (grid[i][j] == '.' ? 1 : 0);
        }
    }
    
    // Function to check if a rectangle from (r1,c1) to (r2,c2) is all '.'
    auto isAllDot = [&](int r1, int c1, int r2, int c2) -> int {
        for(int r = r1; r <= r2; r++) {
            if(prefix[r][c2+1] - prefix[r][c1] != c2 - c1 +1)
                return 0;
        }
        return 1;
    };
    
    // Precompute all possible rectangles and store their internal area
    // Since N is small, we can iterate over all possible rectangles
    typedef struct {
        int top, left, bottom, right, area;
    } Rect;
    Rect rects[90000];
    int rectCount = 0;
    for(int r1=0;r1<N;r1++){
        for(int c1=0;c1<N;c1++){
            for(int r2=r1+2;r2<N;r2++){
                for(int c2=c1+2;c2<N;c2++){
                    if(isAllDot(r1, c1, r2, c2)){
                        int interior_area = (r2 - r1 -1) * (c2 - c1 -1);
                        rects[rectCount].top = r1;
                        rects[rectCount].left = c1;
                        rects[rectCount].bottom = r2;
                        rects[rectCount].right = c2;
                        rects[rectCount].area = interior_area;
                        rectCount++;
                    }
                }
            }
        }
    }
    
    // For each possible top rectangle, find bottom rectangles that have top edge including the bottom edge of top rectangle
    // To optimize, group rectangles by their top edge
    Rect *topRects[300];
    int topCounts[300];
    memset(topCounts, 0, sizeof(topCounts));
    Rect *bottomRects[300];
    int bottomCounts[300];
    memset(bottomCounts, 0, sizeof(bottomCounts));
    for(int i=0;i<rectCount;i++){
        topRects[i] = &rects[i];
        topCounts[i] = 0;
        bottomRects[i] = &rects[i];
        bottomCounts[i] = 0;
    }
    
    long long maxScore = -1;
    for(int i=0;i<rectCount;i++){
        Rect top = rects[i];
        for(int j=0;j<rectCount;j++){
            Rect bottom = rects[j];
            if(bottom.top == top.bottom){
                // Check if bottom's top edge includes top's bottom edge
                if(bottom.left <= top.left && bottom.right >= top.right){
                    long long score = (long long)top.area * (long long)bottom.area;
                    if(score > maxScore){
                        maxScore = score;
                    }
                }
            }
        }
    }
    
    printf("%lld\n", maxScore);
}