/*
 * function_part1.h
 *
 *  Created on: Sep 27, 2018
 *      Author: SUNIL
 */

#ifndef FUNCTIONS_PART1_H_
#define FUNCTIONS_PART1_H_


//define type of Adj_node (refers to a node in list, which is itself part of an adjacent list)
typedef struct Adj_Node node;
struct Adj_Node
{
	int index;//vertex number in a graph
	node *next;//pointer to the next node in the list
};


//define type of Adj_List_Element (an element in the list of lists)
typedef struct Adj_List_Element list_element;
struct Adj_List_Element
{
	int index;//vertex number in a graph
	int list_size;//size of list pointed to by head
	node *head;//pointer to the first neighbor (head) in the list
};

//define type of Graph (structure holding information on the graph)
typedef struct Graph graph;
struct Graph
{
	int graph_size;//no. of vertices in the graph
	list_element *list_array;//pointer to the list of lists (for the adjacency list)
};


/*
 * Allocate memory for elements in a graph and initialize the values.
 *
 * @param graph_size, the number of vertices in the graph to be created
 * @return pointer to graph created if successful, else return NULL
 */
graph* generate_graph(int graph_size);


/*
 * Allocate memory for a node in a list in the adjacency list
 *
 * @param vertex_num, the order of the vertex which is to be added to the list
 * @return pointer to the node created if successful, else, return NULL
 */
node *add_node(int vertex_num);


/*
 * Add a node to the list in the adjacency. this operation represents addition of a neighbor vertex to a list
 *
 * @param *local, a pointer to the graph
 * @param from_node, the index of the node to hich the neighbor is to be added
 * @param to_node, the index of the vertex being added as the neighbor to the 'from_node'
 * return integer indicating success of operation: 0 if successful, -1 otherwise
 */
unsigned int add_to_list(graph *local, int from_node, int to_node);


/*
 * Fill graph using data generated on grid
 *
 * @param *network, pointer to the graph
 * @param **grid, pointer to the 2D matrix
 * @param k, size of the grid
 *
 * return 0 if successful, -1 otherwise
 */
unsigned int graph_fill(graph *network, double  **grid, int k);


/*
 * Print graph to a file in adjacency list format
 *
 * @param *local, pointer to the graph structure
 * @param *filename, pointer to the file to which the function writes
 *
 * return 0 if successful, -1 otherwise
 */
unsigned int printGraph(graph* local, char* filename);

#endif /* FUNCTIONS_PART1_H_ */
