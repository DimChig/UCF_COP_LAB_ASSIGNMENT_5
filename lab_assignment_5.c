#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
    if (head == NULL) return 0; //check
    node* temp = head;
    int l = 0; //lengths counter
    while (temp->next != NULL) { //loop until reaching the end (when temp will = lastNode)
        temp = temp->next; //move to the next node
        l++; //increment counter
    }
    l++; //last character
    return l;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
    if (head == NULL) return ""; //check
    node* temp = head;
    char * s = (char*) malloc(sizeof(char) * (length(head) + 1)); //allocating memory (+1 for '\0')
    int i = 0; //counter
    while (temp->next != NULL) { //loop
        s[i] = temp->letter; //saving letter
        i++; //increment
        temp = temp->next; //moving to next node
    }
    s[i] = temp->letter; //saving last letter
    s[i+1] = '\0'; //saving null character
    return s; //returning pointer to the first letter
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
    if (pHead == NULL) return; //checker

    //Creating new letter
    node* newNode = (node*) malloc(sizeof (node));
    if (newNode == NULL) {
        printf("Failed to allocate memory!");
        return;
    }
    //changing newNode values
    newNode->letter = c;
    newNode->next = NULL;

    node* temp = *pHead;
    if (temp == NULL) { //checking if we have other elements in the list
        //if not, replacing pHead with our new Node
        *pHead = newNode;
        return;
    }

    //else, looping until the end of the list
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode; //updating ".next" of the last note to newNode
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
    if (pHead == NULL) return;
    node* temp = *pHead;
    node* nextNode;
    while (temp->next != NULL) { //looping
        nextNode = temp->next; //saving reference
        free(temp); //freeing memory
        temp = nextNode; //moving forward
    }
    free(nextNode); //freeing last node
    *pHead = NULL; //set head to null
}

int main(void)
{
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt","r");

    fscanf(inFile, " %d\n", &numInputs);

    while (numInputs-- > 0)
    {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++)
        {
            fscanf(inFile," %c", &c);
            insertChar(&head, c);
        }

        str = toCString(head);
        printf("String is : %s\n", str);

        free(str);
        deleteList(&head);

        if (head != NULL)
        {
            printf("deleteList is not correct!");
            break;
        }
    }

    fclose(inFile);
}