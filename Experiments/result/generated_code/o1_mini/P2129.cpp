#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    char type;
    ll p;
    ll q;
} Command;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    ll *x = malloc(sizeof(ll)*n);
    ll *y = malloc(sizeof(ll)*n);
    for(int i=0;i<n;i++) scanf("%lld %lld", &x[i], &y[i]);
    Command *cmd = malloc(sizeof(Command)*m);
    char buffer[2];
    for(int i=0;i<m;i++){
        scanf("%s", buffer);
        cmd[i].type = buffer[0];
        if(buffer[0]=='m'){
            scanf("%lld %lld", &cmd[i].p, &cmd[i].q);
        }
    }
    // Initialize transformation
    ll a=1, b=0, d=0, e=1, c=0, f=0;
    for(int i=m-1;i>=0;i--){
        if(cmd[i].type == 'm'){
            ll p = cmd[i].p, q = cmd[i].q;
            // M' is identity, T'=(p,q)
            // New M = M
            // New T = T + (p, q)
            c += p;
            f += q;
        }
        else{
            ll a_p, b_p, d_p, e_p, c_p, f_p;
            if(cmd[i].type == 'x'){
                a_p = -1; b_p = 0;
                d_p = 0; e_p = 1;
                c_p = 0; f_p = 0;
            }
            else{ // 'y'
                a_p =1; b_p =0;
                d_p =0; e_p = -1;
                c_p =0; f_p =0;
            }
            ll new_a = a_p * a + b_p * d;
            ll new_b = a_p * b + b_p * e;
            ll new_d = d_p * a + e_p * d;
            ll new_e = d_p * b + e_p * e;
            ll new_c = a_p * c + b_p * f + c_p;
            ll new_f = d_p * c + e_p * f + f_p;
            a = new_a;
            b = new_b;
            d = new_d;
            e = new_e;
            c = new_c;
            f = new_f;
        }
    }
    for(int i=0;i<n;i++) {
        ll res_x = a * x[i] + b * y[i] + c;
        ll res_y = d * x[i] + e * y[i] + f;
        printf("%lld %lld\n", res_x, res_y);
    }
    free(x);
    free(y);
    free(cmd);
    return 0;
}