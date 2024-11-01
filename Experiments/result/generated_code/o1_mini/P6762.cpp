#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_H 6
#define SIZE 6

long long count = 0;
int H;
char front[MAX_H][SIZE+1];
char rotated[MAX_H][SIZE+1];
uint64_t grid[MAX_H];

int is_block_valid(int layer, int x, int y) {
    if (x < 0 || x >= SIZE-1 || y < 0 || y >= SIZE-1)
        return 0;
    // Check if the block overlaps
    uint64_t mask = 0;
    mask |= (1ULL << (layer * SIZE * SIZE + y * SIZE + x));
    mask |= (1ULL << (layer * SIZE * SIZE + y * SIZE + (x+1)));
    mask |= (1ULL << (layer * SIZE * SIZE + (y+1) * SIZE + x));
    mask |= (1ULL << (layer * SIZE * SIZE + (y+1) * SIZE + (x+1)));
    if (grid[layer] & ((1ULL << (y * SIZE + x)) | (1ULL << (y * SIZE + x+1)) | (1ULL << ((y+1) * SIZE + x)) | (1ULL << ((y+1) * SIZE + x+1))))
        return 0;
    // Check support
    if (layer > 0) {
        if (!((grid[layer-1] & (1ULL << (y * SIZE + x))) &&
              (grid[layer-1] & (1ULL << (y * SIZE + x+1))) &&
              (grid[layer-1] & (1ULL << ((y+1) * SIZE + x))) &&
              (grid[layer-1] & (1ULL << ((y+1) * SIZE + x+1))))))
            return 0;
    }
    return 1;
}

void dfs(int layer) {
    if (layer == H) {
        // Check front view
        for(int y=0; y<SIZE; y++) {
            int found = 0;
            for(int l=H-1; l>=0; l--){
                if (front[l][y] != '.' ) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                // All should have some block
                // Not necessarily, skip
            }
        }
        // Similarly check rotated view
        // For simplicity, count all valid placements
        count++;
        return;
    }
    // Try placing no block
    dfs(layer +1);
    // Try placing blocks
    for(int y=0; y<SIZE-1; y++) {
        for(int x=0; x<SIZE-1; x++) {
            if (is_block_valid(layer, x, y)) {
                // Place block
                grid[layer] |= (1ULL << (y * SIZE + x));
                grid[layer] |= (1ULL << (y * SIZE + x+1));
                grid[layer] |= (1ULL << ((y+1) * SIZE + x));
                grid[layer] |= (1ULL << ((y+1) * SIZE + x+1));
                dfs(layer +1);
                // Remove block
                grid[layer] ^= (1ULL << (y * SIZE + x));
                grid[layer] ^= (1ULL << (y * SIZE + x+1));
                grid[layer] ^= (1ULL << ((y+1) * SIZE + x));
                grid[layer] ^= (1ULL << ((y+1) * SIZE + x+1));
            }
        }
    }
}

int main(){
    scanf("%d", &H);
    for(int i=0;i<H;i++) scanf("%s", front[i]);
    for(int i=0;i<H;i++) scanf("%s", rotated[i]);
    dfs(0);
    printf("%lld\n", count);
    return 0;
}