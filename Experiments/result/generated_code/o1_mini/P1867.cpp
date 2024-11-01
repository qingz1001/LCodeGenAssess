#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    double health = 10.0;
    int experience = 0;
    for(int i=0;i<n;i++){
        double x;
        int a;
        scanf("%lf %d", &x, &a);
        health -= x;
        if(x < 0 && health > 10.0){
            health = 10.0;
        }
        if(health <= 0.0){
            break;
        }
        experience += a;
    }
    int level =0;
    int exp = experience;
    while(exp >= (1 << level)){
        exp -= (1 << level);
        level++;
    }
    printf("%d %d\n", level, exp);
    return 0;
}