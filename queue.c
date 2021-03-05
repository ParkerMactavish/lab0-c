#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Function prototype for merging queue when sorting
 */
list_ele_t *sort_List(list_ele_t *);
list_ele_t *merge_List(list_ele_t *, list_ele_t *);

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    /* Allocate a memory with size of queue_t */
    queue_t *q = malloc(sizeof(queue_t));
    /* If allocation is not successful */
    /* Return NULL pointer */
    if (!q)
        return NULL;
    /* Initialize data member and return pointer to this queue_t */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* If q is NULL */
    /* Do nothing and return */
    if (!q)
        return;
    /* Iterate through elements in queue q with pointer to list_ele_t*/
    /* For every element, the string pointed by value of the element
        and the element itself would be freed */
    list_ele_t *currentEleToFree = q->head, *nextEleToFree;
    while (currentEleToFree) {
        nextEleToFree = currentEleToFree->next;
        free(currentEleToFree->value);
        free(currentEleToFree);
        currentEleToFree = nextEleToFree;
    }
    /* Free the queue itself */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* Case 1: Queue hasn't been created yet */
    /* Return false directly */
    if (!q)
        return false;
    /* Allocate a element pointer `newh` */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    /* Case 2: newh can't be allocated successfully */
    /* Return false directly */
    if (!newh)
        return false;
    /* Count length of `s` */
    char *srcPtr = s;
    while (*srcPtr)
        srcPtr++;
    /* Make space for length of s plus one `\0` space */
    newh->value = malloc((srcPtr - s + 1) * sizeof(char));
    /* Case 3: newh->value can't be allocated successfully */
    /* Free newh and return false */
    if (!newh->value) {
        free(newh);
        return false;
    }
    /* Get beginning of source string and destination string */
    srcPtr = s;
    char *dstPtr = newh->value;
    /* Copy until terminating character and append a terminating charater at the
        end of destination string*/
    while (*srcPtr) {
        *dstPtr = *srcPtr;
        dstPtr++;
        srcPtr++;
    }
    *dstPtr = 0;
    /* Adjust connection of the linked list */
    newh->next = q->head;
    q->head = newh;
    /* Adjust direct connection to tail */
    if (!q->tail)
        q->tail = newh;
    /* Increase size */
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* Case 1: Queue hasn't been created yet */
    /* Return false directly */
    if (!q)
        return false;
    /* Allocate a element pointer `newt` */
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    /* Case 2: newt can't be allocated successfully */
    /* Return false directly */
    if (!newt)
        return false;
    /* Count length of `s` */
    char *srcPtr = s;
    while (*srcPtr)
        srcPtr++;
    /* Make space for length of s plus one `\0` space */
    newt->value = malloc((srcPtr - s + 1) * sizeof(char));
    /* Case 3: newt->value can't be allocated successfully */
    /* Free newt and return false */
    if (!newt->value) {
        free(newt);
        return false;
    }
    /* Get beginning of source string and destination string */
    srcPtr = s;
    char *dstPtr = newt->value;
    /* Copy until terminating character and append a terminating charater at the
        end of destination string */
    while (*srcPtr) {
        *dstPtr = *srcPtr;
        dstPtr++;
        srcPtr++;
    }
    *dstPtr = 0;
    /* Adjust connection of the liked list in case of empty queue */
    if (!q->head) {
        q->head = newt;
        q->tail = newt;
    } else {
        /* Connect `newt` to `tail` */
        q->tail->next = newt;
        /* Make `newt` as `tail` */
        q->tail = newt;
    }
    /* Make queue as NULL terminated and increase in size */
    newt->next = NULL;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* If q is NULL or empty */
    /* Return false directly */
    if (!q || !q->head)
        return false;
    /* If sp is pointing to an allocated memory */
    /* Copy q->head->value to sp up to bufsize - 1 or end of q->head->value,
        and append a terminating character at the end of sp */
    if (sp) {
        char *srcPtr = q->head->value, *dstBound = sp + bufsize - 1;
        while (*srcPtr && sp < dstBound) {
            *sp = *srcPtr;
            sp++;
            srcPtr++;
        }
        *sp = 0;
    }
    /* Adjust the connection and get the element to remove */
    list_ele_t *eleToRemove = q->head;
    q->head = q->head->next;
    /* Adjust the address which tail is pointed to */
    if (q->size < 2)
        q->tail = q->head;
    /* Free the space taken by string in the element and the element itself */
    free(eleToRemove->value);
    free(eleToRemove);
    /* Decrease size */
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* If value of q is NULL */
    /* Return 0 */
    if (!q)
        return 0;
    /* Return size stored in q */
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* If value of q is NULL */
    /* Return immediately without any operation */
    if (!q || q->size < 2)
        return;
    /* Get prevPtr as NULL, original head to `opPtr`
        and utilize `tmpPtr` to swap head and tail */
    list_ele_t *prevPtr = NULL, *opPtr = q->head, *tmpPtr = q->head;
    q->head = q->tail;
    q->tail = tmpPtr;

    /* Now iterate from new tail (original head) to new head */
    while (prevPtr != q->head) {
        /* prevPtr, opPtr, tmpPtr store previous, current and next elements as
            a sliding window.
            ...| |  | |->| |...
         prevPtr↑    ↑    ↑tmpPtr
                     └opPtr
            ...| |<-| |  | |...
         prevPtr↑    ↑    ↑tmpPtr
                     └opPtr
            ...| |<-| |  | |->
              prevPtr↑    ↑tmpPtr/opPtr
            ...| |<-| |  | |->| |
              prevPtr↑    ↑    ↑tmpPtr
                          └opPtr
        */
        tmpPtr = opPtr->next;
        opPtr->next = prevPtr;
        prevPtr = opPtr;
        opPtr = tmpPtr;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* Check for null-pointing pointer or
        list pointed with only one or zero element */
    /* Return directly */
    if (!q || q->size < 2)
        return;
    /* Utilize `sort_List` function to sort head of queue */
    q->head = sort_List(q->head);
    /* Iterate through the list to get tail */
    /* TODO: Check if it's possible to update tail on sorting list */
    q->tail = q->head;
    for (int i = 1; i < q->size; i++) {
        q->tail = q->tail->next;
    }
}

list_ele_t *sort_List(list_ele_t *head)
{
    /* If head is NULL pointer or the element followed is a NULL pointer */
    /* Return as base case */
    if (!head || !head->next)
        return head;
    /* Assign two pointers to list_ele_t, slow one to get middle point when
        fast iterate through whole list */
    list_ele_t *fast = head->next;
    list_ele_t *slow = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    /* Pointer fast acts as head of second list,
        and make tail of first terminated with a NULL pointer as next */
    fast = slow->next;
    slow->next = NULL;
    /* Recursively split list until base case */
    head = sort_List(head);
    fast = sort_List(fast);
    /* Merge the internally sorted two lists */
    return merge_List(head, fast);
}

list_ele_t *merge_List(list_ele_t *l1, list_ele_t *l2)
{
    /* Declare two pointer to list_ele_t, one for storing head of list,
        the other for iteration */
    list_ele_t *newListIndex, *newListHead;
    /* Get smaller element between first elements on l1 and l2 */
    if (strcmp(l1->value, l2->value) < 0) {
        newListIndex = l1;
        l1 = l1->next;
    } else {
        newListIndex = l2;
        l2 = l2->next;
    }
    /* Assign it to the head */
    newListHead = newListIndex;
    /* Iterate through l1 and l2 */
    while (l1 && l2) {
        /* If first element on l1 is smaller than the one on l2,
            link it element on l1 to current list and get next element on l1 */
        if (strcmp(l1->value, l2->value) < 0) {
            newListIndex->next = l1;
            newListIndex = newListIndex->next;
            l1 = l1->next;
        }
        /* If first element on l2 is smaller than the one on l1,
            link it element on l2 to current list and get next element on l2 */
        else {
            newListIndex->next = l2;
            newListIndex = newListIndex->next;
            l2 = l2->next;
        }
    }
    /* After iteration on l1 and l2, if there is any element left on l1 or l2,
        link them directly to current list */
    if (l1) {
        newListIndex->next = l1;
    }
    if (l2) {
        newListIndex->next = l2;
    }
    /* Return head of list */
    return newListHead;
}