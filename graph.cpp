#include <iostream>
#define Max 100
using namespace std;

/*����ͼ����*/
class Graph {
public:
    int Vertex[Max];           //�����
    int edges[Max][Max];       //�ڽӾ���
    int visited[Max];          //���ʱ�־����
    int n, e;                  //��������ͱ���
    int w;                     //�ߵ�Ȩ
public:
    void Create();
    void DFS(int v);
    void BFS(int v);
    void DFSnon(int v);
    void Reset();
};

void Graph::Create(){
    int i, j, k;
    cout << "������ͼ�Ķ������ͱ�����" << endl;
    cin >> n>>e;

    cout << "������������㣺" << endl;
    for (i = 0; i < n; i++){
        cin >> Vertex[i];
        visited[i] = 0;                                //���������ʼ��
    }

    for (i = 0; i < n; i++) {                         //��ʼ���ڽӾ��� �ñ�Ϊ0
        for (j = 0; j < n; j++)
            edges[i][j] = 0;
    }

    int v1, v2;
    for (k = 0; k < e; k++){
        cout << "������������Ķ��㣺" << endl;
        cin >> v1>> v2;
       edges[v1][v2] = 1;
       edges[v2][v1] = 1;                             //�Գƾ���
    }
}

void Graph::Reset() {                            //���ڸ�������ĸ�λ
    for (int i = 0; i < n; i++) {
        visited[i] = 0;                                //���������ʼ��
    }
}

/*����������������ݹ��㷨*/
void Graph::DFS(int v){
    if (v < 0 || v >= n) {
        cout << "���㲻���ڣ�" << endl;
        return;
    }
    cout << Vertex[v] << " ";
    visited[v] = 1;
    for (int j = 0; j < n; j++)
        if (visited[j] == 0 && edges[v][j] == 1)             //edges[v][j]�����Ҷ���δ�����ʹ�
            DFS(j);
}

/*����������������ǵݹ��㷨*/
void Graph::DFSnon(int v){
    int S[Max];
    int top = -1;                 //����ջ��ջ��ָ��
    int j;

    if (v < 0 || v >= n){
        cout << "���㲻���ڣ�" << endl;
        return;
    }

    cout << Vertex[v] << " ";
    top++;
    S[top] = v;
    visited[v] = 1;

    while (top != -1){
        v = S[top];                                          //ջ��Ԫ�س�ջ
        for (j = 0; j < n; j++){
            if (visited[j] == 0 && edges[v][j] ==1){         //����δ�����ʹ��ұߴ���
                cout << Vertex[j] << " ";
                top++;
                S[top] = j;
                visited[j] = 1;
                break;
            }
        }
        if (j == n) top--;                                  //ֱ��top=-1����ѭ��
    }
}

/*����������������㷨*/
void Graph::BFS(int v) {
    int front, rear;
    int Q[Max];                               //����ջ����Ӧָ��
    front = rear = -1;

    if (v < 0 || v >= n) { cout << "����λ�ô���!"; return; }

    cout << Vertex[v] << " ";
    visited[v] = 1;
    rear++;
    Q[rear] = v;

    while (front != rear) {
        front++;
        v = Q[front];//������Ԫ�س�����
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
    cout << "չʾͼ���ڽӾ���" << endl;
    for (int i = 0; i < G.n; i++) {
        for (int j = 0; j < G.n; j++) {
            cout << G.edges[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "ͼ�����������������(�ݹ��㷨)���Ϊ��" << endl;
    G.DFS(0);
    cout << endl;

    G.Reset();
    cout << "ͼ�����������������(�ǵݹ��㷨)���Ϊ��" << endl;
    G.DFSnon(0);
    cout << endl;

    G.Reset();
    cout << "ͼ�Ĺ�����������������Ϊ��" << endl;
    G.BFS(0);
}

