/* Program:  sjf_sched.c
 * Purpose:  using linked list queues for Round-Robin Scheduling
 *=========================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct process
{
    char data;
    int burst;
    struct process *next;
};

typedef struct process node;

node *head = NULL; /* ready queue's head */
node *tail = NULL; /* ready queue's tail */

node *fhead = NULL; /* SJF scheduling queue's head */
node *ftail = NULL; /* SJF scheduling queue's tail */

void print_list(node *);

void sjf(node *p); /* the shortest job first scheduling algorithm */

/*insert function for the ready queue */
void r_insq(node *new)
{
    if (tail == NULL) /* empty list */
        head = new;
    else
        tail->next = new;
    tail = new;
}

void f_insq(node *new)
{
    if (ftail == NULL) /* empty list */
        fhead = new;
    else
        ftail->next = new;
    ftail = new;
}

int main()
{
    node *p;
    int i;

    /* initializing the ready queue for SJF */
    for (i = 1; i <= 6; i++)
    {
        p = (node *)malloc(sizeof(node));
        p->data = 64 + i;
        p->burst = (int)((double)(99) * rand() / (999999999 + 1.0));
        p->next = NULL;
        r_insq(p);
    }

    printf("The ready queue for the SJF scheduling is: \n\n");
    print_list(head);
    printf("\n\n");

    /* FJF scheduling */
    sjf(head);
    printf("The resulting SJF schedule is: \n\n");
    print_list(fhead);
    printf("\n\n");

    return 0;
}

void sjf(node *p)
{
    //TO DO - Implement SJF Solution
    for (;;) {
        node *traversal = p;
        int shortest_job_length = INT_MAX;
        node *shortest_job = NULL;

        while (traversal != NULL) {

            if (traversal->burst < shortest_job_length) {
                shortest_job_length = traversal->burst;
                shortest_job = traversal;
            }

            traversal = traversal->next;
        }

        if (shortest_job != NULL) {
            node *sj = malloc(sizeof(node));
            sj->data = shortest_job->data;
            sj->burst = shortest_job->burst;
            sj->next = NULL;

            f_insq(sj);

            shortest_job->burst = INT_MAX;
        } else {
            break;
        }
    }
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
