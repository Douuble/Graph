#include <iostream>
#define Max 100
using namespace std;

/*定义图的类*/
class Graph {
public:
    int Vertex[Max];           //顶点表
    int edges[Max][Max];       //邻接矩阵
    int visited[Max];          //访问标志数组
    int n, e;                  //顶点个数和边数
    int w;                     //边的权
public:
    void Create();
    void DFS(int v);
    void BFS(int v);
    void DFSnon(int v);
    void Reset();
};

void Graph::Create(){
    int i, j, k;
    cout << "请输入图的顶点数和边数：" << endl;
    cin >> n>>e;

    cout << "请输入各个顶点：" << endl;
    for (i = 0; i < n; i++){
        cin >> Vertex[i];
        visited[i] = 0;                                //辅助数组初始化
    }

    for (i = 0; i < n; i++) {                         //初始化邻接矩阵 置边为0
        for (j = 0; j < n; j++)
            edges[i][j] = 0;
    }

    int v1, v2;
    for (k = 0; k < e; k++){
        cout << "请输入边依附的顶点：" << endl;
        cin >> v1>> v2;
       edges[v1][v2] = 1;
       edges[v2][v1] = 1;                             //对称矩阵
    }
}

void Graph::Reset() {                            //用于辅助数组的复位
    for (int i = 0; i < n; i++) {
        visited[i] = 0;                                //辅助数组初始化
    }
}

/*深度优先搜索遍历递归算法*/
void Graph::DFS(int v){
    if (v < 0 || v >= n) {
        cout << "顶点不存在！" << endl;
        return;
    }
    cout << Vertex[v] << " ";
    visited[v] = 1;
    for (int j = 0; j < n; j++)
        if (visited[j] == 0 && edges[v][j] == 1)             //edges[v][j]存在且顶点未被访问过
            DFS(j);
}

/*深度优先搜索遍历非递归算法*/
void Graph::DFSnon(int v){
    int S[Max];
    int top = -1;                 //定义栈和栈顶指针
    int j;

    if (v < 0 || v >= n){
        cout << "顶点不存在！" << endl;
        return;
    }

    cout << Vertex[v] << " ";
    top++;
    S[top] = v;
    visited[v] = 1;

    while (top != -1){
        v = S[top];                                          //栈顶元素出栈
        for (j = 0; j < n; j++){
            if (visited[j] == 0 && edges[v][j] ==1){         //顶点未被访问过且边存在
                cout << Vertex[j] << " ";
                top++;
                S[top] = j;
                visited[j] = 1;
                break;
            }
        }
        if (j == n) top--;                                  //直到top=-1结束循环
    }
}

/*广度优先搜索遍历算法*/
void Graph::BFS(int v) {
    int front, rear;
    int Q[Max];                               //定义栈及相应指针
    front = rear = -1;

    if (v < 0 || v >= n) { cout << "顶点位置错误!"; return; }

    cout << Vertex[v] << " ";
    visited[v] = 1;
    rear++;
    Q[rear] = v;

    while (front != rear) {
        front++;
        v = Q[front];//队列首元素出队列
        for (int j = 0; j < n; j++) {
            if (edges[v][j] == 1 && visited[j] == 0) {
                cout << Vertex[j] <<" ";
                visited[j] = 1;
                rear++;
                Q[rear] = j;
            }
        }
    }
}

int main() {
    Graph G;
    G.Create();
    cout << "展示图的邻接矩阵：" << endl;
    for (int i = 0; i < G.n; i++) {
        for (int j = 0; j < G.n; j++) {
            cout << G.edges[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "图的深度优先搜索遍历(递归算法)结果为：" << endl;
    G.DFS(0);
    cout << endl;

    G.Reset();
    cout << "图的深度优先搜索遍历(非递归算法)结果为：" << endl;
    G.DFSnon(0);
    cout << endl;

    G.Reset();
    cout << "图的广度优先搜索遍历结果为：" << endl;
    G.BFS(0);
}

