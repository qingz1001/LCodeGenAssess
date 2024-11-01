#include <stdio.h>

int main(){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    int time[101] = {0};
    for(int i=0;i<3;i++){
        int begin, end;
        scanf("%d %d", &begin, &end);
        for(int m=begin; m < end; m++) time[m]++;
    }
    long long total = 0;
    for(int m=1; m<=100; m++){
        if(time[m] ==1) total += a;
        else if(time[m]==2) total += 2*b;
        else if(time[m]==3) total += 3*c;
    }
    printf("%lld", total);
}