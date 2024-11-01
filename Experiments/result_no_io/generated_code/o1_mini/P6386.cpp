#include <stdio.h>

int main(){
    int a, b, c, d;
    int p, m, g;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d %d", &p, &m, &g);
    
    int times[3] = {p, m, g};
    for(int i=0;i<3;i++){
        int t = times[i];
        int state = 0;
        // Dog1
        if((t % (a + b)) < a){
            state++;
        }
        // Dog2
        if((t % (c + d)) < c){
            state++;
        }
        if(state ==0) printf("none\n");
        else if(state ==1) printf("one\n");
        else printf("both\n");
    }
}