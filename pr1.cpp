#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
class Node
{
    int data;
    Node *left,*right;

    public:
        Node()
        {
            left=right=NULL;
        }
        Node(int v)
        {
            data=v;
            left=right=NULL;
        }
        friend class BinaryTree;
};
class BinaryTree
{
    public: 
        Node* root=NULL;

        Node* createTree(Node *node)
        {
            int data;
            cout<<"Enter data:";
            cin>>data;

            if(data==-1)
                return nullptr;
            
            Node *newNode=new Node(data);
            node=newNode;

            cout<<"To left of "<<data;
            node->left=createTree(node->left);
            cout<<"To right of "<<data;
            node->right=createTree(node->right);

            return node;
        }

        void preorder(Node *node)
        {
            if(node==NULL)
                return;
            
            cout<<node->data<<" ";
            preorder(node->left);
            
            preorder(node->right);
        }

        void iterative_preorder(Node *node)
        {
            stack<Node*> st;
            if(node==NULL)
            {
                cout<<"\nEmpty..";
                return;
            }

            st.push(node);
                
            while (!st.empty())
            {
                Node *node=st.top();
                st.pop();
                cout<<node->data<<" ";

                if(node->right)
                    st.push(node->right);
                if(node->left)
                    st.push(node->left);
            }
            
        }

        void inorder(Node *node)
        {
            if(node==NULL)
                return;
            
            
            inorder(node->left);
            cout<<node->data<<" ";
            inorder(node->right);
        }

        void iterative_inorder(Node *node)
        {
            stack<Node*> st;
            if(node==NULL)
            {
                cout<<"\nEmpty..";
                return;
            }

            // st.push(node);

            while(node!=NULL || !st.empty())
            {
                while(node)
                {
                    st.push(node);
                    node=node->left;
                }

                node=st.top();
                st.pop();
                cout<<node->data<<" ";
                node=node->right;
            }
        }
        void postorder(Node *node)
        {
            if(node==NULL)
                return;           
            
            postorder(node->left);
            postorder(node->right);
            cout<<node->data<<" ";
        }
        void iterative_postorder(Node *root)
        {
            stack<Node*> st1,st2;

            st1.push(root);

            while(!st1.empty())
            {
                Node *node=st1.top();
                st1.pop();

                st2.push(node);
                
                if(node->left)
                    st1.push(node->left);
                if(node->right)
                    st1.push(node->right);
            }

            while(!st2.empty())
            {
                cout<<st2.top()->data<<" ";
                st2.pop();
            }
        }
        void bfs(Node *root)
        {
            Node *node=root;

            queue<Node*> q;
            if(root==NULL)
            {
                cout<<"\nEmpty tree !";
                return;
            }

            q.push(root);

            while(!q.empty())
            {
                node=q.front();
                q.pop();
                cout<<node->data<<" ";

                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }
        }
        int height(Node *node)
        {
            if(node==NULL)
            {
                return 0;
            }

            int lheight=height(node->left);
            int rheight=height(node->right);

            return 1+max(lheight,rheight);
        }

        void countNodes(Node *node,int &internal,int &leaf)
        {
            if(node==NULL)
            {
                return;
            }

            if(!node->left && !node->right) //leaf
            {
                leaf++;
                // countNodes(node->)
            }
            else{
                internal++;
            }
            countNodes(node->left,internal,leaf);
            countNodes(node->right,internal,leaf);
        }

        Node* swapTree(Node *node)
        {
            if(node==NULL)
                return nullptr;

            Node* temp=node->left;
            node->left=node->right;
            node->right=temp;

            node->left=swapTree(node->left);
            node->right=swapTree(node->right);

            return node;
        }

        void printTreeHelper(Node *root,const string &prefix,bool isLeft)
        {
            if(root!=NULL)
            {
                cout<<prefix;
                cout<<(isLeft?"|--":"\\--");
                cout<<root->data<<endl;

                printTreeHelper(root->left,prefix+(isLeft?"|   ":"    "),true);
                printTreeHelper(root->right,prefix+(isLeft?"|   ":"    "),true);
            }
        }
};
int main()
{
    BinaryTree btree;
    Node *copyTree;
    string str="";
    int inter=0,leaf=0;
    int choice;
    do
    {
        cout<<"\n1.Create Tree\t2.BFS\t3.Preorder\t4.Inorder\t5.Postorder\t6.Iterative Preorder\t7.Iterative Inorder\t8.Iterative Postorder\t9.Height\t10.Count nodes\t11.Swap nodes\t12.Copy tree\t13.Delete all nodes\t14.Exit\t15.Display Tree\nEnter your choice: ";
        cin>>choice;

        switch (choice)
        {
        case 1:
            btree.root=btree.createTree(btree.root);
            break;
        case 2:
            btree.bfs(btree.root);
            break;

        case 3:
            btree.preorder(btree.root);
            break;  
        case 4:
            btree.inorder(btree.root);
            break;

            case 5:
            btree.postorder(btree.root);
            break;
            case 6:
            btree.iterative_preorder(btree.root);
            break;
            case 7:
            btree.iterative_inorder(btree.root);
            break;
            case 8:
            btree.iterative_postorder(btree.root);
            break;
            case 9:
            // int 
            cout<<"Height is "<<btree.height(btree.root);
            break;
            case 10:
            
            btree.countNodes(btree.root,inter,leaf);
            cout<<"\nInternal: "<<inter;
            cout<<"\nLeaf: "<<leaf;
            break;
            case 11:
            btree.root=btree.swapTree(btree.root);
            break;
            case 12:
            // copyTree=btree.copyTree(btree.root);
            break;
            case 13:
            // btree.eraseNodes(btree.root);
            break;
            case 14:
            break;
            case 15:
                
                btree.printTreeHelper(btree.root,str,false);
                break;
        
        default:
            break;
        }
    } while (choice!=0);
    
    return 0;
}
// 40 60 30 32 -1 -1 -1 16 -1 -1 15 20 -1 -1 25 -1 -1