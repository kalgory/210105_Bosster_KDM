#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int N, Q;
vector<int> nodes(250001,-1);
priority_queue <pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first < b.first;
}
int node_find(int a){
    if (nodes[a] < 0)
             return a;
    if(a==nodes[a]) return a;
    return nodes[a] = node_find(nodes[a]);
}

 

void node_merge(int a, int b)
{
        a = node_find(a);
        b = node_find(b);
        if (a == b)
                 return;
        if (b < a)
                 swap(a, b);
        nodes[a]=a;
        nodes[b] = a;
}

 





int main(){
    //input
    cin>>N>>Q;//N:좌표의 갯수 Q:case수
    vector<pair<int,int>> x(N);//x좌표,index vector
    vector<pair<int,int>> y(N);//y좌표,index vector
    for(int i=0;i<N;i++) {
        cin>>x[i].first>>y[i].first;
        x[i].second=i;
        y[i].second=i;
    } //x,y좌표 입력
    sort(x.begin(),x.end(),cmp);
    sort(y.begin(),y.end(),cmp);
    for(int i=0;i<N-1;i++){
        pq.push({abs(x[i].first-x[i+1].first),{x[i].second,x[i+1].second}}); //x좌표 우선순위(x좌표거리) 큐 psuh
        pq.push({abs(y[i].first-y[i+1].first),{y[i].second,y[i+1].second}}); //y좌표 우선순위 큐 push
    }
    vector<pair<int,pair<int,pair<int,int>>>> query;
    int target1,target2,weight;
    for(int i=0;i<Q;i++){
        cin>>target1>>target2>>weight;
        query.push_back({weight,{i,{target1,target2}}});
    }
    vector<bool> answer(Q);
    sort(query.begin(),query.end());
    for(int i=0;i<Q;i++){
        target1=query[i].second.second.first;
        target2=query[i].second.second.second;
        weight=query[i].first;
        while(!pq.empty()){
            if(pq.top().first>weight) break;
    //        cout<<pq.top().first<<"\t"<<pq.top().second.first<<"\t"<<pq.top().second.second<<endl;
            node_merge(pq.top().second.first,pq.top().second.second);
            pq.pop();
        }
       // cout<<node_find(target1-1)<<"\t"<<node_find(target2-1)<<"\n";
        answer[query[i].second.first]=(node_find(target1-1)==node_find(target2-1));
    }
    
    for(int i=0;i<Q;i++){
        if(answer[i]) cout<<"YES\n";
        else cout<<"NO\n";
    }
}