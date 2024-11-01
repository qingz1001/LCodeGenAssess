#include <stdio.h>

typedef long long ll;

ll anti_primes[] = {
    1LL, 2LL, 4LL, 6LL, 12LL, 24LL, 36LL, 48LL, 60LL, 120LL, 180LL, 240LL,
    360LL, 720LL, 840LL, 1260LL, 1680LL, 2520LL, 5040LL, 7560LL, 10080LL,
    15120LL, 20160LL, 25200LL, 27720LL, 45360LL, 50400LL, 55440LL, 83160LL,
    110880LL, 166320LL, 221760LL, 277200LL, 332640LL, 498960LL, 554400LL,
    665280LL, 720720LL, 1081080LL, 1441440LL, 2162160LL, 2882880LL, 3603600LL,
    4324320LL, 6486480LL, 7207200LL, 8648640LL, 10810800LL, 14414400LL,
    17297280LL, 21621600LL, 32432400LL, 36756720LL, 43243200LL, 61261200LL,
    73513440LL, 110270160LL, 122522400LL, 147026880LL, 183783600LL, 245044800LL,
    294053760LL, 367567200LL, 551350800LL, 698377680LL, 735134400LL, 1102701600LL,
    1396755360LL, 2095133040LL, 2205403200LL, 2793510720LL, 4190266080LL
};

int main(){
    ll N;
    scanf("%lld", &N);
    int size = sizeof(anti_primes)/sizeof(anti_primes[0]);
    ll res = 1;
    for(int i=0;i<size;i++){
        if(anti_primes[i] <= N){
            res = anti_primes[i];
        }
        else{
            break;
        }
    }
    printf("%lld\n", res);
    return 0;
}