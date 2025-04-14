// Implementation of the FriendBook ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fb.h"
#include "List.h"
#include "Map.h"
#include "Queue.h"

#define DEFAULT_CAPACITY 1 // DO NOT change this line

struct adjNode {
    int v;
    struct adjNode *next;
};

// DO NOT modify this struct
struct fb {
    int numPeople;
    int capacity;

    char **names; // the id of a person is simply the index
                  // that contains their name in this array
    
    Map nameToId; // maps names to ids

    struct adjNode **adj; // adjacency lists, kept in increasing order
};

static void increaseCapacity(Fb fb);
static int nameToId(Fb fb, char *name);

static struct adjNode *newAdjNode(int v);
static bool inAdjList(struct adjNode *l, int v);
static void freeAdjList(struct adjNode *l);

// Please ignore this line
static struct adjNode * __attribute__((unused)) newAdjNode(int v);

////////////////////////////////////////////////////////////////////////

// Creates a new instance of FriendBook
Fb FbNew(void) {
    Fb fb = malloc(sizeof(*fb));
    if (fb == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    fb->numPeople = 0;
    fb->capacity = DEFAULT_CAPACITY;
    
    fb->names = calloc(fb->capacity, sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    fb->nameToId = MapNew();

    fb->adj = calloc(fb->capacity, sizeof(struct adjNode *));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    return fb;
}

void FbFree(Fb fb) {
    for (int i = 0; i < fb->capacity; i++) {
        freeAdjList(fb->adj[i]);
    }
    free(fb->adj);

    MapFree(fb->nameToId);

    for (int i = 0; i < fb->numPeople; i++) {
        free(fb->names[i]);
    }
    free(fb->names);
    
    free(fb);
}

int FbNumPeople(Fb fb) {
    return fb->numPeople;
}

bool FbAddPerson(Fb fb, char *name) {
    if (fb->numPeople == fb->capacity) {
        increaseCapacity(fb);
    }

    if (!MapContains(fb->nameToId, name)) {
        int id = fb->numPeople++;
        fb->names[id] = strdup(name);
        MapSet(fb->nameToId, name, id);
        return true;
    } else {
        return false;
    }
}

static void increaseCapacity(Fb fb) {
    int newCapacity = fb->capacity * 2;
    
    fb->names = realloc(fb->names, newCapacity * sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->names[i] = NULL;
    }
    
    fb->adj = realloc(fb->adj, newCapacity * sizeof(struct adjNode));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->adj[i] = NULL;
    }
    
    fb->capacity = newCapacity;
}

bool FbHasPerson(Fb fb, char *name) {
    return MapContains(fb->nameToId, name);
}

List FbGetPeople(Fb fb) {
    List l = ListNew();
    for (int id = 0; id < fb->numPeople; id++) {
        ListAppend(l, fb->names[id]);
    }
    return l;
}

bool FbIsFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    return inAdjList(fb->adj[id1], id2);
}

////////////////////////////////////////////////////////////////////////
// Your tasks

bool FbFriend(Fb fb, char *name1, char *name2) {
    // TODO: Complete this function
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);

    if (FbIsFriend(fb, name1, name2)) {
        return false;
    }

    struct adjNode *newNode1 = newAdjNode(id2);
    struct adjNode *newNode2 = newAdjNode(id1);
    struct adjNode **curr = &fb->adj[id1];
    while (*curr != NULL && (*curr)->v < id2) {
        curr = &(*curr)->next;
    }
    newNode1->next = *curr;
    *curr = newNode1;

    curr = &fb->adj[id2];
    while (*curr != NULL && (*curr)->v < id1) {
        curr = &(*curr)->next;
    }
    newNode2->next = *curr;
    *curr = newNode2;
    return true;
}

int FbNumFriends(Fb fb, char *name) {
    int id = nameToId(fb, name);
    int count = 0;
    struct adjNode *curr = fb->adj[id];
    while(curr!=NULL){
        count++;
        curr=curr->next;
    }
    return count;
}

List FbMutualFriends(Fb fb, char *name1, char *name2) {
    // TODO: Complete this function
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);

    List l = ListNew();

    struct adjNode *curr1 = fb->adj[id1];
    struct adjNode *curr2 = fb->adj[id2];
    
    while(curr1 != NULL && curr2 != NULL){
        if(curr1->v == curr2->v){
            ListAppend(l, fb->names[curr1->v]);
            curr1=curr1->next;
            curr2=curr2->next;
        }else if(curr1->v < curr2->v){
            curr1=curr1->next;
        }else{
            curr2=curr2->next;
        }
    }

    return l;
}

bool FbUnfriend(Fb fb, char *name1, char *name2) {
    // TODO: Complete this function
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    if (!FbIsFriend(fb, name1, name2)) {
        return false;
    }
    struct adjNode **curr = &fb->adj[id1];
    while (*curr != NULL && (*curr)->v != id2) {
        curr = &(*curr)->next;
    }
    if (*curr != NULL) {
        struct adjNode *temp = *curr;
        *curr = (*curr)->next;
        free(temp);
    }

    curr = &fb->adj[id2];
    while (*curr != NULL && (*curr)->v != id1) {
        curr = &(*curr)->next;
    }
    if (*curr != NULL) {
        struct adjNode *temp = *curr;
        *curr = (*curr)->next;
        free(temp);
    }

    return true;
}

int FbFriendRecs1(Fb fb, char *name, struct recommendation recs[]) {
    // TODO: Complete this function
    return 0;
}

////////////////////////////////////////////////////////////////////////
// Optional task

List FbFriendRecs2(Fb fb, char *name) {
    // TODO: Complete this function
    List l = ListNew();
    return l;
}

////////////////////////////////////////////////////////////////////////
// Helper Functions

// Converts a name to an ID. Raises an error if the name doesn't exist.
static int nameToId(Fb fb, char *name) {
    if (!MapContains(fb->nameToId, name)) {
        fprintf(stderr, "error: person '%s' does not exist!\n", name);
        exit(EXIT_FAILURE);
    }
    return MapGet(fb->nameToId, name);
}

static struct adjNode *newAdjNode(int v) {
    struct adjNode *n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->v = v;
    n->next = NULL;
    return n;
}

static bool inAdjList(struct adjNode *l, int v) {
    for (struct adjNode *n = l; n != NULL && n->v <= v; n = n->next) {
        if (n->v == v) {
            return true;
        }
    }
    return false;
}

static void freeAdjList(struct adjNode *l) {
    struct adjNode *n = l;
    while (n != NULL) {
        struct adjNode *temp = n;
        n = n->next;
        free(temp);
    }
}

