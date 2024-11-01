#include <stdio.h>

#define MAX 100005

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    double H[MAX];
    H[0]=0.0;
    for(int i=1;i<=100000;i++) {
        H[i] = H[i-1] + 1.0/i;
    }
    double sum;
    if(k == 1){
        sum = 1.0;
    }
    else{
        double part1 = (double)(n - k +1) / n;
        double part2 = (k-1 >=0) ? H[k-1] : 0.0;
        sum = part1 + part2;
    }
    printf("%.9lf\n", sum);
    return 0;
}