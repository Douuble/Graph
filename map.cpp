#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>

#define Max 100
#define n 8                    //������
#define e  10                 //����
#define Infinite 10000         //��ʾ���㲻��ͨ��
using namespace std;

/*��ͼ���ඨ��*/
class Map {                   
public:
    char* number[Max];
    char* name[Max];
    char* introduction[Max];
    int edges[Max][Max];       //�ڽӾ���
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

/*��ͼ��Ϣ��ȡ*/
int Map::Read(){                                    
    FILE* fp; 
    int i = 1;
        fp = fopen("map.txt", "r");
        if (fp == NULL) {
            cout << "���ļ�ʧ�ܣ�" << endl;
            exit(0);
        }
        while (fscanf(fp, "%s%s%s", number[i], name[i], introduction[i]) == 3) {  // ѭ������ѧ����Ϣ
            i++;
        }
        if (i == 1)
            cout << "�ļ�Ϊ��!" << endl;
        fclose(fp);
  
    int j,k;
    for (i = 1; i <= n; i++) {                         //��ʼ���ڽӾ��� �ñ�Ϊ��
        for (j = 1; j <=n; j++)
            edges[i][j] = Infinite;
    }
    /*�������·����Ȩֵ*/
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
    cout << "��ͼ��Ϣ�Ѷ�ȡ��ϣ�" << endl;
    return 1;
}

/*�����ѯ*/
void Map::Query() {
    cout << "������Ҫ��ѯ�ľ�����ţ�" << endl;
    char aim[3];
    int i;
    int flag = 0;
    cin >> aim;
    for (i = 1; i <= n; i++)
        if (strcmp(aim,number[i]) == 0) {
            cout << "���ţ�" << number[i] << "  " << "�������ƣ�" <<name[i] << endl;
            cout << "��飺" <<introduction[i] << endl;
            flag = 1;
            break;
        }
    if (flag == 0)  cout << "�ô��Ų�����!" << endl;
}
    
/*���������㷨�Ի�ȡ���·��*/
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

/*��ȡ����·��*/
void Map::Path(int a, int b) {
    int p[Max];
    p[1] = b;
    int i = 2;
    while (a != b) {
        b = path[a][b];
        p[i] = b;
        i++;
    }
    cout << "·��:" << name[a];
    i = i - 2;
    while (i >= 1) {
        cout << "--->" <<name[p[i]];
        i--;
    }
}

/*��·*/
void Map::Ask() {
    Display();
    cout << "������Ҫѯ�ʵ������յ����:";
    int a, b;
    cin >> a >> b;
    if (a < 1 || a>8 || b < 1 || b>8) {
        cout << "ѡ����Ŵ���" << endl;
        return;
    }
    Floyd();
    cout << "��" << name[a] << "��" << name[b] << ":" << endl;
    cout << "���·�����ȣ�" << A[a][b] << "��" << endl;
    Path(a, b);
    cout << endl;
}

/*չʾ��ͼ����*/
void Map::Display() {
    cout << " *У԰��������*   " << endl;
    cout << "����   " << "  " << "��������" << endl;
    for (int i = 1; i <= n; i++) {
        printf("%-8s %-12s\n", number[i], name[i]);
    }
cout << endl;
}

/*����ѡ��˵�*/
void menu() {
    cout << endl;
    cout << "��ѡ������Ҫ�ķ���" << endl;
    cout << "1���鿴��������" << endl;
    cout << "2���鿴��������" << endl;
    cout << "3����·" << endl;
    cout << "4���˳�" << endl;
}

int main() {
    Map M;
    M.Read();
    system("pause");
    system("cls");
    cout << "��ӭʹ��У԰������ѯ����" << endl;
    while (1) {
        menu();
        int choice;
        cin >> choice;
        if (choice == 4) break;
        switch (choice) {
        case 1:M.Display();break;
        case 2:M.Query(); break;
        case 3:system("cls"); M.Ask(); break;
        default:cout << "ѡ����Ŵ���" << endl; break;
        }
    }
}