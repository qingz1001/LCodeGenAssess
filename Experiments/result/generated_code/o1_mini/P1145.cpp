#include <stdio.h>
#include <stdbool.h>

int main(){
    int k;
    scanf("%d", &k);
    if(k <=0 || k >=14){
        return 0;
    }
    int n = 2*k;
    int m =1;
    while(1){
        bool alive[26] = {false};
        for(int i=0;i<n;i++) alive[i]=true;
        int remaining_bad =k;
        int current =0;
        bool valid=true;
        while(remaining_bad >0){
            int count =0;
            int pos = current;
            while(1){
                if(alive[pos]){
                    count++;
                    if(count ==m){
                        break;
                    }
                }
                pos = (pos+1)%n;
            }
            if(pos <k){
                valid=false;
                break;
            }
            alive[pos]=false;
            remaining_bad--;
            current = (pos+1)%n;
        }
        if(valid){
            printf("%d\n", m);
            break;
        }
        m++;
    }
    return 0;
}