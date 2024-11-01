#include <stdio.h>
#include <string.h>

int main(){
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);
    if(n ==1){
        if(x ==1 && m ==a){
            printf("%d", a);
        }
        else{
            printf("0");
        }
        return 0;
    }
    int a2;
    int found =0;
    int a_seq[21];
    for(a2=0; a2<=m && !found; a2++){
        a_seq[1] =a;
        a_seq[2] =a2;
        int passengers =a;
        for(int k=2; k<=n-1; k++){
            int bk = a_seq[k-1];
            if(k >=3){
                a_seq[k] =a_seq[k-1] + a_seq[k-2];
            }
            passengers = passengers - bk + a_seq[k];
            if(passengers <0){
                break;
            }
        }
        if(passengers ==m){
            found =1;
            break;
        }
    }
    if(!found){
        printf("0");
        return 0;
    }
    // Now, a2 is found as current a2
    // Build the sequence again
    a_seq[1] =a;
    a_seq[2] =a2;
    int passengers =a;
    int passengers_x =0;
    for(int k=2; k<=n-1; k++){
        int bk = a_seq[k-1];
        if(k >=3){
            a_seq[k] =a_seq[k-1] + a_seq[k-2];
        }
        passengers = passengers - bk + a_seq[k];
        if(k ==x){
            passengers_x =passengers;
        }
    }
    if(x ==n){
        passengers_x =m;
    }
    if(x ==1){
        passengers_x =a;
    }
    printf("%d", passengers_x);
    return 0;
}