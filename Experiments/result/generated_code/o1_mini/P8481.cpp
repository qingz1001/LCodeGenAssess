#include <stdio.h>
#include <stdlib.h>

int n;
int num[1048576]; // 2^20
int x_query;

int min_steps(int l, int r, int x) {
    if (l == r) return 0;
    // w = 0
    int mid0 = (l + r) / 2;
    int new_l0, new_r0;
    if (num[mid0] < x) {
        new_l0 = mid0 + 1;
        new_r0 = r;
    }
    else {
        new_l0 = l;
        new_r0 = mid0;
    }
    int steps0 = 1 + min_steps(new_l0, new_r0, x);
    // w = 1
    int mid1 = (l + r + 1) / 2;
    int new_l1, new_r1;
    if ((num[mid1] - 1) < x) {
        new_l1 = mid1;
        new_r1 = r;
    }
    else {
        new_l1 = l;
        new_r1 = mid1 - 1;
    }
    int steps1 = 1 + min_steps(new_l1, new_r1, x);
    return steps0 < steps1 ? steps0 : steps1;
}

int main(){
    int q;
    scanf("%d", &n);
    for(int i=0;i<n;i++) scanf("%d", &num[i]);
    scanf("%d", &q);
    while(q--){
        scanf("%d", &x_query);
        printf("%d\n", min_steps(0, n-1, x_query));
    }
    return 0;
}