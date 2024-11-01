#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1005;
const int MAXM = 5005;
const double EPS = 1e-7;

struct Edge {
    int from, to;
    double w;
} edges[MAXM];

int n, m;
double F[MAXN];
vector<vector<int>> adj(MAXN);

bool has_cycle(double C){
    // Transform the graph
    vector<vector<double>> graph(n + 1, vector<double>());
    for(int i=0;i<m;i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        double w = F[v] - C * edges[i].w;
        graph[u].push_back(w);
    }
    // Bellman-Ford to detect positive cycle
    vector<double> dist(n+1, 0.0);
    for(int i=0;i<n;i++){
        bool updated = false;
        for(int u=1; u<=n; u++) {
            for(auto val: graph[u]){
                int v = -1;
                // Find the corresponding edge
                for(int j=0; j<m; j++) if(edges[j].from == u){
                    v = edges[j].to;
                    break;
                }
                if(v != -1 && dist[v] < dist[u] + val){
                    dist[v] = dist[u] + val;
                    updated = true;
                }
            }
        }
        if(!updated) break;
        if(i == n-1 && updated) return true;
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>F[i];
    for(int i=0;i<m;i++) {
        cin>>edges[i].from>>edges[i].to>>edges[i].w;
    }
    double left=0.0, right=1000.0, ans=0.0;
    for(int i=0;i<100;i++){
        double mid=(left+right)/2.0;
        if(has_cycle(mid)){
            ans=mid;
            left=mid;
        }
        else{
            right=mid;
        }
    }
    // Check if any cycle exists
    bool exists=false;
    for(int i=0;i<m;i++) {
        // Simple cycle of two nodes
        for(int j=0;j<m;j++) if(edges[j].from == edges[i].to && edges[j].to == edges[i].from && i != j){
            exists=true;
            break;
        }
        if(exists) break;
    }
    if(ans < EPS){
        cout<<fixed<<setprecision(2)<< "0.00\n";
    }
    else{
        cout<<fixed<<setprecision(2)<< ans<<"\n";
    }
}