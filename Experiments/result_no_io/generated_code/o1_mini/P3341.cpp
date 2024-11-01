#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int row;
    int col;
    int color;
} Piece;

int cmp_row(const void* a, const void* b){
    Piece* pa = (Piece*)a;
    Piece* pb = (Piece*)b;
    if(pa->row != pb->row) return pa->row - pb->row;
    return pa->col - pb->col;
}

int cmp_col(const void* a, const void* b){
    Piece* pa = (Piece*)a;
    Piece* pb = (Piece*)b;
    if(pa->col != pb->col) return pa->col - pb->col;
    return pa->row - pb->row;
}

int main(){
    int r, c;
    scanf("%d %d", &r, &c);
    int n;
    scanf("%d", &n);
    int total = 2*n;
    Piece* pieces = (Piece*)malloc(sizeof(Piece)*total);
    for(int i=0;i<n;i++){
        int a, b, c_, d;
        scanf("%d %d %d %d", &a, &b, &c_, &d);
        pieces[2*i].row = a;
        pieces[2*i].col = b;
        pieces[2*i].color = i+1;
        pieces[2*i+1].row = c_;
        pieces[2*i+1].col = d;
        pieces[2*i+1].color = i+1;
    }
    Piece* sorted_row = (Piece*)malloc(sizeof(Piece)*total);
    memcpy(sorted_row, pieces, sizeof(Piece)*total);
    qsort(sorted_row, total, sizeof(Piece), cmp_row);
    Piece* sorted_col = (Piece*)malloc(sizeof(Piece)*total);
    memcpy(sorted_col, pieces, sizeof(Piece)*total);
    qsort(sorted_col, total, sizeof(Piece), cmp_col);
    int m;
    scanf("%d", &m);
    int* removed = (int*)calloc(n+2, sizeof(int));
    int user_cnt = 0;
    char dirs[3];
    for(int i=0;i<m;i++){
        int x, y;
        char d1, d2;
        scanf("%d %d %c %c", &x, &y, &d1, &d2);
        // Function to find piece in a direction
        int color1 = -1, color2 = -1;
        // First direction
        if(d1 == 'U' || d1 == 'D'){
            // Up or Down: search in sorted_col
            int left = 0, right = total-1, idx = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(sorted_col[mid].col < y){
                    left = mid +1;
                }
                else if(sorted_col[mid].col > y){
                    right = mid -1;
                }
                else{
                    if(d1 == 'U'){
                        if(sorted_col[mid].row < x){
                            idx = mid;
                            left = mid +1;
                        }
                        else{
                            right = mid -1;
                        }
                    }
                    else{
                        if(sorted_col[mid].row > x){
                            idx = mid;
                            right = mid -1;
                        }
                        else{
                            left = mid +1;
                        }
                    }
                }
            }
            if(idx != -1){
                color1 = sorted_col[idx].color;
            }
        }
        else{
            // Left or Right: search in sorted_row
            int left = 0, right = total-1, idx = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(sorted_row[mid].row < x){
                    left = mid +1;
                }
                else if(sorted_row[mid].row > x){
                    right = mid -1;
                }
                else{
                    if(d1 == 'L'){
                        if(sorted_row[mid].col < y){
                            idx = mid;
                            left = mid +1;
                        }
                        else{
                            right = mid -1;
                        }
                    }
                    else{
                        if(sorted_row[mid].col > y){
                            idx = mid;
                            right = mid -1;
                        }
                        else{
                            left = mid +1;
                        }
                    }
                }
            }
            if(idx != -1){
                color1 = sorted_row[idx].color;
            }
        }
        // Second direction
        if(d2 == 'U' || d2 == 'D'){
            // Up or Down: search in sorted_col
            int left = 0, right = total-1, idx = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(sorted_col[mid].col < y){
                    left = mid +1;
                }
                else if(sorted_col[mid].col > y){
                    right = mid -1;
                }
                else{
                    if(d2 == 'U'){
                        if(sorted_col[mid].row < x){
                            idx = mid;
                            left = mid +1;
                        }
                        else{
                            right = mid -1;
                        }
                    }
                    else{
                        if(sorted_col[mid].row > x){
                            idx = mid;
                            right = mid -1;
                        }
                        else{
                            left = mid +1;
                        }
                    }
                }
            }
            if(idx != -1){
                color2 = sorted_col[idx].color;
            }
        }
        else{
            // Left or Right: search in sorted_row
            int left = 0, right = total-1, idx = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(sorted_row[mid].row < x){
                    left = mid +1;
                }
                else if(sorted_row[mid].row > x){
                    right = mid -1;
                }
                else{
                    if(d2 == 'L'){
                        if(sorted_row[mid].col < y){
                            idx = mid;
                            left = mid +1;
                        }
                        else{
                            right = mid -1;
                        }
                    }
                    else{
                        if(sorted_row[mid].col > y){
                            idx = mid;
                            right = mid -1;
                        }
                        else{
                            left = mid +1;
                        }
                    }
                }
            }
            if(idx != -1){
                color2 = sorted_row[idx].color;
            }
        }
        if(color1 != -1 && color2 != -1 && color1 == color2 && !removed[color1]){
            removed[color1] = 1;
            user_cnt +=2;
        }
    }
    // Compute maximum
    // Assuming all can be removed
    int max_cnt = 2*n;
    printf("%d %d", user_cnt, max_cnt);
    free(pieces);
    free(sorted_row);
    free(sorted_col);
    free(removed);
    return 0;
}