#include "highway.h"
#include "stdc++.h"

typedef long long ll;
typedef std::pair<int,int> P;

using namespace std;

const int N = 150000;

#define fi first
#define se second
#define mk make_pair

std::vector<int> w, T1, T2;

vector<P> G[N];

int disu[N], disv[N], idxu[N], idxv[N];
int n, m, pos;
ll res, dist;

int GetPath() {
    fill(w.begin(), w.end(), 0);
    int l = 0,r = m - 1;
    while(l < r) {
        int mid = (l + r) >> 1;
        for(int i = l;i <= mid;i++) w[i] = 1;
        if(ask(w) == res) l = mid + 1;
        else {
            for(int i = l;i <= mid;i++) w[i] = 0;
            r = mid;
        }
    }
    return l;
}

void Bfs(int st, int *dis, int *idx) {
    queue<int>Q;
    while(!Q.empty()) Q.pop();
    for(int i = 0;i < n;i++) dis[i] = -1;
    Q.push(st);
    dis[st] = 0;
    while(!Q.empty()) {
        int o = Q.front();Q.pop();
        for(auto p:G[o]) {
            int to = p.fi,id = p.se;
            if(dis[to] == -1) {
                dis[to] = dis[o] + 1;
                idx[to] = id;
                Q.push(to);
            }
        }
    }
}

int Solve(vector<int>&In, vector<int>&Ot, int *idxIn, int *idxOt) {
    int l = 0, r = int(In.size()) - 1;
    while(l < r) {
        int mid = (l + r) >> 1;
        for(int i = 0;i < m;i++) w[i] = 1;
        w[pos] = 0;
        for(int i = 1;i < (int)Ot.size();i++)  w[idxOt[Ot[i]]] = 0;
        for(int i = 1;i <= mid;i++) w[idxIn[In[i]]] = 0;
        ll ret = ask(w);
        if (ret == res) r = mid;
        else l = mid + 1;
    }
    return In[l];
}

void find_pair(int N, std::vector<int> U, std::vector<int> V, int A, int B) {
    n = N; m = int(U.size());
    for(int i = 0;i < m;i++) w.push_back(0);
    for(int i = 0;i < m;i++) {
        G[U[i]].push_back(mk(V[i], i));
        G[V[i]].push_back(mk(U[i], i));
    }
    
    res = ask(w);
    dist = res / A;
    
    pos = GetPath();
    
    Bfs(U[pos], disu, idxu);
    Bfs(V[pos], disv, idxv);
    for(int i = 0;i < n;i++) {
        if (disu[i] < disv[i]) T1.push_back(i);
        if (disv[i] < disu[i]) T2.push_back(i);
    }
    
    sort(T1.begin(), T1.end(), [](int x, int y) {return disu[x] < disu[y];});
    sort(T2.begin(), T2.end(), [](int x, int y) {return disv[x] < disv[y];});
    int pos1 = Solve(T1, T2, idxu, idxv);
    int pos2 = Solve(T2, T1, idxv, idxu);
    answer(pos1, pos2);
}

