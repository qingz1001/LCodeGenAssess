pp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> parent;
vector<int> sz;
vector< vector<int> > sorted_p;
vector<int> p;
vector<int> inv_p;

int find_set_func(int x){
    if(parent[x] != x){
        parent[x] = find_set_func(parent[x]);
    }
    return parent[x];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    p.resize(n+1);
    inv_p.resize(n+1);
    for(int i=1;i<=n;i++){
        cin >> p[i];
        inv_p[p[i]] = i;
    }
    parent.resize(n+1);
    sz.resize(n+1, 1);
    sorted_p.resize(n+1);
    for(int i=1;i<=n;i++) sorted_p[i].push_back(p[i]);
    for(int i=1;i<=n;i++) parent[i] = i;
    for(int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        int fx = find_set_func(u);
        int fy = find_set_func(v);
        if(fx == fy) continue;
        if(sz[fx] < sz[fy]){
            swap(fx, fy);
        }
        vector<int> tmp;
        tmp.reserve(sz[fx] + sz[fy]);
        merge(sorted_p[fx].begin(), sorted_p[fx].end(),
              sorted_p[fy].begin(), sorted_p[fy].end(),
              back_inserter(tmp));
        sorted_p[fx] = move(tmp);
        sz[fx] += sz[fy];
        parent[fy] = fx;
    }
    int q;
    cin >> q;
    while(q--){
        char op;
        int x, y;
        cin >> op >> x >> y;
        if(op == 'B'){
            int fx = find_set_func(x);
            int fy = find_set_func(y);
            if(fx == fy) continue;
            if(sz[fx] < sz[fy]){
                swap(fx, fy);
            }
            vector<int> tmp;
            tmp.reserve(sz[fx] + sz[fy]);
            merge(sorted_p[fx].begin(), sorted_p[fx].end(),
                  sorted_p[fy].begin(), sorted_p[fy].end(),
                  back_inserter(tmp));
            sorted_p[fx] = move(tmp);
            sz[fx] += sz[fy];
            parent[fy] = fx;
        }
        else if(op == 'Q'){
            int fx = find_set_func(x);
            if(sorted_p[fx].size() >= y){
                int p_k = sorted_p[fx][y-1];
                int node = inv_p[p_k];
                cout << node << "\n";
            }
            else{
                cout << "-1\n";
            }
        }
    }
}