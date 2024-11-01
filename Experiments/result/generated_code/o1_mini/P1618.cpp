#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int z;
} Triplet;

int compare(const void *a, const void *b) {
    Triplet *ta = (Triplet *)a;
    Triplet *tb = (Triplet *)b;
    if (ta->x != tb->x)
        return ta->x - tb->x;
    if (ta->y != tb->y)
        return ta->y - tb->y;
    return ta->z - tb->z;
}

int main(){
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    
    // Calculate k_min
    int k_min_A = (100 + A -1) / A;
    int k_min_B = (100 + B -1) / B;
    int k_min_C = (100 + C -1) / C;
    int k_min = k_min_A;
    if(k_min_B > k_min) k_min = k_min_B;
    if(k_min_C > k_min) k_min = k_min_C;
    
    // Calculate k_max
    int k_max_A = 999 / A;
    int k_max_B = 999 / B;
    int k_max_C = 999 / C;
    int k_max = k_max_A;
    if(k_max_B < k_max) k_max = k_max_B;
    if(k_max_C < k_max) k_max = k_max_C;
    
    Triplet solutions[1000];
    int count = 0;
    
    for(int k = k_min; k <= k_max; k++){
        int x = k * A;
        int y = k * B;
        int z = k * C;
        
        // Check if all are 3-digit
        if(x < 100 || x > 999 || y < 100 || y > 999 || z < 100 || z > 999)
            continue;
        
        int mask = 0;
        int valid = 1;
        int nums[9] = {x / 100, (x / 10) % 10, x % 10,
                      y / 100, (y / 10) % 10, y % 10,
                      z / 100, (z / 10) % 10, z % 10};
        for(int i = 0; i < 9; i++){
            if(nums[i] == 0 || (mask & (1 << nums[i]))){
                valid = 0;
                break;
            }
            mask |= (1 << nums[i]);
        }
        if(valid){
            solutions[count].x = x;
            solutions[count].y = y;
            solutions[count].z = z;
            count++;
        }
    }
    
    if(count == 0){
        printf("No!!!");
        return 0;
    }
    
    qsort(solutions, count, sizeof(Triplet), compare);
    
    for(int i = 0; i < count; i++){
        printf("%d %d %d\n", solutions[i].x, solutions[i].y, solutions[i].z);
    }
    
    return 0;
}