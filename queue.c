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
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *next;
    if (!q)
        return;
    for (list_ele_t *indirect = q->head; indirect != NULL;) {
        free(indirect->value);
        next = indirect->next;
        free(indirect);
        indirect = next;
    }
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
    list_ele_t *newh;
    char *newstr;
    int len = strlen(s);
    /* TODO: What should you do if the q is NULL? */
    if (!q) {
        return false;
    }

    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    newstr = malloc(sizeof(char) * len + 1);
    if (!newstr) {
        free(newh);
        return false;
    }
    for (int i = 0; i < len; i++) {
        *(newstr + i) = *(s + i);
    }
    *(newstr + len) = '\0';
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    newh->value = newstr;
    q->head = newh;
    if (!(q->tail))
        q->tail = newh;
    (q->size)++;
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
    list_ele_t *newt;
    char *newstr;
    int len = strlen(s);
    if (!q)
        return false;
    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }
    newstr = malloc(sizeof(char) * len + 1);
    if (!newstr) {
        free(newt);
        return false;
    }
    for (int i = 0; i < len; i++) {
        *(newstr + i) = *(s + i);
    }
    *(newstr + len) = '\0';
    newt->next = NULL;
    newt->value = newstr;
    if (!q->tail) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    (q->size)++;
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
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *tmp;
    int i;
    if (!q)
        return false;
    if (q->size == 0)
        return false;
    if (!sp)
        return true;
    for (i = 0; (i < bufsize - 1) && (*(q->head->value + i) != '\0'); i++) {
        *(sp + i) = *(q->head->value + i);
    }
    *(sp + i) = '\0';
    tmp = q->head;
    q->head = q->head->next;
    q->size--;
    free(tmp->value);
    free(tmp);
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
    if (!q)
        return 0;
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return;
    if (q->size == 0)
        return;
    list_ele_t *cur = NULL;
    list_ele_t *header = q->head;
    while (header) {
        list_ele_t *next = header->next;
        header->next = cur;
        cur = header;
        header = next;
    }
    list_ele_t *tmp = q->head;
    q->head = q->tail;
    q->tail = tmp;
    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void mergeSort(list_ele_t **head);
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->size == 0 || q->size == 1) {
        return;
    }
    mergeSort(&q->head);
    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}

void mergeSort(list_ele_t **head)
{
    if (!*head || !(*head)->next)
        return;
    list_ele_t *l1 = (*head)->next;
    list_ele_t *l2 = (*head);
    while (l1 && l1->next) {
        l2 = l2->next;
        l1 = l1->next->next;
    }
    l1 = l2->next;
    l2->next = NULL;
    l2 = *head;

    mergeSort(&l1);
    mergeSort(&l2);

    *head = NULL;
    list_ele_t **cur = head;
    while (l1 && l2) {
        if (strcmp(l1->value, l2->value) < 0) {
            *cur = l1;
            l1 = l1->next;
        } else {
            *cur = l2;
            l2 = l2->next;
        }
        cur = &(*cur)->next;
    }
    *cur = l1 ? l1 : l2;
}