#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

typedef struct {
    int prime;
    int power;
} PrimePower;

// Function to compute a^b mod mod
ll power_mod(ll a, ll b, ll mod){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>=1;
    }
    return res;
}

// Extended GCD to find inverse
ll extended_gcd_func(ll a, ll b, ll* x, ll* y){
    if(b ==0){
        *x =1;
        *y =0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd_func(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

// Function to find inverse of a mod m
ll mod_inverse(ll a, ll m){
    ll x, y;
    ll g = extended_gcd_func(a, m, &x, &y);
    if(g !=1){
        return -1;
    }
    else{
        ll res = x % m;
        if(res <0) res +=m;
        return res;
    }
}

// Function to factorize P
int factorize(ll P, PrimePower* factors){
    int cnt =0;
    for(int p=2; p*p <=P; p++){
        if(P % p ==0){
            int c=0;
            while(P % p ==0){
                c++;
                P /=p;
            }
            factors[cnt].prime =p;
            factors[cnt].power =c;
            cnt++;
        }
    }
    if(P >1){
        factors[cnt].prime =P;
        factors[cnt].power =1;
        cnt++;
    }
    return cnt;
}

// Function to compute v_p(x!)
ll count_vp(ll x, int p){
    ll res =0;
    ll div =p;
    while(div <=x){
        res += x / div;
        div *=p;
    }
    return res;
}

// Function to compute factmod(n, p, c, pc)
ll factmod(ll n, int p, int c, ll pc){
    if(n ==0)
        return 1;
    ll res = factmod(n / p, p, c, pc);
    // Compute res = res^1 mod pc
    res = res % pc;
    // Multiply by product from 1 to n%p
    for(int i=1;i<=n%p;i++){
        if(i % p !=0){
            res = res * i % pc;
        }
    }
    // If res is zero, keep it zero
    return res;
}

// Function to combine two congruences x ≡ a1 mod m1 and x ≡ a2 mod m2
// Returns -1 if no solution, else the solution modulo lcm(m1, m2)
ll crt_pair(ll a1, ll m1, ll a2, ll m2){
    ll x, y;
    ll g = extended_gcd_func(m1, m2, &x, &y);
    if((a2 - a1) % g !=0){
        return -1;
    }
    ll lcm = m1 / g * m2;
    ll tmp = (a2 - a1) / g;
    ll add = x * tmp % (m2 / g);
    if(add <0) add += (m2 / g);
    ll res = a1 + add * m1;
    res %= lcm;
    if(res <0) res += lcm;
    return res;
}

int main(){
    ll P;
    scanf("%lld", &P);
    PrimePower factors[20];
    int nf = factorize(P, factors);
    ll n, m;
    scanf("%lld %lld", &n, &m);
    int w[5];
    ll W=0;
    for(int i=0;i<m;i++){
        scanf("%d", &w[i]);
        W +=w[i];
    }
    if(W >n){
        printf("Impossible\n");
        return 0;
    }
    // To store the remainders and moduli
    ll rem[20];
    ll moduli[20];
    for(int i=0;i<nf;i++){
        int p = factors[i].prime;
        int c = factors[i].power;
        ll pc =1;
        for(int j=0;j<c;j++) pc *=p;
        moduli[i] = pc;
        // Compute v_p
        ll vp_num = count_vp(n, p) - count_vp(n - W, p);
        ll vp_den =0;
        for(int j=0;j<m;j++) vp_den += count_vp(w[j], p);
        ll vp = vp_num - vp_den;
        if(vp >=c){
            rem[i] =0;
            continue;
        }
        // Compute factmod(n, p, c, pc)
        ll fn = factmod(n, p, c, pc);
        // Compute factmod(n-W, p, c, pc)
        ll fnw = factmod(n - W, p, c, pc);
        // Inverse of fnw
        ll inv_fnw = mod_inverse(fnw, pc);
        if(inv_fnw == -1){
            rem[i] =0;
            continue;
        }
        ll C = fn * inv_fnw % pc;
        // For each wi, multiply by inverse of factmod(wi, p, c, pc)
        int impossible_flag =0;
        for(int j=0;j<m;j++){
            ll fi = factmod(w[j], p, c, pc);
            ll inv_fi = mod_inverse(fi, pc);
            if(inv_fi == -1){
                impossible_flag =1;
                break;
            }
            C = C * inv_fi % pc;
        }
        if(impossible_flag){
            rem[i]=0;
            continue;
        }
        // Multiply by p^vp
        if(vp >0){
            ll pvp =1;
            for(int j=0;j<vp;j++) pvp = pvp * p % pc;
            C = C * pvp % pc;
        }
        rem[i] = C;
    }
    // Combine all remainders using CRT
    ll ans =0;
    ll M =1;
    for(int i=0;i<nf;i++) M *= moduli[i];
    for(int i=0;i<nf;i++){
        ll ai = rem[i];
        ll mi = moduli[i];
        ll Mi = M / mi;
        ll inv_Mi = mod_inverse(Mi, mi);
        if(inv_Mi == -1){
            printf("Impossible\n");
            return 0;
        }
        ans = (ans + ai * Mi % P * inv_Mi % P) % P;
    }
    printf("%lld\n", ans);
}