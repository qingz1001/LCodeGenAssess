#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long long mask_low;
    unsigned long long mask_high;
} Placement;

Placement placements[500];
int total_placements = 0;
int max_count = 0;
int n, m;

// Define the four orientations
const int dx[4][5] = {
    {0, -1, 0, 0, 0},
    {0, 0, 1, 0, -1},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, -1}
};

const int dy[4][5] = {
    {0, 0, 1, 2, 0},
    {0, 1, 1, 1, 1},
    {0, 0, -1, -2, 0},
    {0, -1, -1, -1, -1}
};

void add_placement(int base, int orientation) {
    int cells[5];
    int valid = 1;
    for(int k=0; k<5; k++) {
        int ni = base / m + dx[orientation][k];
        int nj = base % m + dy[orientation][k];
        if(ni < 0 || ni >= n || nj < 0 || nj >= m){
            valid = 0;
            break;
        }
        cells[k] = ni * m + nj;
    }
    if(valid){
        unsigned long long low = 0, high = 0;
        for(int k=0; k<5; k++) {
            if(cells[k] < 64)
                low |= 1ULL << cells[k];
            else
                high |= 1ULL << (cells[k] - 64);
        }
        placements[total_placements].mask_low = low;
        placements[total_placements].mask_high = high;
        total_placements++;
    }
}

void generate_placements(){
    for(int i=0; i<n*m; i++) {
        for(int ori=0; ori<4; ori++) {
            add_placement(i, ori);
        }
    }
}

void dfs(int index, unsigned long long mask_low, unsigned long long mask_high, int count){
    if(index >= total_placements){
        if(count > max_count)
            max_count = count;
        return;
    }
    if(count + total_placements - index <= max_count){
        return;
    }
    // Take the placement
    if(!(placements[index].mask_low & mask_low) && !(placements[index].mask_high & mask_high)){
        dfs(index + 1, mask_low | placements[index].mask_low, mask_high | placements[index].mask_high, count + 1);
    }
    // Skip the placement
    dfs(index + 1, mask_low, mask_high, count);
}

int main(){
    scanf("%d %d", &n, &m);
    generate_placements();
    dfs(0, 0, 0, 0);
    printf("%d\n", max_count);
    return 0;
}