#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int color;
    int count;
} Color;

int cmp(const void* a, const void* b){
    Color *c1 = (Color*)a;
    Color *c2 = (Color*)b;
    if(c2->count != c1->count) return c2->count - c1->count;
    return c1->color - c2->color;
}

int main(){
    int n, m, c;
    scanf("%d %d %d", &n, &m, &c);
    Color colors[c];
    for(int i=0;i<c;i++){
        colors[i].color = i+1;
        scanf("%d", &colors[i].count);
    }
    qsort(colors, c, sizeof(Color), cmp);
    int grid[n][m];
    int total = n * m;
    int idx = 0;
    int row_dir = 1; // 1 for left to right, -1 for right to left
    for(int i=0;i<n;i++){
        if(row_dir == 1){
            for(int j=0;j<m;j++){
                while(colors[idx].count == 0 && idx < c) idx++;
                if(idx < c){
                    grid[i][j] = colors[idx].color;
                    colors[idx].count--;
                }
            }
        }
        else{
            for(int j=m-1;j>=0;j--){
                while(colors[idx].count == 0 && idx < c) idx++;
                if(idx < c){
                    grid[i][j] = colors[idx].color;
                    colors[idx].count--;
                }
            }
        }
        row_dir *= -1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d%c", grid[i][j], (j<m-1)?' ':'\n');
        }
    }
    return 0;
}