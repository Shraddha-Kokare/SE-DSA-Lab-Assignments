#include<iostream>
#include<climits>
using namespace std;
const int MAX_SIZE=20;

class Graph{
    public:
        int Matrix[MAX_SIZE][MAX_SIZE];
        int totalVertices;

        Graph(int total)
        {
            totalVertices=total;
            for(int i=0;i<total;i++)
            {
                for(int j=0;j<total;j++)
                {
                    Matrix[i][j]=0;
                }
            }
        }

        void createGraph()
        {
            int count,src,dest,weight;
            cout<<"\nEnter the number of edges:";
            cin>>count;

            for(int i=0;i<count;i++)
            {
                cout<<"\nEnter source, destination, weight of the edge:";
                cin>>src>>dest>>weight;

                Matrix[src][dest]=weight;
                Matrix[dest][src]=weight;
            }
        }

        void displayGraph()
        {
            for(int i=0;i<totalVertices;i++)
            {
                for(int j=0;j<totalVertices;j++)
                {
                    cout<<Matrix[i][j]<<"\t";
                }
                cout<<endl;
            }
        }

        void minCost()
        {
            bool visited[MAX_SIZE]={false};
            int total_cost=0;
            int edgeCount=0;

            visited[0]=true;

            while(edgeCount<totalVertices-1)
            {
                int r=-1,c=-1;
                int min=INT_MAX;

                for(int i=0;i<totalVertices;i++)
                {
                    if(visited[i])
                        for(int j=0;j<totalVertices;j++)
                        {
                            if(!visited[j] && Matrix[i][j] && Matrix[i][j]<min)
                            {
                                min=Matrix[i][j];
                                r=i;
                                c=j;
                            }
                        }
                }
                

                if(r!=-1 && c!=-1)
                {
                    visited[c]=true;
                    total_cost=total_cost+Matrix[r][c];

                    cout<<"\nEdge: "<<r<<" - "<<c<<", Cost: "<<Matrix[r][c]<<endl;
                    edgeCount++;
                }
            }
            cout<<"\nTotal Cost: "<<total_cost;
        }
};

int main()
{
    int numVre;
    cout<<"\nEnter the number of vertices: ";
    cin>>numVre;
    Graph graph(numVre);
    graph.createGraph();
    graph.displayGraph();
    graph.minCost();
    return 0;
}

// 0 1 4
// 0 3 5
// 0 4 2
// 4 3 2
// 1 3 3
// 1 2 1
// 2 3 8