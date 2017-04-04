#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>

class GraphVertex
{
private:
	std::vector<int> edge_list;
	bool examined;
	int t;
public:
	GraphVertex(void)
	{
		examined = false;
		t = 0;
	}
	
	typedef std::pair <std::vector<int>::iterator,
				       std::vector<int>::iterator> edge_list_iter;
	
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
	
	void set_t(int new_t)
	{
		t = new_t;
	}
	
	int get_t(void)
	{
		return t;
	}
};

class Graph
{
private:
	std::vector<GraphVertex> vertex_list;
public:
	Graph(void)
	{
		GraphVertex gv;
		vertex_list.push_back(gv);
	};
	typedef std::pair <std::vector<GraphVertex>::iterator,
				       std::vector<GraphVertex>::iterator> vertex_list_iter;
	void print(void);
	void add_edge(int from, int to);
	void load(const char* file_path);
	void dfs(int vertex, int& t, std::vector<int>& order);
	void dfs_loop(std::vector<int>& order_out);
	void dfs_loop_t(std::vector<int>& order_in, std::vector<int>& component_list);
	vertex_list_iter get_vertex_list(void)
	{
		return std::make_pair(vertex_list.begin(), vertex_list.end());
	}
};

void Graph::add_edge(int from, int to)
{
	int max = std::max(from, to);
	
	if(max > vertex_list.size() - 1)
	{
		vertex_list.resize(max + 1);
	}
	
	vertex_list[from].add_edge(to);
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
		
		if(gv.is_examined())
		{
			std::cout << "e;\t";
		}
		else
		{
			std::cout << "ne;\t";
		}
		
		std::cout << "t = " << gv.get_t() << ":\t";
		
		while(edge_it.first != edge_it.second)
		{
			std::cout << *edge_it.first << " ";
			edge_it.first++;
		}
		
		std::cout << std::endl;
		++i;
	}
}

void Graph::load(const char* file_path)
{
	std::ifstream file;
	
	file.open(file_path, std::ifstream::in);
	
	while(!file.eof())
	{
		int first, second;
		file >> first;
		file >> second;
		if(!file.eof())
		{
			//std::cout << first << " " << second << std::endl;
			add_edge(first, second);
		}
	}
	
	file.close();	
}

void Graph::dfs(int vertex, int& t, std::vector<int>& order)
{
	std::stack<int> s;
	vertex_list[vertex].examine();
	s.push(vertex);
	while(!s.empty())
	{
		int v = s.top();
		int u;
		GraphVertex::edge_list_iter edge_it = vertex_list[v].get_edge_list();
		
		while(edge_it.first != edge_it.second)
		{
			u = *edge_it.first;
			if(vertex_list[u].is_examined() == false)
			{
				break;
			}
			edge_it.first++;
		}
		
		if(edge_it.first != edge_it.second)
		{
			vertex_list[u].examine();
			s.push(u);
		}
		else
		{
			t += 1;
			vertex_list[v].set_t(t);
			order.push_back(v);
			s.pop();
		}
	}
}

void Graph::dfs_loop(std::vector<int>& order_out)
{
	int t = 0;
	
	for(int i = 1; i < vertex_list.size(); i++)
	{
		if(vertex_list[i].is_examined() == false)
		{
			dfs(i, t, order_out);
		}
	}
}

void Graph::dfs_loop_t(std::vector<int>& order_in, std::vector<int>& component_list)
{
	int t = 0;
	std::vector<int> temp;
	
	for(std::vector<int>::reverse_iterator rit = order_in.rbegin(); rit != order_in.rend(); rit++)
	{
		if(vertex_list[*rit].is_examined() == false)
		{
			t = 0;
			dfs(*rit, t, temp);
			component_list.push_back(temp.size());
			temp.resize(0);
		}
	}	
	std::cout << std::endl;
}

void graph_transpose(Graph& g, Graph& gt)
{
	Graph::vertex_list_iter vi = g.get_vertex_list();
	int i = 0;
	while(vi.first != vi.second)
	{
		GraphVertex::edge_list_iter ei = (*vi.first).get_edge_list();
		while(ei.first != ei.second)
		{
			gt.add_edge(*ei.first, i);
			ei.first++;
		}
		i++;
		vi.first++;
	}
}

bool compare (int i, int j) { return (i > j); }

int main(int argc, const char *argv[])
{
	std::cout << "Hello!" << std::endl;
	
	// Graph dummy_graph;
	// dummy_graph.add_edge(1, 1);
	// dummy_graph.add_edge(1, 2);
	// dummy_graph.add_edge(1, 3);
	// dummy_graph.add_edge(2, 1);
	// dummy_graph.add_edge(2, 3);
	// dummy_graph.add_edge(3, 2);
	// dummy_graph.print();
	
	std::cout << std::endl << std::endl;
	
	if(argc == 2)
	{
		std::vector<int> order;
		std::vector<int> component_list;
		Graph file_graph;
		
		file_graph.load(argv[1]);
		file_graph.dfs_loop(order);
		//file_graph.print();
		
		// for(std::vector<int>::iterator it = order.begin(); it != order.end(); it++)
		// {
			// std::cout << *it << " ";
		// }
		// std::cout << std::endl;
		
		Graph transposed_graph;
		graph_transpose(file_graph, transposed_graph);
		//transposed_graph.print();
		
		transposed_graph.dfs_loop_t(order, component_list);
		
		std::sort(component_list.begin(), component_list.end(), compare);
		
		for(std::vector<int>::iterator it = component_list.begin(); it != component_list.end(); it++)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		
	}
	
	return 0;
}