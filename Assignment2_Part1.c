/*
 * Assignment2.c
 *
 *  Created on: Sep 23, 2018
 *      Author: SUNIL
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "functions_part1.h"

unsigned int main(int argc, char *argv[])
{
	if(argc!=4)
	{
		printf("\nPlease enter all arguments");
	}

	int K = -1;
	sscanf(argv[1],"%d",&K);//grid size
	if(K==-1)//checking for valid input
	{
		printf("\nPlease enter valid grid size");
		return -1;
	}
	double P = -1;
	sscanf(argv[2],"%lf",&P);//probability of a node being colored
	if(P>1 || P<0)//checking for valid probability input
	{
		printf("\nPlease enter valid grid size");
		return -1;
	}
	char *filename = argv[3];//filename to write output of graphgen to
	strcat(filename,".txt");//Appending .txt to the filename passed by the user

	srand(time(NULL));//seed rand() with time
	double **grid = (double **) malloc(K*sizeof(double *));//allocate memory for grid
	if(grid==NULL)//check for success of memory allocation
	{
		printf("\nMemory allocation failed.");
		return -1;//operation failure
	}
	for (int i=0;i<K;i++)//traverse through all rows of grid
	{
		grid[i] = (double *) malloc(K*sizeof(double));//allocate memory for all columns of grid element i
		if(grid[i]==NULL)//Check for success of memory allocation
			{
				printf("\nMemory allocation failed.");
				return -1;//operation failure
			}
	}

	int no_colored_nodes=0;//variable to track colored nodes
	for (int i=0;i<K;i++)//traverse through grid rows
		for (int j=0;j<K;j++)//traverse through grid columns
		{
			double gen_prob = (rand()/(double)RAND_MAX);//generate probability values
			if(gen_prob<P)//Check for colored cell
			{
				grid[i][j]=no_colored_nodes;//Meaning that the cell is colored with a probability of P, and we store the node number here (instead of just 1 or 0)
				no_colored_nodes++;//Increase count of number of colored nodes
			}
			else
			{
				grid[i][j]=-1;//Meaning that the cell is left uncolored with a probability of 1-P
			}

		}

	//code to print grid generated
	printf("\nGenerated Grid\n");
	for (int i=0;i<K;i++)//iterate through rows of grid
	{
		printf("\n");
			for (int j=0;j<K;j++)//iterate through columns of grid
			{
				if(grid[i][j]>=0)//checking if grid cell is colored
					printf("\t%3d",1);//meaning colored
				else
					printf("\t%3d",0);//meaning uncolored

			}
	}

	graph *network = generate_graph(no_colored_nodes);//create a graph, allocate memory here
	if(network==NULL)//check for success of graph creation
	{
		printf("\nGraph could not be generated");
		return -1;
	}

	graph_fill(network, grid, K);//Fill graph with values

	printGraph(network, filename);//print graph to file in adjacency list format

	//code to free memory allocated for nodes in a list in an adjacency list
	for(int i=0;i<network->graph_size;i++)
	{
		node *current=network->list_array[i].head;
		while(current!=NULL)
		{
			node *temp = current;
			current=current->next;
			free(temp);
		}
	}

	//code to free memory allocated for adjacency list
	if(network->list_array!=NULL)
		free(network->list_array);

	//code to free memory allocated to the graph
	if(network!=NULL)
		free(network);

	//code to free memory for grid columns
	for (int i=0;i<K;i++)
	{
		if(grid[i]!=NULL)
			free(grid[i]);
	}

	//free memory allocated to grid rows
	if(grid!=NULL)
		free(grid);

	return 0;
}






