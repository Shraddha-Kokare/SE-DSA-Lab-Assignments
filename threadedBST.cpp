#include<iostream>
using namespace std;

class TBTNode
{
    public:
        int data;
        TBTNode* left;
        TBTNode* right;
        bool lthread,rthread;

        TBTNode(int val)
        {
            data=val;
            left=right=NULL;
            lthread=rthread=true;
        }
};

class Tree
{
    public:
        TBTNode *root;

        Tree()
        {
            root=NULL;
        }
        void insert(int val)
        {
            TBTNode* newNode=new TBTNode(val);

            if(root==NULL)
            {
                root=newNode;
                return;
            }

            TBTNode *current=root;
            while(true)
            {
                if(val<current->data)
                {
                    if(current->lthread)
                    {
                        newNode->left=current->left;
                        newNode->right=current;
                        current->left=newNode;
                        current->lthread=false;

                        return;
                    }
                    else{
                        current=current->left;
                    }
                }
                else if(val>current->data){
                    if(current->rthread)
                    {
                        newNode->right=current->right;
                        newNode->left=current;
                        current->right=newNode;
                        current->rthread=false;

                        return;
                    }
                    else{
                        current=current->right;
                    }
                }
            }
        }

        void preorder()
        {
            TBTNode* current=root;

            while (current!=NULL)
            {
                cout<<current->data<<"  ";
                if(!current->lthread)
                {
                    current=current->left;
                }
                else if(!current->rthread)
                {
                    current=current->right;
                }
                else{
                    while(current!=NULL && current->rthread)
                    {
                        current=current->right;
                    }
                    if(current!=NULL)
                        current=current->right;
                }
            } 
        }

        void inorder()
        {
            TBTNode* current=root;

            while(!current->lthread)
            {
                current=current->left;
            }

            while(current!=NULL)
            {
                cout<<current->data<<"\t";

                if(current->rthread)
                {
                    current=current->right;
                }
                else{
                    current=current->right;
                    while (!current->lthread)
                    {
                        current=current->left;
                    }
                    
                }
            }
        }

        bool deleteNode(int key)
        {
            TBTNode* parent=NULL;
            TBTNode* current=root;

            // Search for node
            bool found=false;
            while(current!=NULL)
            {
                if(key==current->data)
                {
                    found=true;
                    break;
                }

                parent=current;
                if(key<current->data)
                {
                    if(!current->lthread)
                    {
                        current=current->left;
                    }
                    else
                        break;
                    
                }
                else{
                    if(!current->rthread)
                    {
                        current=current->right;
                    }
                    else
                        break;
                }
            }
            if(!found)
                return false;

            // case 1: 2 children
            if(!current->lthread && !current->rthread)
            {
                deleteNodeWithTwoChildren(current);
            }

            // case 2: Node with 1 child
            else if(!current->lthread || !current->rthread)
            {
                deleteNodeWithOneChild(parent,current);
            }

            // case 3: Node is a leaf node
            else{
                deleteLeaf(parent,current);
            }
        }

        void deleteNodeWithTwoChildren(TBTNode* current)
        {
            TBTNode* parentSucc=current;
            TBTNode* succ=current->right;

            while (!succ->lthread)
            {
                parentSucc=succ;
                succ=succ->left;
            }

            current->data=succ->data;

            // Delete successor
            if(succ->lthread && succ->rthread)
            {
                deleteLeaf(parentSucc,succ);
            }
            else{
                deleteNodeWithOneChild(parentSucc,succ);
            }
            
        }

        void deleteNodeWithOneChild(TBTNode* parent,TBTNode* current)
        {
            TBTNode* child;

            if(!current->lthread)
            {
                child=current->left;
                // Find rightmost of left child
                TBTNode* predecessor=inorderPredecessor(current);
                predecessor->right=current->right;
            }
            else if(!current->rthread)
            {
                child=current->right;
                TBTNode *successor=inorderSuccessor(current);
                successor->left=current->left;
            }

            if(parent==NULL)
                root=child;
            else if(current==parent->left)
            {
                parent->left=child;
            }
            else{
                parent->right=child;
            }

            delete current;

        }

        
        void deleteLeaf(TBTNode* parent,TBTNode* current)
        {
            // Deleting root
            if(parent==NULL)
            {
                root=NULL;
            }
            else if(current==parent->left)
            {
                parent->left=current->left;
                parent->lthread=true;
            }
            else if(current==parent->right)
            {
                parent->right=current->right;
                parent->rthread=true;
            }

            delete current;
        }


        TBTNode* inorderPredecessor(TBTNode* node)
        {
            if(node->lthread)
            {
                return node->left;
            }

            node=node->left;
            while(!node->rthread)
            {
                node=node->right;
            }
            return node;
        }

        TBTNode* inorderSuccessor(TBTNode* node)
        {
            if(node->rthread)
            {
                return node->right;
            }

            node=node->right;
            while (!node->lthread)
            {
                node=node->left;
            }

            return node;
            
        }

};

int main()
{
    int choice,val;
    Tree tree;
    do
    {
        cout<<"\n\n1.Insert\t2.Preorder\t3.Inorder\t4.Delete\t5.Exit\nEnter your choice:";
        cin>>choice;

        switch (choice)
        {
        case 1:
            cout<<"\nEnter value:";
            cin>>val;
            tree.insert(val);
            break;
        
        case 2:
            tree.preorder();
            break;

        case 3:
            tree.inorder();
            break;

        case 4:
            int num;
            cout<<"\nEnter number to delete: ";
            cin>>num;
            tree.deleteNode(num);
            break;
        
        default:
            break;
        }

    } while (choice!=5);
    
    
    return 0;
}

// 1 100 1 50 1 170 1 25 1 80
// 1 100 1 20 1 150 1 10 1 30 1 120 1 170 1 7 1 15 1 25 1 50 1 160 1 200 1 5 1 13 1 28  1 60 1 155 1 26 1 152 1 157