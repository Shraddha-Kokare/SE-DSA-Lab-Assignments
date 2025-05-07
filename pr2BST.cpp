#include<iostream>
#include<queue>
#define SPACE 10
using namespace std;


class Node
{
    public:
        int data;
        Node *left,*right;
        int level;

        Node(int val)
        {
            data=val;
            level=0;
            left=right=NULL;
        }
};

class BST
{
private:
    /* data */
public:
    Node* root=NULL;


    // Code for creating BST iteratively

    // void createBST()
    // {
    //     int count,data;
    //     cout<<"\nEnter the number of nodes:";
    //     cin>>count;

    //     for(int i=0;i<count;i++)
    //     {
    //         cout<<"Enter data:";
    //         cin>>data;

    //         Node *newNode=new Node(data);
    //         int flag=0;

    //         if(root==NULL)
    //         {
    //             root=newNode;
    //             flag=1;
    //             cout<<"\nRoot";
    //         }
    //         else{
    //             Node* parent=root;
    //             int level=0;

    //             while (flag!=1)
    //             {
    //                 if(newNode->data<parent->data)
    //                 {
    //                     if(parent->left==NULL)
    //                     {
    //                         parent->left=newNode;
    //                         level++;
    //                         newNode->level=level;
    //                         flag=1;
    //                         cout<<"\nInserted";
    //                     }
    //                     else{
    //                         parent=parent->left;
    //                         level++;
    //                     }
    //                 }
    //                 else if(newNode->data>parent->data){
    //                     if(parent->right==NULL)
    //                     {
    //                         parent->right=newNode;
    //                         level++;
    //                         newNode->level=level;
    //                         flag=1;
    //                         cout<<"\nInserted";
    //                     }
    //                     else{
    //                         parent=parent->right;
    //                         level++;
    //                     }
    //                 }
    //             }
                

    //         }
    //     }
    // }

    Node* insertNode(Node* root,int val)
    {
        if(root==NULL)
        {
            return new Node(val);
        }

        if(val<root->data)
        {
            root->left=insertNode(root->left,val);
        }
        else if(val>root->data)
        {
            root->right=insertNode(root->right,val);
        }

        return root;

    }

    int findHeight(Node *node)
    {
        if(node==NULL)
            return 0;

        int lheight=findHeight(node->left);
        int rheight=findHeight(node->right);

        return 1+max(lheight,rheight);
    }

    void MinMaxValue()
    {
        Node* node=root;

        while(node->left)
        {
            node=node->left;
        }
        cout<<"\nMinimum value: "<<node->data;

        node=root;
        while(node->right)
        {
            node=node->right;
        }
        cout<<"\nMaximum Value: "<<node->data; 
    }

    void search(int val)
    {
        int comp=0;
        Node* node=root;

        while(node)
        {
            comp++;
            if(val<node->data)
            {
                node=node->left;
            }
            else if(val>node->data)
            {
                node=node->right;
            }
            else{
                
                cout<<"Value found in "<<comp<<" comparisions.";
                return;
            }
        }

        cout<<"\nVallue not found !";
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

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    bool deleteNode(int val)
    {
        Node *parent=NULL;
        Node* current=root;

        // Searching
        while (current && current->data!=val)
        {
            parent=current;
            if(val<current->data)
            {
                current=current->left;
            }
            else{
                current=current->right;
            }
        }

        if(current==NULL)
            return false;

        // Case 1: Leaf node
        if(current->left==NULL && current->right==NULL)
        {
            if(current!=root)
                if(parent->left==current)
                {
                    parent->left=NULL;
                }
                else{
                    parent->right=NULL;
                }
            else{
                root=nullptr;
            }
            delete current;
        }
        // case 2: Node has 2 children
        else if(current->left!=NULL && current->right!=NULL)
        {
            Node* successor=findMin(current->right);
            int succdata=successor->data;

            deleteNode(succdata);

            current->data=succdata;
        }
        // case 3: Node has 1 child
        else{
            Node* child;
            if(current->left)
            {
                child=current->left;
            }
            else{
                child=current->right;
            }


            if(current==root)
            {
                root=child;
            }
            else{
                if(current==parent->left)
                {
                    parent->left=child;
                }
                else{
                    parent->right=child;
                }
            }

            delete current;
        }
        return true;
        
    }

    void inorder(Node* node)
    {
        if(node==NULL)
            return;
        
        inorder(node->left);
        cout<<node->data<<" ";
        inorder(node->right);
    }

    void preorder(Node* node)
    {
        if(node==NULL)
        {
            return;
        }

        cout<<node->data<<" ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node)
    {
        if(node==NULL)
            return;
        
        postorder(node->left);
        postorder(node->right);
        cout<<node->data<<" ";
    }

    void displayVertical(Node* root) {
        if (!root) return;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node* current = q.front();
                q.pop();
                
                cout << current->data << " ";
                
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            cout << endl;
        }
    }

   
    void printTreeHelper(Node* root, const string& prefix, bool isLeft) {
        if (root != nullptr) {
            cout << prefix;
            cout << (isLeft ? "|--" : "\\--");
            cout << root->data << endl;

            // Enter the next level - left and right branches
            printTreeHelper(root->left, prefix + (isLeft ? "|   " : "    "), true);
            printTreeHelper(root->right, prefix + (isLeft ? "|   " : "    "), false);
        }
    }
};


int main()
{
    BST bst;

    int choice,val,count;
    do
    {
        cout<<"\n1.Create BST\t2.Preorder\t3.Inorder\t4.Postorder\t5.Height\t6.MinMax Value\t7.Search\t8.Swap TreeNodes\t9.Display Tree\t10.Delete node\nEnter your choice:";
        cin>>choice;

        switch (choice)
        {
        case 1:
            // bst.createBST();
            cout<<"\nEnter the number of nodes your want to insert:";
            cin>>count;
            for(int i=0;i<count;i++)
            {
                cout<<"Enter data:";
                cin>>val;
                bst.root=bst.insertNode(bst.root,val);
            }
            break;

        case 2:
            bst.preorder(bst.root);
            break;
        
        case 3:
            bst.inorder(bst.root);
            break;

        case 4:
            bst.postorder(bst.root);
            break;

        case 5:
            cout<<"\nHeight of tree is "<<bst.findHeight(bst.root);
            break;

        case 6:
            bst.MinMaxValue();
            break;

        case 7:
            cout<<"\nEnter value to search: ";
            cin>>val;
            bst.search(val);
            break;

        case 8:
            cout<<"\nPreorder Traversal Before: ";
            bst.preorder(bst.root);
            bst.root=bst.swapTree(bst.root);
            cout<<"\nPreorder Traversal After: ";
            bst.preorder(bst.root);
            break;

        case 9:
            bst.printTreeHelper(bst.root,"",false);
            // bst.displayVertical(bst.root);
            // bst.print2D(bst.root,10);
            // bst.printBT("",bst.root,false);
            break;

        case 10:
            cout<<"\nEnter value:";
            cin>>val;
            bst.deleteNode(val);
            break;
        
        default:
            break;
        }
    } while (choice!=0);
    
    return 0;
}