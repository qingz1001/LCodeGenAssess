#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tree;

typedef struct {
    int y;
    int x;
} YXPair;

typedef struct {
    int x;
    int y;
} XYPair;

int compare_by_y_then_x(const void* a, const void* b) {
    Tree* ta = (Tree*)a;
    Tree* tb = (Tree*)b;
    if (ta->y != tb->y)
        return ta->y - tb->y;
    return ta->x - tb->x;
}

int compare_by_x_then_y(const void* a, const void* b) {
    Tree* ta = (Tree*)a;
    Tree* tb = (Tree*)b;
    if (ta->x != tb->x)
        return ta->x - tb->x;
    return ta->y - tb->y;
}

int compare_col_valid(const void* a, const void* b) {
    XYPair* pa = (XYPair*)a;
    XYPair* pb = (XYPair*)b;
    if (pa->x != pb->x)
        return pa->x - pb->x;
    return pa->y - pb->y;
}

int compare_sorted_tree(const void* a, const void* b) {
    Tree* ta = (Tree*)a;
    Tree* tb = (Tree*)b;
    if (ta->x != tb->x)
        return ta->x - tb->x;
    return ta->y - tb->y;
}

int binary_search_tree(Tree* trees, int W, int x, int y) {
    int left = 0, right = W - 1, mid, cmp;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (trees[mid].x == x && trees[mid].y == y)
            return 1;
        if (trees[mid].x < x || (trees[mid].x == x && trees[mid].y < y))
            left = mid + 1;
        else
            right = mid - 1;
    }
    return 0;
}

int binary_search_col_valid(XYPair* list, int size, int x, int y) {
    int left = 0, right = size -1, mid, cmp;
    while (left <= right) {
        mid = left + (right - left) /2;
        if (list[mid].x == x && list[mid].y == y)
            return 1;
        if (list[mid].x < x || (list[mid].x == x && list[mid].y < y))
            left = mid +1;
        else
            right = mid -1;
    }
    return 0;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int W;
    scanf("%d", &W);
    Tree* trees = (Tree*)malloc(sizeof(Tree)*W);
    for(int i=0;i<W;i++) scanf("%d %d", &trees[i].x, &trees[i].y);
    int k;
    scanf("%d", &k);
    
    // Sort by y then x
    qsort(trees, W, sizeof(Tree), compare_by_y_then_x);
    
    // Prepare row_valid_list
    YXPair* row_valid = (YXPair*)malloc(sizeof(YXPair)*W);
    int row_valid_count =0;
    int i=0;
    while(i < W){
        int current_y = trees[i].y;
        int start = i;
        while(i < W && trees[i].y == current_y) i++;
        int count = i - start;
        if(count >= 2*k){
            for(int j= start +k; j < start + count -k; j++){
                int valid =1;
                for(int d=1; d<=k; d++) {
                    if(trees[j-d].x != trees[j].x -d){
                        valid=0;
                        break;
                    }
                }
                if(valid){
                    for(int d=1; d<=k; d++) {
                        if(trees[j+d].x != trees[j].x +d){
                            valid=0;
                            break;
                        }
                    }
                }
                if(valid){
                    row_valid[row_valid_count].y = current_y;
                    row_valid[row_valid_count].x = trees[j].x;
                    row_valid_count++;
                }
            }
        }
    }
    
    // Sort by x then y
    qsort(trees, W, sizeof(Tree), compare_by_x_then_y);
    
    // Prepare col_valid_list
    XYPair* col_valid = (XYPair*)malloc(sizeof(XYPair)*W);
    int col_valid_count =0;
    i=0;
    while(i < W){
        int current_x = trees[i].x;
        int start = i;
        while(i < W && trees[i].x == current_x) i++;
        int count = i - start;
        if(count >= 2*k){
            for(int j= start +k; j < start + count -k; j++){
                int valid =1;
                for(int d=1; d<=k; d++) {
                    if(trees[j-d].y != trees[j].y -d){
                        valid=0;
                        break;
                    }
                }
                if(valid){
                    for(int d=1; d<=k; d++) {
                        if(trees[j+d].y != trees[j].y +d){
                            valid=0;
                            break;
                        }
                    }
                }
                if(valid){
                    col_valid[col_valid_count].x = current_x;
                    col_valid[col_valid_count].y = trees[j].y;
                    col_valid_count++;
                }
            }
        }
    }
    
    // Sort col_valid by x then y
    qsort(col_valid, col_valid_count, sizeof(XYPair), compare_col_valid);
    
    // Sort trees by x then y for binary search
    qsort(trees, W, sizeof(Tree), compare_sorted_tree);
    
    // Sort row_valid not necessary, iterate as is
    // Now iterate row_valid and check if in col_valid and not a tree
    long long total =0;
    for(int r=0; r<row_valid_count; r++){
        int y = row_valid[r].y;
        int x = row_valid[r].x;
        if(binary_search_col_valid(col_valid, col_valid_count, x, y)){
            if(!binary_search_tree(trees, W, x, y)){
                total++;
                if(total >= 2147483648LL) total -= 2147483648LL;
            }
        }
    }
    
    printf("%lld\n", total);
    
    free(trees);
    free(row_valid);
    free(col_valid);
    return 0;
}