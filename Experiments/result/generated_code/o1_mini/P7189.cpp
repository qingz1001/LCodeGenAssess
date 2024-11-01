#include <stdio.h>

int main(){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    int begin[3], end[3];
    for(int i=0;i<3;i++) scanf("%d %d", &begin[i], &end[i]);
    int total=0;
    for(int minute=1; minute<=100; minute++){
        int count=0;
        for(int i=0;i<3;i++) if(begin[i]<=minute && minute < end[i]) count++;
        if(count ==1) total +=a;
        else if(count ==2) total +=2*b;
        else if(count ==3) total +=3*c;
    }
    printf("%d\n", total);
}