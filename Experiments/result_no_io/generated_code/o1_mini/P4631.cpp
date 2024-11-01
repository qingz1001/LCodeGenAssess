#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long long x, y, r;
    int index;
} Circle;

typedef struct Node {
    int circle;
    struct Node* next;
} Node;

#define TABLE_SIZE 300007
#define HASH_MULTIPLIER 1000003
#define GRID_SIZE 1000000

int compare(const void* a, const void* b){
    Circle *c1 = (Circle*)a;
    Circle *c2 = (Circle*)b;
    if(c1->r != c2->r){
        return (c2->r > c1->r) - (c2->r < c1->r);
    }
    return c1->index - c2->index;
}

int main(){
    int n;
    scanf("%d", &n);
    Circle *circles = (Circle*)malloc(n * sizeof(Circle));
    for(int i=0;i<n;i++){
        scanf("%lld %lld %lld", &circles[i].x, &circles[i].y, &circles[i].r);
        circles[i].index = i;
    }
    qsort(circles, n, sizeof(Circle), compare);
    // Initialize hash table
    Node* hash_table[TABLE_SIZE];
    for(int i=0;i<TABLE_SIZE;i++) hash_table[i] = NULL;
    // Initialize answer array
    int *ans = (int*)calloc(n, sizeof(int));
    for(int i=0;i<n;i++){
        Circle c = circles[i];
        // Determine cell range
        long long min_x = c.x - c.r;
        long long max_x = c.x + c.r;
        long long min_y = c.y - c.r;
        long long max_y = c.y + c.r;
        // Compute cell boundaries
        long long cell_min_x = min_x >= 0 ? min_x / GRID_SIZE : (min_x+1) / GRID_SIZE -1;
        long long cell_max_x = max_x >= 0 ? max_x / GRID_SIZE : (max_x+1) / GRID_SIZE -1;
        long long cell_min_y = min_y >= 0 ? min_y / GRID_SIZE : (min_y+1) / GRID_SIZE -1;
        long long cell_max_y = max_y >= 0 ? max_y / GRID_SIZE : (max_y+1) / GRID_SIZE -1;
        int assigned = 0;
        for(long long cx = cell_min_x; cx <= cell_max_x && !assigned; cx++){
            for(long long cy = cell_min_y; cy <= cell_max_y && !assigned; cy++){
                long long key = cx * HASH_MULTIPLIER + cy;
                if(key < 0) key = -key;
                int hash = key % TABLE_SIZE;
                Node* node = hash_table[hash];
                while(node){
                    Circle d = circles[node->circle];
                    long long dx = c.x - d.x;
                    long long dy = c.y - d.y;
                    long long dist_sq = dx * dx + dy * dy;
                    long long rad_sum = c.r + d.r;
                    if(dist_sq <= rad_sum * rad_sum){
                        ans[c.index] = d.index +1;
                        assigned = 1;
                        break;
                    }
                    node = node->next;
                }
            }
        }
        if(!assigned){
            ans[c.index] = c.index +1;
        }
        // Insert current circle into hash table
        long long cell_x = c.x >=0 ? c.x / GRID_SIZE : (c.x+1) / GRID_SIZE -1;
        long long cell_y = c.y >=0 ? c.y / GRID_SIZE : (c.y+1) / GRID_SIZE -1;
        long long key = cell_x * HASH_MULTIPLIER + cell_y;
        if(key < 0) key = -key;
        int hash = key % TABLE_SIZE;
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->circle = i;
        new_node->next = hash_table[hash];
        hash_table[hash] = new_node;
    }
    // Prepare output in original order
    int *output = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) output[circles[i].index] = ans[circles[i].index];
    for(int i=0;i<n;i++){
        printf("%d%c", output[i], i<n-1?' ':'\n');
    }
    // Free memory
    free(circles);
    free(ans);
    free(output);
    for(int i=0;i<TABLE_SIZE;i++){
        Node* node = hash_table[i];
        while(node){
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
    return 0;
}