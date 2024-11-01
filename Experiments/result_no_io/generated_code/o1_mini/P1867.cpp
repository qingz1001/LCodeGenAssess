#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int x, a;
    int life = 10;
    long long total_exp = 0;
    for(int i=0;i<n;i++){
        scanf("%d %d", &x, &a);
        if(x >0){
            life -= x;
        }
        else{
            life -= x;
            if(life >10) life=10;
        }
        if(life <=0){
            break;
        }
        total_exp += a;
    }
    int level=0;
    long long sum=0;
    while(sum + (1LL<<level) <= total_exp){
        sum += (1LL<<level);
        level++;
    }
    long long rem = total_exp - sum;
    printf("%d %lld\n", level, rem);
    return 0;
}