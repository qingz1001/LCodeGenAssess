#include <stdio.h>
#include <math.h>

#define MAX 32768

int main(){
    int counts[MAX+1];
    for(int i=0;i<=MAX;i++) counts[i]=0;

    int a, b, c, d;
    for(a=1; a*a <= MAX; a++){
        int a2 = a*a;
        counts[a2]++;
        for(b=a; a2 + b*b <= MAX; b++){
            int b2 = b*b;
            counts[a2 + b2]++;
            for(c=b; a2 + b2 + c*c <= MAX; c++){
                int c2 = c*c;
                counts[a2 + b2 + c2]++;
                for(d=c; a2 + b2 + c2 + d*d <= MAX; d++){
                    counts[a2 + b2 + c2 + d*d]++;
                }
            }
        }
    }

    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        printf("%d\n", counts[n]);
    }
    return 0;
}