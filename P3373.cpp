#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+10;
struct node{
    int l,r;
    long long sum=0;
    long long lazy=0;
    long long mul=1;
}tree[N*4];
long long a[N];
inline void pushdown_mul(int u,int mod){
    if(tree[u].mul==1)return;
    int lc=u<<1,rc=u<<1|1;
    tree[lc].lazy*=tree[u].mul;
    tree[lc].lazy%=mod;
    tree[lc].mul*=tree[u].mul;
    tree[lc].mul%=mod;
    tree[lc].sum*=tree[u].mul;
    tree[lc].sum%=mod;
    
    tree[rc].lazy*=tree[u].mul;
    tree[rc].lazy%=mod;
    tree[rc].mul*=tree[u].mul;
    tree[rc].mul%=mod;
    tree[rc].sum*=tree[u].mul;
    tree[rc].sum%=mod;
    
    tree[u].mul=1;
}
inline void pushdown_add(int u,int mod){
    if(tree[u].lazy==0)return;
    int lc=u<<1,rc=u<<1|1;
    tree[lc].lazy+=tree[u].lazy;
    tree[lc].lazy%=mod;
    tree[lc].sum+=tree[u].lazy*(tree[lc].r-tree[lc].l+1);
    tree[lc].sum%=mod;
    
    tree[rc].lazy+=tree[u].lazy;
    tree[rc].lazy%=mod;
    tree[rc].sum+=tree[u].lazy*(tree[rc].r-tree[rc].l+1);
    tree[rc].sum%=mod;

    tree[u].lazy=0;
}
void build(int u,int l,int r,int mod){
    if(l==r){
        tree[u].sum=a[l];
        tree[u].lazy=0;
        tree[u].mul=1;
        tree[u].l=l;
        tree[u].r=r;
        return;
    }
    int mid=(l+r)>>1,lc=u<<1,rc=u<<1|1;
    build(lc,l,mid,mod);
    build(rc,mid+1,r,mod);
    tree[u].sum=tree[lc].sum+tree[rc].sum;
    tree[u].lazy=0;
    tree[u].mul=1;
    tree[u].l=l;
    tree[u].r=r;
}
void range_add(int u,int L,int R,long long v,int mod){
    if(tree[u].l>=L&&tree[u].r<=R){
        tree[u].lazy+=v;
        tree[u].lazy%=mod;
        tree[u].sum+=v*(tree[u].r-tree[u].l+1);
        tree[u].sum%=mod;
        return;
    }
    //根据线性性质，先乘后加
    pushdown_mul(u,mod);
    pushdown_add(u,mod);
    int mid=(tree[u].l+tree[u].r)>>1,lc=u<<1,rc=u<<1|1;
    if(L<=mid)range_add(lc,L,R,v,mod);
    if(R>mid)range_add(rc,L,R,v,mod);
    tree[u].sum=tree[lc].sum%mod+tree[rc].sum%mod;
    tree[u].sum%=mod;
}
void range_mul(int u,int L,int R,long long v,int mod){
    if(tree[u].l>=L&&tree[u].r<=R){
        tree[u].mul*=v;
        tree[u].mul%=mod;
        tree[u].lazy*=v;//乘法标记同步到加法即 (a+k)*v=a*v+k*v
        tree[u].lazy%=mod;
        tree[u].sum*=v;
        tree[u].sum%=mod;
        return;
    }
    //根据线性性质，先乘后加
    pushdown_mul(u,mod);
    pushdown_add(u,mod);
    int mid=(tree[u].l+tree[u].r)>>1,lc=u<<1,rc=u<<1|1;
    if(L<=mid)range_mul(lc,L,R,v,mod);
    if(R>mid)range_mul(rc,L,R,v,mod);
    tree[u].sum=tree[lc].sum%mod+tree[rc].sum%mod;
    tree[u].sum%=mod;
}
long long query(int u,int L,int R,int mod){
    if(tree[u].l>=L&&tree[u].r<=R){
        return tree[u].sum;
    }
    pushdown_mul(u,mod);
    pushdown_add(u,mod);
    int mid=(tree[u].l+tree[u].r)>>1,lc=u<<1,rc=u<<1|1;
    long long res=0;
    if(L<=mid)res+=query(lc,L,R,mod)%mod;
    if(R>mid)res+=query(rc,L,R,mod)%mod;
    return res%mod;
}
int main(){
    int n,m,mod;
    cin>>n>>m>>mod;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n,mod);
    while(m--){
        int op;
        cin>>op;
        if(op==3){
            int L,R;
            cin>>L>>R;
            cout<<query(1,L,R,mod)<<endl;
        }
        else if(op==1){
            int L,R;
            long long v;
            cin>>L>>R>>v;
            range_mul(1,L,R,v,mod);
        }
        else{
            int L,R;
            long long v;
            cin>>L>>R>>v;
            range_add(1,L,R,v,mod);
        }
    }
    return 0;
}