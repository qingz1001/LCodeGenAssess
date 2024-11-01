#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Cow;

int cmp_int(const void* a, const void* b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    if(ia < ib) return -1;
    if(ia > ib) return 1;
    return 0;
}

int cmp_cow_x(const void* a, const void* b){
    Cow ca = *(Cow*)a;
    Cow cb = *(Cow*)b;
    if(ca.x != cb.x) return ca.x - cb.x;
    return ca.y - cb.y;
}

int cmp_cow_y(const void* a, const void* b){
    Cow ca = *(Cow*)a;
    Cow cb = *(Cow*)b;
    if(ca.y != cb.y) return ca.y - cb.y;
    return ca.x - cb.x;
}

int binary_search(int* arr, int size, int val){
    int left = 0, right = size;
    while(left < right){
        int mid = left + (right - left)/2;
        if(arr[mid] >= val){
            right = mid;
        }
        else{
            left = mid +1;
        }
    }
    return left;
}

int main(){
    int N;
    scanf("%d", &N);
    Cow cows[N];
    int a_list[1000];
    int b_list[1000];
    for(int i=0;i<N;i++){
        scanf("%d %d", &cows[i].x, &cows[i].y);
        a_list[i] = cows[i].x +1;
        b_list[i] = cows[i].y +1;
    }
    // Sort and remove duplicates for a
    qsort(a_list, N, sizeof(int), cmp_int);
    int na=0;
    for(int i=0;i<N;i++){
        if(i==0 || a_list[i]!=a_list[i-1]){
            a_list[na++] = a_list[i];
        }
    }
    // Sort and remove duplicates for b
    qsort(b_list, N, sizeof(int), cmp_int);
    int nb=0;
    for(int i=0;i<N;i++){
        if(i==0 || b_list[i]!=b_list[i-1]){
            b_list[nb++] = b_list[i];
        }
    }
    // Initialize grid
    int grid[na+1][nb+1];
    for(int i=0;i<=na;i++) {
        for(int j=0;j<=nb;j++) {
            grid[i][j] = 0;
        }
    }
    // Populate grid
    for(int i=0;i<N;i++){
        int a_idx = binary_search(a_list, na, cows[i].x +1);
        int b_idx = binary_search(b_list, nb, cows[i].y +1);
        if(a_idx < na && b_idx < nb){
            grid[a_idx][b_idx] +=1;
        }
    }
    // Compute prefix sums
    int pref[na+1][nb+1];
    for(int i=0;i<=na;i++){
        for(int j=0;j<=nb;j++){
            if(i ==0 || j==0){
                pref[i][j] = 0;
            }
            else{
                pref[i][j] = grid[i][j] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
            }
        }
    }
    int total = pref[na][nb];
    int min_M = N;
    for(int i=0;i<na;i++){
        for(int j=0;j<nb;j++){
            int q3 = pref[i][j];
            int q2 = pref[i][nb] - q3;
            int q4 = pref[na][j] - q3;
            int q1 = total - q3 - q2 - q4;
            int M = q1;
            if(q2 > M) M = q2;
            if(q3 > M) M = q3;
            if(q4 > M) M = q4;
            if(M < min_M){
                min_M = M;
            }
        }
    }
    printf("%d\n", min_M);
    return 0;
}