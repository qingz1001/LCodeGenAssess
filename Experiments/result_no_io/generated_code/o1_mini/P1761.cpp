#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int index;
    int size;
    double x;
    double y;
    double left;
    double right;
} Square;

int compare_size_desc(const void* a, const void* b) {
    Square* sa = (Square*)a;
    Square* sb = (Square*)b;
    if (sb->size != sa->size)
        return sb->size - sa->size;
    return sa->index - sb->index;
}

int main(){
    int n;
    while(scanf("%d", &n) && n != 0){
        Square squares[n];
        for(int i=0;i<n;i++){
            scanf("%d", &squares[i].size);
            squares[i].index = i+1;
        }
        qsort(squares, n, sizeof(Square), compare_size_desc);
        for(int i=0;i<n;i++){
            double half_diag = (squares[i].size * sqrt(2)) / 2.0;
            if(i == 0){
                squares[i].x = half_diag;
            }
            else{
                double x = half_diag;
                for(int j=0;j<i;j++){
                    double dist = (squares[j].size + squares[i].size) / sqrt(2.0);
                    double candidate_x = squares[j].x + dist;
                    if(candidate_x > x){
                        x = candidate_x;
                    }
                }
                squares[i].x = x;
            }
            squares[i].left = squares[i].x - half_diag;
            squares[i].right = squares[i].x + half_diag;
        }
        // Determine visibility
        int visible[n];
        for(int i=0;i<n;i++) visible[i] = 1;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(squares[j].left <= squares[i].left && squares[j].right >= squares[i].right){
                    visible[i] = 0;
                    break;
                }
            }
        }
        // Collect visible indices
        int vis_indices[n], cnt=0;
        for(int i=0;i<n;i++) {
            if(visible[i]) vis_indices[cnt++] = squares[i].index;
        }
        // Sort indices
        for(int i=0;i<cnt-1;i++) {
            for(int j=i+1;j<cnt;j++) {
                if(vis_indices[i] > vis_indices[j]){
                    int temp = vis_indices[i];
                    vis_indices[i] = vis_indices[j];
                    vis_indices[j] = temp;
                }
            }
        }
        // Print
        for(int i=0;i<cnt;i++) {
            if(i>0) printf(" ");
            printf("%d", vis_indices[i]);
        }
        printf("\n");
    }
}