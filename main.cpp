// https://terms.naver.com/entry.nhn?cid=58944&docId=3574654&categoryId=58970
#include <bits/stdc++.h>
using namespace std;


int T, p, q;
int posA, posB;
int cycleStartPos;
int nineMK;

int getGCD(int a, int b) {
	if (b == 0)
		return a;
	return getGCD(b, a%b);
}

bool isNotINF() {
	int q2 = q;
	posA = posB = 0;
	while (q2 % 2 == 0) {
		q2 /= 2;
		posA++;
	}
	while (q2 % 5 == 0) {
		q2 /= 5;
		posB++;
	}

	cycleStartPos = max(posA, posB);

	nineMK = q2;
	if (q2 == 1)
		return true;
	else
		return false;
}

int getDist() {
	// make (10^N)-1 sample : 9, 99, 999, 19, 29, 2999, 29999
	int temp = 9 % nineMK;
	int ret = 1;

	while (temp != 0) {
		ret++;
		temp = temp * 10 + 9;
		temp = temp % nineMK;
	}
	
	return ret;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> p >> q;
		int d = getGCD(p, q);
		p /= d;
		q /= d;
		string ans = to_string(p / q);

		if (p % q == 0 || isNotINF()) {
			// 유한소수 표현 가능
			p = p % q * 10;

			if (p != 0)
				ans += '.';
			while (p != 0) {
				ans += p / q + '0';
				p = p % q * 10;
			}

		}
		else {
			// 무한소수 (또는 순환하는 무한소수)
			int cycleDist = getDist();
			ans += '.';

			for (int i = 0; i < cycleStartPos; i++) {
				p = p % q * 10;
				ans += p / q + '0';
			}
			
			ans += '(';
			p = p % q * 10;
			
			for (int i = 0; i < cycleDist; i++) {
				ans += p / q + '0';
				p = p % q * 10;
			}
			ans += ')';
		}

		cout << "#" << tc << " " << ans << "\n";
	}
	
	return 0;
}