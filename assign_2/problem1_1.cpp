#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

#include <sys/time.h>

#define RUN 100

using namespace std;

typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp ()
{
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

string str_rand(int length) {
    char tmp;							// tmp: 暂存一个随机数
    string buffer;						// buffer: 保存返回值

    random_device rd;					// 产生一个 
    default_random_engine random(rd());	// 用 rd 初始化一个随机数
    
    for (int i = 0; i < length; i++) {
        tmp = random() % 26;
        tmp += 'A';
        buffer += tmp;
    }
    return buffer;
}

int delta = 10;
int w = 1;

int find_common_substring(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();

    int opt[m+1][n+1];

    for (int i=0; i<m+1; i++) {
        opt[i][0] = 0;
    }
    for (int j=0; j<n+1; j++) {
        opt[0][j] = 0;
    }

    for (int i=1; i<m+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (s1[i-1] == s2[j-1]) {
                opt[i][j] = opt[i-1][j-1] + w;
            }
            else {
                opt[i][j] = max(0, opt[i-1][j-1] - delta);
            }
            // cout << opt[i][j] << endl;
        }
    }

    int max_opt = 0, max_i = 0, max_j = 0;
    for (int i=1; i<m+1; i++) {
        for (int j=1; j<n+1; j++) {
            if (opt[i][j] > max_opt) {
                max_opt = opt[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    cout << max_i << "," << max_j << endl;

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
    // string s1;
    // string s2;

    // cout << "Input the first sequence: " << endl;
    // cin>>s1;
    // cout << "Input the second sequence: " << endl;
    // cin>>s2;
    int step = 10;
    ofstream outfile("time1.txt");
    for (int i=1; i<=RUN; i++) {
        int seq_l = i*step;
        string s1;
        string s2;
        s1 = str_rand(seq_l);
        s2 = str_rand(seq_l);
        timestamp_t t0 = get_timestamp();
        find_common_substring(s1, s2);
        timestamp_t t1 = get_timestamp();
        double secs = (t1 - t0) / 1000000.0L;
        outfile << secs << endl;
        cout << endl;
    }
    outfile.close();

    
    // timestamp_t t0 = get_timestamp();
    // find_common_substring(s1, s2);
    // timestamp_t t1 = get_timestamp();

    return 0;
}