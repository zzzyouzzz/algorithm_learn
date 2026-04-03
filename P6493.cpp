#include <iostream>
using namespace std;
const int N = 2e5+10;
struct Node{
    int val;
    int l,r;
    int s,h;//区间前后缀
}tree[N<<2];
int s[N];
void pushup(int p){//思路类似单次求最大子段的分治做法，重点在分割区间后的合并过程，需要考虑区间前后缀的情况
    //由于存在多次修改查询，所以采用树来记忆，而非直接分治；
    int lc = p<<1,rc = lc|1;
    if(s[tree[lc].r]==s[tree[rc].l]){
        tree[p].val=max(tree[lc].val,tree[rc].val);
        tree[p].s=tree[lc].s;
        tree[p].h=tree[rc].h;
    }else{
        tree[p].val=max(tree[lc].val,tree[rc].val);
        tree[p].val=max(tree[p].val,tree[lc].h+tree[rc].s);
        if(tree[lc].s==tree[lc].r-tree[lc].l+1){
            tree[p].s=tree[lc].s+tree[rc].s;
        }else{
            tree[p].s=tree[lc].s;
        }
        if(tree[rc].h==tree[rc].r-tree[rc].l+1){
            tree[p].h=tree[rc].h+tree[lc].h;
        }else{
            tree[p].h=tree[rc].h;
        }
    }
}
void build(int p,int l,int r){
    if(l==r){
        tree[p].val=1;
        tree[p].s=1;
        tree[p].h=1;
        tree[p].l=l;
        tree[p].r=r;
        return;
    }
    int mid = l+r>>1;
    int lc = p<<1,rc = lc|1;
    build(lc,l,mid);
    build(rc,mid+1,r);
    pushup(p);
    tree[p].l=l;
    tree[p].r=r;
}
void amend(int p,int x){
    if(tree[p].l==x&&tree[p].r==x){
        s[x]=~s[x];
        return;
    }
    int mid = (tree[p].l+tree[p].r)>>1;
    int lc = p<<1,rc = lc|1;
    if(x<=mid){
        amend(lc,x);
    }else{
        amend(rc,x);
    }
    pushup(p);
}
int main(){
    int n,m;
    cin>>n>>m;
    build(1,1,n);
    while(m--){
        int x;
        cin>>x;
        amend(1,x);
        cout<<tree[1].val<<endl;
    }
}
