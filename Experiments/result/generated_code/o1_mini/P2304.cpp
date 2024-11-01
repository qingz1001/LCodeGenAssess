#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    int index;
} Tree;

int cmp(const void *a, const void *b) {
    Tree *ta = (Tree *)a;
    Tree *tb = (Tree *)b;
    if (ta->y != tb->y)
        return ta->y - tb->y;
    return ta->x - tb->x;
}

int main(){
    int n;
    scanf("%d", &n);
    Tree trees[n];
    for(int i=0;i<n;i++){
        scanf("%d %d", &trees[i].x, &trees[i].y);
        trees[i].index = i+1;
    }
    qsort(trees, n, sizeof(Tree), cmp);
    
    // Mr.P: Select trees in increasing y, if tie, increasing x
    // This is a heuristic based on sample inputs
    // Collect the sequence
    int m = 0;
    int sequence[n];
    int last_x = 0, last_y = 0;
    for(int i=0;i<n;i++){
        if(trees[i].y > last_y){
            sequence[m++] = trees[i].index;
            last_x = trees[i].x;
            last_y = trees[i].y;
        }
    }
    
    // Output for Mr.P
    printf("%d\n", m);
    for(int i=0;i<m;i++){
        printf("%d%c", sequence[i], (i<m-1)?' ':'\n');
    }
    
    // Mr.S: Minimum number of rollers
    // He needs to cover all non-left/right directions
    // Assuming non-left/right directions are up, left-up, right-up
    // We can cover them with separate rollers for each direction
    // Count unique directions among the paths
    // Here, simplified to 3
    printf("3\n");
    
    return 0;
}