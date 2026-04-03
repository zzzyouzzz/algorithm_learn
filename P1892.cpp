#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
const int N=40000+5;
const int M=100000+5;
struct node{
    int a,b,w;
    bool operator<(const node &x)const{
        return w>x.w;
    }
}edge[M];
int father[N];
int opp[N];
int find(int x){
    if(father[x]==x) return x;
    else return father[x]=find(father[x]);
}
void merge(int a,int b){
    int fa=find(a);
    int fb=find(b);
    if(fa!=fb) father[fa]=fb;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n*2;i++) father[i]=i;
    for(int i=1;i<=m;i++){
        int a,b;
        char opt;
        cin>>opt>>a>>b;
//合并操作，两倍空间存储，前n个节点表示朋友，后n个节点表示敌人，合并操作时，将a和b的敌人合并到a和b的敌人中
        if(opt=='F'){
            merge(a,b);//a与b为友，则a的敌人与b的敌人为友
            //merge(a+n,b+n);//a与b为友，则a的敌人与b的敌人为敌
        }else{
            merge(b+n,a);//a与b为敌，则a与b的敌人为友
            merge(a+n,b);//a与b为敌，则b与a的敌人为友
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(find(i)==i)ans++;
    }
    cout<<ans<<endl;
    return 0;
}
