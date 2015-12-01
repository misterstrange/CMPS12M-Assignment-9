#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf(stderr, __VA_ARGS__);

/* Internal implementation definitions */
struct queue_node {
    queue_item_t item;
    struct queue_node *link;
};

typedef struct queue_node queue_node;

struct queue {
    queue_node *front;
    queue_node *rear;
};

/* Functions */

queue *queue_new(void) {
    queue *this = malloc(sizeof (struct queue));
    assert(this != NULL);
    this->front = NULL;
    this->rear = NULL;
    return this;
}

void queue_free(queue *this) {
    assert(queue_isempty(this));
    free(this);
}

void queue_insert(queue *this, queue_item_t item) {
    struct queue_node *n;
    n = (struct queue_node *) malloc(sizeof (struct queue_node));
    n->item = item;
    n->link = NULL;
    if (this->front == NULL) {
        this->front = n;
        this->rear = n;
    }
    else {
        this->rear->link = n;
        this->rear = n;
    }
}

queue_item_t queue_remove(queue *this) {
    assert(!queue_isempty(this));
    struct queue_node *n = this->front;
    queue_item_t package = this->front->item;
    this->front = n->link;
    free(n);
    return package;
}

bool queue_isempty(queue *this) {
    return this->front == NULL;
}
