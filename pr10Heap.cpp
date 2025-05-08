#include<iostream>
using namespace std;
// class BinaryTree;

class Node{
    private:
        int data;
        Node *left,*right;

    public:
        Node(int val)
        {
            data=val;
            left=right=NULL;
        }
    
    friend class BinaryTree;
};

class BinaryTree
{
    public:
        Node *root;

        BinaryTree()
        {
            root=NULL;
        }

        Node* createTree(Node* root)
        {
            int val;
            cout<<"\nEnter data: ";
            cin>>val;

            if(val==-1)
            {
                return NULL;
            }

            Node* newNode=new Node(val);
            root=newNode;
            
            cout<<"For left of "<<val;
            root->left=createTree(root->left);
            cout<<"For right of "<<val;
            root->right=createTree(root->right);

            return root;
        }

        void inorder(Node* node)
        {
            // cout<<"\nInorder: ";
            if(node==NULL)
                return;
            
            inorder(node->left);
            cout<<node->data<<"\t";
            inorder(node->right);
        }

        void preorder(Node* node)
        {
            if(node==NULL)
                return;
            cout<<node->data<<"\t";
            preorder(node->left);
            preorder(node->right);
        }

        void postorder(Node* node)
        {
            if(node==NULL)
                return;
            
            postorder(node->left);
            postorder(node->right);
            cout<<node->data<<"\t";
        }

        int height(Node* node)
        {
            if(root==NULL)
                return -1;
            
            int lHeight=height(node->left);
            int rHeight=height(node->right);

            return 1+max(lHeight,rHeight);
        }

        void countNodes(Node* node,int &internal,int &leaf)
        {
            if(root==NULL)
                return;

            if(root->left==NULL && root->right==nullptr)
            {
                leaf++;
            }
            else{
                internal++;
            }

            countNodes(node->left,internal,leaf);
            countNodes(node->right,internal,leaf);
        }

        void swapNodes(Node* node)
        {
            if(root==NULL)
                return;

            Node* temp=node->left;
            node->left=node->right;
            node->right=temp;

            swapNodes(node->left);
            swapNodes(node->right);
        }

        Node* copyTree(Node* node)
        {
            if(root==NULL)
                return nullptr;
            
            Node* newNode=new Node(node->data);
            newNode->left=copyTree(node->left);
            newNode->right=copyTree(node->right);

            return newNode;
        }

        void eraseNodes(Node* node)
        {
            if(root==NULL)
                return;
            
            eraseNodes(node->left);
            eraseNodes(node->right);

            cout<<"\nDeleting node: "<<node->data<<endl;

            delete node;
            root=NULL;
        }

        Node* createMinHeap(Node* node)
        {
            if(node->left)
            {
                node->left=createMinHeap(node->left);

                if(node->left->data<node->data)
                {
                    int temp=node->data;
                    node->data=node->left->data;
                    node->left->data=temp;
                }  
            }

            if(node->right)
            {
                node->right=createMinHeap(node->right);
                if(node->right->data<node->data)
                {
                    int temp=node->data;
                    node->data=node->right->data;
                    node->right->data=temp;
                }
            }

            return node;
        }

        Node* createMaxHeap(Node* node)
        {
            if(node->left)
            {
                node->left=createMaxHeap(node->left);

                if(node->left->data>node->data)
                {
                    int temp=node->data;
                    node->data=node->left->data;
                    node->left->data=temp;
                }  
            }

            if(node->right)
            {
                node->right=createMaxHeap(node->right);
                if(node->right->data>node->data)
                {
                    int temp=node->data;
                    node->data=node->right->data;
                    node->right->data=temp;
                }
            }

            return node;
        }
};

int main()
{
    BinaryTree btree;
    int choice;
    do
    {
        cout<<"\n1.Create Tree\t2.BFS\t3.Preorder\t4.Inorder\t5.Postorder\t6.Min heap\t7.Max heap\t8.Iterative Postorder\t9.Height\t14.Exit\nEnter your choice: ";
        cin>>choice;

        switch (choice)
        {
        case 1:
            btree.root=btree.createTree(btree.root);
            break;
        case 2:
        
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
            btree.root=btree.createMinHeap(btree.root);
            break;
            case 7:
            btree.root=btree.createMaxHeap(btree.root);
            break;
            case 8:
            break;
            case 9:
            break;
            case 10:
            break;
            case 11:
            break;
            case 12:
            break;
            case 13:
            break;
            case 14:
            break;
        
        default:
            break;
        }
    } while (choice!=0);
    

    return 0;
} 
