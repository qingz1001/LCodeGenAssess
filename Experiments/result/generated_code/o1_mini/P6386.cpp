#include <stdio.h>

int main(){
    int a, b, c, d;
    int p, m, g;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d %d", &p, &m, &g);
    
    int times[3] = {p, m, g};
    char *outputs[3];
    
    for(int i=0;i<3;i++){
        int t = times[i];
        int count=0;
        // Dog1
        if(((t-1) % (a+b)) < a){
            count++;
        }
        // Dog2
        if(((t-1) % (c+d)) < c){
            count++;
        }
        if(count ==0){
            printf("none\n");
        }
        else if(count ==1){
            printf("one\n");
        }
        else{
            printf("both\n");
        }
    }
    return 0;
}