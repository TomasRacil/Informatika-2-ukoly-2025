#include <bits/stdc++.h>

/*using namespace std;
typedef long long ll;

#define MOD 2147483647

int main(){	
	ll a = 65, b = 8921;
	int ans1 = 0, ans2 = 0;

	// part 1
	for(int i = 0; i < 40000000; i++) {
		a *= 16807;
		a %= MOD;
		b *= 48271;
		b %= MOD;

		bitset<16> tmp1(a), tmp2(b);
		if(tmp1 == tmp2) {
			ans1++;
		}
	}
	cout << ans1 << endl;
	return 0;
}*/

long generator (long previous, int factor){
    return (previous * factor) % 2147483647;
}

bool compare_last_bits(long a, long b){

}
int generation(long a_start, long b_start, int steps){
    long a_result = a_start;
    long b_result = b_start;
    int pocet_shod = 0;
    for (int i = 0; i < steps; i++){
        a_result = generator(a_result, 16807);
        b_result = generator(b_result, 48271);
        if (compare_last_bits(a_result, b_result)){
            pocet_shod++;
        }
    }
    return pocet_shod;
}