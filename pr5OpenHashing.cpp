#include<iostream>
#include<string>
#define tableSize 10
using namespace std;

class Node
{
    int key;
    string value;
    Node* next;

    public:
        Node()
        {
            key=-1;
            value="";
            next=NULL;
        }
        Node(int k,string val)
        {
            key=k;
            value=val;
            next=NULL;
        }
        friend class Dictionary;
};

class Dictionary
{
    Node *table[tableSize];
    int hashFunction(int k)
    {
        return k%tableSize;
    }

    public:
        Dictionary()
        {
            for(int i=0;i<tableSize;i++)
            {
                table[i]=NULL;
            }
        }

        void insertNode(int k,string val)
        {
            int index=hashFunction(k);
            Node *temp=table[index];

            Node *newNode=new Node(k,val);

            if (table[index]==NULL)
            {
                table[index]=newNode;
                return;
            }

            while(temp->next)
            {
                if(temp->key==k)
                {
                    temp->value=val;
                    return;
                }
                temp=temp->next;
            }
            temp->next=newNode;
        }

        void display()
        {
            for(int i=0;i<tableSize;i++)
            {
                Node* temp=table[i];

                while (temp)
                {
                    cout<<"["<<temp->key<<":"<<temp->value<<"]";
                    temp=temp->next;
                }
                cout<<"NULL";
                cout<<"\n";
            }
        }

        void search(int val)
        {
            int index=hashFunction(val);
            Node* temp=table[index];

            while(temp!=NULL)
            {
                if(temp->key==val)
                {
                    cout<<"Found: ["<<temp->key<<":"<<temp->value<<"]";
                    return;
                }
                temp=temp->next;
            }

            cout<<"\nNot found!!";
        }

        void deleteKey(int k)
        {
            int index=hashFunction(k);

            Node *temp=table[index];
            Node *prev=NULL;

            while(temp!=NULL && temp->key!=k)
            {
                prev=temp;
                temp=temp->next;
            }

            if(temp==NULL)
            {
                cout<<"\nNot Found";
                return;
            }
            else if(prev==NULL)
            {
                table[index]=temp->next;
            }
            else{
                prev->next=temp->next;
            }

            delete temp;
        }
};

int main()
{
    Dictionary dict;
    int choice,key;
    string val;
    do
    {
        cout<<"\n1.Insert\t2.Display\t3.Search\t4.Delete\t5.Exit\nEnter your choice:";
        cin>>choice;

        switch (choice)
        {
        case 1:
            cout<<"\nKey:";
            cin>>key;
            cout<<"Value:";
            cin>>val;
            dict.insertNode(key,val);
            break;

        case 2:
            dict.display();
            break;

        case 3:
            cout<<"\nEnter value to search:";
            cin>>key;
            dict.search(key);
            break;

        case 4:
            cout<<"\nEnter value to delete:";
            cin>>key;
            dict.deleteKey(key);
            break;
        
        default:
            break;
        }
    } while (choice!=5);
    
 
    return 0;
}