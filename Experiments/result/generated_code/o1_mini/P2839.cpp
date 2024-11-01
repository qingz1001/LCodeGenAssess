#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define MAX_Q 25000
#define MAX_SUB 20000

typedef long long ll;

// Comparator for qsort
int cmp(const void* a, const void* b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

// Function to find median
int find_median(int* arr, int size){
    int mid = size / 2;
    // Create a copy
    int* copy = (int*)malloc(size * sizeof(int));
    for(int i=0;i<size;i++) copy[i] = arr[i];
    qsort(copy, size, sizeof(int), cmp);
    int median = copy[mid];
    free(copy);
    return median;
}

int main(){
    int n;
    scanf("%d", &n);
    int s[MAX_N];
    for(int i=0;i<n;i++) scanf("%d", &s[i]);
    int Q;
    scanf("%d", &Q);
    int queries[4];
    ll last = 0;
    for(int q=0; q<Q; q++){
        scanf("%d %d %d %d", &queries[0], &queries[1], &queries[2], &queries[3]);
        int a = (queries[0] + (int)last) % n;
        int b = (queries[1] + (int)last) % n;
        int c = (queries[2] + (int)last) % n;
        int d = (queries[3] + (int)last) % n;
        ll q_arr[4] = {a, b, c, d};
        // Sort q_arr
        for(int i=0;i<3;i++) {
            for(int j=i+1;j<4;j++) {
                if(q_arr[i] > q_arr[j]){
                    ll temp = q_arr[i];
                    q_arr[i] = q_arr[j];
                    q_arr[j] = temp;
                }
            }
        }
        a = q_arr[0];
        b = q_arr[1];
        c = q_arr[2];
        d = q_arr[3];
        int max_median = -1;
        for(int l = a; l <= b; l++){
            for(int r = c; r <= d && r >= l; r++){
                int len = r - l +1;
                int median = find_median(&s[l], len);
                if(median > max_median) max_median = median;
            }
        }
        printf("%d\n", max_median);
        last = max_median;
    }
    return 0;
}