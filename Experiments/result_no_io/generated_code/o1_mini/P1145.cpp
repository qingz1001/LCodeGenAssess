#include<stdio.h>
#include<stdlib.h>

int main(){
    int k;
    scanf("%d", &k);
    int n = 2*k;
    int m=1;
    while(1){
        int alive[26];
        for(int i=0;i<n;i++) alive[i]=1;
        int count =0;
        int pos=0;
        int bad_killed=0;
        int first_good_killed = -1;
        while(1){
            int step =0;
            while(step < m){
                if(alive[pos]){
                    step++;
                    if(step == m){
                        break;
                    }
                }
                pos = (pos +1) % n;
            }
            if(alive[pos]){
                if(pos < k){
                    if(first_good_killed == -1){
                        first_good_killed = bad_killed;
                    }
                }
                else{
                    bad_killed++;
                }
                alive[pos]=0;
                if(bad_killed == k){
                    if(first_good_killed == -1){
                        // All bads killed and first good not yet killed
                        break;
                    }
                    else{
                        break;
                    }
                }
            }
            pos = (pos +1) % n;
        }
        if(bad_killed == k){
            printf("%d\n", m);
            return 0;
        }
        m++;
    }
}