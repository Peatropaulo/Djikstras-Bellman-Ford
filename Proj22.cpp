# include <iostream>
# include <vector>
# include "Graph.cpp"
# include <limits>
#include <ctime>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <iomanip> 
#include <time.h>
#include <stdio.h>
using namespace std;
int minDist(vector<int> d,vector<bool> s, int size); //Gets Min Distance
void shortestPath(Graph *G, int source,int u,int e); //Dijakstra's Algorithim
int makeGraph2(Graph* G,vector<Vertex*> *Vertix,vector<Edge*> *Edge,int nodeCount);//Revised Make Graph
void Bellman(Graph *G,int source, vector<Vertex*> Vertix,vector<Edge*> Edge,int u,int e);//Bellman-ford Algorithim
void outputToFile(double h,double d,double c,int edge,int count);//output first file
void outputToFile2(double h,double d,double c,int edge,int count);//output second file
int main()
{
	srand(time(NULL));//Rand time
	vector<Vertex*> VList;//List of Verticeis
	vector<Edge*> EList;//List Of Edges
	for (int i = 0; i < 101; ++i)//100 iterations for graphing
	{
	Graph* G=new Graph();//Makes Graph
	cout<<i<<endl;//Which Iteration we are on
	int u=rand()%8192+64;//Rand between 8192 and 64
	makeGraph2(G,&VList,&EList,u);//Makes the Graph and keeps a list of edges and verticies
 	//G->printGraph();//prints graph 
	cout<<VList.size()<<" : "<<EList.size()<<endl;
	shortestPath(G,0,u,EList.size());//Dijakstras
	//Bellman(G,0,VList,EList,u,e);//Bellman-Ford
	VList.clear();//clears Verticeis
	EList.clear();//Clears Verticeis
	G->Clear();//Clears the graph
	delete G;//Free the Memory
	G=NULL;//Make sure we dont call bad memory
	}
	return 0;
}
// /C:\\MinGw\bin\proj22
int makeGraph2(Graph* G,vector<Vertex*> *Vertix,vector<Edge*> *Edge,int nodeCount)
{
	Vertex *Vert; 
	Vertex *s=new Vertex(0);
	Vertix->push_back(s);
	G->add(s);
	for (int i = 0; i < nodeCount; i++)
	{
		Vert=new Vertex(i+1); 
		Vertix->push_back(Vert);
		G->add(Vert);
	}
	for(int y=0;y<G->size();y++)
	{
		Vertex *v=G->getVert(y);
	for(int x=0;x<G->size();x++)
		{
			if(G->getVert(x)!=v  && rand()%(100)==6)//Makes sure a vertex cannot connect to itself and a % chance to make a conenction for each vertex
			{
				int Edgeweight = rand()%5+1;//Random Edge Weight
				Edge->push_back(v->addEdge(G->getVert(x),Edgeweight));//Adds edge to vertex and thus to graph
			}
		}
	}
	
}
void Bellman(Graph *G,int source, vector<Vertex*> Vertix,vector<Edge*> Edge,int u,int e)
{	
	const clock_t begin_time=clock();//Gets the intial time
	vector<int> Distance; //Distance Vector
	vector<int> Hop;//Hop Vector
	int n=Vertix.size();//Vertex Size

	for(int i=0;i<n;i++) //Initalize the distance to be infinite
		Distance.push_back(numeric_limits<int>::max());	
	for(int i=0;i<Edge.size();i++)// Initalize the hop matirx
		Hop.push_back(0);
	Distance[source]=0;//Distance to source is 0
	for (int i = 0; i <= n-1; ++i)//Number of Verticeis
	{
		for(int x=0;x<Edge.size();x++)//Number of Edges
		{
			int u=Edge[x]->getOrigin()->getName();//Origin Vetex
			int v=Edge[x]->getDestination()->getName();//Destiantin Vertex
			int w=Edge[x]->getDistance();//Weight
			if (Distance[u] != numeric_limits<int>::max() && Distance[u] + w < Distance[v])//as long as the path with this edge weight added is less than the total so far add its distance to our total
			{
				Distance[v] = Distance[u] + w;//we update it
			Hop[x]=Hop[x]+1;
		}
		}
	}
	/*for (int i = 0; i < Edge.size(); ++i)// Print
	{
	int u=Edge[i]->getOrigin()->getName();
			int v=Edge[i]->getDestination()->getName();
			int w=Edge[i]->getDistance();

		if (Distance[u] != numeric_limits<int>::max()&& Distance[u] + w < Distance[v])
			printf("Graph contains negative weight cycle.");
	}*/

	double avgD; //Average Distance
	double avgH; //Average Hops
	double sumH=0,sumD=0; // Sums
	int total1=0,total2=1; // Totals
	float dif = (float) (clock()-begin_time)/CLOCKS_PER_SEC;//Time for the algorithim
for (int i = 0; i < Distance.size(); ++i)//Sums everything together
{
	if(Distance[i]!=numeric_limits<int>::max())
	{
	sumD+=Distance[i];
	total1++;
}
	if(Hop[i]!=0)
		{	sumH+=Hop[i];
			total2++;
		}
}

avgH=sumH/total2;//average
avgD=sumD/total1;//average
	cout<<"Average Distance"<<"  "<<"       Average Hops   "<<"           Time"<<endl;
cout<<std::fixed<<std::setprecision(8)<<avgD<<"            :         "<<avgH<<"    :   "<<dif<<endl;
	outputToFile(dif,avgD,avgH,Edge.size(),u);//outputs to file
}
void shortestPath(Graph *G, int source,int u, int e)
{
	const clock_t begin_time=clock();
		vector<bool> shortPath; //vector of bools IDEA CREDIT WIKIPEDIA
	vector<int> Distance; // vector of bools IDEA CREDIT WIKIPEDIA
	vector<int> Hop;
	int n=G->size();

	for(int i=0;i<n;i++) 
	{
		shortPath.push_back(false); //Make everything false
		Distance.push_back(numeric_limits<int>::max());// Make the distances infinite
		Hop.push_back(0);
	}
	Distance[source]=0;//the distance from source is zero duh (Base Case)
	for (int i = 0; i < n-1; i++) //for every vertex not in the graph
	{
		int min=minDist(Distance,shortPath,n); //Find the minimum node path from the vertex as long as it isnt in the set
		
		shortPath[min]=true;//place that vertex in the set

		for(int c=0;c<n;c++)
		{
			// As long as the vertex is not in the set
			// and as long as the vertex conenction to another is valid
			// and as long as the weight isnt innfinfity
			//and as long as the path with this edge weight added is less than the total so far add its distance to our total
			if(!shortPath[c] && G->getVert(min)->hasEdge(G->getVert(c)) && Distance[min]!=numeric_limits<int>::max() && (Distance[min] + G->getDistance(min,c))<Distance[c])
			{
				Hop[c]=Hop[c]+1;
				Distance[c]=Distance[min]+G->getDistance(min,c);
			}
		}

	} ///this is just to print
	//	cout<<"Vertex "<<" Distance "<<" Hops"<<endl;
	//for(int x=0;x<Distance.size();x++)
	//{
	//	if(Distance[x]==numeric_limits<int>::max())
	//	cout<<x<<"     :     "<<"N/A"<<endl;
	//	else
	//		cout<<x<<"     :     "<<Distance[x]<<"   :   "<<Hop[x]<<endl;
	//}
	
	double avgD;
	double avgH;
	double sumH=0,sumD=0;
	int total1=0,total2=1;
	float dif = (float) (clock()-begin_time)/CLOCKS_PER_SEC;
for (int i = 0; i < Distance.size(); ++i)
{
	if(Distance[i]!=numeric_limits<int>::max())
	{
	sumD+=Distance[i];
	total1++;
}
	if(Hop[i]!=0)
		{	sumH+=Hop[i];
			total2++;
		}
}

avgH=sumH/total2;
avgD=sumD/total1;
	cout<<"Average Distance"<<"  "<<"       Average Hops   "<<"           Time"<<endl;
cout<<std::fixed<<std::setprecision(8)<<avgD<<"            :         "<<avgH<<"    :   "<<dif<<endl;
	outputToFile2(dif,avgD,avgH,e,u);

}
void outputToFile(double h,double d,double c,int edge,int count)
{
ofstream myfile; 
myfile.open("Bellman.txt",std::fstream::app);//Text File in CSV format for matlab to read
  if (myfile.is_open())
  {
    myfile << std::fixed << std::setprecision(8) <<count<<","<<edge<<","<<h<<","<<d<<","<<c<<endl;
    myfile.close();
  }
  else cout << "Unable to open file";
}
void outputToFile2(double h,double d,double c,int edge,int count)
{
ofstream myfile; 
myfile.open("Dijakstra.txt",std::fstream::app);
  if (myfile.is_open())
  {
    myfile << std::fixed << std::setprecision(8) <<count<<","<<edge<<","<<h<<","<<d<<","<<c<<endl;
    myfile.close();
  }
  else cout << "Unable to open file";
}
int minDist(vector<int> d,vector<bool> s,int size)
{
	int min=numeric_limits<int>::max();
	int minPos;

	for (int a = 0; a < size ; a++)
	{
		if(s[a]==false && d[a]<=min)//As long as the node isnt in the set and min current is greater we switch min pos and min
		{
			min=d[a];
			minPos=a;
		}

	}
		return minPos;

}
//C:\\MinGw\bin\PMHW6