#include <iostream>
#include <vector>
#include <utility>

typedef std::pair <std::vector<int>::iterator,
				   std::vector<int>::iterator> edge_list_iter;

class GraphVertex
{
private:
	std::vector<int> edge_list;
	bool examined;
public:
	GraphVertex(void)
	{
		examined = false;
	}
	
	bool is_examined(void)
	{
		return examined;
	}
	
	void examine(void)
	{
		examined = true;
	}

	void add_edge(int vertex)
	{
		edge_list.push_back(vertex);
	}
	
	edge_list_iter get_edge_list(void)
	{
		return std::make_pair(edge_list.begin(), edge_list.end());
	}
};

class Graph
{
private:
	std::vector<GraphVertex> vertex_list;
public:
	Graph(char *file_path);
	Graph(void)
	{
		GraphVertex gv;
		vertex_list.push_back(gv);
	};
	void print(void);
	void add_edge(int vertex, int edge);
};

Graph::Graph(char *file_path)
{
	
}

void Graph::add_edge(int vertex, int edge)
{
	if(vertex > vertex_list.size() - 1)
	{
		GraphVertex gv;
		gv.add_edge(edge);
		vertex_list.push_back(gv);
	}
	else
	{
		vertex_list[vertex].add_edge(edge);
	}
}

void Graph::print(void)
{
	for(std::vector<GraphVertex>::iterator it = vertex_list.begin(); it != vertex_list.end(); it++)
	{
		GraphVertex gv = *it;
		edge_list_iter edge_it = gv.get_edge_list();
		while(edge_it.first != edge_it.second)
		{
			std::cout << *edge_it.first << " ";
			edge_it.first++;
		}
		std::cout << std::endl;
	}
}

int main(void)
{
	std::cout << "Hello!" << std::endl;
	
	Graph dummy_graph;
	dummy_graph.add_edge(1, 1);
	dummy_graph.add_edge(1, 2);
	dummy_graph.add_edge(1, 3);
	dummy_graph.add_edge(2, 1);
	dummy_graph.add_edge(2, 3);
	dummy_graph.add_edge(3, 2);
	dummy_graph.print();
	
	return 0;
}