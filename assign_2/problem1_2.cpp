#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include <sys/time.h>

using namespace std;

typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp ()
{
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

float l_freq[26] = {8.4966, 2.072, 4.5388, 3.3844, 11.1607, 1.8121, 2.4705, 3.0034, 7.5448, 0.1965, 1.1016, 5.4893, 3.0129, 6.6544, 7.1635, 3.1671, 0.1962, 7.5809, 5.7351, 6.9509, 3.6308, 1.0074, 1.2899, 0.2902, 1.7779, 0.2722};
float l_min = *min_element(l_freq, l_freq+26);
float l_max = *max_element(l_freq, l_freq+26);

int find_common_substring(string s1, string s2, float delta) {
    int m = s1.length();
    int n = s2.length();

    float opt[m+1][n+1];

    for (int i=0; i<m+1; i++) {
        opt[i][0] = 0;
    }
    for (int j=0; j<n+1; j++) {
        opt[0][j] = 0;
    }

    for (int i=1; i<m+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (s1[i-1] == s2[j-1]) {
                opt[i][j] = opt[i-1][j-1] + l_freq[int(s1[i-1])-int('A')];
            }
            else {
                opt[i][j] = max(float(0), opt[i-1][j-1] - delta);
            }
            // cout << opt[i][j] << endl;
        }
    }

    float max_opt = 0;
    int max_i = 0, max_j = 0;
    for (int i=1; i<m+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (opt[i][j] > max_opt) {
                max_opt = opt[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    // cout << max_i << "," << max_j << endl;

    int max_ij = max(max_i, max_j);
    string res1;
    string res2;

    for (int i=0; i<max_ij; i++) {
        if (opt[max_i-i][max_j-i]==0) break;
        else {
            res1.push_back(s1[max_i-i-1]);
            res2.push_back(s2[max_j-i-1]);
        }
    }

    reverse(res1.begin(), res1.end());
    reverse(res2.begin(), res2.end());

    cout << res1 << endl;
    cout << res2 << endl;

    
    return 0;
}

int main() {
    srand(time(NULL));

    string s1;
    string s2;

    cout << "Input the first sequence: " << endl;
    cin>>s1;
    cout << "Input the second sequence: " << endl;
    cin>>s2;

    float delta[10] = {};

    for (int i=0; i<10; i++) {
        delta[i] = 0.1962 + i*(11.1607-0.1962)/9;
        cout << "Experiment " << i << endl;
        cout << "delta=" << delta[i] << endl;
        timestamp_t t0 = get_timestamp();
        find_common_substring(s1, s2, delta[i]);
        timestamp_t t1 = get_timestamp();

        double secs = (t1 - t0) / 1000000.0L;

        cout << "Time cost: " << secs << endl;

        cout << endl;
    }
    // find_common_substring(s1, s2, 1);
    
    return 0;
}