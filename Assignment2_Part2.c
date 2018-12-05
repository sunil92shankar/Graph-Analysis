/*
 * Assignment2_Part2.c
 *
 *  Created on: Sep 25, 2018
 *      Author: SUNIL
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions_part2.h"

int main(int argc, char*argv[])
{
	if(argc!=3)
	{
		printf("\nEnter all arguments");
		return 1;
	}

	char* topology=argv[1];
	
	if(topology==NULL)
	{
		printf("\nErroneous argument");
		return 1;
	}

	//code to add .txt to filename
	int str_len = strlen(topology) + strlen(".txt");//get the sum lengths of strings to be concatenated
    	char *new = (char*)malloc(str_len*sizeof(char) + 1);//allocate memory for new string including space for end of string character \0
    	*new = '\0';//store no value in string (empty string) to prepare for concatenation
	topology = strcat(new,topology);
	topology = strcat(topology ,".txt");//concatenate both strings	
	
	char *outfile=argv[2];
	if(outfile==NULL)
	{
		printf("\nErroneous argument");
		return 1;
	}
	
	
	//code to add .txt to filename
	str_len = strlen(outfile) + strlen(".txt");
    	char *new_memory = (char*)malloc(str_len*sizeof(char) + 1);
    	*new_memory = '\0';//empty caharacter array
	outfile = strcat(new_memory, outfile);
	outfile = strcat(outfile ,".txt");	

	FILE *fp;//create file pointer

	fp=fopen(topology,"r");//open file
	if(fp==NULL)//check for successful opening of file
	{
		printf("\nInput File IO error");
		return 1;
	}


	//this part of the code traverses through the text, and extracts vertices and their neighbors
	int value_read=0;//variable to read neighbors (index) to vertices
	char c;//character variable to read and check newline and space characters
	int vertex_index=-1;//variable to hold vertex index (neighbors will be added to this vertex)
	int no_of_nodes=-1;//variable to hold size of the graph
	graph* network = NULL;//create a pointer to a graph
	int check=0;//variable to check for end of text
	while(fp && check==0)//while file pointer is valid and end of file is not reached
	{
		do
		{
			int x = fscanf(fp,"%d%c",&value_read,&c);//read an integer and following character
			if(x==-1)//check for vertex with no neighbors
			{
				add_to_list(network,vertex_index,value_read);//add edge between vertex and neighbor to graph
				check=-1;
				break;
			}
			if(x==1)//reaching end of text being read
			{
				check=-1;
				break;
			}
			if(x!=2)//Check for error in reading file
				{
					printf("\n\tError in reading file");
					return 1;
				}
			else
				{
					if(vertex_index==-1)//check for need to create graph
					{
						no_of_nodes = value_read;//total number of vertices in the graph
						network = generate_graph(no_of_nodes);//Create a graph object
						if(network==NULL)//Check if memory was allocated to graph object
						{
							printf("\nGraph could not be created");
							return -1;
						}
					}

					if(vertex_index!=-1 && c!='\n')//condition where neighbor to vertex exists
					{
						while(fscanf(fp,"%d%c",&value_read,&c)==2)//traverse through all neighbors
						{
							add_to_list(network,vertex_index,value_read);//add edge between vertex and neighbor to graph
							if(c=='\n')//end of line (all neighbors of a vertex checked)
								break;
						}
					}
				}
		}while(c!='\n');//while neighbors to a vertex exist

		vertex_index++;//go to next vertex in graph, and then all its neighbors are traversed for adding into the graph

	}

	int component_nos=0;//Variable to hole total number of components in a graph
	int component_size[1000000]={0};//Array holding sizes of components, assuming no. of components does not exceed 1000000
	for(int i=0;i<network->graph_size;i++)//traversing through all graph vertices
	{
		if(network->visitation_status[i]<0)//check if vertex has been visited for DFS purposes
			{
				component_nos++;//update number of components
				DFS(network,i,&component_nos, component_size);//call DFS on unvisited vertex
			}
	}

	unsigned int check_var = file_print_stat(component_nos, component_size, outfile);//print statistics to file
	if(check_var==-1)//check for success of printing operation
	{
		printf("\nStats could not be printed to file");
		return -1;
	}

	//free memory for new filenames (topology and outfile) created
	if(new!=NULL)
		free(new);
	if(new_memory!=NULL)
		free(new_memory);

	//code to free memory allocated for nodes in a list in an adjacency list and visitation status
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

	//code to free memory allocated for storing visitation station
	if(network->visitation_status!=NULL)
	{
		free(network->visitation_status);
	}

	//code to free memory allocated to the graph
	if(network!=NULL)
		free(network);

return 0;
}
