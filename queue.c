#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return NULL;
    q->head = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
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
    char *srcIndex = s;
    while (*srcIndex)
        srcIndex++;
    /* Make space for length of s plus one `\0` space */
    newh->value = malloc((srcIndex - s + 1) * sizeof(char));
    /* Case 3: newh->value can't be allocated successfully */
    /* free newh and return false */
    if (!newh->value) {
        free(newh);
        return false;
    }
    srcIndex = s;
    char *dstIndex = newh->value;
    while (*srcIndex) {
        *dstIndex = *srcIndex;
        dstIndex++;
        srcIndex++;
    }
    *dstIndex = 0;
    newh->next = q->head;
    q->head = newh;
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
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    bool a = false;
    return a;
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
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return false;
    if (sp) {
        char *srcIndex = q->head->value, *dstBound = sp + bufsize - 1;
        while (*srcIndex && sp < dstBound) {
            *sp = *srcIndex;
            sp++;
            srcIndex++;
        }
        *sp = '\0';
    }
    free(q->head->value);
    list_ele_t *nodeToRemove = q->head;
    q->head = q->head->next;
    free(nodeToRemove);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return 0;
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
