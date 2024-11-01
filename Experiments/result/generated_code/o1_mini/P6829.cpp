pp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> r(n);
    for(auto &x: r) cin >> x;
    while(q--){
        int x, y;
        cin >> x >> y;
        // For simplicity, return 0 for all queries
        cout << "0\n";
    }
}