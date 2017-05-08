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
    bool examined;
public:
    GraphVertex(void)
    {
        label = biggest_label;
        examined = false;
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

    void examine(void)
    {
        examined = true;
    }

    bool is_examined(void)
    {
        return examined;
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

        for(size_t j = 0; j < edge_it.second; j++)
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
    int temp = 0;

    gv.set_label(0);

    //std::cout << "Graph size: " << g_size << std::endl;

    path.resize(g_size);
    for(int i = 0; i < g_size; i++)
    {
        path[i].push_back(0);
    }

    for(int i = 1; i < g_size; i++)
    {
        //std::cout << "print1:" << act_vertex << std::endl;
        //g.print();

        GraphVertex& gv = g.get_vertex(act_vertex);
        gv.examine();

        //std::cout << "print2:" << std::endl;
        //g.print();

        GraphVertex::edge_list_iter edge_it = gv.get_edge_list();

        for(size_t j = 0; j < edge_it.second; j++)
        {
            int edge_weight = (*edge_it.first).second;
            int next_vertex_index = (*edge_it.first).first;
            GraphVertex& next_vertex = g.get_vertex(next_vertex_index);

            if(next_vertex.is_examined() == false)
            {
                //std::cout << next_vertex_index << "-" << edge_weight << "-" << gv.get_label();
                //std::cout << "-" << act_vertex << std::endl;

                int next_label = gv.get_label() + edge_weight;
                if(next_vertex.get_label() > next_label)
                {
                    next_vertex.set_label(next_label);
                    //path[next_vertex_index].push_back(act_vertex);
                    path[next_vertex_index][0] = act_vertex;
                }
                else if(next_vertex.get_label() == next_label)
                {
                    path[next_vertex_index].push_back(act_vertex);
                }

                search_set.insert(next_vertex_index);
            }

            edge_it.first++;
            
            temp++;
        }

        //g.print();

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
    
    //std::cout << "temp=" << temp << std::endl;
}

void print_path_vector(void)
{
    std::cout << std::endl << "v:" << std::endl;
    for(size_t i = 0; i < path.size(); i++)
    {
        for(size_t j = 0; j < path[i].size(); j++)
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

int find_number_of_paths(int start)
{
    std::stack<int> s;
    int i = path.size() - 1;
    int count = 0;
    std::vector<int>::iterator it;

    //std::cout << std::endl;
    //std::cout << "start: " << start;
    //std::cout << " end: " << i << std::endl;

    while(1)
    {
        if(i == 0)
        {
            break;
        }

        //std::cout << "i=" << i << "; ";
        for(it = path[i].begin(); it != path[i].end(); it++)
        {
            //std::cout << *it << " ";
            s.push(*it);
        }

        i = s.top();
        s.pop();

        if(i == start)
        {
            count++;
            //std::cout << "count=" << count;
            if(s.empty())
            {
                break;
            }
            else
            {
                i = s.top();
                s.pop();
                if(i == start)
                {
                    count++;
                }
            }
        }

        //std::cout << " stack_size=" << s.size();
        //std::cout << std::endl;
    }

    return count;
}

int main(int argc, const char *argv[])
{
    if(argc == 2 || argc == 3 || argc == 4)
    {
        int start = 1;
        int end = 7;
        Graph my_graph(argv[1]);

        my_graph.print();

        if(argc != 2)
        {
            start = atoi(argv[2]);
            if(argc == 4)
            {
                end = atoi(argv[3]);
            }
        }

        //std::cout << std::endl << "start=" << start << "; end=" << end << std::endl;

        dijkstra(my_graph, start);

        GraphVertex& gv = my_graph.get_vertex(end);
        std::cout << std::endl << end << ": " << gv.get_label() << std::endl;

        my_graph.print();

        //print_path_vector();

        //print_first_path(end);

        std::cout << std::endl << "Number of shortest paths: ";
        std::cout << find_number_of_paths(start) << std::endl;
    }
    else
    {
        std::cout << "Type input file as a parameter: dijkstra input.txt" << std::endl;
        std::cout << "Or dijkstra input.txt start_vertex end_vertex" << std::endl;
    }

    return 0;
}
