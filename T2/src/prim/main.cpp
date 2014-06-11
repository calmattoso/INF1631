// A N³ (wacky) implementation with adjacency list

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int lowest_weight_in_graph=99999;

void printGraph(vector< pair<int,int> >* adjacency_list,int num_vertices)
{
	for(int vertex=0;vertex<num_vertices;vertex++)
	{
		int vertex_degree = adjacency_list[vertex].size();
		for(int i=0;i<vertex_degree;i++)
		{
			printf("%d <-> %d [%d]\n",vertex,adjacency_list[vertex][i].first,adjacency_list[vertex][i].second);
		}
	}
	return;
}

int* maximumGeneratingTree(vector< pair<int,int> >* adjacency_list,int num_vertices)
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

vector< pair<int,int> >* readGraph(int* num_vertices,int* num_edges)
{
	scanf(" %d %d",num_vertices,num_edges);

	vector< pair<int,int> >* adjacency_list = new vector< pair<int,int> >[*num_vertices];

	int vertex_a,vertex_b;
	int weight;
	for(int i=0;i<*num_edges;i++)
	{
		scanf(" %d %d %d",&vertex_a,&vertex_b,&weight);

		if(weight<lowest_weight_in_graph)
		{
			lowest_weight_in_graph = weight;
		} 

		adjacency_list[vertex_a].push_back(make_pair(vertex_b,weight));

		adjacency_list[vertex_b].push_back(make_pair(vertex_a,weight));
	}

	return adjacency_list;
}

int main(void)
{
	int num_vertices;
	int num_edges;

	vector< pair<int,int> >* adjacency_list;
	int* max_gen_tree;

	adjacency_list = readGraph(&num_vertices,&num_edges);
	printf("Original Adjacency List:\n");
	printGraph(adjacency_list,num_vertices);

	max_gen_tree = maximumGeneratingTree(adjacency_list,num_vertices);
	printf("Tree Generated:\n");
	for(int i=0;i<num_vertices;i++)
	{
		printf("%d -> %d\n",i,max_gen_tree[i]);
	}

	delete[] adjacency_list;
	delete[] max_gen_tree;

	return 0;
}