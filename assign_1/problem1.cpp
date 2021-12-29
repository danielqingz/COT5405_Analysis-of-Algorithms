#include <iostream>
#include <set>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>

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


void create_graph(int NUM, int NUMEDGE) {
    set<pair<int, int> > container;
	set<pair<int, int> >::iterator it;

    for (int j=1; j<=NUMEDGE; j++)
    {
        int a = rand() % NUM;
        int b = rand() % NUM;
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
        edges.push_back({a, b});
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

vector<vector<int> > find_cycle(vector<vector<int>>& edges) {
    vector<vector<int> > cycle;
    int nodesCount = edges.size();
    vector<int> parent(nodesCount + 1);
    for (int i = 1; i <= nodesCount; ++i) {
        parent[i] = i;
    }
    for (auto& edge: edges) {
        int node1 = edge[0], node2 = edge[1];
        if (Find(parent, node1) != Find(parent, node2)) {
            Union(parent, node1, node2);
            cycle.push_back({edge[0],edge[1]});
        } else {
            // cout << "Find cycle!" << endl;
            return cycle;
            break;
        }
    }
    return vector<vector<int>>{};
}


int main() {
    vector<vector<int> > cycle;
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
    // for(int i=0;i<edges.size();i++){
    //     cout<<"["<<edges[i][0]<<","<<edges[i][1]<<"]"<<endl;
    // }

    /*****  automatically generate for experiment *****/
    ofstream outfile("time1.txt");
    for (int i=1; i<=RUN; i++) {
        int NUM = i*50; // Number of Vertices
	    int NUMEDGE = i*50; // Number of Edges

        create_graph(NUM, NUMEDGE);

        timestamp_t t0 = get_timestamp();
        cycle = find_cycle(edges);

        timestamp_t t1 = get_timestamp();

        double secs = (t1 - t0) / 1000000.0L;

        outfile << secs << endl;
    }
    outfile.close();

    /*********  evaluation on test case *********/
    // cycle = find_cycle(edges);
    // for (int i=0; i<cycle.size(); i++) {
    //     cout << cycle[i][0] << "-" << cycle[i][1] << " -> ";
    // }
    // cout << endl;

	return(0);
}
