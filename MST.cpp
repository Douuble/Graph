#include<iostream>
#define Infinite 10000  //���Ա�ʾ��
#define Max 100
using namespace std;

typedef struct EDGE {         //����Kruskal�㷨�Ľṹ����
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
	int edges[Max][Max];                  //�ڽӾ���
	int Vertex[Max];                      //�����
	int n, e;                             //�������ͱ���
};

/*�����ڽӾ���洢�Ĵ�Ȩͼ*/
void MST::Create(int v) {
	int i, j;
	cout << "��������ͨͼ���������������" << endl;
	cin >> n >> e;

	cout << "������������㣺" << endl;
	for (i = 0; i < n; i++) {
		cin >> Vertex[i];
		for (j = 0; j < n; j++) {                //��ʼ���ڽӾ���
			edges[i][j] = Infinite;
		}
	}

	int w, v1, v2;
	cout << "������ߵ�Ȩֵ���������Ķ��㣺" << endl;
	for (i = 0; i < e; i++) {
		cin >> w >> v1 >> v2;
		edges[v1][v2] = w;
		edges[v2][v1] = edges[v1][v2];              //����ͼΪ�ڽӾ���Գ�
	}
}

/*Prim�㷨*/
void MST::Prim(int v) {
	int lowcost[Max];                          //��¼Ȩֵ
	int closest[Max];                          
	int min;
	int i, j, k;
	int count1 = 0;
	for (i = 0; i < n; i++) {		              //��lowcost[]��closest[]����ֵ
		lowcost[i] = edges[v][i];
		closest[i] = v;
	}
	lowcost[v] = 0;                           /*����һ���������U��*/
	for (i = 1; i < n; i++) {	              //��(V-U)�����µĶ����ҳ���U����Ķ���k
		min = Infinite;
		for (j = 0; j < n; j++) {
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];
				k = j;		                                 //��¼�ҵ������������
			}
		}
		cout << " ��(" << closest[k] << "," << k << ")��ȨΪ" << min << endl;
		count1 = count1 + min;
		lowcost[k] = 0;                        //���k�Ѿ�����U

		for (j = 0; j < n; j++) {             //��(V-U)�еĶ���j��lowcost[]��closest[]���е���
			if (lowcost[j] != 0 && edges[k][j]<lowcost[j]) {
				lowcost[j] = edges[k][j];
				closest[j] = k;               
			}
		}
	}
	cout << "��ȨֵΪ��" << count1 << endl;;
}

/*Kruskal�㷨*/
void MST::Kruskal(int v) {
	int i, j, k = 0;
	int m1, m2, sn1 = 0, sn2 = 0;
	int count2 = 0;
	int vset[Max];                 //�洢��ͨ�������
	edge E[Max];
	for (i = 0; i < n; i++) {                       //��ʼ��E[]��vset[]
		vset[i] = i;
		for (j = 0; j < n; j++) {
			if (edges[i][j] != Infinite) {          //�ж���ͨ����
				E[k].data = edges[i][j];
				E[k].u1 = i; E[k].u2 = j;
				k++;
			}
		}
	}
	/*�Ա߼�E���е�������*/
	QuickSort(0, k - 1, E);
	int m = 0;
	int c = 1;		                    //c��ʾ��ǰ����ı���
	while (c < n) {	                    //��С������n-1����
		sn1 = vset[E[m].u1];
		sn2 = vset[E[m].u2];
		if (sn1 != sn2)                 //�����������ڲ�ͬ�ļ��ϣ��ñ�����С�����ı�
		{
			cout << " ��(" << E[m].u1 << "," << E[m].u2 << ")��ȨΪ" << E[m].data << endl;
			count2 = count2 + E[m].data;
			c++;		   	//���ɱ�����1
			for (int l = 0; l < n; l++)  	//�޸���ͨ�������
				if (vset[l] == sn2)
					vset[l] = sn1;
		}
		m++;		               	   //ɨ����һ����
	}
	cout << "��ȨֵΪ��" << count2 << endl;
}

/*Kruskal��Ҫ���õĿ�������*/
void MST::QuickSort(int left, int right,edge E[Max]) {
	/*���ģ����ݻ�׼����������л��֣�С����������࣬�������Ҳࣩ*/
	int i, j;
	int standard;                       //�洢��׼��
	if (left > right) {                   //��ֹ
		return;
	}
	standard = E[left].data;
	i = left;
	j = right;
	while (i != j) {
		while (E[j].data >= standard && i < j) {         //����������С�ڻ�׼����ֵ
			j--;
		}
		while (E[i].data <= standard && i < j) {      //���������Ҵ��ڻ�׼����ֵ
			i++;
		}
		/*��������������������Ϣ���������е�λ��*/
		if (i <= j) {
			swap(E[i], E[j]);
		}
	}
	/*������׼����i=jʱ��ֵ*/
	swap(E[i], E[left]);
	QuickSort(left, i - 1, E);//�ݹ鴦���������
	QuickSort(i + 1, right, E);//�ݹ鴦�������ұ�	
}

int main() {
	MST M;
	M.Create(0);
	cout << "չʾͼ���ڽӾ���" << endl;
	for (int i = 0; i < M.n; i++) {
		for (int j = 0; j < M.n; j++) {
			cout << M.edges[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Prim�㷨�µĴ�Ȩ��ͨͼ����С�������ɱ�ʾΪ��" << endl;
	M.Prim(0);
	cout << endl;

	cout<<"Kruskal�㷨�µĴ�Ȩ��ͨͼ����С������Ϊ��" << endl;
    M.Kruskal(0);
}