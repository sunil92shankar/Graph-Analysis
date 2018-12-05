/*
 * functions.c
 *
 *  Created on: Sep 24, 2018
 *      Author: SUNIL
 */

#include "functions_part1.h"
#include<stdio.h>
#include<stdlib.h>


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
		}

		return network;//Successful operation, return pointer to graph created
}

/*
 * Function to add a node as a neighbor of an element in the adjacency list
 */
node *add_node(int vertex_num)
{
	node *new_node = (node *) malloc (sizeof(node *));//allocate memory for nodes that represent neighbors to adjacency list vertives TODO
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
	node *new_node=add_node(to_node);//create node and save pointer
	if(new_node==NULL)//check if node creation was successful
	{
		printf("\nNode could not be created");
		return -1;//failed operation
	}

	//Procedure to add a new node to a list in the adjacency list
	local->list_array[from_node].list_size++;//as we add a node to a list in the adjacency list, the size of the list increases
	new_node->next=local->list_array[from_node].head;//new node points to previous head of list
	local->list_array[from_node].head=new_node;//new_node becomes the new head of the list

	return 0;//successful addition of edge
}

/*
 * Function to fill a graph with generated values
 */
unsigned int graph_fill(graph *network, double  **grid, int k)
{
	if(network==NULL || grid==NULL ||k<0)//parameter check
	{
		printf("\nInvalid arguments. Operation unsuccessful");
		return -1;//failed operation return -1
	}
	int vertex_count=0;// variable to track vertex to which neighbors are to be added
		for(int i=0;i<k;i++)//k is the size of the grid, here we traverse through the rows of the grid
		{
			for(int j=0;j<k;j++)//traverse through columns of the grid
			{
				if(grid[i][j]>=0)//check if the grid is colored. Note that grid[i][j] is the also the vertex index
				{
						//most general: check for the grid [1:K-1,1:K-1] to account for out of bound conditions
						if (i>0 && i<k-1 && j>0 && j<k-1)
						{
							if(grid[i-1][j]>=0)//Checking neighbor in north
							{
								int check = add_to_list(network,vertex_count,grid[i-1][j]);//check for success of operation to add edge to vertex 'vertex_count'
								if(check==-1)//Checking if operation was unsuccessful
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;//Unsuccessful operation
								}
							}

							if(grid[i+1][j]>=0)//Checking neighbor in south
							{
								int check = add_to_list(network,vertex_count,grid[i+1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j-1]>=0)//Checking neighbor in west
							{
								int check = add_to_list(network,vertex_count,grid[i][j-1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j+1]>=0)//Checking neighbor in east
							{
								int check = add_to_list(network,vertex_count,grid[i][j+1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}
						}

						//checking top left corner grid cell
						if (i==0 && j==0)
						{

							if(grid[i+1][j]>=0)//Checking neighbor in south
							{
								int check = add_to_list(network,vertex_count,grid[i+1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j+1]>=0)//Checking neighbor in east
							{
								int check = add_to_list(network,vertex_count,grid[i][j+1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}
						}

						//checking top right corner cell
						if (i==0 && j==k-1)
						{

							if(grid[i+1][j]>=0)//Checking neighbor in south
							{
								int check=add_to_list(network,vertex_count,grid[i+1][j]);if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j-1]>=0)//Checking neighbor in west
							{
								int check = add_to_list(network,vertex_count,grid[i][j-1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}
						}


						//checking bottom right corner cell
						if (i==k-1 && j==k-1)
						{

							if(grid[i-1][j]>=0)//Checking neighbor in north
							{
								int check = add_to_list(network,vertex_count,grid[i-1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j-1]>=0)//Checking neighbor in west
							{
								int check = add_to_list(network,vertex_count,grid[i][j-1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

						}

						//checking bottom left corner cell
						if (i==k-1 && j==0)
						{

							if(grid[i-1][j]>=0)//Checking neighbor in north
							{
								int check = add_to_list(network,vertex_count,grid[i-1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j+1]>=0)//Checking neighbor in east
							{
								int check = add_to_list(network,vertex_count,grid[i][j+1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

						}

						//checking top row (except left and right extremes)
						if (i==0 && j!=0 && j!=k-1)
						{

							if(grid[i+1][j]>=0)//Checking neighbor in south
							{
								int check = add_to_list(network,vertex_count,grid[i+1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j+1]>=0)//Checking neighbor in east
							{
								int check = add_to_list(network,vertex_count,grid[i][j+1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}
							if(grid[i][j-1]>=0)//Checking neighbor in west
							{
								int check = add_to_list(network,vertex_count,grid[i][j-1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

						}

						//check rightmost column (except top and bottom extremes)
						if (j==k-1 && i!=0 && i!=k-1)
						{

							if(grid[i-1][j]>=0)//Checking neighbor in north
							{
								int check = add_to_list(network,vertex_count,grid[i-1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i+1][j]>=0)//Checking neighbor in south
							{
								int check = add_to_list(network,vertex_count,grid[i+1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j-1]>=0)//Checking neighbor in west
							{
								int check = add_to_list(network,vertex_count,grid[i][j-1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

						}

						//check bottommost row (except left and right extremes)
						if (i==k-1 && j!=0 && j!=k-1)
						{

							if(grid[i-1][j]>=0)//Checking neighbor in north
							{
								int check = add_to_list(network,vertex_count,grid[i-1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j+1]>=0)//Checking neighbor in east
							{
								int check = add_to_list(network,vertex_count,grid[i][j+1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}
							if(grid[i][j-1]>=0)//Checking neighbor in west
							{
								int check = add_to_list(network,vertex_count,grid[i][j-1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

						}

						//check left most column (except top and bottom extremes)
						if (j==0 && i!=0 && i!=k-1)
						{

							if(grid[i-1][j]>=0)//Checking neighbor in north
							{
								int check = add_to_list(network,vertex_count,grid[i-1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i+1][j]>=0)//Checking neighbor in south
							{
								int check = add_to_list(network,vertex_count,grid[i+1][j]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

							if(grid[i][j+1]>=0)//Checking neighbor in east
							{
								int check = add_to_list(network,vertex_count,grid[i][j+1]);
								if(check==-1)
								{
									printf("\nAdd to list operation Unsuccessful");
									return -1;
								}
							}

						}

					vertex_count++;//moving through all vertices in the graph
				}
			}
		}

		return 0;
}

//TODO Modify??
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
	if(fp==NULL)//check for success in opening file TODO return val?
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
            check = check->next;
        }
    }
    fclose(fp);
    return 0;

}
