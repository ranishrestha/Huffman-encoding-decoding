#include <iostream>
#include <fstream>
#include<string>

using namespace std;

class HTreeNode
{
    public:
    string chStr;
    int prob;
    string code;
    HTreeNode* left;
    HTreeNode* right;
    HTreeNode* next;

    HTreeNode()
    {
        chStr = "dummy";
        prob = 0;
        code = "";
        left =NULL;
        right = NULL;
        next =NULL;

    }
    HTreeNode(string chStrr, int probr, string coder, HTreeNode *leftr, HTreeNode *rightr, HTreeNode *nextr)
    {
        chStr = chStrr;
        prob = probr;
        code = coder;
        left = leftr;
        right = rightr;
        next = nextr;

    }

    void printNode (HTreeNode* T, ofstream &outFile)
    {
        if(T->left == NULL && T->right == NULL && T->next!= NULL && T->next!= nullptr)
        {
            outFile << "( " <<T->chStr <<", " << T->prob <<", "<< T->code<<","<< T->next->chStr << ","  <<"NULL, NULL" <<")->";  
        }
        
        else if ((T->left == NULL && T->right == NULL && T->next == NULL )|| (T->left == NULL && T->right == NULL && T->next == nullptr ))
        {
            outFile << "( " <<T->chStr <<", " << T->prob <<", "<< T->code<<",NULL, NULL, NULL)->";   
        }
        else if (T->next == NULL || T->next == nullptr )
        {
            outFile << "( " <<T->chStr <<", " << T->prob <<", "<< T->code<<",NULL," << T->left->chStr <<"," << T->right->chStr <<")->";  
        }
        else
        outFile << "( " <<T->chStr <<", " << T->prob <<", "<< T->code<<","<< T->next->chStr << "," << T->left->chStr <<"," << T->right->chStr <<")->";  
    }
};

class LinkedList
{
    public:
    HTreeNode* listHead;
    LinkedList()
    {
        listHead = new HTreeNode();

    }
    LinkedList(HTreeNode* head)
    {
        listHead = head;
    }
    HTreeNode* findSpot (HTreeNode *listHead, HTreeNode *newNode)
    {
        HTreeNode *spot = listHead;
        while(spot -> next!= NULL && spot->next->prob < newNode -> prob)
        {
             spot = spot->next;
        }
        return spot;

    }
    public: void listInsert(HTreeNode* listHead, HTreeNode* newNode)
    {
       
        HTreeNode* spot = findSpot(listHead, newNode);
        newNode->next = spot->next;
        spot->next = newNode;
       
        
    }

    public: void printList(HTreeNode *listHead, ofstream &outFile )
    {
        HTreeNode *iterator = listHead;
        outFile << "List Head ->";
        while(iterator->next!= nullptr)
        {
           
            iterator->printNode(iterator, outFile);
            iterator = iterator->next;
            
        }
        if (iterator->next == nullptr)
        {
            iterator->printNode(iterator, outFile);
        }
        
        outFile<< endl;
    }

};

class HuffmanBinaryTree
{
    public:
    LinkedList myList;
    HTreeNode* Root;

    HuffmanBinaryTree ()
    {
        Root = new HTreeNode();
    }
    HuffmanBinaryTree(HTreeNode *root)
    {
        Root = root;
    }
    public: HTreeNode *constructHuffmanLList (ifstream &inFile, ofstream &outFile)
    {
        
        string chStr1;
        int prob;
        HTreeNode* listHead = myList.listHead;
        while(inFile >> chStr1 >> prob)
        {
            
            HTreeNode* newNode = new HTreeNode(chStr1,prob," ",NULL,NULL,NULL);
            myList.listInsert(listHead,newNode);
            outFile <<"HList:" <<endl;
            myList.printList(listHead,outFile);

        }
        return listHead;
    }
    public: HTreeNode* constructHuffmanBinTree (HTreeNode* listHead, ofstream &outFile)
    {
        HTreeNode *point = listHead;
        while( point->next ->next!=nullptr)
      {
            HTreeNode* treeNode = new HTreeNode();
            treeNode->chStr = point->next->chStr+point->next->next->chStr;
            cout << treeNode->chStr;
            treeNode->prob = point-> next->prob + point->next->next->prob;
            cout << treeNode->prob;
            treeNode->left = point->next;
            treeNode->right = point->next ->next;
            treeNode ->next = NULL;
             myList.listInsert(listHead, treeNode);
             listHead->next = listHead ->next ->next->next;
             outFile <<"bintree:" << endl;
             myList.printList(listHead,outFile);
        
       }
        return point->next;

    }
    bool isLeaf(HTreeNode* T)
    {
        if(T->left == NULL && T->right == NULL)
        return true;
        return false;
    }
    void constructcharcode(HTreeNode* T, string code, ofstream& outFile )
    {
        if(isLeaf(T))
        {
            T->code =code;
            outFile << T->chStr <<"," <<T->code << endl;

        }
        else
        {
            constructcharcode(T->left, code+"0",outFile);
            constructcharcode(T->right, code+"1", outFile);
        }
        

    }
    void preOrder (HTreeNode* root, ofstream &outFile)
    {
        if (isLeaf(root))
        {
            root->printNode(root,outFile);
        }
        else
        {
            root->printNode(root,outFile);
            preOrder(root->left, outFile);
            preOrder(root->right, outFile);
        }
    }
    void inOrder (HTreeNode* root, ofstream &outFile)
    {
        if (isLeaf(root))
        {
            root->printNode(root,outFile);
        }
        else
        {
            inOrder(root->left, outFile);
            root->printNode(root,outFile);
            inOrder(root->right, outFile);
        }
    }
    void postOrder (HTreeNode* root, ofstream &outFile)
    {
        if (isLeaf(root))
        {
            root->printNode(root,outFile);
        }
        
        else
        {
            postOrder(root->left, outFile);
            postOrder(root->right, outFile);
            root->printNode(root,outFile);
        }
        
    }
};

int main(int argc, char** argv)
{
    ifstream infile;
    ofstream outfile1;
    ofstream outfile2;
    ofstream outfile3;
    infile.open(argv[1]);
    outfile1.open(argv[2]);
    outfile2.open(argv[3]);
    outfile3.open(argv[4]);
    HuffmanBinaryTree myTree;
    HTreeNode* myListHead;
    myListHead = myTree.constructHuffmanLList(infile, outfile3);
    myTree.myList.printList(myListHead,outfile2);
    HTreeNode* root;
    root = myTree.constructHuffmanBinTree(myListHead, outfile3);
    outfile2 << "inOrder:" <<endl;
    myTree.inOrder(root, outfile2);
    outfile2 << endl<< "preOrder:" <<endl;
    myTree.preOrder(root, outfile2);
    outfile2 << endl<<"postOrder:" <<endl;
    myTree.postOrder(root, outfile2);
    myTree.constructcharcode(root, " ", outfile1);
    infile.close();
    outfile1.close();
    outfile2.close();
    outfile3.close();

}