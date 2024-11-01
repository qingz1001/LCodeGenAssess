#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 8
#define MAX_ASSIGNMENTS 100000
#define MAX_NUMBER 20

typedef long long ll;

int n;
int sectors[MAX_N];
int max_i = 0;
int assignments_count = 0;
int assignments_storage[MAX_ASSIGNMENTS][MAX_N];

int sums_present[200];

void compute_max_i(int current_sectors[]) {
    memset(sums_present, 0, sizeof(sums_present));
    for(int start = 0; start < n; start++) {
        int sum = 0;
        for(int len = 1; len <= n; len++) {
            int idx = (start + len -1) % n;
            sum += current_sectors[idx];
            if(sum < 200)
                sums_present[sum] = 1;
        }
    }
    int current_max = 0;
    while(sums_present[current_max +1]) current_max++;
    if(current_max > max_i) {
        max_i = current_max;
        assignments_count = 0;
    }
    if(current_max == max_i) {
        if(assignments_count < MAX_ASSIGNMENTS){
            for(int i=0;i<n;i++)
                assignments_storage[assignments_count][i] = current_sectors[i];
            assignments_count++;
        }
    }
}

void backtrack(int pos, int current_sectors[]) {
    if(pos == n) {
        compute_max_i(current_sectors);
        return;
    }
    for(int num=1; num<=MAX_NUMBER; num++) {
        current_sectors[pos] = num;
        backtrack(pos+1, current_sectors);
    }
}

int main(){
    scanf("%d", &n);
    if(n <1 || n >8){
        return 0;
    }
    int current_sectors[MAX_N];
    memset(current_sectors, 0, sizeof(current_sectors));
    current_sectors[0] = 1;
    backtrack(1, current_sectors);
    printf("%d\n", max_i);
    for(int i=0;i<assignments_count;i++) {
        for(int j=0;j<n;j++) {
            if(j>0) printf(" ");
            printf("%d", assignments_storage[i][j]);
        }
        printf("\n");
    }
    return 0;
}