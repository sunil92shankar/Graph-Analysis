/*
 * functions.c
 *
 *  Created on: Sep 24, 2018
 *      Author: SUNIL
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "functions_part2.h"

/*
 * Generate graph of a given size
 */
graph* generate_graph(int graph_size)
{
	if(graph_size<0)//Parameter check
		{
			printf("Graph creation failed. graph size cannot be negative");
			return NULL;
		}
		graph *network = (graph *) malloc (sizeof(graph));//Allocate memory for graph
		if(network==NULL)//check for success of memory allocation
		{
			printf("\nMemory allocation for graph failed.");
			return NULL;
		}
		network->graph_size=graph_size;//Initialize graph size to graph object
		network->list_array = (list_element *)malloc (graph_size * sizeof(list_element));//Allocate memory for adjacency list
		network->visitation_status=(int *)malloc (graph_size * sizeof(int));//Allocate memory for visitation status
		if(network->visitation_status==NULL)//check for success of memory allocation
				{
					printf("\nMemory allocation for graph failed.");
					return NULL;
				}
		if(network->list_array==NULL)//check for success of memory allocation
		{
			printf("\nMemory allocation for graph failed.");
			return NULL;
		}

		//initialize adjacency list elements from [0 to 'no.of.nodes in graph']
		for(int i=0;i<graph_size;i++)
		{
			network->list_array[i].head=NULL;//No neighbors (nodes) of adjacency list elements as of now
			network->list_array[i].index=i;//Allocating indices (node numbers) to adjacency list elements
			network->list_array[i].list_size=0;//While adjacency list itself is filled, the elements do not point to any neighbors (nodes)
			network->visitation_status[i]=-1;//initializing visitation status for vertex i
		}

		return network;//Successful operation, return pointer to graph created
}


/*
 * Function to add a node as a neighbor of an element in the adjacency list
 */
node *add_node(int vertex_num)
{
	node *new_node = (node *) malloc (sizeof(node *));//allocate memory for nodes that represent neighbors to adjacency list vertices
	if(new_node==NULL)//check success of memory allocation operation
	{
		printf("\nMemory allocation for a node was unsuccessful.");
		return NULL;
	}
	new_node->index = vertex_num;//initialize index of node
	new_node->next=NULL;//new node does not point to any other node as of yet

	return new_node;//Successful operation in adding a node, return pointer to node created
}


/*
 * Add an edge to the graph, in other words add a neighbor (node) to a list in an adjacency list
 * Adds edge (from_node, to_node) to the graph
 */
unsigned int add_to_list(graph *local, int from_node, int to_node)
{
	if(local==NULL || from_node<0 || to_node<0)//parameter check
	{
		printf("\nInvalid arguments");
		return -1;//failed operation
	}

	int fr_node=-1;
	for(int i=0;i<local->graph_size;i++)
	{
		if(local->list_array[i].index==from_node)
		{
			fr_node=i;
		}
	}

	node *new_node=add_node(to_node);//create node and save pointer
	if(new_node==NULL)//check if node creation was successful
	{
		printf("\nNode could not be created");
		return -1;//failed operation
	}

	//Procedure to add a new node to a list in the adjacency list
	local->list_array[fr_node].list_size++;//as we add a node to a list in the adjacency list, the size of the list increases
	new_node->next=local->list_array[fr_node].head;//new node points to previous head of list
	local->list_array[fr_node].head=new_node;//new_node becomes the new head of the list

	return 0;//successful addition of edge
}

//TODO Modify
/*
 * Function to write graph to file in adjacency list format
 */
unsigned int printGraph(graph* local, char* filename)
{
	if(local==NULL || filename==NULL)//parameter check
	{
		return -1;
	}
	FILE *fp;//declare file pointer
	fp = fopen(filename,"w");
	if(fp==NULL)
	{
		printf("\n\tFile Could not be opened");
		return -1;
	}

	fprintf(fp,"%d", local->graph_size);//printing graph size to file

    for (int i= 0; i < local->graph_size;i++)//iterating over all vertices in the graph
    {
        node * check = local->list_array[i].head;
        fprintf(fp,"\n%d", local->list_array[i].index);//print the index of the adjacency list element
        while (check)//iterating through all elements/nodes in the list pointed to by the adjacency list element
        {
            fprintf(fp," %d", check->index);//print neighbor of adjacency list vertex to file
            check = check->next;//move to next neighbor
        }
    }
    fclose(fp);//close file pointer
    return 0;

}

/*
 * This function performs DFS on a subgraph starting from a predefined source node
 */
unsigned int DFS(graph *local, int node_initial, int *comp_nos, int *comp_size)
{

	if(local==NULL || node_initial<0 || comp_nos==NULL)//parameter checks
		{
			printf("\nFaulty arguments");
			return -1;//Argument error
		}
	local->visitation_status[node_initial]=1;//node_initial is marked as having been visited
	node* temp=local->list_array[node_initial].head;//store neighbor of node initial in temp
	comp_size[*comp_nos]++;//update component size for current component
	while(temp!=NULL)//loop through neighbors of vertex node_initial
	{
		if(local->visitation_status[temp->index]==-1)//if a neighbor has not been visited, then apply DFS on that neighbor
		{
			DFS(local,temp->index,comp_nos, comp_size);//Recursive application of DFS
		}

		temp=temp->next;//move to next node in list
	}

	return 0;
}


/*
 * Function to print statistics to a file
 */
unsigned int file_print_stat(int component_nos, int *component_size, char *filename)
{
	FILE *fp;//declare file pointer fp
	fp = fopen(filename,"w");//open file and assign to file pointer
	if(fp==NULL)//Check file pointer
	{
		printf("\n\tFile Could not be opened");
		return -1;
	}

	fprintf(fp,"%d", component_nos);//print number of components in the graph to file

	double ave_size=0;//variable to calculate average component size
	for(int i=1;i<=component_nos;i++)//traverse through all components
	{
		ave_size+=component_size[i];//sum up component sizes
	}
	ave_size=ave_size/component_nos;//get average of component sizes
	fprintf(fp,"\n%lf",ave_size);//print average size of components to file

	int max_size=0;//variable to hold max size of components
	for(int i=1;i<=component_nos;i++)//traverse through all components
	{
		if(max_size<component_size[i])//search for maximum component size
			max_size=component_size[i];
	}
	fprintf(fp,"\n%d", max_size);//print max component size to file
	
	for(int i=1;i<=max_size;i++)//traverse through sizes of components
	{
		int count=0;//variable to hold number of components of a size
		for(int j=1;j<=component_nos;j++)//traverse through all components
			{
				if(i==component_size[j])//calculating number of components of size i
					count++;
			}
		fprintf(fp,"\n%d %d", i, count);//print component size and corresponding number of components to file
	}

    fclose(fp);
    return 0;//successful printing to file
}
