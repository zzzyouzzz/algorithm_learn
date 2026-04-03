#include <iostream>
using namespace std;
const int N=1e6+10;
struct Node{
    int l,r;
    int val;
    int lazy;
}tree[N<<2];
void pushdown(int p){
    if(tree[p].lazy==0)return;
    int lc=p<<1,rc=lc|1;
    tree[lc].lazy+=tree[p].lazy;
    tree[lc].lazy%=2;
    tree[lc].val=tree[p].lazy==1?tree[lc].r-tree[lc].l+1-tree[lc].val:tree[lc].val;
    tree[rc].lazy+=tree[p].lazy;
    tree[rc].lazy%=2;
    tree[rc].val=tree[p].lazy==1?tree[rc].r-tree[rc].l+1-tree[rc].val:tree[rc].val;
    tree[p].lazy=0;
}
void build(int p,int l,int r){
    if(l==r){
        tree[p].val=0;
        tree[p].lazy=0;
        //记得初始化l,r
        tree[p].l=l;
        tree[p].r=r;
        return;
    }
    int mid=l+r>>1,lc=p<<1,rc=lc|1;
    build(lc,l,mid);
    build(rc,mid+1,r);
    tree[p].val=tree[lc].val+tree[rc].val;
    tree[p].lazy=0;
    //记得初始化l,r
    tree[p].l=l;
    tree[p].r=r;
}
void range_update(int p,int l,int r){
    if(tree[p].l>=l&&tree[p].r<=r){
        tree[p].lazy+=1;
        tree[p].lazy%=2;
        //tree[p].val=tree[p].lazy==1?tree[p].r-tree[p].l+1-tree[p].val:tree[p].val;错误写法
        tree[p].val=tree[p].r-tree[p].l+1-tree[p].val;//更新当前节点的值,但不以lazy更新
        return;
    }
    pushdown(p);
    int lc=p<<1,rc=lc|1;//二分查找
    if(tree[lc].r>=l)range_update(lc,l,r);
    if(tree[rc].l<=r)range_update(rc,l,r);
    tree[p].val=tree[lc].val+tree[rc].val;
}
int query(int p,int l,int r){
    if(tree[p].l>=l&&tree[p].r<=r){
        return tree[p].val;
    }
    pushdown(p);
    int lc=p<<1,rc=lc|1;//树上二分查找
    int res=0;
    if(tree[lc].r>=l)res+=query(lc,l,r);
    if(tree[rc].l<=r)res+=query(rc,l,r);
    return res;
}
int main()
{
    int n,m;
    cin>>n>>m;
    build(1,1,n);
    while(m--){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==0){
            range_update(1,l,r);
        }
        else{
            cout<<query(1,l,r)<<endl;
        }
    }
    return 0;
}