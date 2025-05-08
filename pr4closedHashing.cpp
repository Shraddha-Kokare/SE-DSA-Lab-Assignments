#include<iostream>
#include<string>
using namespace std;

#define TableSize 10

class Client
{
    long long phone;
    string name;
    bool present;

    public:
        Client()
        {
            phone=-1;
            name="-";
            present=false;
        }

    friend class HashTable;
};

class HashTable
{
    Client table[TableSize];

    int hashFunction(long long phone)
    {
        return phone%TableSize;
    }

    public:
        HashTable()
        {
            for(int i=0;i<TableSize;i++)
            {
                // table[i]=new Client();
                table[i].present=false;
            }
        }
        void insertWithoutReplacement(long long phone,string name)
        {
            int index=hashFunction(phone);
            int original=index;

            // find empty slot
            while(table[index].present)
            {
                index=(index+1)%TableSize;
                if(index==original)
                {
                    cout<<"\nTable is full !!";
                    return;
                }
                    
            }
            table[index].phone=phone;
                    table[index].name=name;
                    table[index].present=true;
            
        }

        void insertWithReplacement(long long phone,string name)
        {
            int index=hashFunction(phone);

            if(table[index].present)
            {
                int existingIndex=hashFunction(table[index].phone);

                if(existingIndex!=index)
                {
                    long long existingPhone=table[index].phone;
                    string existingName=table[index].name;

                    table[index].name=name;
                    table[index].phone=phone;
                    table[index].present=true;

                    insertWithReplacement(existingPhone,existingName);
                }
                else{

                    int newIndex=(index+1)%TableSize;

                    while (table[newIndex].present)
                    {
                        newIndex=(newIndex+1)%TableSize;

                        if(newIndex==index)
                        {
                            cout<<"\nHash table is full !";
                            return;
                        }
                    }

                    table[newIndex].name=name;
                    table[newIndex].phone=phone;
                    table[newIndex].present=true;
                    
                }
            }
            else{
                table[index].name=name;
                table[index].phone=phone;
                table[index].present=true;
            }
        }

        void display()
        {
            cout<<"\nIndex\tPhone Number\tName\tPresent";
            for(int i=0;i<TableSize;i++)
            {
                cout<<endl<<i;
                if(table[i].present)
                    cout<<"\t"<<table[i].phone<<"\t"<<table[i].name<<"\t"<<((table[i].present)?"True":"False");
                else{
                    cout<<"\t"<<"--\t--\tFalse";
                }
                // cout<<endl;
            }
        }

        int search(long long phone)
        {
            int index=hashFunction(phone);

            int original=index;
            int comparisions=0;

            while (table[index].present)
            {
                comparisions++;
                if(table[index].phone==phone)
                {
                    return comparisions;
                }
                index=(index+1)%TableSize;
                if(index==original)
                {
                    return -1;
                }
            }
            return -1;
        }
};

int main()
{
    string name;
    long long phone;
            

    int choice,found;
    HashTable tb;
    int useReplacement;
    cout<<"\nUse replacement method ?";
    cin>>useReplacement;

    do
    {
        cout<<"\n1.Insert \t2.Search\t3.Display\t4.Exit\nEnter your choice:";
        cin>>choice;

        switch (choice)
        {
        case 1:
                cout<<"\nEnter name:";
                cin>>name;
                cout<<"Enter phone:";
                cin>>phone;
            if(useReplacement)
            {
                tb.insertWithReplacement(phone,name);
            }
            else{
                cout<<"\nWithout replacement..";
                tb.insertWithoutReplacement(phone,name);
            }
            break;

        case 2:
            cout<<"\nEnter phone number to search:";
            cin>>phone;
            found=tb.search(phone);
            if(found==-1)
            {
                cout<<"\nNot found !";
            }
            else{
                cout<<"\nFound in comparisions: "<<found;
            }
            
            break;

        case 3:
            tb.display();
            break;

        case 4:
            
            break;
        
        default:
            break;
        }
    } while (choice!=4);
    

    return 0;
}