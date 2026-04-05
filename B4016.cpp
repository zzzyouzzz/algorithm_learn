/*
树的直径问题，
定义：树的直径为树中任意两个节点之间的最长路径。
从任一节点出发所访问到的最远点一定为树的直径的一端。（反证法）

*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5+10;
struct Edge{
    int to,next;
    int val;
}e[N<<1];
int head[N],cnt;
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
    e[cnt].val=w;
}
/*法1：两次dfs*/
int far_node[N],dis[N],ans=0;
//法三：计算从u出发子树的第二远路径，与最远路径和为候选答案
int next_dis[N];
void dfs(int u,int from){
    int up_d=0;
    for(int i=head[u];i;i=e[i].next){
        if(e[i].to==from) continue;
        dfs(e[i].to,u);
        if(dis[e[i].to]+e[i].val>dis[u]){
            next_dis[u]=max(next_dis[u],dis[u]);
            dis[u]=dis[e[i].to]+e[i].val;
            far_node[u]=far_node[e[i].to];
            up_d=i;
        }else{
            next_dis[u]=max(next_dis[u],dis[e[i].to]+e[i].val);
        }
    }
    ans=max(ans,next_dis[u]+dis[u]);
    /*法2：dp利用dis数组计算从u出发的两条最远路径，和为候选答案*/
    /*for(int i=head[u];i;i=e[i].next){
        if(i==up_d) continue;
        ans=max(ans,dis[e[i].to]+e[i].val+dis[u]);//路径1为dis[e[i].to],路径2为dis[u]+e[i].val
    }*/
    
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v,1);
        add(v,u,1);
    }
    memset(dis,0,sizeof dis);
    for(int i=1;i<=n;i++){
        far_node[i]=i;
    }
    dfs(1,0);
    /*int res=far_node[1];
    memset(dis,0,sizeof dis);
    for(int i=1;i<=n;i++){
        far_node[i]=i;
    }
    dfs(res,0);*/
    
    cout<<ans<<endl;
    return 0;
}
