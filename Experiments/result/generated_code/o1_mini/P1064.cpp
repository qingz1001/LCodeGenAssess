#include <stdio.h>
#include <string.h>

#define MAX_N 32000
#define MAX_M 60

int main_v[MAX_M+1];
int main_p[MAX_M+1];
int att_v[MAX_M+1][2];
int att_p[MAX_M+1][2];
int att_num[MAX_M+1];
int dp_array[MAX_N+1];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    memset(main_v, 0, sizeof(main_v));
    memset(att_num, 0, sizeof(att_num));
    for(int i=1; i<=m; i++){
        int v, p, q;
        scanf("%d %d %d", &v, &p, &q);
        if(q ==0){
            main_v[i] = v;
            main_p[i] = p;
        }
        else{
            int main_idx = q;
            att_v[main_idx][att_num[main_idx]] = v;
            att_p[main_idx][att_num[main_idx]] = p;
            att_num[main_idx]++;
        }
    }
    memset(dp_array, 0, sizeof(dp_array));
    for(int i=1; i<=m; i++){
        if(main_v[i] ==0) continue;
        int option_count=1;
        int opt_cost[4];
        int opt_value[4];
        opt_cost[0] = main_v[i];
        opt_value[0] = main_v[i] * main_p[i];
        if(att_num[i] >=1){
            opt_cost[option_count] = main_v[i] + att_v[i][0];
            opt_value[option_count] = main_v[i]*main_p[i] + att_v[i][0]*att_p[i][0];
            option_count++;
        }
        if(att_num[i] >=2){
            opt_cost[option_count] = main_v[i] + att_v[i][1];
            opt_value[option_count] = main_v[i]*main_p[i] + att_v[i][1]*att_p[i][1];
            option_count++;
            opt_cost[option_count] = main_v[i] + att_v[i][0] + att_v[i][1];
            opt_value[option_count] = main_v[i]*main_p[i] + att_v[i][0]*att_p[i][0] + att_v[i][1]*att_p[i][1];
            option_count++;
        }
        for(int j=n; j>=0; j--){
            for(int k=0; k<option_count; k++){
                if(j >= opt_cost[k]){
                    if(dp_array[j] < dp_array[j - opt_cost[k]] + opt_value[k]){
                        dp_array[j] = dp_array[j - opt_cost[k]] + opt_value[k];
                    }
                }
            }
        }
    }
    int max =0;
    for(int j=0; j<=n; j++) if(dp_array[j] > max) max= dp_array[j];
    printf("%d\n", max);
    return 0;
}