#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

class Node
{
    public:
        string data;
        Node* next;
        Node* down;

        Node(string d)
        {
            data=d;
            next=down=NULL;
        }
};

class AdjList
{
    Node *head;

    public:
        AdjList()
        {
            head=NULL;
        }

        void create()
        {
            int n,adjCount;
            string vertex;
            Node *current;

            cout<<"\nHow many vertices are there in the graph ?";
            cin>>n;

            for(int i=0;i<n;i++)
            {
                cout<<"\nEnter Vertex: ";
                cin>>vertex;

                if(head==NULL)
                {
                    head=new Node(vertex);
                    current=head;
                }
                else{
                    current->down=new Node(vertex);
                    current=current->down;
                }

                cout<<"How many nodes are adjacent to this node: ";
                cin>>adjCount;

                Node* temp=current;

                for(int j=0;j<adjCount;j++)
                {
                    cout<<"Enter adjacent Node: ";
                    cin>>vertex;

                    temp->next=new Node(vertex);
                    temp=temp->next;
                }
            }

            cout<<"\nAdjacency list created successfully !";
        }

        void display()
        {
            Node* vertex=head;

            while(vertex)
            {
                cout<<"\n";
                Node* temp=vertex;
                while(temp)
                {
                    cout<<" --> "<<temp->data;
                    temp=temp->next;
                }
                cout<<"NULL\n";
                
                vertex=vertex->down;
            }
        }

        void DFS()
        {
            stack<Node*> st;
            vector<Node*> visited;
            cout<<"\nDFS result: ";

            st.push(head);
            visited.push_back(head);

            while (!st.empty())
            {
                Node* curr=st.top();
                st.pop();

                cout<<curr->data<<"  ";

                Node* temp=head;

                while(temp->data!=curr->data)
                {
                    temp=temp->down;
                }
                temp=temp->next;

                while(temp!=NULL)
                {
                    if(!isVisited(visited,temp))
                    {
                        st.push(temp);
                        visited.push_back(temp);
                    }
                    temp=temp->next;
                }
            } 
        }

        bool isVisited(vector<Node*> visited,Node* current)
        {
            for(int i=0;i<visited.size();i++)
            {
                if(visited[i]->data==current->data)
                {
                    return true;
                }
            }
            return false;
        }

        void BFS()
        {
            cout<<"\n\nBFS result: ";

            queue<Node*> q;
            vector<Node*> visited;

            q.push(head);
            visited.push_back(head);

            while(!q.empty())
            {
                Node* curr=q.front();
                q.pop();

                cout<<curr->data<<"  ";

                Node* temp=head;
                while(temp->data!=curr->data)
                {
                    temp=temp->down;
                }
                temp=temp->next;

                while(temp!=NULL)
                {
                    if(!isVisited(visited,temp))
                    {
                        q.push(temp);
                        visited.push_back(temp);
                    }
                    temp=temp->next;
                }
            }
        }
};

int main()
{
    AdjList adjList;
    adjList.create();
    adjList.display();
    adjList.DFS();
    adjList.BFS();

    return 0;
}


// 5 Khadak 3 Kothrud Swargate Katraj Kothrud 2 Khadak Swargate Katraj 3 Khadak Swargate Hadap Swargate 4 Kothrud Khadak Katraj Hadap Hadap 2 Swargate Katraj