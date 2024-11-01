#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int events[10010] = {0};
    for(int i=0;i<m;i++){
        int s;
        scanf("%d", &s);
        int first, last, station;
        scanf("%d", &first);
        last = first;
        for(int j=1;j<s;j++){
            scanf("%d", &station);
            last = station;
        }
        events[first] +=1;
        if(last+1 <= n+1){
            events[last+1] -=1;
        }
    }
    int sum=0, max=0;
    for(int i=1;i<=n;i++){
        sum += events[i];
        if(sum > max){
            max = sum;
        }
    }
    printf("%d", max);
    return 0;
}