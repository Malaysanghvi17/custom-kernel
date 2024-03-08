#define NULL ((void*)0)
// kernel.c
#include <stddef.h>
// Simple memory allocator for the kernel
#define MEMORY_SIZE (1024 * 1024)  // Adjust the size as needed

static char memory[MEMORY_SIZE];
static size_t next_free = 0;

void* kmalloc(size_t size) {
    if (next_free + size <= MEMORY_SIZE) {
        void* ptr = &memory[next_free];
        next_free += size;
        return ptr;
    } else {
        // Handle out-of-memory situation
        return NULL;
    }
}

void kfree(void* ptr) {
    // Memory freeing logic if needed
    // This simple allocator does not free memory, but you might need to implement this function
}

struct ListNode {
    int data;
    struct ListNode* next;
};

// Initialize the head of the linked list
struct ListNode* head = NULL;

// Function to insert a new node at the end of the linked list
void insertNode(int newData) {
    struct ListNode* newNode = (struct ListNode*)kmalloc(sizeof(struct ListNode));
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        // If the list is empty, make the new node the head
        head = newNode;
    } else {
        // Traverse the list to find the last node
        struct ListNode* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Insert the new node at the end
        current->next = newNode;
    }
}

// Function to print the elements of the linked list
void printList(char* vidptr, unsigned int* i) {
    struct ListNode* current = head;
    while (current != NULL) {
        // Print or manipulate the data as needed
        // Assuming vidptr is a char* pointing to video memory
        // (this is a simplistic example, and actual video memory access may differ)
        vidptr[*i] = current->data + '0';
        vidptr[*i + 1] = 0x07;
        *i = *i + 2;

        current = current->next;
    }
}

// Example kernel code
void kmain(void) {
    const char *str = "hello, my first kernel!";
    char *vidptr = (char*)0xb8000;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int screensize;

    // this loop clears the screen
    screensize = 80 * 25 * 2;
    while (j < screensize) {
        vidptr[j] = ' ';
        vidptr[j+1] = 0x07;
        j = j + 2;
    }

    j = 0;

    // this loop writes the string to video memory
    while (str[j] != '\0') {
        vidptr[i] = str[j];
        vidptr[i+1] = 0x07;
        ++j;
        i = i + 2;
    }

    // Example usage of the linked list
    int n = 1000;
    int k = 1;
    while(k <= n){
        insertNode(k);
        k++;
    }
    // insertNode(1);
    // insertNode(2);
    // insertNode(3);
    // insertNode(4);
    // insertNode(5);
    // insertNode(6);
    // insertNode(7);
    // insertNode(8);
    printList(vidptr, &i);


    // // Example usage of the simple memory allocator
    // int* data = (int*)kmalloc(sizeof(int));
    // if (data != NULL) {
    //     *data = 42;
    //     // Use 'data' as needed
    // }

    // Note: kfree(data) can be used if needed, but this simple allocator does not implement freeing.

    // Halt the CPU or perform other kernel operations
    __asm__ volatile("hlt");
}
