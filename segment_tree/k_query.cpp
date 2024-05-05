int n, q, a[maxn];
vi st[4*maxn];

void build(int id, int l, int r){
    if(l == r){
        st[id].pb(a[l]);
        return;
    }
    int mid = (l+r)/2;
    build(id*2, l, mid);
    build(id*2+1, mid+1, r);
    st[id].resize(st[id*2].size()+st[id*2+1].size());
    merge(st[id*2].begin(), st[id*2].end(), st[id*2+1].begin(), st[id*2+1].end(), st[id].begin());
}

int get(int id, int l, int r, int u, int v, int k){
    if(u > r || v < l)
        return {};
    if(u <= l && v >= r)
        return st[id].size()-(upper_bound(st[id].begin(), st[id].end(), k) - st[id].begin());
    int mid = (l+r)/2;
    return get(id*2, l, mid, u, v, k) + get(id*2+1, mid+1, r, u, v, k);
}

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    cin >> q;
    while(q--){
        int l, r, k; cin >> l >> r >> k;
        cout << get(1, 1, n, l, r, k) << '\n'; 
    }
}
