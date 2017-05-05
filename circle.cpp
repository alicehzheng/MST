#include<iostream>  
#include<fstream>  
using  namespace std;  
  
#define MAX 100  
#define MAXCOST 0x7fffffff

typedef struct{
    int x,y,w;
}Node;
Node a[MAX];

int cmp(const void*a, const void *b){//从小到大
    return ((Node*)a)->w - ((Node*)b)->w;
}

int cmp2(const void*a, const void *b){//从大到小
    return ((Node*)b)->w - ((Node*)a)->w;
}

int graph[MAX][MAX];  

int Wshall(int array[][MAX],int n){
    // cout << "it is in Wshall"<<endl;
    int i,j,k,m = 0;
    int r[n+1][n+1], B[n+1][n+1];
    for(i = 1; i<=n ; ++i){
        for(j = 1; j <= n; ++j){
            r[i][j] = 0;
            B[i][j] = array[i][j];
        }
    }
   // cout << "it is in Wshall 2"<<endl;

    for(j = 1; j <= n; ++j){
        for(i = 1; i<=n ; ++i){
            if(B[i][j] >= 1){
                for(k = 1; k <= n; k++){
                    B[i][k] = B[i][k] + B[j][k];
                }
            }
        }
    }
   // // cout << "it is in Wshall 3"<<endl;

    for(i = 1; i <= n; i++){
        for( j = 1; j <= n; j++){
            r[i][j] = B[i][j];
            if(r[i][j] >= 1 || i==j){
                m = m+1;
            }
        }
    }
   // // cout << "it is in Wshall 4"<<endl;

    if(m == n*n) return 1;
    else return 0;
}

int circle(int graph[][MAX], int n, int m)  
{  
    int max, p, q, am;
    for(int i =0; i<m; ++i){
        p = a[i].x;
        q = a[i].y;
        // am = a[i].w;
        graph[p][q] = 0;
        graph[q][p] = 0;
        if(Wshall(graph,n) == 1){
            cout << "delete V" << p << "-> V" << q << "=" << a[i].w <<endl;
        }else{
           graph[p][q] = a[i].w;
           graph[q][p] = a[i].w;
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j < i; ++j){
            if(graph[i][j] != 0){
                cout << "V" << i << "-> V" << j << "=" << graph[i][j] <<endl;
                ans+= graph[i][j];
            }
        }
    }
    return ans;
}  
  
int main()  
{  
    int i, j, k, m, n;  
    int x, y, cost;  
    // ifstream in("input.txt");  
    // in >> m >> n;//n=顶点的个数，m=边的个数  
    //初始化图G  
    cin >> n >> m;
    for (i = 1; i <= n; i++)  
    {  
        for (j = 1; j <= n; j++)  
        {  
            graph[i][j] = 0;  
        }  
    }
    // if(m < n-1){
    //     cout << "not connect" << endl;
    //     exit(0);
    // }if(m == n-1){
    //     cout << "It is a tree" << endl;
    //     exit(0);
    // }  
    //构建图G 
    a[0].w = MAXCOST;
    for (k = 0; k < m; k++)  
    {  
        // in >> i >> j >> cost;
        cin >> i >> j >> cost;
        a[k].x = i;
        a[k].y = j;
        a[k].w = cost;  
        graph[i][j] = cost;  
        graph[j][i] = cost;  
    }  
    // for(int i=1;i<=n;++i){
    //     for(int j=1;j<=n;++j){
    //         cout<<graph[i][j]<<" ";
    //     }
    //     cout <<"\n";
    // }
    qsort(a, m, sizeof(a[0]), cmp2);
    cout << "*_*" << endl;
    for(int i=0;i<m;++i){
        cout << a[i].x <<' '<<a[i].y <<' '<<a[i].w <<endl;
    }
    //求解最小生成树  
    cost = circle(graph, n, m);  
    //输出最小权值和  
    cout << "最小权值和=" << cost << endl;  
    // system("pause");  
    return 0;  
}  