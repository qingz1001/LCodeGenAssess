#include <stdio.h>
#include <string.h>

#define MAX 100005

long long BIT_l[MAX];
long long BIT_r_arr[MAX];
int n;

void update(long long BIT[], int index) {
    while (index <= n) {
        BIT[index] += 1;
        index += index & (-index);
    }
}

long long query(long long BIT[], int index){
    long long res = 0;
    while (index > 0){
        res += BIT[index];
        index -= index & (-index);
    }
    return res;
}

int main(){
    int m;
    scanf("%d %d", &n, &m);
    int q, l, r;
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &q, &l, &r);
        if(q == 1){
            update(BIT_l, l);
            update(BIT_r_arr, r);
        }
        else{
            long long res = query(BIT_l, r) - query(BIT_r_arr, l-1);
            printf("%lld\n", res);
        }
    }
    return 0;
}