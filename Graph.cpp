#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <limits>
using namespace std;
class Vertex;
class Edge
{
	private:	
		Vertex *origin;
		Vertex *destination;
		int distance;
	public:
		Edge(Vertex *org,Vertex *dest,int dist)// Each edge connects two verticies with a given weight
			{
				destination = dest;
				distance = dist;
				origin= org;
			}
		Vertex* getDestination() //gets destination vetex
			{
				return destination;
			}
		Vertex* getOrigin() //get orgin vertex
			{
				return origin;
			}
		int getDistance()// gets wegiht/ distance
			{
				return distance;
			}
		
};

class Vertex
{
	private:
		int idetification; // My bad spelling, but the name of the node
		vector<Edge*> edgeList; //vector of edges
	public:
		Vertex(int s)// constructor
		{
			idetification=s;
		}
		int getName() //return name
		{
			return idetification;
		}
		 Edge* addEdge(Vertex *v, int dist)// adds the edge to the graph CREDIT WIKIPEDIA
		{
			Edge *E = new Edge(this,v,dist);
			edgeList.push_back(E);
			return E;
		}
		void print() //prints the Node
		{
			cout<< idetification<<" : "<< endl;
			for(int i=0;i<edgeList.size();i++)
				cout<<edgeList.at(i)->getOrigin()->getName()<<"----"<<edgeList[i]->getDistance()<<"----"<<edgeList[i]->getDestination()->getName()<<endl;
		}
		bool hasEdge(Vertex* v, int *c )//Checks if the vertex is connected to another vetex and gives the postion
		{

			for(int count=0; count< edgeList.size();count++)
				if((edgeList[count]->getOrigin()==this && edgeList[count]->getDestination()==v))
				{
					*c=count;
					return true;
					
				}
				{
			return false;
		}	
		}
		bool hasEdge(Vertex* v) //just returns a bool if the vertex is connect to another vertex
		{

			for(int count=0; count< edgeList.size();count++)
				if((edgeList[count]->getOrigin()==this && edgeList[count]->getDestination()==v))
					return true;
			return false;
		}
		int getEdgeDist(Vertex* v)// gets the edge distance connecting two vetexs returns infinity if they arent conencted
		{ int c;
			for(int count=0; count< edgeList.size();count++)
				if(this->hasEdge(v,&c))
					return edgeList[c]->getDistance();
				else return numeric_limits<int>::max();
			
		}	
		void Clear()
		{
			for (int i = 0; i < edgeList.size(); ++i)
			{
			delete edgeList[i];
			edgeList[i]=NULL;
			}
		}
		int size(){return edgeList.size();}
	


};
class Graph
{
private:
	vector<Vertex*> vert;
public:
	Graph() //contructor
	{}
	void add(Vertex *v)//Adds vertex to vector of verticies
	{
		vert.push_back(v);
	}
	int getPos(Vertex *v)//gets pos of a vertex
	{
		for (int i = 0; i < vert.size(); ++i)
		{
			if(vert[i]==v)
				return i;
			return -1;
		}
	}
	Vertex* getVert(int p)//gets a vertex given a pos
	{
		return vert[p];
	}

	void printGraph() //prints graph 
	{
		for(int i=0; i<vert.size();i++)
			vert.at(i)->print();
	}
	int size(){return vert.size();}//returns number of vectors
	int getDistance(int i, int j)//calls the getEdgeDist (Made it easier for me to follow along with the book)
	{
		return vert[i]->getEdgeDist(vert[j]);
	}
	void Clear(){
		for (int i = 0; i < vert.size(); ++i)
		{
			vert[i]->Clear();
			delete vert[i];
			vert[i]=NULL;
		}
	}
	void sizeTot()
	{

		int sum=0;
		for(int i=0; i<vert.size();i++)
			sum+=vert.at(i)->size();
		cout<<vert.size()<<" "<<sum<<endl;
	}


};