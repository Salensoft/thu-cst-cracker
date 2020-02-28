#include <iostream>
#include <iomanip>
using namespace std;

int d_point[101];//��1-100�����Ķ�
int road[101][501][2];//��1-100�����ĵ�1-500���ߣ���β��㡢�߳���
int m = 0, n = 0;
int is_visited[101];//Dijkstra�㷨�Ƿ�Ϊ���ý��
int distance_p2p[101][101];//�㵽�����
int road2[501][3];
//double distance_p2s[101][501];//�㵽�߾���
double max_distance[101];//���������
int infdis = 500000;

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
	//test
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
			distance_p2p[i][j] = infdis;
			is_visited[j] = 0;
		}
		distance_p2p[i][i] = 0;
		for (int num_S = n; num_S > 0;) {
			//����b
			int j = -1, Pj = infdis;
			for (int k = 1; k <= n; k++) {
				if ((is_visited[k] == 0) && (distance_p2p[i][k] < Pj)) {
					Pj = distance_p2p[i][k];
					j = k;
				}
			}
			is_visited[j] = 1;
			num_S--;
			//cout << j << ' ' << Pj << ' ' << num_S << endl;
			if (num_S == 0) {
				break;
			}
			//����c
			for (int k = 0; k < d_point[j]; k++) {
				int ed = road[j][k][0];
				//cout << ed << ' ' << (is_visited[ed] == 0) << ' ' << distance_p2p[i][ed] << ' ' << Pj + road[j][k][1] << ' ' << (distance_p2p[i][ed] > Pj + road[j][k][1]) << endl;
				if ((is_visited[ed] == 0) && (distance_p2p[i][ed] > Pj + road[j][k][1])) {
					distance_p2p[i][ed] = Pj + road[j][k][1];
				}
			}
			//cout << endl;
		}
		//cout << i << " is finished" << endl << endl;
	}
	/*
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << distance_p2p[i][j] << ' ';
		}
		cout << endl;
	}
	*/
	//������p2s
	for (int i = 1; i <= n; i++) {
		max_distance[i] = -1;
		for (int j = 0; j < m; j++) {
			double tmp_distance = (distance_p2p[i][road2[j][0]] + distance_p2p[i][road2[j][1]] + road2[j][2]) / 2.0;
			if (max_distance[i] < tmp_distance) {
				max_distance[i] = tmp_distance;
			}
		}
	}
	double min_maxdis = infdis;
	for (int i = 1; i <= n; i++) {
		if (min_maxdis > max_distance[i]) {
			min_maxdis = max_distance[i];
		}
	}
	cout << setiosflags(ios::fixed) << setprecision(2) << min_maxdis;
	return 0;
}