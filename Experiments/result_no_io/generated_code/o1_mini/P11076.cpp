#include <stdio.h>
#include <string.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        long long n, x, y;
        scanf("%lld %lld %lld", &n, &x, &y);
        char s[200005];
        scanf("%s", s);
        long long f =0, s_count =0;
        for(int i=0;i<n;i++){
            if(s[i]=='F') f++;
            else s_count++;
        }
        long long x_p = x - f;
        long long y_p = y - s_count;
        if(y_p <=0){
            printf("-1\n");
        }
        else{
            long long M = (x_p + y_p -1)/y_p;
            printf("%lld\n", M);
        }
    }
    return 0;
}