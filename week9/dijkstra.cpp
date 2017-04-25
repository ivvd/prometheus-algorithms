#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <list>
#include <utility>
#include <algorithm>
#include <climits>
#include <cstdlib>

const int biggest_label = 1000000000;

class GraphVertex
{
private:
	std::map<int,int> edge_list;
	int label;
public:
	GraphVertex(void)
	{
		label = biggest_label;
	}
	
	typedef std::pair <std::map<int,int>::iterator, size_t> edge_list_iter;

	void add_edge(int vertex, int weight)
	{
		edge_list.insert(std::pair<int, int>(vertex, weight));
	}
	
	edge_list_iter get_edge_list(void)
	{
		return std::make_pair(edge_list.begin(), edge_list.size());
	}
	
	void set_label(int new_label)
	{
		label = new_label;
	}
	
	int get_label(void)
	{
		return label;
	}
};

class Graph
{
private:
	std::vector<GraphVertex> vertex_list;
public:
	Graph(const char* file_path);
	void print(void);
	GraphVertex& get_vertex(int number)
	{
		return vertex_list[number];
	}
	int get_number_of_vertices(void)
	{
		return vertex_list.size();
	}
};

Graph::Graph(const char* file_path)
{
	std::ifstream file;
	
	file.open(file_path, std::ifstream::in);
	
	int vertices, edges;
	file >> vertices;
	file >> edges;
	
	vertex_list.resize(vertices+1);
	
	while(!file.eof())
	{
		int from, to, weight;
		file >> from;
		file >> to;
		file >> weight;
		if(!file.eof())
		{
			//std::cout << from << " " << to << " " << weight << std::endl;
			vertex_list[from].add_edge(to, weight);
		}
	}
	
	file.close();	
}

void Graph::print(void)
{
	int i = 0;
	std::cout << std::endl;
	for(std::vector<GraphVertex>::iterator it = vertex_list.begin(); it != vertex_list.end(); it++)
	{
		GraphVertex gv = *it;
		GraphVertex::edge_list_iter edge_it = gv.get_edge_list();
		
		std::cout << i << ";\t";
		
		std::cout << "label = " << gv.get_label() << ":\t";
		
		for(int j = 0; j < edge_it.second; j++)
		{
			std::cout << "(" << (*edge_it.first).first << "," << (*edge_it.first).second << ") ";
			edge_it.first++;
		}
		
		std::cout << std::endl;
		++i;
	}
}

std::vector< std::vector<int> > path;

void dijkstra(Graph& g, int start)
{
	int g_size = g.get_number_of_vertices();
	int act_vertex = start;
	std::set<int> search_set;
	GraphVertex& gv = g.get_vertex(act_vertex);
	
	gv.set_label(0);
	
	//std::cout << "Graph size: " << g_size << std::endl;
	
	path.resize(g_size);
	for(int i = 0; i < g_size; i++)
	{
		path[i].push_back(0);
	}
	
	for(int i = 1; i < g_size; i++)
	{
		gv = g.get_vertex(act_vertex);
		GraphVertex::edge_list_iter edge_it = gv.get_edge_list();
		
		for(int j = 0; j < edge_it.second; j++)
		{
			int edge_weight = (*edge_it.first).second;
			int next_vertex_index = (*edge_it.first).first;
			GraphVertex& next_vertex = g.get_vertex(next_vertex_index);
			
			//std::cout << next_vertex_index << "-" << edge_weight << "-" << gv.get_label() << std::endl;
			
			if(next_vertex.get_label() > (gv.get_label() + edge_weight))
			{
				next_vertex.set_label(gv.get_label() + edge_weight);
				//path[next_vertex_index].push_back(act_vertex);
				path[next_vertex_index][0] = act_vertex;
			}
			else if(next_vertex.get_label() == (gv.get_label() + edge_weight))
			{
				path[next_vertex_index].push_back(act_vertex);
			}
			
			search_set.insert(next_vertex_index);
			
			edge_it.first++;
		}
		
		if(search_set.size() > 0)
		{
			std::set<int>::iterator it;
			std::set<int>::iterator min_vertex_it;
			int min_label = INT_MAX;
			for(it = search_set.begin(); it != search_set.end(); it++)
			{
				GraphVertex& gv = g.get_vertex(*it);
				if(gv.get_label() < min_label)
				{
					min_label = gv.get_label();
					min_vertex_it = it;
				}
			}
			act_vertex = *min_vertex_it;
			
			//std::cout << "min_label: " << min_label << "; min_vertex: " << act_vertex;
			//std::cout << "; i: " << i << std::endl;
			
			search_set.erase(min_vertex_it);
		}
		else
		{
			break;
		}
	}
}

void print_path_vector(void)
{
	std::cout << std::endl << "v:" << std::endl;
	for(int i = 0; i < path.size(); i++)
	{
		for(int j = 0; j < path[i].size(); j++)
		{
			std::cout << path[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void print_first_path(int end)
{
	int next = end;
	std::list<int> first_path;
	
	do
	{
		first_path.push_back(next);
		next = path[next][0];
	}
	while(next != 0);
	
	std::cout << std::endl << "Path:" << std::endl;
	std::list<int>::reverse_iterator rit;
	for(rit = first_path.rbegin(); rit != first_path.rend(); rit++)
	{
		std::cout << *rit << " ";
	}
	std::cout << std::endl;
}

int main(int argc, const char *argv[])
{
	if(argc == 2 || argc == 3)
	{
		Graph my_graph(argv[1]);
		my_graph.print();
		
		if(argc == 2)
		{
			dijkstra(my_graph, 1);
		}
		else
		{
			int start = atoi(argv[2]);
			dijkstra(my_graph, start);
		}
		
		int vertex = 7;
		GraphVertex& gv = my_graph.get_vertex(vertex);
		std::cout << vertex << ": " << gv.get_label() << std::endl;
		
		print_path_vector();
		
		print_first_path(vertex);
	}
	else
	{
		std::cout << "Type input file as a parameter: dijkstra input.txt" << std::endl;
		std::cout << "Or dijkstra input.txt start_vertex" << std::endl;
	}
	
	return 0;
}
