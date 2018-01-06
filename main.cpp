/*
 * Author: Sahir
 * Code:   Solves 15 Puzzle via OpenMP using Breadth First Search
 */

//*****************************************************************************************
// Libraries:
//*****************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
#include <map>
#include <omp.h>
#include <list> 

using namespace std;

//*****************************************************************************************
// Global variables:
//*****************************************************************************************
int nodesExplored;
int nodesGenerated;
string optrs[] = {"UP", "DOWN", "LEFT", "RIGHT"};
int goal[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
//*****************************************************************************************

class Node{

  public:
//*****************************************************************************************
// Class variables:
//*****************************************************************************************
     int puzzle[16];
     Node *parent;
     string optr;
     int static id;
//*****************************************************************************************
// Class functions:
//*****************************************************************************************
     Node(){
		 parent = NULL;
		 optr = "";
		 id++;
     }//close ctor
//*****************************************************************************************
    Node(int board[]){
		optr = "";
		parent = NULL;

		for(int i=0;i<16;i++)
			this->puzzle[i] = board[i];
		id++;
    }//close ctor
//*****************************************************************************************
     Node(Node *temp){
		 this->parent = temp->parent;
		 optr = temp->optr;

		 for(int i=0;i<16;i++)
			this->puzzle[i] = temp->puzzle[i];
		 id++;
    }//close copy ctor
//*****************************************************************************************
    string ToString(){
		string retStr="";
		for(int i=0;i<16;i++){
			stringstream ss;
			ss << puzzle[i];
			string str = ss.str();
			retStr = retStr + str;	
		}//close for	
		return retStr;
    }//close ToString
//*****************************************************************************************
};//close class
//*****************************************************************************************
//Static Node id init
int Node::id=0;
//*****************************************************************************************
void Print(int puzzle[], int num){
	
	if(num == 0) cout<<"Solution Found: ";
	else 		 cout<<"Step#"<<num<<":";
	
	cout<<endl;

	for(int i=0;i<16;i++){
    	cout<<puzzle[i]<<" ";
    	if((i+1)%4 == 0)
			cout<<endl;   
	}//close for
}//close Print
//*****************************************************************************************
void SolPath(Node *head){

    Node *p = head;
    
	if(p==NULL)
    	return;
	  
    int i = 0;
    
	while(p!=NULL){
		Print(p->puzzle,i);
		p = p->parent;
		i++;
    }//close while
    
	cout<<endl;
}//close SolPath
//*****************************************************************************************
bool GoalTest(int board[]){

	int count = 0;
	for(int i=0;i<16;i++){
		if(board[i] == goal[i])
			count++;
	}//close for

	if(count == 16)
		return true;

	return false;
}//close GoalTest
//*****************************************************************************************
bool validate(int board[], string o){
    
     if(o == "UP"){
        if(board[0] == 0 || board[1] == 0 || board[2]== 0 || board[3]== 0)
            return false;
        else 
            return true;
     }//close UP
     
     else if(o == "DOWN"){
        if(board[15] == 0 || board[14] == 0 || board[13]== 0 || board[12]== 0)
            return false;
        else 
            return true;         
     }//close DOWN
     
     else if(o == "LEFT"){
        if(board[0] == 0 || board[4] == 0 || board[8]== 0 || board[12]== 0)
           return false;
        else 
           return true;
     }//close LEFT
     
     else{
        if(board[3] == 0 || board[7] == 0 || board[11]== 0 || board[15]== 0)
            return false;
        else 
            return true;
     }//close RIGHT
}//close validate
//*****************************************************************************************
int SearchBlank(int board[]){
	for(int i=0;i<16;i++)
	  if(board[i] == 0)
		return i;
}//close SearchBlank
//*****************************************************************************************

int main() {

	//Open the input file
	ifstream in;
	in.open("input.txt");

	//Declare the puzzle array
	int puzzle[16];

	//Fill it with input
	for(int i=0;i<16;i++)
		in >> puzzle[i];
	
	//Close the file
	in.close();
	
	//Create a new node and pass the puzzle array
	Node node = new Node(puzzle);
//*****************************************************************************************
//	 START BFS:
//*****************************************************************************************
	//Flag to close the loop if solution found
	static bool flag = true;
	
	//Queue of Nodes for BFS
	queue<Node> BFS_Q;
	
	//Push the first node
	BFS_Q.push(node);
	
	//Note the Start time
	double start_time = omp_get_wtime();

	//Initial Goal Check
	if(GoalTest(node.puzzle)){
		Print(node.puzzle,0);
	}//close if
	else{
	
		//List to store all the visited puzzle configs
		list<string> hashSet;
		
		//Run OMP with 8 threads and the following shared variables:
		#pragma omp parallel num_threads(8) shared(BFS_Q, hashSet, nodesExplored, nodesGenerated)
		{	
			//Loop until solution is found
			while(flag){
					
				#pragma omp critical
				{ if(!BFS_Q.empty()){
				}//close pragma critical
					//Get the front node		       	
					Node* current =  new Node (BFS_Q.front());
					
					//Pop it
					BFS_Q.pop();
				
					//Put it in the hash list
					hashSet.push_back(current->ToString());
					
					//Increment the nodes explored
					nodesExplored++;

					//Loop operator times:
			       		for(int i=0;i<4 && flag;i++){
						
						 //Validate if the current operator applied is valid
						 if(validate(current->puzzle,optrs[i]) == true){
						 
						 	//Create a new board and copy the config
							int board[16];
							for(int j=0;j<16;j++)
								board[j] = current->puzzle[j];
							   
							//Fetch the blank index
							int blankIndex = SearchBlank(board);
							
							//Apply operator wise changes
							if(optrs[i] == "UP"){
							    board[blankIndex] = board[blankIndex-4];
							    board[blankIndex-4] = 0;
							}//close if
							else if(optrs[i] == "DOWN"){
							    board[blankIndex] = board[blankIndex+4];
							    board[blankIndex+4] = 0;
							}//close else if
							else if(optrs[i] == "LEFT"){
							    board[blankIndex] = board[blankIndex-1];
							    board[blankIndex-1] = 0;
							}//close if
							else{
							    board[blankIndex] = board[blankIndex+1];
							    board[blankIndex+1] = 0;
							}//close if				
							
							//Create a new node with operator applied
							Node* child = new Node(board);
							
							//Set it's parent
							child->parent = current;
							
							//and the applied operator
							child->optr = optrs[i];
							
							//Increment the nodes generated
							nodesGenerated++;

							//If the node is not in the hash list
							if(!(find(hashSet.begin(),hashSet.end(),child->ToString())
								!= hashSet.end())){	
								
								//And if it's the goal state					
								if(GoalTest(child->puzzle) == true){
									//Print the Solution Path
									SolPath(child);
									//Exit the main loop
									flag = false;
									
					            		}//close if
								
								//Otherwise, add it into the Queue
								BFS_Q.push(child);
					       	
							}//close if
						  }//close if
					}//close for
				  }//close if
			}//close while
		 }//close pragma
	}//close else

	//Calculate the time taken
    double time = omp_get_wtime() - start_time;

    cout<<"Breath First Search Completed"<<endl;
    cout<<"Time taken: "<<time<<endl;
    cout<<"Nodes Explored: "<<nodesExplored<<endl;
    cout<<"Nodes Generated: "<<nodesGenerated<<endl;	
	
	return 0;
}//close main

