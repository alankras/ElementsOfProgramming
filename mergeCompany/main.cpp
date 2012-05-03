#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;
const int maxint = ((unsigned)(-1) >> 1);

void process(int N, int D, vector<vector<int> >& stat, vector<int>& min_level, vector<int>& next, vector<int>& now_comp) {
	for (int i = 0; i < N - 1; i++) {
		int m1, m2;
		cin >> m1 >> m2;
		m1--;
		m2--;
		int pr1 = now_comp[m1];
		int pr2 = now_comp[m2];
		if (pr1 > pr2) swap(pr1, pr2);
		next[0] = maxint;
		int min_l = maxint;
		for (int j = 1; j <= D; j++) {
			next[j] = min(max(stat[pr1][j - 1], min_level[pr2] + 1), max(stat[pr2][j - 1], min_level[pr1] + 1));
			min_l = min(min_l, next[j]);
		}
		for (int j = 0; j < N; j++) {
			if (now_comp[j] == pr2) now_comp[j] = pr1;
		}
		for (int j = 0; j <= D; j++) {
			stat[pr1][j] = next[j];
		}
		min_level[pr1] = min_l;
	}
}

void init(int N, int D, vector<vector<int> >& stat, vector<int>& min_level, vector<int>& next, vector<int>& now_comp) {
		for (int i = 0; i < N; i++) {
			now_comp[i] = i;
			stat[i][0] = 1;
			for (int j = 1; j <= D; j++) {
				stat[i][j] = maxint;
			}
			min_level[i] = 1;
		}
}

void mergeCompany(int T) {
	for(int tc = 1; tc <= T; tc++) {
		int N, D;
		cin >> N >> D;
		vector<int> now_comp(N);
		vector<vector<int> > stat(N, vector<int> (D + 1));
		vector<int> min_level(N);
		vector<int> next(N);
		init(N, D, stat, min_level, next, now_comp);
		process(N, D, stat, min_level, next, now_comp);
		cout << "Case #" << tc << ": " << min_level[0] << endl;
	}
}

int main() {
	int T;
	cin >> T;
	mergeCompany(T);
	return 0;
}