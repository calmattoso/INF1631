#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include "../lib/CPUTimer/CPUTimer.h"

using namespace std;

float highest_weight_in_graph=-99999.9;

void printGraph(vector< pair<int,float> >* adjacency_list,int num_vertices)
{
	for(int vertex=0;vertex<num_vertices;vertex++)
	{
		int vertex_degree = adjacency_list[vertex].size();
		for(int i=0;i<vertex_degree;i++)
		{
			printf("%d <-> %d [%f]\n",vertex,adjacency_list[vertex][i].first,adjacency_list[vertex][i].second);
		}
	}
	return;
}

pair<int,int>* maximumGeneratingForest(vector< pair<int,float> >* adjacency_list,int num_vertices,int* num_edges_generated)
{
	pair<int,int>* forest = new pair<int,int>[num_vertices-1];
	*num_edges_generated = 0;
	int* conex_component = new int[num_vertices];
	int number_of_conex_components = num_vertices;
	bool has_merged = true;

	for(int i=0;i<num_vertices;i++)
	{
		// Caso Base (Componentes Conexos de Um Vértice)
		conex_component[i]=i;
	}

	// Indução

	// Assumindo um grafo conexo, quero rodar o algoritmo até sobrar 1 componente conexa
	while(has_merged)
	{
		has_merged = false;
		/*
		printf("Forest Until Now:\n");
		for(int i=0;i<num_vertices;i++)
		{
			printf("[%d] is in %d\n",i,conex_component[i]);
		}
		for(int i=0;i<*num_edges_generated;i++)
		{
			printf("%d <-> %d\n",forest[i].first,forest[i].second);
		}
		*/
		for(int k=0;k<number_of_conex_components;k++)
		{
			// Encontrar a aresta de maior peso
			int min_weight = highest_weight_in_graph+1;
			int vertex_to_add = -1;
			int origin_vertex = -1;
			for(int vertex=0;vertex<num_vertices;vertex++)
			{
				if(conex_component[vertex]==k)
				{
					// Percorre todo
					for(int j=0;j<adjacency_list[vertex].size();j++)
					{
						int vertex_checked = adjacency_list[vertex][j].first;
						float edge_weight = adjacency_list[vertex][j].second;

						if(edge_weight<min_weight && conex_component[vertex_checked]!=conex_component[vertex])
						{
							min_weight = edge_weight;
							vertex_to_add = vertex_checked;
							origin_vertex = vertex;
						}
					}
				}
				else
				{
					continue;
				}
			}
			if(vertex_to_add != -1 && origin_vertex != -1)
			{
				has_merged = true;
				forest[*num_edges_generated] = make_pair(origin_vertex,vertex_to_add);
				(*num_edges_generated)++;
				int lowest_con_comp = conex_component[origin_vertex]<conex_component[vertex_to_add]?conex_component[origin_vertex]:conex_component[vertex_to_add];
				int highest_con_comp = conex_component[origin_vertex]<conex_component[vertex_to_add]?conex_component[vertex_to_add]:conex_component[origin_vertex];

				//printf("\nIn component %d:\n",k);
				//printf("Vetex %d (component %d) wants to merge with %d (component %d)\n",origin_vertex,conex_component[origin_vertex],vertex_to_add,conex_component[vertex_to_add]);
				//printf("All vertexes of component %d will be turned into component %d.\n\n",highest_con_comp,lowest_con_comp);

				for(int vertex=0;vertex<num_vertices;vertex++)
				{
					if(conex_component[vertex]==highest_con_comp)
					{
						conex_component[vertex] = lowest_con_comp;
					}
				}
			}
		}
	}
	return forest;
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
			if(distance>highest_weight_in_graph)
			{
				distance = highest_weight_in_graph;
			}
		}
	}
	/*
	scanf(" %d %d",num_vertices,num_edges);

	vector< pair<int,int> >* adjacency_list = new vector< pair<int,int> >[*num_vertices];

	int vertex_a,vertex_b;
	int weight;
	for(int i=0;i<*num_edges;i++)
	{
		scanf(" %d %d %d",&vertex_a,&vertex_b,&weight);

		if(weight>highest_weight_in_graph)
		{
			highest_weight_in_graph = weight;
		} 

		adjacency_list[vertex_a].push_back(make_pair(vertex_b,weight));

		adjacency_list[vertex_b].push_back(make_pair(vertex_a,weight));
	}
	*/


	return adjacency_list;
}

int main(void)
{
	int num_vertices;
	int num_edges;
	int edges_generated;
	vector< pair<int,float> >* adjacency_list;
	pair<int,int>* max_gen_forest;

	CPUTimer timer_total;
	int total_runs = 0;

	adjacency_list = readGraph(&num_vertices,&num_edges);
	//printf("Original Adjacency List:\n");
	//printGraph(adjacency_list,num_vertices);
	do
	{
		total_runs++;
		timer_total.start();
		max_gen_forest = maximumGeneratingForest(adjacency_list,num_vertices,&edges_generated);
		timer_total.stop();

		if(timer_total.getCPUTotalSecs()>=5.0f) break;

		delete[] max_gen_forest;
	}
	while(timer_total.getCPUTotalSecs()<5.0f);

	printf("Forest Generated:\n");
	for(int i=0;i<edges_generated;i++)
	{
		printf("%d <-> %d\n",max_gen_forest[i].first,max_gen_forest[i].second);
	}
	printf("%d runs generated in %f seconds: %f seconds/run.\n",total_runs,timer_total.getCPUTotalSecs(),timer_total.getCPUTotalSecs()/(float)total_runs);

	delete[] adjacency_list;
	delete[] max_gen_forest;

	return 0;
}