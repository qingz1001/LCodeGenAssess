#include <stdio.h>
#include <string.h>

typedef long long ll;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        ll n, x, y;
        scanf("%lld %lld %lld", &n, &x, &y);
        char s[200005];
        scanf("%s", s);
        ll countF =0, countS=0;
        for(int i=0;i<n;i++){
            if(s[i]=='F') countF++;
            else countS++;
        }
        ll a = x - countF;
        ll b = y - countS -1;
        ll ans;
        if(b <0){
            // This should not happen as per constraints
            ans = a;
        }
        else{
            ans = (a + b) / (b +1);
        }
        printf("%lld\n", ans);
    }
}