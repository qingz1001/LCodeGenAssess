#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int min_x;
    int max_x;
    int y;
} HLine;

typedef struct {
    int min_y;
    int max_y;
    int x;
} VLine;

int main(){
    int N;
    scanf("%d", &N);
    
    HLine hlines[100];
    int hcount = 0;
    VLine vlines[100];
    int vcount = 0;
    
    for(int i=0;i<N;i++){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if(y1 == y2){
            HLine hl;
            hl.y = y1;
            if(x1 < x2){
                hl.min_x = x1;
                hl.max_x = x2;
            }
            else{
                hl.min_x = x2;
                hl.max_x = x1;
            }
            hlines[hcount++] = hl;
        }
        else{
            VLine vl;
            vl.x = x1;
            if(y1 < y2){
                vl.min_y = y1;
                vl.max_y = y2;
            }
            else{
                vl.min_y = y2;
                vl.max_y = y1;
            }
            vlines[vcount++] = vl;
        }
        
        // Count rectangles
        int rect = 0;
        for(int a=0;a<hcount-1;a++){
            for(int b=a+1;b<hcount;b++){
                HLine h1 = hlines[a];
                HLine h2 = hlines[b];
                int k = 0;
                for(int c=0;c<vcount;c++){
                    VLine v = vlines[c];
                    if(v.x >= h1.min_x && v.x <= h1.max_x &&
                       v.x >= h2.min_x && v.x <= h2.max_x &&
                       v.min_y <= h1.y && v.max_y >= h1.y &&
                       v.min_y <= h2.y && v.max_y >= h2.y){
                        k++;
                    }
                }
                if(k >=2){
                    rect += (k*(k-1))/2;
                }
            }
        }
        printf("%d\n", rect);
    }
    return 0;
}