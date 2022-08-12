#include<iostream>
#define Infinite 10000  //用以表示∞
#define Max 100
using namespace std;

typedef struct EDGE {         //用于Kruskal算法的结构定义
	int data;
	int u1, u2;
}edge;

class MST {
public:
	void Create(int v);
	void Prim(int v);
	void Kruskal(int v);
	void QuickSort(int left, int right, edge E[Max]);
public:
	int edges[Max][Max];                  //邻接矩阵
	int Vertex[Max];                      //顶点表
	int n, e;                             //顶点数和边数
};

/*创建邻接矩阵存储的带权图*/
void MST::Create(int v) {
	int i, j;
	cout << "请输入连通图顶点个数及边数：" << endl;
	cin >> n >> e;

	cout << "请输入各个顶点：" << endl;
	for (i = 0; i < n; i++) {
		cin >> Vertex[i];
		for (j = 0; j < n; j++) {                //初始化邻接矩阵
			edges[i][j] = Infinite;
		}
	}

	int w, v1, v2;
	cout << "请输入边的权值及其依附的顶点：" << endl;
	for (i = 0; i < e; i++) {
		cin >> w >> v1 >> v2;
		edges[v1][v2] = w;
		edges[v2][v1] = edges[v1][v2];              //无向图为邻接矩阵对称
	}
}

/*Prim算法*/
void MST::Prim(int v) {
	int lowcost[Max];                          //记录权值
	int closest[Max];                          
	int min;
	int i, j, k;
	int count1 = 0;
	for (i = 0; i < n; i++) {		              //给lowcost[]和closest[]赋初值
		lowcost[i] = edges[v][i];
		closest[i] = v;
	}
	lowcost[v] = 0;                           /*将第一个顶点放入U中*/
	for (i = 1; i < n; i++) {	              //在(V-U)中余下的顶点找出离U最近的顶点k
		min = Infinite;
		for (j = 0; j < n; j++) {
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];
				k = j;		                                 //记录找到的最近顶点编号
			}
		}
		cout << " 边(" << closest[k] << "," << k << ")的权为" << min << endl;
		count1 = count1 + min;
		lowcost[k] = 0;                        //标记k已经加入U

		for (j = 0; j < n; j++) {             //对(V-U)中的顶点j及lowcost[]和closest[]进行调整
			if (lowcost[j] != 0 && edges[k][j]<lowcost[j]) {
				lowcost[j] = edges[k][j];
				closest[j] = k;               
			}
		}
	}
	cout << "其权值为：" << count1 << endl;;
}

/*Kruskal算法*/
void MST::Kruskal(int v) {
	int i, j, k = 0;
	int m1, m2, sn1 = 0, sn2 = 0;
	int count2 = 0;
	int vset[Max];                 //存储连通分量编号
	edge E[Max];
	for (i = 0; i < n; i++) {                       //初始化E[]和vset[]
		vset[i] = i;
		for (j = 0; j < n; j++) {
			if (edges[i][j] != Infinite) {          //判断连通条件
				E[k].data = edges[i][j];
				E[k].u1 = i; E[k].u2 = j;
				k++;
			}
		}
	}
	/*对边集E进行递增排序*/
	QuickSort(0, k - 1, E);
	int m = 0;
	int c = 1;		                    //c表示当前构造的边数
	while (c < n) {	                    //最小生成树n-1条边
		sn1 = vset[E[m].u1];
		sn2 = vset[E[m].u2];
		if (sn1 != sn2)                 //若两顶点属于不同的集合，该边是最小生树的边
		{
			cout << " 边(" << E[m].u1 << "," << E[m].u2 << ")的权为" << E[m].data << endl;
			count2 = count2 + E[m].data;
			c++;		   	//生成边数增1
			for (int l = 0; l < n; l++)  	//修改连通分量编号
				if (vset[l] == sn2)
					vset[l] = sn1;
		}
		m++;		               	   //扫描下一条边
	}
	cout << "其权值为：" << count2 << endl;
}

/*Kruskal需要调用的快速排序*/
void MST::QuickSort(int left, int right,edge E[Max]) {
	/*核心：根据基准数对数组进行划分（小于枢轴在左侧，大于在右侧）*/
	int i, j;
	int standard;                       //存储基准数
	if (left > right) {                   //终止
		return;
	}
	standard = E[left].data;
	i = left;
	j = right;
	while (i != j) {
		while (E[j].data >= standard && i < j) {         //从右向左找小于基准数的值
			j--;
		}
		while (E[i].data <= standard && i < j) {      //从左向右找大于基准数的值
			i++;
		}
		/*交换两个数（及其他信息）在数组中的位置*/
		if (i <= j) {
			swap(E[i], E[j]);
		}
	}
	/*交换基准数和i=j时的值*/
	swap(E[i], E[left]);
	QuickSort(left, i - 1, E);//递归处理枢轴左边
	QuickSort(i + 1, right, E);//递归处理枢轴右边	
}

int main() {
	MST M;
	M.Create(0);
	cout << "展示图的邻接矩阵：" << endl;
	for (int i = 0; i < M.n; i++) {
		for (int j = 0; j < M.n; j++) {
			cout << M.edges[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Prim算法下的带权连通图的最小生成树可表示为：" << endl;
	M.Prim(0);
	cout << endl;

	cout<<"Kruskal算法下的带权连通图的最小生成树为：" << endl;
    M.Kruskal(0);
}