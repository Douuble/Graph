#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>

#define Max 100
#define n 8                    //顶点数
#define e  10                 //边数
#define Infinite 10000         //表示顶点不连通∞
using namespace std;

/*地图的类定义*/
class Map {                   
public:
    char* number[Max];
    char* name[Max];
    char* introduction[Max];
    int edges[Max][Max];       //邻接矩阵
    int A[Max][Max];
    int path[Max][Max];
public:
    Map() {
        for (int i = 0; i < Max; i++) {
            name[i] = new char[100];
            introduction[i] = new char[100];
            number[i] = new char[100];
        }
    }
    int Read();
    void Display();
    void Query();
    void Ask();
    void Floyd();              
    void Path(int a,int b);
};

/*地图信息读取*/
int Map::Read(){                                    
    FILE* fp; 
    int i = 1;
        fp = fopen("map.txt", "r");
        if (fp == NULL) {
            cout << "打开文件失败！" << endl;
            exit(0);
        }
        while (fscanf(fp, "%s%s%s", number[i], name[i], introduction[i]) == 3) {  // 循环读入学生信息
            i++;
        }
        if (i == 1)
            cout << "文件为空!" << endl;
        fclose(fp);
  
    int j,k;
    for (i = 1; i <= n; i++) {                         //初始化邻接矩阵 置边为∞
        for (j = 1; j <=n; j++)
            edges[i][j] = Infinite;
    }
    /*储存各条路径的权值*/
    edges[1][6] = edges[6][1] = 600;
    edges[1][8] = edges[8][1] = 250;
    edges[2][5] = edges[5][2] = 200;
    edges[3][4] = edges[4][3] = 150;
    edges[2][8] = edges[8][2] = 120;
    edges[4][6] = edges[6][4] = 100;
    edges[4][5] = edges[5][4] = 80;
    edges[7][6] = edges[6][7] = 70;
    edges[3][5] = edges[5][3] = 40;
    edges[7][4] = edges[4][7] = 30;
    cout << "地图信息已读取完毕！" << endl;
    return 1;
}

/*景点查询*/
void Map::Query() {
    cout << "请输入要查询的景点代号：" << endl;
    char aim[3];
    int i;
    int flag = 0;
    cin >> aim;
    for (i = 1; i <= n; i++)
        if (strcmp(aim,number[i]) == 0) {
            cout << "代号：" << number[i] << "  " << "景点名称：" <<name[i] << endl;
            cout << "简介：" <<introduction[i] << endl;
            flag = 1;
            break;
        }
    if (flag == 0)  cout << "该代号不存在!" << endl;
}
    
/*弗洛伊德算法以获取最短路径*/
void Map::Floyd() {                 
    int i, j, k;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; j++) {                
            A[i][j] = edges[i][j];
            if (A[i][j] < Infinite && i != j)
                path[i][j] = i;
            else
                path[i][j] = -1;
        }
    }
    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (A[i][j]>A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

/*获取具体路径*/
void Map::Path(int a, int b) {
    int p[Max];
    p[1] = b;
    int i = 2;
    while (a != b) {
        b = path[a][b];
        p[i] = b;
        i++;
    }
    cout << "路径:" << name[a];
    i = i - 2;
    while (i >= 1) {
        cout << "--->" <<name[p[i]];
        i--;
    }
}

/*问路*/
void Map::Ask() {
    Display();
    cout << "请输入要询问的起点和终点序号:";
    int a, b;
    cin >> a >> b;
    if (a < 1 || a>8 || b < 1 || b>8) {
        cout << "选择序号错误！" << endl;
        return;
    }
    Floyd();
    cout << "从" << name[a] << "到" << name[b] << ":" << endl;
    cout << "最短路径长度：" << A[a][b] << "米" << endl;
    Path(a, b);
    cout << endl;
}

/*展示地图总览*/
void Map::Display() {
    cout << " *校园景点总览*   " << endl;
    cout << "代号   " << "  " << "景点名称" << endl;
    for (int i = 1; i <= n; i++) {
        printf("%-8s %-12s\n", number[i], name[i]);
    }
cout << endl;
}

/*功能选择菜单*/
void menu() {
    cout << endl;
    cout << "请选择您需要的服务：" << endl;
    cout << "1、查看景点总览" << endl;
    cout << "2、查看景点详情" << endl;
    cout << "3、问路" << endl;
    cout << "4、退出" << endl;
}

int main() {
    Map M;
    M.Read();
    system("pause");
    system("cls");
    cout << "欢迎使用校园导游咨询服务！" << endl;
    while (1) {
        menu();
        int choice;
        cin >> choice;
        if (choice == 4) break;
        switch (choice) {
        case 1:M.Display();break;
        case 2:M.Query(); break;
        case 3:system("cls"); M.Ask(); break;
        default:cout << "选择序号错误！" << endl; break;
        }
    }
}