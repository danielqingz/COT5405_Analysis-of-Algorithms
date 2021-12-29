#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <random>
#include <map>

#include <sys/time.h>

#define RUN 10

using namespace std;

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp (){
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

vector<float> vec_rand(int length) {
    vector<float> buffer;

    buffer.insert(buffer.begin(), float(0));

    random_device rd;
    default_random_engine random(rd());

    for (int i = 1; i < length; i++) {
        buffer.push_back(random());
    }
    return buffer;
}

int delta = 1;

void find_interval(vector<int> seq_list_x, vector<float> seq_list_y) {
    int n = seq_list_x.size();
    int m = *max_element(seq_list_x.begin(), seq_list_x.end());
    // reduce running time
    float error[n+1][n+1];
    memset(error, 0, sizeof(error));
    float a,b,c;
    for (int i=1; i<=n; i++) {
        a = 0;
        b = 0;
        c = 0;
        for (int j=i; j<=n; j++) {
            a += seq_list_y[j];
            b = a/(j-i+1);
            c += pow(seq_list_y[j],2);
            error[j][i] = c+(j-i+1)*pow(b,2)-2*a*b;
            // cout << "error[j][i]: " << error[j][i] << endl; 
        }
    }

    double opt[n+1];
    opt[0] = double(0);
    double min_tmp;
    for (int j=1; j<=n; j++) {
        min_tmp = error[j][1] + delta;
        opt[j] = min_tmp;
        for (int i=1; i<=j; i++) {
            if (error[j][i] + delta + opt[i-1] < min_tmp) {
                min_tmp = error[j][i] + delta + opt[i-1];
                opt[j] = min_tmp;
            }
        }
        // cout << "opt[j]: " << opt[j] << endl;
    }


    int idx = n;
    vector< int > res;
    int count = 1;
    res.push_back(m);
    while(idx>1) {
        for (int i=1; i<idx+1; i++) {
            if ((error[idx][i] + delta + opt[i-1])==opt[idx]) {
                res.push_back(seq_list_x[i]);
                count++;
                if (i-1!=0) {
                    res.push_back(seq_list_x[i-1]);
                }
                idx = i-1;
                // if (idx==1) {
                //     goto stop;
                // }
                break;
            }
        }
    }
    // stop:

    int res_lenght = res.size();

    for (int i=res_lenght; i>2; i--) {
        cout << res[i-1] << '-' << res[i-2] << endl;
        i-=1;
    }

}

int main() {
    vector< int > seq_list_x;
    vector< float > seq_list_y;

    srand(time(NULL));

    ifstream seq_list_file("seq_list.txt");
    if (!seq_list_file) {
        cout << "Failed to read points!" << endl;
        exit(0);
    }
    string line;
    while (getline(seq_list_file, line)) {
        vector<float> result;
        stringstream s_stream(line);
        while (s_stream.good()) {
            string substr;
            getline(s_stream, substr, '\t');
            result.push_back(stof(substr));
        }
        seq_list_x.push_back((int)result[0]);
        seq_list_y.push_back(result[1]);
    }
    
    seq_list_x.insert(seq_list_x.begin(), int(0));
    seq_list_y.insert(seq_list_y.begin(), float(0));

    double time_total = 0;
    for (int i=0; i<RUN; i++) {
        timestamp_t t0 = get_timestamp();
        find_interval(seq_list_x, seq_list_y);
        timestamp_t t1 = get_timestamp();
        double secs = (t1 - t0) / 1000000.0L;
        time_total += secs;
        cout << endl;
    }
    cout << "Average time cost: " << time_total/10 << endl;

    return 0;
}