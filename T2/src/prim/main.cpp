// A N³ (wacky) implementation with adjacency list

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include "../lib/CPUTimer/CPUTimer.h"


using namespace std;

int lowest_weight_in_graph=99999;

void printGraph(vector< pair<int,float> >* adjacency_list,float num_vertices)
{
	for(int vertex=0;vertex<num_vertices;vertex++)
	{
		int vertex_degree = adjacency_list[vertex].size();
		for(int i=0;i<vertex_degree;i++)
		{
			printf("%d <-> %f [%f]\n",vertex,adjacency_list[vertex][i].first,adjacency_list[vertex][i].second);
		}
	}
	return;
}

int* maximumGeneratingTree(vector< pair<int,float> >* adjacency_list,int num_vertices)
{
	int* tree = new int[num_vertices];
	bool* is_vertice_in_tree = new bool[num_vertices];

	for(int i=0;i<num_vertices;i++)
	{
		is_vertice_in_tree[i]=false;
		tree[i]=-1;
	}

	// Caso Base (adiciona o vértice zero na árvore)
	is_vertice_in_tree[0] = true;

	// Indução

	// Cda iteração adiciona um vértice na árvore
	for(int i=0;i<num_vertices;i++)
	{
		// Encontrar a aresta de maior peso
		//printf("________________\n");
		//printf("Lowest Weight = %d\n",lowest_weight_in_graph);
		int max_weight = lowest_weight_in_graph-1;
		int vertex_to_add = -1;
		int origin_vertex = -1;
		for(int vertex=0;vertex<num_vertices;vertex++)
		{
			//printf("Checking Vertex = %d\n",vertex);
			if(is_vertice_in_tree[vertex])
			{
				// Percorre todo
				for(int j=0;j<adjacency_list[vertex].size();j++)
				{
					int vertex_checked = adjacency_list[vertex][j].first;
					int edge_weight = adjacency_list[vertex][j].second;

					//printf("%d <-> %d com peso %d ( peso maximo = %d)\n",vertex,vertex_checked,edge_weight,max_weight);

					if(edge_weight>max_weight && !is_vertice_in_tree[vertex_checked])
					{
						max_weight = edge_weight;
						vertex_to_add = vertex_checked;
						origin_vertex = vertex;
						//printf(">>Nova aresta maxima: %d -> %d com peso %d\n",vertex_to_add,origin_vertex,edge_weight);
					}
				}
			}
			else
			{
				continue;
			}
		}
		if(vertex_to_add == -1 || origin_vertex == -1)
		{
			break;
		}
		is_vertice_in_tree[vertex_to_add] = true;
		tree[vertex_to_add] = origin_vertex;

		//printf("Vertex Added = %d -> %d.\n",vertex_to_add,origin_vertex);
	}
	return tree;
}

vector< pair<int,float> >* readGraph(int* num_vertices,int* num_edges)
{
	int v,x,y;
	vector<float> v_x;
	vector<float> v_y;
	while(scanf(" %f %f",&x,&y) == 2)
	{
		v_x.push_back(x);
		v_y.push_back(y);
	}
	*num_vertices = v_x.size();
	*num_edges = (*num_vertices)*(*num_vertices-1);
	vector< pair<int,float> >* adjacency_list = new vector< pair<int,float> >[*num_vertices];
	float distance;
	for(int i=0;i<*num_vertices;i++)
	{
		for(int j=0;j<*num_vertices;j++)
		{
			distance = sqrt((v_x[j]-v_x[i])*(v_x[j]-v_x[i])+(v_y[j]-v_y[i])*(v_y[j]-v_y[i]));
			adjacency_list[i].push_back(make_pair(j,distance));
			adjacency_list[j].push_back(make_pair(i,distance));
			if(distance>lowest_weight_in_graph)
			{
				distance = lowest_weight_in_graph;
			}
		}
	}
	return adjacency_list;
}

int main(void)
{
	int num_vertices;
	int num_edges;

	vector< pair<int,float> >* adjacency_list;
	int* max_gen_tree;

	CPUTimer timer_total;
	int total_runs = 0;

	adjacency_list = readGraph(&num_vertices,&num_edges);
	printf("Original Adjacency List:\n");
	printGraph(adjacency_list,num_vertices);

	do
	{
		total_runs++;
		timer_total.start();
		max_gen_tree = maximumGeneratingTree(adjacency_list,num_vertices);		
		timer_total.stop();
	}
	while(timer_total.getCPUTotalSecs()<5.0f);

	printf("Tree Generated:\n");
	for(int i=0;i<num_vertices;i++)
	{
		printf("%d -> %d\n",i,max_gen_tree[i]);
	}

	printf("%d runs generated in %f seconds: %f seconds/run.\n",total_runs,timer_total.getCPUTotalSecs(),timer_total.getCPUTotalSecs()/(float)total_runs);


	delete[] adjacency_list;
	delete[] max_gen_tree;

	return 0;
}