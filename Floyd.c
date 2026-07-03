#include <stdio.h>
#include <stdlib.h>

#define INF 999999
#define V 6

void printPath(int i, int j,int path[V][V]){
    if(path[i][j] == -1)return;
    
    printPath(i, path[i][j],path);
    printf("%d->",path[i][j]);
    printPath(path[i][j],j,path);
}

void Floyd(int m, int n, int graph[V][V]){
    int dist[V][V];
    int path[V][V];
    
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            dist[i][j] = graph[i][j];
            path[i][j] = -1;
        }
    }
    
    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                if(dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    
    if(dist[m][n] !=INF){
    printf("%d与%d两点间的最短路径为：",m,n);
    printf("%d->",m);
    printPath(m, n, path);
    printf("%d",n);
    printf("\n最短路径长度为：%d",dist[m][n]);}
    else{
        printf("%d不可到达%d",m,n);
    }
}

int main(){
    int m, n;
    int graph[V][V] = {
        {0, 50, 10, INF, 70, INF},
        {INF, 0, 15, INF, 10, INF},
        {20, INF, 0, 15, INF, INF},
        {INF, 20, INF, 0, 35, INF},
        {INF, INF, INF, 30, 0, INF},
        {INF, INF, INF, 3, INF, 0}
    };
    
    printf("请输入所求两点：");
    scanf("%d %d",&m,&n);
    
    Floyd(m, n, graph);
    
    return 0;
}