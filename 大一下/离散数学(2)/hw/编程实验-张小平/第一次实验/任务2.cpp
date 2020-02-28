#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int d_point[101];//��1-100�����Ķ�
int road[101][151][2];//��1-100�����ĵ�1-500���ߣ���β��㡢�߳���
int m = 0, n = 0;
int is_visited[101];//Dijkstra�㷨�Ƿ�Ϊ���ý��
int dis_pp[101][101];//�㵽�����
double distance_p2s[101][151];//�㵽�߾���
double distance_s2s[151][151];//�㵽�߾���
double max_distance[151];//�ߵ�������
int infdis = 500000;

int road2[151][3];//x��y��t
int fjil2[151][151][402];//Fjl2[j][i][k]��ʾ��j���ߵ���i��������λ�õ������뺯��F_j(l2)��k/4/road2[j][3]<=l2<=(k+1)/4/road2[j][3]���ֵ�б��
double f0[151][151];//f0[j][i]��ʾ��j������˵㵽��i���ߵ�������
int Fjl2[151][402];//Fjl2[j][k]��ʾ��j���ߵ�����λ�õ������뺯��F_j(l2)��k/4/road2[j][3]<=l2<=(k+1)/4/road2[j][3]���ֵ�б��
double F0[151];//F0[j]��ʾ��j������˵㵽����λ�õ�������
double answer[151];//answer[j]��ʾ��j�������ŵ㵽����λ�õ������롣
double final_answer;//��ʾ�����
int main() {
	//����¼������
	cin >> n >> m;
	int x = 0, y = 0, t = 0;
	for (int i = 1; i <= n; i++) {
		d_point[i] = 0;
	}
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> t;
		road[x][d_point[x]][0] = y;
		road[x][d_point[x]][1] = t;
		road[y][d_point[y]][0] = x;
		road[y][d_point[y]][1] = t;
		d_point[x]++;
		d_point[y]++;
		road2[i][0] = x;
		road2[i][1] = y;
		road2[i][2] = t;
	}
	/*
	cout << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << ' ' << d_point[i] << endl;
		for (int j = 0; j < d_point[i]; j++) {
			cout << j << ' ' << road[i][j][0] << ' ' << road[i][j][1] << endl;
		}
		cout << endl;
	}
	cout << endl;
	*/
	//���¶�ÿ����Dijkstra�㷨
	for (int i = 1; i <= n; i++) {
		//����a
		for (int j = 1; j <= n; j++) {
			dis_pp[i][j] = infdis;
			is_visited[j] = 0;
		}
		dis_pp[i][i] = 0;
		for (int num_S = n; num_S > 0;) {
			//����b
			int j = -1, Pj = infdis;
			for (int k = 1; k <= n; k++) {
				if ((is_visited[k] == 0) && (dis_pp[i][k] < Pj)) {
					Pj = dis_pp[i][k];
					j = k;
				}
			}
			is_visited[j] = 1;
			num_S--;
			if (num_S == 0) {
				break;
			}
			//����c
			for (int k = 0; k < d_point[j]; k++) {
				int ed = road[j][k][0];
				if ((is_visited[ed] == 0) && (dis_pp[i][ed] > Pj + road[j][k][1])) {
					dis_pp[i][ed] = Pj + road[j][k][1];
				}
			}
		}
	}
	/*
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << dis_pp[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	*/
	//������fij
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < m; i++) {
			int vj1 = road2[j][0], vj2 = road2[j][1], vi1 = road2[i][0], vi2 = road2[i][1], wi =road2[i][2], wj = road2[j][2];
			//cout << vi1 << ' ' << vi2 << ' ' << vj1 << ' ' << vj2 << ' ' << wi << ' ' << wj;
			f0[j][i] = (dis_pp[vi1][vj1] + dis_pp[vi2][vj1] + wi) / 2.0;
			int a = dis_pp[vi1][vj2] - dis_pp[vi1][vj1] + wj;
			int b = dis_pp[vi2][vj2] - dis_pp[vi2][vj1] + wj;
			int c, d;
			if (a > b) {
				c = b * 2;
				d = a * 2;
			}
			else {
				c = a * 2;
				d = b * 2;
			}
			//cout <<  "  " << f0[j][i] << ' ' << a << ' ' << b << ' ' << c << ' ' << d << endl;
			int tmp = 4 * wj;
			for (int k = 0; k < c; k++) {
				fjil2[j][i][k] = 1;
			}
			for (int k = c; k < d; k++) {
				fjil2[j][i][k] = 0;
			}
			for (int k = d; k < tmp; k++) {
				fjil2[j][i][k] = -1;
			}
		}
	}
	//ע�⣬���ϵ�fjj�Ǵ���ģ��������洦��
	/*
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < m; i++) {
			cout << f0[j][i] << ' ';
			int tmp = 4 * road2[j][2];
			for (int k = 0; k < tmp; k++) {
				cout << fjil2[j][i][k] + 1;
			}
			cout << endl;
		}
		cout << endl;
	}
	*/
	//������Fjl2��F0
	for (int j = 0; j < m; j++) {
		//��fjj��Ϊ��ʼ��
		int tmp = 4 * road2[j][2];
		F0[j] = road2[j][2] + 0.0;
		for (int i = 0; 2 * i < tmp; i++) {
			Fjl2[j][i] = -1;
		}
		for (int i = tmp / 2; i < tmp; i++) {
			Fjl2[j][i] = 1;
		}
		//��һ�Ƚ�fji��Fj
		for (int i = 0; i < m; i++) {
			if (i != j) {
				double tmpi = f0[j][i];//����fji(k/2wj)
				double tmpj = F0[j];//����Fj(k/2wj)
				if (F0[j] < f0[j][i]) {
					F0[j] = f0[j][i];
				}
				//cout << tmpi << ' ' << tmpj << ' ';
				for (int k = 0; k < tmp; k++) {
					tmpi += 0.25 * fjil2[j][i][k];
					tmpj += 0.25 * Fjl2[j][k];
					//cout << tmpi << ' ' << tmpj << ' ';
					if ((tmpi > tmpj) || ((tmpi == tmpj) && (Fjl2[j][k] > fjil2[j][i][k]))) {
						Fjl2[j][k] = fjil2[j][i][k];
					}
				}
				///cout << endl << endl;
			}
		}
	}
	/*
	cout << "2out" << endl;
	for (int j = 0; j < m; j++) {
		cout << F0[j] << ' ';
		int tmp = 4 * road2[j][2];
		for (int k = 0; k < tmp; k++) {
			cout << Fjl2[j][k] + 1;
		}
		cout << endl;
	}
	*/
	//������answer[]
	for (int i = 0; i < m; i++) {
		answer[i] = F0[i];
		int num = 0;//����
		for (int k = 0, tmp = 4 * road2[i][2], tmp_num = 0; k < tmp; k++) {
			tmp_num += Fjl2[i][k];
			if (num > tmp_num) {
				num = tmp_num;
			}
		}
		answer[i] += 0.25 * num;
	}
	//������final_answer
	final_answer = answer[0];
	for (int i = 1; i < m; i++) {
		if (final_answer > answer[i]) {
			final_answer = answer[i];
		}
	}
	cout << setiosflags(ios::fixed) << setprecision(2) << final_answer;
	return 0;
}