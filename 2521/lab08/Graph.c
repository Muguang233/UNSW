// Implementation of the Undirected Weighted Graph ADT
// Uses an adjacency matrix

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Pq.h"

// DO NOT modify this struct
struct graph {
    int nV;         // #vertices
    int nE;         // #edges
    double **edges; // adjacency matrix storing positive weights
                    // 0 if nodes not adjacent
};

static bool validVertex(Graph g, Vertex v);

////////////////////////////////////////////////////////////////////////

Graph GraphNew(int nV) {
    assert(nV > 0);

    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nV = nV;
    g->nE = 0;

    g->edges = malloc(nV * sizeof(double *));
    if (g->edges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        g->edges[i] = calloc(nV, sizeof(double));
        if (g->edges[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    return g;
}

void GraphFree(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

////////////////////////////////////////////////////////////////////////

int GraphNumVertices(Graph g) {
    return g->nV;
}

bool GraphInsertEdge(Graph g, struct edge e) {
    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));
    assert(e.v != e.w);
    assert(e.weight > 0.0);

    if (g->edges[e.v][e.w] == 0.0) {
        g->edges[e.v][e.w] = e.weight;
        g->edges[e.w][e.v] = e.weight;
        g->nE++;
        return true;
    } else {
        return false;
    }
}

bool GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));

    if (g->edges[v][w] != 0.0) {   // edge e in graph
        g->edges[v][w] = 0.0;
        g->edges[w][v] = 0.0;
        g->nE--;
        return true;
    } else {
        return false;
    }
}

double GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));
    
    return g->edges[v][w];
}

void GraphShow(Graph g) {
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (int v = 0; v < g->nV; v++) {
        for (int w = v + 1; w < g->nV; w++) {
            if (g->edges[v][w] != 0.0) {
                printf("Edge %d - %d: %lf\n", v, w, g->edges[v][w]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////
// Your task

Graph GraphMst(Graph g) {
  int nV = GraphNumVertices(g);
  if (nV == 0) return NULL;

  bool *visited = malloc(nV * sizeof(bool));
  if (visited == NULL) return NULL;
  for (int i = 0; i < nV; i++) {
    visited[i] = false;
  }

  Graph mst = GraphNew(nV);
  Pq pq = PqNew();

  visited[0] = true;

  for (int w = 0; w < nV; w++) {
    double weight = GraphIsAdjacent(g, 0, w);
    if (weight > 0.0) {
      struct edge e = {0, w, weight};
      PqInsert(pq, e);
    }
  }

  while (!PqIsEmpty(pq)) {
    struct edge e = PqExtract(pq);
    int v = e.v;
    int w = e.w;

    if (visited[v] && visited[w]) continue;

    int newV;
    if (visited[v]) {
      newV = w;
    } else {
      newV = v;
    }
    visited[newV] = true;
    GraphInsertEdge(mst, e);

    for (int u = 0; u < nV; u++) {
      if (!visited[u]) {
        double weight = GraphIsAdjacent(g, newV, u);
        if (weight > 0.0) {
          struct edge newE = {newV, u, weight};
          PqInsert(pq, newE);
        }
      }
    }
  }

  for (int i = 0; i < nV; i++) {
    if (!visited[i]) {
      GraphFree(mst);
      PqFree(pq);
      free(visited);
      return NULL;
    }
  }
  
  PqFree(pq);
  free(visited);
  return mst;
}

////////////////////////////////////////////////////////////////////////

static bool validVertex(Graph g, Vertex v) {
    return v >= 0 && v < g->nV;
}

