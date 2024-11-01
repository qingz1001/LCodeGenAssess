#include <stdio.h>
#include <stdlib.h>

#define MAX_TILES 200
unsigned long long tiles_low[MAX_TILES];
unsigned long long tiles_high[MAX_TILES];
int tile_count = 0;
int max_count = 0;
int n, m;

typedef struct {
    int di[3];
    int dj[3];
} Shape;

// Define the four T-shapes
Shape shapes[4] = {
    // Up
    { {0, 1, 2}, {1, 1, 1} },
    // Right
    { {1, 1, 1}, {0, 1, 2} },
    // Down
    { {0, 1, 2}, {1, 1, 1} },
    // Left
    { {1, 1, 1}, {0, 1, 2} }
};

void add_tile(int base_i, int base_j, Shape shape) {
    int cells[5][2];
    // For T-shape up and down
    if (shape.di[0] == 0 || shape.di[0] == 1) {
        cells[0][0] = base_i + shape.di[0];
        cells[0][1] = base_j + shape.dj[0];
        cells[1][0] = base_i + shape.di[1];
        cells[1][1] = base_j + shape.dj[1];
        cells[2][0] = base_i + shape.di[2];
        cells[2][1] = base_j + shape.dj[2];
        cells[3][0] = base_i + shape.di[1] + 1;
        cells[3][1] = base_j + shape.dj[1];
        cells[4][0] = base_i + shape.di[1] - 1;
        cells[4][1] = base_j + shape.dj[1];
    }
    unsigned long long low = 0, high = 0;
    for(int k=0;k<5;k++) {
        int i = cells[k][0];
        int j = cells[k][1];
        if(i <0 || i >=n || j <0 || j >=m) return;
        int pos = i * m + j;
        if(pos < 64) low |= 1ULL << pos;
        else high |= 1ULL << (pos - 64);
    }
    tiles_low[tile_count] = low;
    tiles_high[tile_count] = high;
    tile_count++;
}

int cmp(const void *a, const void *b){
    unsigned long long x = tiles_low[*(int*)a] | tiles_high[*(int*)a];
    unsigned long long y = tiles_low[*(int*)b] | tiles_high[*(int*)b];
    if(__builtin_popcountll(x) < __builtin_popcountll(y)) return -1;
    if(__builtin_popcountll(x) > __builtin_popcountll(y)) return 1;
    return 0;
}

void preprocess() {
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            for(int s=0;s<4;s++) {
                Shape shape;
                if(s ==0){
                    // Up
                    shape.di[0]=0; shape.dj[0]=-1;
                    shape.di[1]=0; shape.dj[1]=0;
                    shape.di[2]=0; shape.dj[2]=1;
                }
                else if(s==1){
                    // Right
                    shape.di[0]=-1; shape.dj[0]=0;
                    shape.di[1]=0; shape.dj[1]=0;
                    shape.di[2]=1; shape.dj[2]=0;
                }
                else if(s==2){
                    // Down
                    shape.di[0]=0; shape.dj[0]=-1;
                    shape.di[1]=0; shape.dj[1]=0;
                    shape.di[2]=0; shape.dj[2]=1;
                }
                else{
                    // Left
                    shape.di[0]=-1; shape.dj[0]=0;
                    shape.di[1]=0; shape.dj[1]=0;
                    shape.di[2]=1; shape.dj[2]=0;
                }
                add_tile(i, j, shape);
            }
        }
    }
}

void backtrack(int idx, unsigned long long occupied_low, unsigned long long occupied_high, int count){
    if(idx == tile_count){
        if(count > max_count) max_count = count;
        return;
    }
    if(count + (tile_count - idx) <= max_count) return;
    // Try to include the current tile
    if( (tiles_low[idx] & occupied_low)==0 && (tiles_high[idx] & occupied_high)==0 ){
        backtrack(idx+1, occupied_low | tiles_low[idx], occupied_high | tiles_high[idx], count+1);
    }
    // Skip the current tile
    backtrack(idx+1, occupied_low, occupied_high, count);
}

int main(){
    scanf("%d %d", &n, &m);
    preprocess();
    backtrack(0, 0, 0, 0);
    printf("%d\n", max_count);
    return 0;
}