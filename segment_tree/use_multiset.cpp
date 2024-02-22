// #define _CRT_SECURE_NO_WARNINGS
// #pragma GCC optimize ("O3")
// #pragma GCC target ("sse4")
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
#include <bits/stdc++.h>
using namespace std;

#define filein() freopen("test.inp", "r", stdin);
#define fileout() freopen("test.out", "w", stdout);
#define fast() ios_base::sync_with_stdio(NULL);cin.tie(NULL);
#define ll long long
#define MOD (int)(1e9+7)
#define N (int)1e7
#define INF ((1ll<<31)-1)
#define bit(mask, i) ((mask>>i)&1)

#define vi vector<int>
#define pii pair<int, int>
#define pb push_back
#define fi first
#define se second
#define maxn 100006

int n, m, a[maxn];
multiset<int> st[4*maxn];

void build(int id, int l, int r){
    if(l == r){
        st[id].insert(a[l]);
        return;
    }
    int mid = (l+r)/2;
    build(id*2, l, mid);
    build(id*2+1, mid+1, r);
    st[id] = st[id*2];
    for(int x : st[id*2+1])
        st[id].insert(x);
}

int get(int id, int l, int r, int u, int v, int k){
    if(u > r || v < l)
        return INF;
    if(u <= l && v >= r){
        auto it = st[id].lower_bound(k);
        if(it != st[id].end())
            return *it;
        return INF;
    }
    int mid = (l+r)/2;
    int t1 = get(id*2, l, mid, u, v, k);
    int t2 = get(id*2+1, mid+1, r, u, v, k);
    return min(t1, t2);
}

void update(int id, int l, int r, int pos, int val){
    if(pos < l || pos > r)
        return;
    if(l == r){
        st[id].clear();
        st[id].insert(val);
        return; 
    }
    int mid = (l+r)/2;
    update(id*2, l, mid, pos, val);
    update(id*2+1, mid+1, r, pos, val);
    st[id].erase(st[id].find(a[pos]));
    st[id].insert(val);
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    while(m--){
        int tv; cin >> tv;
        if(tv == 1){
            int x, v; cin >> x >> v;
            update(1, 1, n, x, v);
            a[x] = v;
        }
        else{
            int l, r, k; cin >> l >> r >> k;
            int ans = get(1, 1, n, l, r, k);
            cout << (ans==INF?-1:ans) << '\n';
        }
    }
}

int main(){
    fast();
    #ifndef ONLINE_JUDGE
    filein(); fileout();
    #endif    
    // int t; cin >> t;
    // while(t--)
        solve();
    cerr << "\nTime run: " << 1000 * clock() / CLOCKS_PER_SEC << "ms" << '\n';
    return 0;
}
