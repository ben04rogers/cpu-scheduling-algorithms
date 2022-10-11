/* Program:  rr_sched.c
 * Purpose:  using linked list queues for Round-Robin Scheduling
 *=========================================================*/

#include <stdlib.h>
#include <stdio.h>

struct process
{
    char data;
    int burst;
    struct process *next;
};

#define QUANTUM 50

typedef struct process node;

node *head = NULL; /* ready queue's head */
node *tail = NULL; /* ready queue's tail */

node *dhead = NULL; /* dispatcher RR scheduling queue's head */
node *dtail = NULL; /* dispatcher RR scheduling queue's tail */

void print_list(node *);

/*insert function for the ready queue */
void r_insq(node *new)
{
    if (tail == NULL) /* empty list */
        head = new;
    else
        tail->next = new;
    tail = new;
}

/* delete function for the ready queue */
node *r_delq()
{
    struct process *tmp;
    if (head == NULL) /* list empty */
        return (NULL);

    tmp = head;
    if (head == tail) /* only one element in the list */
        head = tail = NULL;
    else
        head = head->next;

    return (tmp);
}

/* insert function for the scheduling queue*/

void d_insq(node *new)
{
    if (dtail == NULL) /* empty list */
        dhead = new;
    else
        dtail->next = new;
    dtail = new;
}

int main()
{
    node *p;
    int i;

    /* initializing the ready queue for RR */
    for (i = 1; i <= 5; i++)
    {
        p = (node *)malloc(sizeof(node));
        p->data = 64 + i;
        p->burst = (int)((double)(99) * rand() / (999999999 + 1.0));
        p->next = NULL;
        r_insq(p);
    }

    printf("The ready queue for the RR scheduling is: \n\n");
    print_list(head);
    printf("\n\n");

    /* the RR scheduling algorithm, insert your solution here for task1 */
    for (;;) {
        int finished = 1;
        node *traverse = head;

        while (traverse != NULL) {
            if (traverse->burst > 0) {
                finished = 0;
                int burst_size;
                if (traverse->burst < QUANTUM) {
                    burst_size = traverse->burst;
                } else {
                    burst_size = QUANTUM;
                }

                traverse->burst -= burst_size;
                
                // Create new node
                node *rr_node = malloc(sizeof(node));
                rr_node->data = traverse->data;
                rr_node->burst = burst_size;
                rr_node->next = NULL;
                
                // Insert node
                d_insq(rr_node);
            }
            traverse = traverse->next;
        }

        if (finished) break;
    }


    printf("The resulting RR schedule is: \n\n");
    print_list(dhead);
    printf("\n\n");

    return 0;
}

void print_list(node *p)
{
    if (p == NULL)
        printf("^\n");
    else
    {
        while (p->next)
        {
            printf("(%c, %d) --> ", p->data, p->burst);
            p = p->next;
        }
        printf("(%c, %d) ^\n ", p->data, p->burst);
    }
}
