/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * GitHub:RafaelEstevamReis wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 */
 
#include <stdio.h>   // Allow the usage of printf
#include <stdlib.h>  // Allow the usage of 'malloc', 'free' and 'system(...)'
#include <stdbool.h> // Allow usage of 'bool', 'true' and 'false'

// Create a structure to store a NODE of the List
//  Contains all mandatory info: An ID, and the Next and prev  pointes
typedef struct Nodes{
    // Mandatory Info
    struct Nodes *Next, *Prev;
    int ID;

    // Content
    //  Carefuly insert here your stuff ...
    
} Node;

// Holds a LinkedList instance
//  makes easy to store, maipulate and declarate a new lists
typedef struct LinkedList{
    Node *Start, *End;
} List;

// Create a CabllBack to the Enumarate function
//  Returns FALSE to stop enumerating
typedef bool (*callback)(List*, Node*);

// Create a new empty list
List* CreateList(){
    List *lst = malloc(sizeof(List));
    lst->Start = NULL;
    lst->End = NULL;

    return lst;
}
// Add a new node at the end of the list
//  Returns the new node
Node* AddNodeAtEnd(List* List){
    // Alloc and clean
    Node* newNode = malloc(sizeof(Node));
    newNode->ID = 0;
    newNode->Next = NULL;
    newNode->Prev = NULL;
    
    if(List->Start == NULL){
        List->Start = newNode;
    }

    if(List->End != NULL){
        // Stores the old end (it's not necessary but keeps the code easy to read)
        Node* oldEnd = List->End;
        // As newNode is the new last value of the list, 
        //  we must set the newNode 'previous' to oldEnd
        newNode->Prev = oldEnd;
        // .. and the oldEnd next to be our newNode
        oldEnd->Next = newNode;
    }
    // Finally, set the new last item of the list as newNode
    List->End = newNode;

    return newNode;
}
// Find a node by it's ID and return the node or returns NULL
//   PS: find a node could be implemented using EnumerateList
Node* FindNodeById(List* List, int ID){
    Node* aux = List->Start;
    // Look foward
    while(aux != NULL){
        if(aux->ID == ID) return aux;
        // Move to next
        aux = aux->Next;
    }
    return NULL;
}

// Remove a node by it's ID
void RemoveNodeById(List* List, int ID){
    Node* toRemove = FindNodeById(List, ID);
    // there are no nodes to remove
    if(toRemove == NULL) return;

    // change previus 'next'
    if(toRemove->Prev != NULL) toRemove->Prev->Next = toRemove->Next;
    // change next 'previous'
    if(toRemove->Next != NULL) toRemove->Next->Prev = toRemove->Prev;

    // if toRemove was the start... adjust this...
    if(List->Start == toRemove) List->Start = toRemove->Next;
    // if toRemove was the end... adjust this...
    if(List->End == toRemove) List->End = toRemove->Prev;

    // And finally ...
    free(toRemove);
}

// Run entire List calling the "callback" function to each node, returning the count
int EnumerateList(List* List, callback CB){
    Node* aux = List->Start;
    int count = 0;
    // Look foward
    while(aux != NULL){
        // If has a callback...
        if(CB != NULL) {
            if(CB(List,aux) == false) break;
        }
        // Move to next
        aux = aux->Next;
        count ++;
    }
    return count;
}
// Show a single Node
bool ShowNode(List* List, Node* node){
    printf("Node ID: %d\n",node->ID);
    return true; // Don't stop me now  ~o~
}

int main(int argc, char *argv[]){
    printf("Empty\n");
    List* lst = CreateList();
    // Add the first
    Node* newNode = AddNodeAtEnd(lst);
    newNode->ID = 1;
    // Add the second
    newNode = AddNodeAtEnd(lst);
    newNode->ID = 2;
    // Add the third
    newNode = AddNodeAtEnd(lst);
    newNode->ID = 3;
    
    // Enumerate All, calling 'ShowNode' on each
    printf("-- Enumarate: \n");
    int count = EnumerateList(lst,ShowNode);
    printf("The list has %d items\n",count);
    
    printf("Removing the '2'\n");
    RemoveNodeById(lst, 2);

    // Enumerate All, to test the removal
    printf("-- Enumarate: \n");
    EnumerateList(lst,ShowNode);

    // Remove first to test
    RemoveNodeById(lst, 1);
    // Enumerate All to check
    printf("-- Enumarate: \n");
    EnumerateList(lst,ShowNode);

    // Remove last to test
    RemoveNodeById(lst, 3);
    // Enumerate All to check
    printf("-- Enumarate: \n");
    count = EnumerateList(lst,ShowNode);
    printf("The list now has %d items\n",count);

    system("pause");
    return 0; // sucess
}
