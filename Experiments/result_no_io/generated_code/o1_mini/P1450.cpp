#include <stdio.h>

int main(){
    int c[4], n;
    scanf("%d %d %d %d %d", &c[0], &c[1], &c[2], &c[3], &n);
    while(n--){
        int d[4], s;
        scanf("%d %d %d %d %d", &d[0], &d[1], &d[2], &d[3], &s);
        long long count = 0;
        for(int x0=0; x0<=d[0] && x0 * c[0] <= s; x0++){
            int rem1 = s - x0 * c[0];
            for(int x1=0; x1<=d[1] && x1 * c[1] <= rem1; x1++){
                int rem2 = rem1 - x1 * c[1];
                for(int x2=0; x2<=d[2] && x2 * c[2] <= rem2; x2++){
                    int rem3 = rem2 - x2 * c[2];
                    if(rem3 % c[3] == 0){
                        int x3 = rem3 / c[3];
                        if(x3 <= d[3]){
                            count++;
                        }
                    }
                }
            }
        }
        printf("%lld\n", count);
    }
    return 0;
}