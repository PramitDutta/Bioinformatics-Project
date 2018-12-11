#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <map>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <ctime>

#define PATTERN_1 2
#define PATTERN_2 3
#define PATTERN_3 5

using namespace std;

int nodeSize;
int **edges; // edge matrix
int edgeSize;
int **edges_static; // edge matrix
int edgeSize_static;

int nodeSize_dynamic;
int **edges_dynamic; // edge matrix in dynamic
int edgeSize_dynamic;

int **edges_motif;

map<string, int> mapping; //map node name to 0,1,2,3..
map<string, int>::iterator mapIter;
int lastMapped = 0;
int comb2(int a)
{
    return (a) * (a-1) /2;
}
int comb3(int a)
{
    return (a) * (a-1) * (a - 2) /6;
}

int addedNodes[100];
int noOfAddedNodes = 0;
int deletedNodes[100];
int noOfDeletedNodes = 0;
//int addedEdges[100][2];
int noOfAddedEdges = 0;
//int deletedEdges[100][2];
int noOfDeletedEdges = 0;


//map<pair<int, int>, int> edge_dynamic_info; // Maps an edge(2 nodes to a value which is tells whether it is part of motif */
typedef pair<int, int> key_edge;
typedef pair<key_edge, key_edge> key_edge_pair;
struct edge_info {
	int n1;
	int n2;
};

struct edge_pair {
	edge_info e1;
	edge_info e2;
};
map<int, key_edge> temp_p3;
map<int, key_edge>::iterator temp_p3_it;
map<key_edge, key_edge_pair> motif_3;
map<key_edge, key_edge_pair>::iterator motif_3_it;
map<key_edge, int> addedEdges;
map<key_edge, int>::iterator addedEdges_it;
map<key_edge, int> deletedEdges;
map<key_edge, int>::iterator deletedEdges_it;
void printMotif_3()
{
    cout<< endl;
    		for (motif_3_it = motif_3.begin(); motif_3_it != motif_3.end();		++motif_3_it)
                {
				    cout << "(" << (motif_3_it->first).first <<  "," << (motif_3_it->first).second << ") ";
				    cout << "(" << (motif_3_it->second).first.first <<  "," << (motif_3_it->second).first.second << ") " ;
				    cout << "(" << (motif_3_it->second).second.first <<  "," << (motif_3_it->second).second.second << ") " << endl;
				}
				cout<< endl;
}

//list<key_edge> temp_3;
//list<key_edge>::iterator temp_3_it;

list<key_edge> temp3;
list<key_edge>::iterator temp3_it;

map<key_edge, int> edge_temp_info;
map<key_edge, int>::iterator edge_temp_info_it;
map<key_edge, key_edge> edge_dynamic_info;
map<key_edge, key_edge>::iterator edge_dynamic_info_it;
map<key_edge, key_edge> edge_dynamic_info3;
map<key_edge, key_edge>::iterator edge_dynamic_info3_it;
typedef pair<int, int> value_edge;
map<int, edge_info> temp;
map<int, edge_info>::iterator temp_it;

//map<int, value_edge> temp;
//map<int, value_edge>::iterator temp_it;

list<int> connectedNodes;
map<int, list<int>*> connectedList;
list<int>::iterator iter;
map<int, list<int>*>::iterator listIter;


enum VertexState {
	White, Gray, Black
};

int f2_p0;
int f2_p1;
int f2_p2;
int f2_p3;

long f1_p0;
long f1_p1;
long f1_p2;
long f1_p3;

int *A;
int *B;
int *C;
int *D;

struct Motif {
	int d;
	int *e;
};

list<Motif*> motif_list1;

bool compDe(const Motif* a, const Motif* b) {
	return a->d < b->d;
}

int returnUnique(int** arr, int index1, int index2)
{
    if(index1 < index2)
    {
        return arr[index1] [index2];
    }
    return 0;
}

key_edge g_ke[1000];
void EdgeRandomiser(int n)
{
    cout << "b4 swap :";
    for(int i = 0; i < n ; i++)
    {
        cout << "(" << g_ke[i].first<< ","<<g_ke[i].second << ") ";
    }
    cout << endl;
    for(int i = n-1; i > 0; i--)
    {
        int r = rand() % (i+1);
        key_edge temp_r = g_ke[r];
        g_ke[r] = g_ke[i];
        g_ke[i] = temp_r;
    }
    cout << "after swap :";
    for(int i = 0; i < n ; i++)
    {
        cout << "(" << g_ke[i].first<< ","<<g_ke[i].second << ") ";
    }
    cout << endl;
}

bool GetAvailableNbEdges_Motif_3(key_edge ke_rand, key_edge exclude_edge, int isExcludeEdge)
{
    cout << "here at func GetAvailableNbEdges_Motif_3" << endl;
    int k = 0;

    int r = rand() % 2;
    int ker1, ker2;

    if(r==1)
    {
        ker1 = ke_rand.first;
        ker2 = ke_rand.second;
    }
    else
    {
        ker1 = ke_rand.second;
        ker2 = ke_rand.first;
    }

    for(int i = 0; i < nodeSize; i++)
    //for(int i = 0; i < nodeSize_dynamic; i++)
    {
        key_edge kedge1, kedge2;

        if(edges_static[i][ker1] == 1)
        //if(edges_dynamic[i][ker1] == 0)
        {
            key_edge keys;
            keys.first = min(i, ker1);
            keys.second = max(i, ker1);
            if(edge_temp_info.find(keys) != edge_temp_info.end())
            {
                continue;
            }
        }
        else
        {
            continue;
        }

        kedge1.first = min(i, ker1);
        kedge1.second = max(i, ker1);

        if(isExcludeEdge == 1)
        {

            if((exclude_edge == kedge1) || (kedge1 == ke_rand))
            {
                continue;
            }

        }
        if(motif_3.find(kedge1) != motif_3.end())
        {
            continue;
        }

        g_ke[k++] = kedge1;

    }

    if(k > 1)
    {
        cout << "b4 rand1" << endl;

        EdgeRandomiser(k);
        for(int p = 0; p < k; p++)
        {
            cout << "1.Edge rand = (" << g_ke[p].first <<  "," << g_ke[p].second << ") ";
        }
        cout << "after rand" << endl;
        cout << endl;
        return true;
    }
    else
    {

        cout << "k less than 1" << endl;
    }

    k = 0;
    for(int i = 0; i < nodeSize; i++)
    //for(int i = 0; i < nodeSize_dynamic; i++)
    {
        key_edge kedge2;

        if(edges_static[i][ker2] == 1)
        //if(edges_dynamic[i][ker2] == 0)
        {
            key_edge keys;
            keys.first = min(i, ker2);
            keys.second = max(i, ker2);
            if(edge_temp_info.find(keys) != edge_temp_info.end())
            {
                continue;
            }
        }
        else
        {
            continue;
        }
        kedge2.first = min(i, ker2);
        kedge2.second = max(i, ker2);
        if(isExcludeEdge)
        {

            if((exclude_edge == kedge2) || (kedge2 == ke_rand))
            {
                continue;
            }


        }
        if(motif_3.find(kedge2) != motif_3.end())
        {
            continue;
        }
        g_ke[k++] = kedge2;
    }
    if(k > 1)
    {
        cout << "b4 rand2" << endl;

        EdgeRandomiser(k);
        for(int p = 0; p < k; p++)
        {
            cout << "2.Edge rand = (" << g_ke[p].first <<  "," << g_ke[p].second << ") ";
        }
        cout << "after rand1" << endl;
        cout << endl;
        return true;
    }
    else
    {

        cout << "2. k less than 1" << endl;
    }
    return false;
}

bool GetAvailableNbEdges_Motif_3_Add(key_edge ke_rand, key_edge exclude_edge, int isExcludeEdge)
{
    cout << "here at func GetAvailableNbEdges_Motif_3_Add" << endl;
    int k = 0;

    int r = rand() % 2;
    int ker1, ker2;

    if(r==1)
    {
        ker1 = ke_rand.first;
        ker2 = ke_rand.second;
    }
    else
    {
        ker1 = ke_rand.second;
        ker2 = ke_rand.first;
    }

    for(int i = 0; i < nodeSize_dynamic; i++)
    {
        key_edge kedge1, kedge2;
#if 0
        if(edges_dynamic[i][ker1] == 0)
        {
            continue;
        }
        #endif
        if(edges_dynamic[i][ker1] == 1)
        //if(edges_dynamic[i][ker1] == 0)
        {
            key_edge keys;
            keys.first = min(i, ker1);
            keys.second = max(i, ker1);
            if(edge_temp_info.find(keys) != edge_temp_info.end())
            {
                continue;
            }
        }
        else
        {
            continue;
        }

        kedge1.first = min(i, ker1);
        kedge1.second = max(i, ker1);

        if(isExcludeEdge == 1)
        {

            if((exclude_edge == kedge1) || (exclude_edge == ke_rand))
            {
                continue;
            }

        }
        if(motif_3.find(kedge1) != motif_3.end())
        {
            continue;
        }

        g_ke[k++] = kedge1;

    }

    if(k > 1)
    {

        EdgeRandomiser(k);
        for(int p = 0; p < k; p++)
        {
            cout << "1.Edge rand = (" << g_ke[p].first <<  "," << g_ke[p].second << ") ";
        }
        cout << endl;
        return true;
    }

    k = 0;
    for(int i = 0; i < nodeSize_dynamic; i++)
    {
        key_edge kedge2;

        //if(edges_dynamic[i][ker2] == 0)
        //{

          //  continue;
        //}
        if(edges_dynamic[i][ker2] == 1)
        //if(edges_dynamic[i][ker1] == 0)
        {
            key_edge keys;
            keys.first = min(i, ker2);
            keys.second = max(i, ker2);
            if(edge_temp_info.find(keys) != edge_temp_info.end())
            {
                continue;
            }
        }
        else
        {
            continue;
        }
        kedge2.first = min(i, ker2);
        kedge2.second = max(i, ker2);
        if(isExcludeEdge)
        {

            if((exclude_edge == kedge2) || (exclude_edge == ke_rand))
            {
                continue;
            }


        }
        if(motif_3.find(kedge2) != motif_3.end())
        {
            continue;
        }
        g_ke[k++] = kedge2;
    }
    if(k > 1)
    {

        EdgeRandomiser(k);
        for(int p = 0; p < k; p++)
        {
            cout << "2.Edge rand = (" << g_ke[p].first <<  "," << g_ke[p].second << ") ";
        }
        cout << endl;
        return true;
    }
    return false;
}

void loadData(char* fileName) {
	ifstream in(fileName, ifstream::in);
	if (!in.is_open()) {
		cout << "Error opening file 2" << endl;
		exit(1);
	}
	else
    {
        cout << "Data file opened successfully." << endl;
    }
	in >> nodeSize;
	in >> edgeSize;

	cout << "node size = " << nodeSize << " edge size = " << edgeSize << endl;

	int srcNode, dstNode;
	edges = new int*[nodeSize];
	edges_static = new int*[nodeSize];
	edges_motif = new int*[nodeSize];
	for (srcNode = 0; srcNode < nodeSize; srcNode++) {
		edges[srcNode] = new int[nodeSize]();
		edges_static[srcNode] = new int[nodeSize]();
		edges_motif[srcNode] = new int[nodeSize]();
		for (int i = 0; i < nodeSize; i++)
        {
            edges_motif[srcNode][i] = 1; /* 2 for pattern 1, 3 for pattern 2, 5 for pattern 3 */

            //for(int i = 0; i < nodeSize; i++)
            //{
                //edge_dynamic_info.insert(make_pair(key_edge(srcNode, i),1));
            //}
        }

	}

	string srcName, dstName;
	while (!in.eof()) {
		//check if the file is not formatted good
		if (!(in >> srcName >> dstName))
			break;
			cout << "src name =" << srcName << endl;

		if (mapping.find(srcName) == mapping.end()) {
            mapping[srcName] = lastMapped;
			cout << "map src name =" << srcName << "last mapped = " << lastMapped << endl;
			lastMapped++;

		}
		if (mapping.find(dstName) == mapping.end()) {
			mapping[dstName] = lastMapped;
			cout << "map dst name =" << dstName << "last mapped = " << lastMapped << endl;
			lastMapped++;
        }

		srcNode = mapping[srcName];
		dstNode = mapping[dstName];
		edges[srcNode][dstNode] = 1;
		cout << " i j = " << srcNode << dstNode << endl;
		edges[dstNode][srcNode] = 1;
		edges_static[srcNode][dstNode] = 1;
		edges_static[dstNode][srcNode] = 1;
	}

	in.close();

}

void loadData_dynamic(char* fileName) {
	ifstream in(fileName, ifstream::in);
	if (!in.is_open()) {
		cout << "Error opening file 4" << endl;
		exit(1);
	}
	else
    {
        cout << "Data file opened successfully." << endl;
    }
	in >> nodeSize_dynamic;
	in >> edgeSize_dynamic;

	cout << "node size = " << nodeSize_dynamic << " edge size = " << edgeSize_dynamic << endl;

	int srcNode, dstNode;
	edges_dynamic = new int*[nodeSize_dynamic];
	for (srcNode = 0; srcNode < nodeSize_dynamic; srcNode++) {
		edges_dynamic[srcNode] = new int[nodeSize_dynamic]();
	}

	string srcName, dstName;
	while (!in.eof()) {
		//check if the file is not formatted good
		if (!(in >> srcName >> dstName))
			break;
			//cout << "src name =" << srcName << endl;
		if (mapping.find(srcName) == mapping.end()) {
			mapping[srcName] = lastMapped;
			//connectedNodes.push_back(lastMapped);
			cout << "dynamic map src name =" << mapping[srcName] << "last mapped = " << lastMapped << endl;
			lastMapped++;

			addedNodes[mapping[srcName]];
			noOfAddedNodes++;


		}
		if (mapping.find(dstName) == mapping.end()) {
			mapping[dstName] = lastMapped;
			//connectedNodes.push_back(lastMapped);
			cout << "dynamic map dst name =" << mapping[dstName] << "last mapped = " << lastMapped << endl;
			lastMapped++;

			addedNodes[mapping[srcName]];
			noOfAddedNodes++;

		}
		srcNode = mapping[srcName];
		dstNode = mapping[dstName];
		edges_dynamic[srcNode][dstNode] = 1;
		//cout << " dynamic i j = " << srcNode << dstNode << endl;
		edges_dynamic[dstNode][srcNode] = 1;
	}

	in.seekg(0, ios::beg);
	int isFound = 0;

	noOfDeletedNodes = 0;
	for(mapIter = mapping.begin(); mapIter != mapping.end(); mapIter++)
    {
        isFound = 0;
        in >> nodeSize;
	    in >> edgeSize;
        while (!in.eof()) {
		    //check if the file is not formatted good
            if (!(in >> srcName >> dstName))
                return;

            cout<<"check = "<<mapping[srcName] << " "<< mapIter->second << " " << mapIter->first <<endl;
            if (mapping[srcName] == mapIter->second) {
                isFound = 1;
                break;
            }
            if (mapping[dstName] == mapIter->second) {
                isFound = 1;
                break;
            }
        }
        if(isFound == 0)
        {
            cout<<"node deleted = " << mapping[srcName] << " " << mapping[dstName] <<endl;

            deletedNodes[noOfDeletedNodes] = mapping[srcName];
            noOfDeletedNodes++;

        }
        in.seekg(0, ios::beg);
    }
    //cout << "added=" << noOfAddedNodes << " del = "<< noOfDeletedNodes << endl;

	in.close();
}

void findChangesInNetwork_dynamic()
{
    int i = 0, j = 0;
    int iterAdd = 0;
    int iterDel = 0;
    key_edge ke;

    cout << "min = " << min(nodeSize, nodeSize_dynamic) << " " << nodeSize << " " << nodeSize_dynamic;
    for(i = 0; i < min(nodeSize, nodeSize_dynamic); i++)
    {
        for(j = i + 1; j < min(nodeSize, nodeSize_dynamic); j++)
        {
            if((edges_static[i][j] == 1) && (edges_dynamic[i][j] == 0)) //edge deletion
            {
                //deletedEdges[iterDel][0] = min(i,j);
                //deletedEdges[iterDel][1] = max(i,j);
                ke.first = min(i,j);
                ke.second = max(i,j);
                deletedEdges.insert(make_pair(ke, 0));
                cout << " EDGE deleted = (" << ke.first << ","<< ke.second << ")" << endl;

                //cout << "(" << deletedEdges[iterDel][0] << ","<< deletedEdges[iterDel][1] << ") " << endl;
                iterDel++;
            }
            noOfDeletedEdges = iterDel;

            if((edges_static[i][j] == 0) && (edges_dynamic[i][j] == 1)) //edge addition
            {
                //addedEdges[iterAdd][0] = min(i,j);
                //addedEdges[iterAdd][1] = max(i,j);

                //cout << "(" << addedEdges[iterAdd][0] << ","<< addedEdges[iterAdd][1] << ")" << endl;
                ke.first = min(i,j);
                ke.second = max(i,j);

                addedEdges.insert(make_pair(ke, 0));
                iterAdd++;
            }
            noOfAddedEdges = iterAdd;
        }
    }
    for(i = min(nodeSize, nodeSize_dynamic); i < max(nodeSize, nodeSize_dynamic); i++)
    {
        for(j = 0; j < max(nodeSize, nodeSize_dynamic); j++)
        {
            if(nodeSize < nodeSize_dynamic) // edge addition
            {
                if(edges_dynamic[i][j] == 1)
                {
                    //addedEdges[iterAdd][0] = min(i,j);
                    //addedEdges[iterAdd][1] = max(i,j);
                    //cout << "(" << addedEdges[iterAdd][0] << ","<< addedEdges[iterAdd][1] << ")" << endl;
                    ke.first = min(i,j);
                    ke.second = max(i,j);
                    addedEdges.insert(make_pair(ke, 0));
                    iterAdd++;
                }
                noOfAddedEdges = iterAdd;
            }
            if(nodeSize > nodeSize_dynamic) // edge deletion            {
            {
                if(edges_static[i][j] == 1)
                {
                    //deletedEdges[iterAdd][0] = min(i,j);
                    //deletedEdges[iterAdd][1] = max(i,j);
                    //cout << "(" << deletedEdges[iterAdd][0] << ","<< deletedEdges[iterAdd][1] << ")" << endl;
                    ke.first = min(i,j);
                    ke.second = max(i,j);
                    deletedEdges.insert(make_pair(ke, 0));
                    cout << " EDGE deleted = (" << ke.first << ","<< ke.second << ")" << endl;
                    iterDel++;
                }
                noOfDeletedEdges = iterDel;
            }
        }
    }
}

void determineMotifs_dynamic()
{
    //pattern 3 key-(a,b,c)

    edge_info p3_e1, p3_e2, p3_e3,p1_e1,p1_e2,p1_e3;
    key_edge e3, e2;
    /* Edge deletion */
    int isFound_1 = 0, isFound_2 = 0;
    int isNotFound_1 = 0, isNotFound_2 = 0;
    //Pattern 3
    cout << "b4" << endl;
    printMotif_3();
    //for(int i = 0; i < noOfDeletedEdges; i++ )
    for (deletedEdges_it = deletedEdges.begin(); deletedEdges_it != deletedEdges.end(); deletedEdges_it++)
    {
        key_edge e1;
        e1.first = deletedEdges_it->first.first;
        e1.second = deletedEdges_it->first.second;
        cout<< endl << "EDGE deleted = (" << deletedEdges_it->first.first  << "," << deletedEdges_it->first.second << ")"<<endl;
        //edge_dynamic_info3_it = edge_dynamic_info3.find(e1);
        //motif_3_it = motif_3.find(e1);
        {
            int count_a = 0, count_b = 0;
            for(int j = 0; j < nodeSize; j++)
            {
                isFound_1 = 0, isFound_2 = 0;
                key_edge keys;
                keys.first = min(j,deletedEdges_it->first.first);
                keys.second = max(j,deletedEdges_it->first.first);
                int a = 1;
                if(edge_temp_info.find(keys) == edge_temp_info.end())
                {
                    a = 0;
                }
                //cout<< j << " "<<edges_static[j][deletedEdges[i][0]] << " "<<a<<endl;
                if((edges_static[j][deletedEdges_it->first.first] == 1)/* && (edge_temp_info.find(keys) == edge_temp_info.end())*/) /* Found */
                if((edges_static[j][deletedEdges_it->first.first] == 1) && (edge_temp_info.find(keys) == edge_temp_info.end()))
                //if(returnUnique(edges_static, j, deletedEdges[i][0]) == 1)
                {
                    if(j != deletedEdges_it->first.second)
                    {
                        //cout<< " CHECK_0 (" << j << "," << deletedEdges[i][0] << ")"<<endl;
                        count_a++;

                        /*
                        e2.first = min(j,deletedEdges[i][0]);
                        e2.second = max(j,deletedEdges[i][0]);
                        if(edge_dynamic_info3.find(e2) != edge_dynamic_info3.end())
                        {
                           isFound_1 = 1;
                        }
                        */
                    }
                }
                keys.first = min(j,deletedEdges_it->first.second);
                keys.second = max(j,deletedEdges_it->first.second);
                //if(edges_static[j] [deletedEdges[i][1]] == 1)
                //if((edges_static[j] [deletedEdges_it->first.second] == 1) /*&& (edge_temp_info.find(keys) == edge_temp_info.end()*/)
                if((edges_static[j] [deletedEdges_it->first.second] == 1) && (edge_temp_info.find(keys) == edge_temp_info.end()))
                {
                    //edge_temp_info.insert(make_pair(key_edge(deletedEdges[i][0], deletedEdges[i][1]), 1));

                    if(j != deletedEdges_it->first.first)
                    {
                        //cout<< " CHECK_1 (" << j << "," << deletedEdges[i][1] << ")"<<endl;
                        count_b++;
                        /*
                        e3.first = min(j,deletedEdges[i][1]);
                        e3.second = max(j,deletedEdges[i][1]);
                        if(edge_dynamic_info3.find(e3) != edge_dynamic_info3.end())
                        {
                           isFound_2 = 1;
                        }*/
                    }
                }
            }
            {
                {
                    {
                        key_edge keys;
                        /*e1.first = deletedEdges[i][0], ;
                        e1.second = deletedEdges[i][1];*/
                        keys.first = min(deletedEdges_it->first.first, deletedEdges_it->first.second);
                        keys.second = max(deletedEdges_it->first.first, deletedEdges_it->first.second);
                        cout << "Searched edge (" << deletedEdges_it->first.first<< "," << deletedEdges_it->first.second << ")"<< endl;
                        if((motif_3_it = motif_3.find(keys)) != motif_3.end())
                        {
                            f2_p3--;
                            key_edge k1,k2,k3;
                            key_edge_pair kep = motif_3_it->second;

                            cout << "Edge deleted = (" << (motif_3_it->first).first <<  "," << (motif_3_it->first).second << ") ";
                            motif_3.erase(motif_3_it->first);
                            motif_3_it = motif_3.find(kep.first);
                            cout << "Edge deleted = (" << (motif_3_it->first).first <<  "," << (motif_3_it->first).second << ") ";
                            motif_3.erase(motif_3_it->first);
                            motif_3_it = motif_3.find(kep.second);
                            cout << "Edge deleted = (" << (motif_3_it->first).first <<  "," << (motif_3_it->first).second << ") ";
                            motif_3.erase(motif_3_it->first);

                            g_ke[0] = kep.first;
                            g_ke[1] = kep.second;

                            cout << "here2" << endl;
                            EdgeRandomiser(2);

                            cout << "here3" << endl;
                            key_edge ke_ins;
                            key_edge_pair kep_ins;
                            key_edge ke_rand = g_ke[0], ke_rand2 = g_ke[1];
                            bool isTrue = false;
                            cout << "here4 (" <<  g_ke[0].first << ","<< g_ke[0].second << ")" << endl;
                            isTrue = GetAvailableNbEdges_Motif_3(ke_rand, keys/* exclude this */, 1);

                             cout << "here5" << endl;
                            int ke_rand_indx = 0;
                            key_edge_pair ep1, ep2, ep3;
                            if(isTrue == false)
                            {
                                cout << "here7 (" <<  g_ke[1].first << ","<< g_ke[1].second << ")" << endl;

                                isTrue = GetAvailableNbEdges_Motif_3(ke_rand2, keys/* exclude this */, 1);
                                if(isTrue == false)
                                {
                                    //isTrue = GetAvailableNbEdges_Motif_3(ke_rand2, motif_3_it->first/* exclude this */, 0);
                                    //ke_rand_indx = 1;
                                }
                                else
                                {
                                    ke_rand = ke_rand2;
                                    cout<< endl << "get Avail 2nd  time " << endl;
                                    ep1.first = g_ke[0];
                                    ep1.second = g_ke[1];
                                    ep2.first = ke_rand;
                                    ep2.second = g_ke[1];
                                    ep3.first = ke_rand;
                                    ep3.second = g_ke[0];
                                }
                                ke_rand_indx = 1;
                            }
                            else
                            {
                                cout<< endl << "get Avail !st time " << endl;
                                ep1.first = g_ke[0];
						        ep1.second = g_ke[1];
						        ep2.first = ke_rand;
						        ep2.second = g_ke[1];
						        ep3.first = ke_rand;
						        ep3.second = g_ke[0];
                            }
                            if(ke_rand_indx == 1)
                            {
                                //ke_rand = ke_rand2;
                            }
                            if(isTrue == true)
                            {
                                f2_p3++;


                                motif_3.insert(make_pair(ke_rand, ep1));
                                cout << "Edge added = (" << ke_rand.first <<  "," << ke_rand.second << ") ";
                                motif_3.insert(make_pair(ep1.first, ep2));
                                cout << "Edge added = (" << ep1.first.first <<  "," << ep1.first.second << ") ";
                                motif_3.insert(make_pair(ep1.second, ep3));
                                cout << "Edge added = (" << ep1.second.first <<  "," << ep1.second.second << ") ";
                            }
                        }
                    }
                }



                /*if(isFound_1 && isFound_2 && edge_dynamic_info3_it != edge_dynamic_info3.end())
                {
                    f2_p3--;
                    edge_dynamic_info3.erase(e2);
                    edge_dynamic_info3.erase(e3);
                }*/
            }
            cout<< "count_a = "<<count_a << "count_b" <<count_b<<endl;
            cout << "f1_p3 b4 = "<< f1_p3 << endl;
            f1_p3 = f1_p3 - comb2(count_a) - comb2(count_b);
            //f1_p3 = f1_p3 - comb3(count_a + 1) - comb3(count_b + 1);
            cout << "f1_p3 after = "<< f1_p3 << endl;
        }
        key_edge ins;
        ins.first = min(deletedEdges_it->first.first, deletedEdges_it->first.second);
        ins.second = max(deletedEdges_it->first.first, deletedEdges_it->first.second);
        //edge_temp_info.insert(make_pair(key_edge(deletedEdges_it->first.first, deletedEdges_it->first.second, 1));
        edge_temp_info.insert(make_pair(ins, 1));
        //motif_3.insert(make_pair(ke_rand, ep1));
    }
    edge_temp_info.clear();
    cout << "after deletion " << endl;
    printMotif_3();
    cout << "after deletion print" << endl;




    for (addedEdges_it = addedEdges.begin(); addedEdges_it != addedEdges.end(); addedEdges_it++)
    {
        key_edge e;
        e.first = addedEdges_it->first.first;
        e.second = addedEdges_it->first.second;
        p3_e1.n1 = e.first;
        p3_e1.n2 = e.second;
        //edge_dynamic_info3_it = edge_dynamic_info3.find(e);

        cout<< "EDGE added = (" << addedEdges_it->first.first  << "," << addedEdges_it->first.second << ")"<<endl;

        {
            int count_a = 0, count_b = 0;
            for(int j = 0; j < nodeSize_dynamic; j++)
            {
                int isNotFound_1 = 0, isNotFound_2 = 0;
                key_edge keys;
                keys.first = min(j,addedEdges_it->first.first);
                keys.second = max(j,addedEdges_it->first.first);

                if((edges_dynamic[j][addedEdges_it->first.first] == 1) && (edge_temp_info.find(keys) == edge_temp_info.end())) /* Found */
                //if(returnUnique(edges_static, j, deletedEdges[i][0]) == 1)
                {

                    if(j != addedEdges_it->first.second)
                    {
                        count_a++;
                        cout<< " CHECK_2 (" << j << "," << addedEdges_it->first.first << ")"<<endl;

                        /*e2.first = min(j,addedEdges[i][0]);
                        e2.second = max(j,addedEdges[i][0]);
                        p3_e2.n1 = e2.first;
                        p3_e2.n2 = e2.second;
                        if(edge_dynamic_info3.find(e2) == edge_dynamic_info3.end())
                        {
                            isNotFound_1 = 1;
                        }*/
                    }
                }

                keys.first = min(j,addedEdges_it->first.second);
                keys.second = max(j,addedEdges_it->first.second);
                if((edges_dynamic[j][addedEdges_it->first.second] == 1) && (edge_temp_info.find(keys) == edge_temp_info.end()))
                //if(returnUnique(edges_static, j, deletedEdges[i][1]) == 1)
                {
                    //edge_temp_info.insert(make_pair(key_edge(keys.first, keys.second), 1));
                    if(j != addedEdges_it->first.first)
                    {
                        count_b++;

                        cout<< " CHECK_3 (" << j << "," << addedEdges_it->first.second << ")"<<endl;

                        /*e3.first = min(j,addedEdges[i][1]);
                        e3.second = max(j,addedEdges[i][1]);
                        p3_e3.n1 = e2.first;
                        p3_e3.n2 = e2.second;
                        if(edge_dynamic_info3.find(e3) == edge_dynamic_info3.end())
                        {
                           isNotFound_2 = 1;
                        }*/
                    }

                }
                /*if(isNotFound_1 && isNotFound_2 && edge_dynamic_info3_it == edge_dynamic_info3.end())
                {
                    f2_p3++;
                    //edge_dynamic_info3.erase(e2);
                    //insert(make_pair(key_edge(p3_e.n1, p3_e.n2), key_edge(p3_e.n1, p3_e.n2)));
                    edge_dynamic_info3.insert(make_pair(key_edge(p3_e1.n1, p3_e1.n2), key_edge(p3_e1.n1, p3_e1.n2)));
                    edge_dynamic_info3.insert(make_pair(key_edge(p3_e2.n1, p3_e2.n2), key_edge(p3_e2.n1, p3_e2.n2)));
                    edge_dynamic_info3.insert(make_pair(key_edge(p3_e2.n1, p3_e2.n2), key_edge(p3_e2.n1, p3_e2.n2)));
                }*/
            }
            {
                {
                    {
                        {
                            cout << "here 10";
                            key_edge ke_rand;
                            ke_rand.first = e.first;
                            ke_rand.second = e.second;
                            bool isTrue = GetAvailableNbEdges_Motif_3_Add(ke_rand, ke_rand/* exclude this */, 1);
                            int ke_rand_indx = 0;
                            if(isTrue == true)
                            {
                                f2_p3++;

                                key_edge_pair ep1, ep2, ep3;

                                ep1.first = g_ke[0];
						        ep1.second = g_ke[1];
						        ep2.first = ke_rand;
						        ep2.second = g_ke[1];
						        ep3.first = ke_rand;
						        ep3.second = g_ke[0];

                                motif_3.insert(make_pair(ke_rand, ep1));
                                cout << "real Edge added = (" << ke_rand.first <<  "," << ke_rand.second << ") ";
                                motif_3.insert(make_pair(ep1.first, ep2));
                                cout << "real Edge added = (" << ep1.first.first <<  "," << ep1.first.second << ") ";
                                motif_3.insert(make_pair(ep1.second, ep3));
                                cout << "real Edge added = (" << ep1.second.first <<  "," << ep1.second.second << ") ";
                            }
                        }
                    }
                }
            }
            f1_p3 = f1_p3 + comb2(count_a) + comb2(count_b);
            cout<< "Edge Added count_a = "<<count_a << "count_b" <<count_b<<endl;
        }
        key_edge ins;
        ins.first = min(addedEdges_it->first.first, addedEdges_it->first.second);
        ins.second = max(addedEdges_it->first.first, addedEdges_it->first.second);
        //edge_temp_info.insert(make_pair(key_edge(deletedEdges_it->first.first, deletedEdges_it->first.second, 1));
        edge_temp_info.insert(make_pair(ins, 1));
        //edge_temp_info.insert(make_pair(key_edge(addedEdges[i][0], addedEdges[i][1]), 1));
    }
    //edge_temp_info.clear();


    cout << "after addition " << endl;
    printMotif_3();

    cout << endl << "f1_p3 = " << f1_p3 << "f2_p3 = " << f2_p3 << endl;
#if 0
    //Pattern 1 :

    for(int i = 0; i < noOfDeletedEdges; i++ )
    {
        key_edge e1;
        e1.first = deletedEdges[i][0];
        e1.second = deletedEdges[i][1];
        //cout<< "EDGE deleted = (" << deletedEdges[i][0]  << "," << deletedEdges[i][1] << ")"<<endl;
        edge_dynamic_info_it = edge_dynamic_info.find(e1);
        {
            int count_a = 0;
            for(int j = 0; j < nodeSize; j++)
            {
                isFound_1 = 0;
                key_edge keys,keys1;
                keys.first = min(j,deletedEdges[i][0]);
                keys.second = max(j,deletedEdges[i][0]);
                keys1.first = min(j,deletedEdges[i][1]);
                keys1.second = max(j,deletedEdges[i][1]);
                int a = 1;
                if((edge_temp_info.find(keys) == edge_temp_info.end()) ||(edge_temp_info.find(keys1) == edge_temp_info.end()))
                {
                    a = 0;
                }
               // cout<< j << " "<<edges_static[j][deletedEdges[i][0]] << " "<<a<<endl;
                if((edges_static[j][deletedEdges[i][0]] == 1 && edges_static[j][deletedEdges[i][1]] == 1) && (edge_temp_info.find(keys) == edge_temp_info.end())) /* Found */
                //if(returnUnique(edges_static, j, deletedEdges[i][0]) == 1)
                {
                    if(j != deletedEdges[i][1] || j!= deletedEdges[i][0])
                    {
                        //cout<< " CHECK_0 (" << j << "," << deletedEdges[i][0] << ")"<<endl;
                        count_a++;

                        e2.first = min(j,deletedEdges[i][0]);
                        e2.second = max(j,deletedEdges[i][0]) ;
                        e3.first = min(j,deletedEdges[i][1]);
                        e3.second = max(j,deletedEdges[i][1]) ;
                        if((edge_dynamic_info.find(e2) != edge_dynamic_info.end())|| (edge_dynamic_info.find(e3) != edge_dynamic_info.end()))
                        {
                           isFound_1 = 1;
                        }
                    }
                }

                if(isFound_1 && edge_dynamic_info_it != edge_dynamic_info.end())
                {
                    f2_p1--;
                    edge_dynamic_info.erase(e2);
                    edge_dynamic_info.erase(e3);
                }
            }
            cout<< "count_a = "<<count_a << endl;
            f1_p1 = f1_p1 - count_a;
        }
        edge_temp_info.insert(make_pair(key_edge(deletedEdges[i][0], deletedEdges[i][1]), 1));
    }
    //Addition of Edge
    for(int i = 0; i < noOfAddedEdges; i++ )
    {
        key_edge e;
        e.first = addedEdges[i][0];
        e.second = addedEdges[i][1];
        p1_e1.n1 = e.first;
        p1_e1.n2 = e.second;
        edge_dynamic_info_it = edge_dynamic_info.find(e);

        cout<< "EDGE added = (" << addedEdges[i][0]  << "," << addedEdges[i][1] << ")"<<endl;

        {
            int count_a = 0;
            for(int j = 0; j < nodeSize_dynamic; j++)
            {
                int isNotFound_1 = 0;
                key_edge keys,keys1;
                keys.first = min(j,addedEdges[i][0]);
                keys.second = max(j,addedEdges[i][0]);
                keys1.first = min(j,addedEdges[i][1]);
                keys1.second = max(j,addedEdges[i][1]);

                if(((edges_dynamic[j][addedEdges[i][0]] == 1)&& (edges_dynamic[j][addedEdges[i][1]] == 1))&& ((edge_temp_info.find(keys) == edge_temp_info.end()) &&(edge_temp_info.find(keys1) == edge_temp_info.end())))   /* Found */
                //if(returnUnique(edges_static, j, deletedEdges[i][0]) == 1)
                {

                    if(j != addedEdges[i][1] || j != addedEdges[i][0] )
                    {
                        count_a++;
                        //cout<< " CHECK_2 (" << j << "," << addedEdges[i][0] << ")"<<endl;
                        e2.first = min(j,addedEdges[i][0]);
                        e2.second = max(j,addedEdges[i][0]);
                        p1_e2.n1 = e2.first;
                        p1_e2.n2 = e2.second;
                        e3.first = min(j,addedEdges[i][1]);
                        e3.second = max(j,addedEdges[i][1]);
                        p1_e3.n1 = e3.first;
                        p1_e3.n2 = e3.second;
                        if(edge_dynamic_info.find(e2) == edge_dynamic_info.end() || edge_dynamic_info.find(e3) == edge_dynamic_info.end())
                        {
                            isNotFound_1 = 1;
                        }
                    }

                }

                if(isNotFound_1  && edge_dynamic_info_it == edge_dynamic_info.end())
                {
                    f2_p1++;
                    //edge_dynamic_info3.erase(e2);
                    //insert(make_pair(key_edge(p3_e.n1, p3_e.n2), key_edge(p3_e.n1, p3_e.n2)));
                    edge_dynamic_info.insert(make_pair(key_edge(p1_e1.n1, p1_e1.n2), key_edge(p1_e1.n1, p1_e1.n2)));
                    edge_dynamic_info.insert(make_pair(key_edge(p1_e2.n1, p1_e2.n2), key_edge(p1_e2.n1, p1_e2.n2)));
                    edge_dynamic_info.insert(make_pair(key_edge(p1_e2.n1, p1_e2.n2), key_edge(p1_e2.n1, p1_e2.n2)));
                }
            }
            f1_p1 = f1_p1 + (count_a);
            cout<< "Edge Added count_a = "<<count_a <<endl;
        }
        edge_temp_info.insert(make_pair(key_edge(addedEdges[i][0], addedEdges[i][1]), 1));
    }

    edge_temp_info.clear();
    #endif
    cout << "f1_p1 = " << f1_p1 << "f2_p1 = " << f2_p1 << endl;


}

void readFile(char* fileName) {

	ifstream in(fileName, ifstream::in);
	if (!in.is_open()) {
		cout << "Error opening file 3" << endl;
		exit(1);
	}

	int srcNode, dstNode;
	edges = new int*[nodeSize];
	for (srcNode = 0; srcNode < nodeSize; srcNode++) {
		edges[srcNode] = new int[nodeSize]();
	}
	string srcName, dstName;
	while (!in.eof()) {
		//check if the file is not formatted good
		if (!(in >> srcName >> dstName))
			break;
		srcNode = mapping[srcName];
		dstNode = mapping[dstName];
		edges[srcNode][dstNode] = 1;
		edges[dstNode][srcNode] = 1;
	}
	in.close();
}

void countDegree() {
	//also fill the index start from 1;
	int index = 1;
	for (int i = 0; i < nodeSize; i++) {
		for (int j = i + 1; j < nodeSize; j++) {
			if (edges[i][j]) {
				edges[i][j] = index;
				edges[j][i] = index;
				index++;
			}
		}
	}

	//count degree
	A = new int[nodeSize];
	B = new int[nodeSize];
	C = new int[nodeSize];
	D = new int[nodeSize];

	for (int i = 0; i < nodeSize; i++) {
		int count = 0;
		for (int j = 0; j < nodeSize; j++) {
			if (edges[i][j])
				count++;
		}
		A[i] = count;
		//cout << " A[" << i << "] = " << A[i];
		C[i] = 0.5 * (count - 1) * (count - 2);
		//cout << " C[" << i << "] = " << C[i];
		D[i] = 1.5 * (count - 3) * (count - 2);
		//cout << " D[" << i << "] = " << D[i];
	}
	cout << endl;
}

void DFS(int u, VertexState state[], list<int>& connectedNodes) {
	state[u] = Gray;
	for (int v = 0; v < nodeSize; v++) {
		if (edges[u][v] && state[v] == White) {
			connectedNodes.push_back(v);
			DFS(v, state, connectedNodes);
		}
	}
	state[u] = Black;
}

void findMotifs(map<int, list<int>*>& m) {
	int num = 0;
	int num1 = 0;
	map<int, list<int>*>::iterator it;
	list<Motif*> motif_list;
	//list<Motif*> motif_list1;
	list<Motif*>::iterator motif_it;
	int index1 = -1;
	int index2 = -1;
	int index3 = -1;
    edge_info e1, e2, e3;
    edge_info p3_e1, p3_e2, p3_e3;

	//find pattern 0 and pattern 1
	int *edgeCount = new int[edgeSize + 1]();
	bool * db = new bool[edgeSize + 1];
	for (int o = 0; o <= edgeSize; ++o) {
		db[o] = 0;
		edgeCount[o] = 0;
	}
	list<int>* value;
	list<int>::iterator a, b;

	for (it = m.begin(); it != m.end(); ++it) {
		int key = it->first;

		if (A[key] > 1) {
			value = it->second;
			a = value->begin();
			while (a != value->end()) {
				b = a;
				++b;
				while (b != value->end()) {
					//pattern 0
					{
						Motif *de = new Motif();
						de->d = 2 * A[key] + A[*a] + A[*b] - 6;
						//cout << "key *a *b A[][][]= " << key << " " << *a << " " << *b << " " << A[key]<< " " <<A[*a] << " " << A[*b] << endl;
						de->e = new int[2];
						;
						de->e[0] = edges[key][*a];
						de->e[1] = edges[key][*b];
						//cout << "motif = " << de->d << " " << de->e[0] << " " << de->e[1] << endl;
						motif_list.push_back(de);
						//cout << "(" << de->e[0] << "," << de->e[1] << ") " << endl;
						num++;
					}

					// pattern 1
					if (key < *a && edges[*a][*b]) {
						Motif *de1 = new Motif();
						de1->d = 0;
						de1->e = new int[3];
						index1 = edges[key][*a];
						index2 = edges[key][*b];
						index3 = edges[*a][*b];
						//cout<< "ind1 ind2 ind3 = " << index1 << index2 << index3<< endl;

						//edge_dynamic_info

						e1.n1 = key;
						e1.n2 = *a;
						//cout << "key * = " << key << *a << endl;
						e2.n1 = key;
						e2.n2 = *b;
						e3.n1 = *a;
						e3.n2 = *b;
						temp.insert(make_pair(index1, e1));
						temp.insert(make_pair(index2, e2));
						temp.insert(make_pair(index3, e3));

						de1->e[0] = index1;
						de1->e[1] = index2;
						de1->e[2] = index3;
						motif_list1.push_back(de1);
						//cout << "(" << de1->e[0] << "," << de1->e[1] << "," << de1->e[2] << ") " << endl;

						edgeCount[index1]++;
						edgeCount[index2]++;
						edgeCount[index3]++;

						edges_motif[key][*a] *= 2;
						edges_motif[key][*b] *= 2;
						edges_motif[*a][*b] *= 2;
						num1++;
					}
					++b;
				}
				++a;
			}
		}

	}
	f1_p0 += num;
	f1_p1 += num1;

	//find f2 measure of pattern 0
	if (num == 0) {
	} else if (num == 1) {
		f2_p0++;
		Motif* a = motif_list.front();
		//TODO::
		delete[] a->e;
		delete a;
	} else {
		//do the sort
		motif_list.sort(compDe);

		for (motif_it = motif_list.begin(); motif_it != motif_list.end();
				++motif_it) {
				    //cout<< "motif deg = " << (*motif_it)->d << endl;
			index1 = (*motif_it)->e[0];
			index2 = (*motif_it)->e[1];
			if (!db[index1] && !db[index2]) {
				f2_p0++;
				db[index1] = 1;
				db[index2] = 1;
			}
			delete[] (*motif_it)->e;
			delete *motif_it;
		}
	}
	motif_list.clear();
	for (int o = 0; o <= edgeSize; ++o) {
		db[o] = 0;
	}

	//find f2 measure of pattern 1
	if (num1 == 0) {
	} else if (num1 == 1) {
		f2_p1++;
		Motif* a = motif_list1.front();
		delete[] a->e;
		delete a;
	} else {
		for (motif_it = motif_list1.begin(); motif_it != motif_list1.end();
				++motif_it) {
			index1 = (*motif_it)->e[0];
			index2 = (*motif_it)->e[1];
			index3 = (*motif_it)->e[2];
			(*motif_it)->d = edgeCount[index1] + edgeCount[index2]
					+ edgeCount[index3] - 3;

                temp_it = temp.find(index1);
				edge_info p1_e = temp_it->second;
                edge_dynamic_info.insert(make_pair(key_edge(p1_e.n1, p1_e.n2), (key_edge(p1_e.n1, p1_e.n2))));
				temp_it = temp.find(index2);
                p1_e = temp_it->second;
                edge_dynamic_info.insert(make_pair(key_edge(p1_e.n1, p1_e.n2), (key_edge(p1_e.n1, p1_e.n2))));
                temp_it = temp.find(index3);
                p1_e = temp_it->second;
                edge_dynamic_info.insert(make_pair(key_edge(p1_e.n1, p1_e.n2), (key_edge(p1_e.n1, p1_e.n2))));
		}

		//do the sort
		motif_list1.sort(compDe);

		for (motif_it = motif_list1.begin(); motif_it != motif_list1.end();
				++motif_it) {
			index1 = (*motif_it)->e[0];
			index2 = (*motif_it)->e[1];
			index3 = (*motif_it)->e[2];
			if (!db[index1] && !db[index2] && !db[index3]) {
				f2_p1++;
				db[index1] = 1;
				db[index2] = 1;
				db[index3] = 1;

				//TODO::
			}
			delete[] (*motif_it)->e;
			delete *motif_it;
		}
	}
	//motif_list1.clear();
	temp.clear();
	for (int o = 0; o <= edgeSize; ++o) {
		db[o] = 0;
	}
	num = 0;
	list<int>::iterator c;
	int numTran1, numTran2, numTran3;
	numTran1 = numTran2 = numTran3 = 0;
	for (it = m.begin(); it != m.end(); ++it) {
		int key = it->first;
		if (A[key] > 1) {
			value = it->second;
			a = value->begin();
			while (a != value->end()) {
				b = a;
				++b;
				while (b != value->end()) {
					//pattern 2 c-a-key-b
					if (A[*a] > 1) {
						//start from b
						for (c = m[*a]->begin(); c != m[*a]->end(); ++c) {
							if (*c != key && *c > *b) {
								Motif* de2 = new Motif();
								int count = 0;
								//compute degree
								if (A[*c] > 1) {
									count += B[*c] - (A[*c] - 1) - A[*a];
								}
								if (A[*a] > 2) {
									count += 2
											* (B[*a] - (A[*a] - 2) - A[*c]
													- A[key]);
								}

								if (A[*b] > 1) {
									count += B[*b] - (A[*b] - 1) - A[key];
								}
								if (A[key] > 2) {
									count += 2
											* (B[key] - (A[key] - 2) - A[*a]
													- A[*b]);
								}

								count += (A[*b] - 1) * (A[key] - 2);
								count += (A[*c] - 1) * (A[*a] - 2);
								count += (A[*a] - 2) * (A[key] - 2);
								count += A[*a] + A[*b] + A[*c] + A[key] - 6;

								de2->e = new int[3];
								de2->e[0] = edges[*c][*a];
								de2->e[1] = edges[*a][key];
								de2->e[2] = edges[key][*b];
								numTran1 = edgeCount[de2->e[0]];
								numTran2 = edgeCount[de2->e[1]];
								numTran3 = edgeCount[de2->e[2]];

								if (edges[*c][key]) {
									numTran1--;
									numTran2--;
									count -= 5;
								} else if (edges[*c][*b])
									count--;
								else if (edges[*a][*b]) {
									numTran3--;
									numTran2--;
									count -= 5;
								}

								de2->d = count - 3 * numTran1 - 3 * numTran2
										- 3 * numTran3;
								motif_list.push_back(de2);
								//cout << "(" << de2->e[0] << "," << de2->e[1] << "," << de2->e[2] << ") " << endl;
								num++;

							}
						}
					}
					if (A[*b] > 1) {
						//start from a , a-key-b-c
						for (c = m[*b]->begin(); c != m[*b]->end(); ++c) {
							if (*c != key && *c > *a) {
								Motif* de2 = new Motif();
								int count = 0;
								//compute degree
								if (A[*c] > 1) {
									count += B[*c] - (A[*c] - 1) - A[*b];
								}
								if (A[*b] > 2) {
									count += 2
											* (B[*b] - (A[*b] - 2) - A[*c]
													- A[key]);
								}

								if (A[*a] > 1) {
									count += B[*a] - (A[*a] - 1) - A[key];
								}
								if (A[key] > 2) {
									count += 2
											* (B[key] - (A[key] - 2) - A[*a]
													- A[*b]);
								}

								count += (A[*c] - 1) * (A[*b] - 2);
								count += (A[*a] - 1) * (A[key] - 2);
								count += (A[key] - 2) * (A[*b] - 2);
								count += A[*a] + A[*b] + A[*c] + A[key] - 6;

								de2->e = new int[3];
								de2->e[0] = edges[*a][key];
								de2->e[1] = edges[key][*b];
								de2->e[2] = edges[*b][*c];
								numTran1 = edgeCount[de2->e[0]];
								numTran2 = edgeCount[de2->e[1]];
								numTran3 = edgeCount[de2->e[2]];

								if (edges[*a][*b]) {
									numTran1--;
									numTran2--;
									count -= 5;
								} else if (edges[*a][*c])
									count--;
								else if (edges[key][*c]) {
									numTran3--;
									numTran2--;
									count -= 5;
								}

								de2->d = count - 3 * numTran1 - 3 * numTran2
										- 3 * numTran3;
								motif_list.push_back(de2);
								//cout << "(" << de2->e[0] << "," << de2->e[1] << "," << de2->e[2] << ") " << endl;
								num++;
							}
						}
					}
					++b;
				}
				++a;
			}
		}

	}
	f1_p2 += num;

	//find f2 measure of pattern 2
	if (num == 0) {
	} else if (num == 1) {
		f2_p2++;
		Motif* a = motif_list.front();
		delete[] a->e;
		delete a;
	} else {
		//do the sort
		motif_list.sort(compDe);

		for (motif_it = motif_list.begin(); motif_it != motif_list.end();
				++motif_it) {
			index1 = (*motif_it)->e[0];
			index2 = (*motif_it)->e[1];
			index3 = (*motif_it)->e[2];
			if (!db[index1] && !db[index2] && !db[index3]) {
				f2_p2++;
				db[index1] = 1;
				db[index2] = 1;
				db[index3] = 1;
			}
			delete[] (*motif_it)->e;
			delete *motif_it;
		}

	}
	motif_list.clear();
	for (int o = 0; o <= edgeSize; ++o) {
		db[o] = 0;
	}
	delete[] edgeCount;

    //find f2 measure of pattern 3
	num = 0;
	for (it = m.begin(); it != m.end(); ++it) {
		int key = it->first;
		if (A[key] > 2) {
			value = it->second;
			a = value->begin();
			while (a != value->end()) {
				b = a;
				++b;
				while (b != value->end()) {
					//pattern 3
					c = b;
					++c;
					while (c != value->end()) {
						Motif *de3 = new Motif();
						de3->d = D[key] + C[*a] + C[*b] + C[*c];
						de3->e = new int[3];

						de3->e[0] = edges[key][*a];
						de3->e[1] = edges[key][*b];
						de3->e[2] = edges[key][*c];
						motif_list.push_back(de3);

                        /* storing motifs */
						//struct edge_info e1,e2,e3;
						key_edge e1,e2,e3;

						e1.first = min(key, *a);
						e1.second = max(key, *a);
						e2.first = min(key, *b);
						e2.second = max(key, *b);
						e3.first = min(key, *c);
						e3.second = max(key, *c);

                        /*
						key_edge_pair ep1, ep2, ep3;
						ep1.first = e1;
						ep1.second = e2;
						ep2.first = e2;
						ep2.second = e3;
						ep3.first = e1;
						ep3.second = e3;

                        motif_3.insert(make_pair(e1, ep1));
                        motif_3.insert(make_pair(e2, ep2));
                        motif_3.insert(make_pair(e3, ep3));*/


						p3_e1.n1 = key;
						p3_e1.n2 = *a;
						//cout << "key * = " << key << *a << endl;
						p3_e2.n1 = key;
						p3_e2.n2 = *b;
						p3_e3.n1 = key;
						p3_e3.n2 = *c;
						temp.insert(make_pair(de3->e[0], p3_e1));
						temp.insert(make_pair(de3->e[1], p3_e2));
						temp.insert(make_pair(de3->e[2], p3_e3));

						temp_p3.insert(make_pair(de3->e[0], e1));
						temp_p3.insert(make_pair(de3->e[1], e2));
						temp_p3.insert(make_pair(de3->e[2], e3));


						num++;
						++c;
					}
					++b;
				}
				++a;
			}
		}
	}
	f1_p3 += num;
	if (num == 0) {
	} else if (num == 1) {
		f2_p3++;
		Motif* a = motif_list.front();
		delete[] a->e;
		delete a;
	} else {
		//do the sort
		motif_list.sort(compDe);

		for (motif_it = motif_list.begin(); motif_it != motif_list.end();
				++motif_it) {
			index1 = (*motif_it)->e[0];
			index2 = (*motif_it)->e[1];
			index3 = (*motif_it)->e[2];

			if (!db[index1] && !db[index2] && !db[index3]) {
				f2_p3++;
				db[index1] = 1;
				db[index2] = 1;
				db[index3] = 1;
/*
				temp_it = temp.find(index1);
				edge_info p3_e = temp_it->second;
                edge_dynamic_info3.insert(make_pair(key_edge(p3_e.n1, p3_e.n2), key_edge(p3_e.n1, p3_e.n2)));
				temp_it = temp.find(index2);
                p3_e = temp_it->second;
                edge_dynamic_info3.insert(make_pair(key_edge(p3_e.n1, p3_e.n2), key_edge(p3_e.n1, p3_e.n2)));
				temp_it = temp.find(index3);
                p3_e = temp_it->second;
                edge_dynamic_info3.insert(make_pair(key_edge(p3_e.n1, p3_e.n2), key_edge(p3_e.n1, p3_e.n2)));
                */
                key_edge e1,e2,e3;
                {
                    {
                        temp_p3_it = temp_p3.find(index1);
                        e1.first = min((temp_p3_it->second).first, (temp_p3_it->second).second);
                        //e1.first = min(key, *a);
						e1.second = max((temp_p3_it->second).first, (temp_p3_it->second).second);
						temp_p3_it = temp_p3.find(index2);
						e2.first = min((temp_p3_it->second).first, (temp_p3_it->second).second);
						e2.second = max((temp_p3_it->second).first, (temp_p3_it->second).second);
						temp_p3_it = temp_p3.find(index3);
						e3.first = min((temp_p3_it->second).first, (temp_p3_it->second).second);
						e3.second = max((temp_p3_it->second).first, (temp_p3_it->second).second);

						key_edge_pair ep1, ep2, ep3;
						ep1.first = e2;
						ep1.second = e3;
						ep2.first = e1;
						ep2.second = e3;
						ep3.first = e1;
						ep3.second = e2;

                        motif_3.insert(make_pair(e1, ep1));
                        motif_3.insert(make_pair(e2, ep2));
                        motif_3.insert(make_pair(e3, ep3));
                    }
                }
            }
			delete[] (*motif_it)->e;
			delete *motif_it;
		}

	}
	temp.clear();
	temp_p3.clear();
	cout<< "After patter det = "<<endl;
	//printMotif_3();

	motif_list.clear();
	for (int o = 0; o <= edgeSize; ++o) {
		db[o] = 0;
	}
	cout << "end of find motif" << endl;
}

void filterData() {
	VertexState *state = new VertexState[nodeSize];
	for (int i = 0; i < nodeSize; i++) {
		state[i] = White;
	}

	for (int i = 0; i < nodeSize; i++) {
		if (state[i] == White) {
			//one subgraph find
			connectedNodes.push_back(i);
			DFS(i, state, connectedNodes);
			int num = connectedNodes.size();

			if (num >= 3) {
				//need to find basic motifs
				//build adjacency list
				for (iter = connectedNodes.begin();
						iter != connectedNodes.end(); ++iter) {
                    //cout << "iter = " << *iter << endl;
					int n = *iter;
					list<int>* neigh = new list<int>();
					int count = 0;
					for (int m = 0; m < nodeSize; m++) {
						if (edges[n][m]) {
							neigh->push_back(m);
							count += A[m];
						}
					}
					B[n] = count;
                    //cout << " B[" << n << "] = " << B[n];
					connectedList[n] = neigh;
				}
				findMotifs(connectedList);
			}

			connectedNodes.clear();
			for (listIter = connectedList.begin();
					listIter != connectedList.end(); ++listIter)
				delete listIter->second;
			connectedList.clear();
		}
	}
	delete[] state;
	delete[] A;
	delete[] B;
	delete[] C;
	delete[] D;
}

int main() {
	//original motif count

    char filename[FILENAME_MAX];
    int choice;
	while(1)
    {
        choice = 3;
        //original motif count
        cout << "Enter choice - 1 for static training, 2 for dynamic calculation, 3 for exit:" << endl;
        cin >> choice;

        time_t ostart_user;
        time_t oend_user;

        time_t ostart = clock();
        if(choice == 1)
        {
            ostart_user = clock();
            cout << "Enter filename:" << endl;
            cin >> filename;
            oend_user = clock();

            f1_p0 = f1_p1 = f1_p2 = f1_p3 = 0;
            f2_p0 = f2_p1 = f2_p2 = f2_p3 = 0;
            //loadData("data/test.txt");
            loadData(filename);
            countDegree();
            filterData();
            //for (int i = 0; i < nodeSize; i++)
            //    delete[] edges[i];
            //delete[] edges;
            cout << "f1_p0	f2_p0" << endl;
            cout << f1_p0 << "	" << f2_p0 << endl;
            cout << f1_p1 << "	" << f2_p1 << endl;
            cout << f1_p2 << "	" << f2_p2 << endl;
            cout << f1_p3 << "	" << f2_p3 << endl;
            cout << "=================" << endl;
        }
        else if(choice == 2)
        {
            ostart_user = clock();
            cout << "Enter filename:" << endl;
            cin >> filename;
            oend_user = clock();
            loadData_dynamic(filename);
            findChangesInNetwork_dynamic();
            //filterdata_dynamic(); // Edit connected list
            determineMotifs_dynamic();
            cout << "f1_p0	f2_p0" << endl;
            cout << f1_p0 << "	" << f2_p0 << endl;
            cout << f1_p1 << "	" << f2_p1 << endl;
            cout << f1_p2 << "	" << f2_p2 << endl;
            cout << f1_p3 << "	" << f2_p3 << endl;
            cout << "=================" << endl;
        }
        else if(choice == 3)
        {
            /* TODO also delete the memory */
            break;
        }
        else
        {
            continue;
        }
        time_t oend = clock();
        cout << "running time:	" << double(oend - ostart - (oend_user - ostart_user)) / CLOCKS_PER_SEC << endl;
    }

	long f1p0, f1p1, f1p2, f1p3;
	int f2p0, f2p1, f2p2, f2p3;
	f1p0 = f1_p0;
	f1p1 = f1_p1;
	f1p2 = f1_p2;
	f1p3 = f1_p3;
	f2p0 = f2_p0;
	f2p1 = f2_p1;
	f2p2 = f2_p2;
	f2p3 = f2_p3;

}
