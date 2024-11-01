#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000002

long long diff_arr[MAX_N];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if(y > x){
            diff_arr[x] += z;
            diff_arr[y] -= z;
        }
        else{
            diff_arr[x] += z;
            diff_arr[n+1] -= z;
            diff_arr[1] += z;
            diff_arr[y] -= z;
        }
    }
    long long current = 0;
    long long max_passengers = 0;
    for(int i=1;i<=n;i++){
        current += diff_arr[i];
        if(current > max_passengers){
            max_passengers = current;
        }
    }
    long long carriages = (max_passengers + 35) / 36;
    printf("%lld\n", carriages);
    return 0;
}