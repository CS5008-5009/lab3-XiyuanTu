#include <stdio.h>
#include <stdlib.h>

// Structure for each node of the linked list
typedef struct node {
    int value;
    struct node* next;
} Node;

typedef struct sList {
    Node* head;
    int size;
} SList;

Node* makeNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

SList* makeSList() {
    SList* newList = (SList*)malloc(sizeof(SList));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

void insert(SList* sList, int value, int position) {
    // Create a new node
    Node* newNode = makeNode(value);
    
    // insert the new node at the head
    if (position == 1) {
        newNode->next = sList->head;
        sList->head = newNode;
        sList->size++;
        return;
    }

    Node* pointer = sList->head;

    position--;

    while (--position > 0) {
        if (pointer == NULL) {
            return;
        }
        pointer = pointer->next;
    }

    newNode->next = pointer->next;
    pointer->next = newNode;
    sList->size++;
}

void insertHead(SList* sList, int value) {
    insert(sList, value, 1);
}

void insertTail(SList* sList, int value) {
    insert(sList, value, sList->size + 1);
}


void printLinkedList(SList* sList) {
    Node* pointer = sList->head;
    
    while (pointer != NULL) {
        if (pointer->next != NULL) {
            printf("%d, ", pointer->value);
        } else {
            printf("%d", pointer->value);
        }
        pointer = pointer->next;
    }

    printf("\n");
}

void delete(SList* sList, int value) {
    if (sList->size == 0) {
        return;
    }

    Node* dummy = makeNode(0);
    dummy->next = sList->head;

    Node* pointer = dummy;

    while (pointer != NULL) {
        while (pointer->next != NULL && pointer->next->value == value) {
            Node* next = pointer->next;
            pointer->next = pointer->next->next;
            free(next);
            sList->size--;
        }
        pointer = pointer->next;
    }

    sList->head = dummy->next;
    free(dummy);
}

void deleteHead(SList* sList) {
    if (sList->size == 0) {
        return;
    }

    if (sList->size == 1) {
        Node* head = sList->head;
        sList->head = NULL;
        free(head);
        sList->size--;
        return;
    }

    Node* head = sList->head;
    sList->head = sList->head->next;
    free(head);
    sList->size--;
}

void deleteTail(SList* sList) {
    if (sList->size == 0) {
        return;
    }

    if (sList->size == 1) {
        Node* head = sList->head;
        sList->head = NULL;
        free(head);
        sList->size--;
        return;
    }
    
    Node* pointer = sList->head;

    while (pointer->next->next != NULL) {
        pointer = pointer->next;
    }
    Node* tail = pointer->next;
    pointer->next = NULL;
    free(tail);
    sList->size--;
}

int search(SList* sList, int value) {
    if (sList->size == 0) {
        return -1;
    }

    int position = 1;

    Node* pointer = sList->head;

    while (pointer != NULL) {
        if (pointer->value == value) {
            return position;
        }
        pointer = pointer->next;
        position++;
    }

    return -1;
}

void freeLinkedList(SList* sList) {
    if (sList == NULL) {
        return;
    }

    if (sList->head == NULL) {
        free(sList);
        return;
    }

    Node* curr = sList->head;
    Node* next = curr->next;

    while (curr != NULL) {
        free(curr);
        curr = next;
        if (next != NULL) {
            next = next->next;
        }
    }
}

int main() {
    SList* sList = makeSList();
    insertTail(sList, 23);
    insertTail(sList, 52);
    insertTail(sList, 19);
    insertTail(sList, 9);
    insertTail(sList, 100);

    printf("Current list: ");
    printLinkedList(sList);
    printf("\n");

    printf("Search 19. It's position is %d\n", search(sList, 19));
    printf("\n");

    printf("Insert 7 at position 3\n");
    insert(sList, 7, 3);
    printf("Current list: ");
    printLinkedList(sList);
    printf("\n");

    printf("Insert 7 at head\n");
    insertHead(sList, 7);
    printf("Current list: ");
    printLinkedList(sList);
    printf("\n");

    printf("Insert 7 at tail\n");
    insertTail(sList, 7);
    printf("Current list: ");
    printLinkedList(sList);
    printf("\n");

    printf("Delete 19\n");
    delete(sList, 19);
    printf("Current list: ");
    printLinkedList(sList);
    printf("\n");

    printf("Delete head\n");
    deleteHead(sList);
    printf("Current list: ");
    printLinkedList(sList);
    printf("\n");

    printf("Delete tail\n");
    deleteTail(sList);
    printf("Current list: ");
    printLinkedList(sList);
    printf("\n");
    
    freeLinkedList(sList);
    
    return 0;
}