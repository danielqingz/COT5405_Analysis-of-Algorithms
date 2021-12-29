#include <iostream>
#include <set>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>
#include<algorithm>

#include <sys/time.h>

#define RUN 1000

typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp ()
{
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

using namespace std;

vector<vector<int> > edges;
vector<vector<int> > spanning_tree;


void create_graph(int NUM, int NUMEDGE) {
    set<pair<int, int> > container;
	set<pair<int, int> >::iterator it;

    for (int j=1; j<=NUMEDGE; j++)
    {
        int a = rand() % NUM;
        int b = rand() % NUM;
        int weight = rand()%100+1;
        pair<int, int> p = make_pair(a, b);
        pair<int, int> reverse_p = make_pair(b, a);

        while (container.find(p) != container.end() ||
                container.find(reverse_p) != container.end() || a == b)
        {
            a = rand() % NUM;
            b = rand() % NUM;
            p = make_pair(a, b);
            reverse_p = make_pair(b, a);
        }
        container.insert(p);
        edges.push_back({a, b, weight});
    }

    container.clear();
    printf("\n");
}

int Find(vector<int>& parent, int index) {
    if (parent[index] != index) {
        parent[index] = Find(parent, parent[index]);
    }
    return parent[index];
}

void Union(vector<int>& parent, int index1, int index2) {
    parent[Find(parent, index1)] = Find(parent, index2);
}

int MST(vector<vector<int>>& edges) {
    int nodes_count = edges.size();
    int count = 0;
    int total_weight = 0;
    vector<int> parent(nodes_count + 1);
    for (int i = 1; i <= nodes_count; ++i) {
        parent[i] = i;
    }
    for (auto& edge: edges) {
        int node1 = edge[0], node2 = edge[1], weight = edge[2];
        if (Find(parent, node1) != Find(parent, node2)) {
            Union(parent, node1, node2);
            count++;
            total_weight = total_weight + weight;
            spanning_tree.push_back({node1,node2});
            if (count==nodes_count) {
                return total_weight;
            }
        }
    }
    return total_weight;
}


int main() {
    int MST_weight;
	//For random values every time
	srand(time(NULL));

    /*******  Test case by manually inputting *******/
	// int NUM; // Number of Vertices
	// int NUMEDGE; // Number of Edges
    // cout << "Input number of vertices: " << endl;
    // cin>>NUM;
    // cout << "Input number of edges: " << endl;
    // cin>>NUMEDGE;
    // create_graph(NUM, NUMEDGE);
    // sort(edges.begin(),edges.end(),[](vector<int>& a,vector<int>& b){
    //     return a[2]<b[2];
    // });
    // for(int i=0;i<edges.size();i++){
    //     cout<<"["<<edges[i][0]<<","<<edges[i][1]<<"]"<<"weight: "<<edges[i][2]<<endl;
    // }


    ofstream outfile("time2.txt");

    for (int i=1; i<=RUN; i++) {
        int NUM = i*10; // Number of Vertices
	    int NUMEDGE = rand()%(NUM+8)+1; // Number of Edges

        create_graph(NUM, NUMEDGE);

        timestamp_t t0 = get_timestamp();

        sort(edges.begin(),edges.end(),[](vector<int>& a,vector<int>& b){
            return a[2]<b[2];
        });

        MST_weight = MST(edges);

        /******  Plot spanning tree  ******/
        // for (int i=0;i<spanning_tree.size();i++) {
        //     cout<<"["<<spanning_tree[i][0]<<","<<spanning_tree[i][1]<<"]"<<endl;
        // }
        // cout << MST_weight << endl;

        timestamp_t t1 = get_timestamp();

        double secs = (t1 - t0) / 1000000.0L;

        outfile << secs << endl;
    }

    outfile.close();

	return(0);
}
