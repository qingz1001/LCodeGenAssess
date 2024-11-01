#include <stdio.h>

#define MAX 1000002

long long diff[MAX];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if(x < y){
            diff[x] += z;
            diff[y] -= z;
        }
        else{
            diff[x] += z;
            diff[n+1] -= z;
            diff[1] += z;
            diff[y] -= z;
        }
    }
    long long current = 0, max_people = 0;
    for(int i=1;i<=n;i++){
        current += diff[i];
        if(current > max_people){
            max_people = current;
        }
    }
    long long carriages = (max_people + 35) / 36;
    printf("%lld\n", carriages);
    return 0;
}