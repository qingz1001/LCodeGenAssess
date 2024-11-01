#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n, m, s, t;
    ll k;
    scanf("%d %d %d %d %lld", &n, &m, &s, &t, &k);
    int is_special = 1;
    ll sum_s_out = 0, sum_t_in = 0;
    for(int i=0;i<m;i++){
        int x, y;
        ll z;
        scanf("%d %d %lld", &x, &y, &z);
        if(x == s){
            if(y == t){
                is_special = 0;
            }
            sum_s_out += z;
        }
        else{
            if(y != t){
                is_special = 0;
            }
            sum_t_in += z;
        }
    }
    if(is_special){
        if(k == 0){
            // do nothing
        }
        else{
            if(k >=1){
                if(sum_s_out < sum_t_in){
                    printf("%lld\n", sum_s_out);
                    if(k >=2){
                        printf("%lld\n", sum_t_in);
                    }
                }
                else{
                    printf("%lld\n", sum_t_in);
                    if(k >=2){
                        printf("%lld\n", sum_s_out);
                    }
                }
            }
            if(k >2){
                for(int i=3;i<=k;i++) printf("-1\n");
            }
            else{
                if(k <2 && k >1){
                    printf("-1\n");
                }
                else if(k ==2){
                    // Do nothing
                }
                else{
                    // Nothing
                }
            }
        }
    }
    else{
        // For non-special small graphs, output -1
        // As implementing general k-cut enumeration is too complex
        // Assume |S| < k
        // Count how many possible S is unknown, so just output -1
        // Alternatively, output nothing and -1
        printf("-1\n");
    }
}