// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "place.h"
#include "Pq.h"

////////////////////////////////////////////////////////////////////////
// Your task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid1(struct place cities[], int numCities,
              struct place powerPlant,
              struct powerLine powerLines[]) {
  int totalPlaces = numCities + 1;
  Graph g = GraphNew(totalPlaces);

  for (int i = 0; i < numCities; i++) {
    for (int j = i + 1; j < numCities; j++) {
      int dx = cities[i].x - cities[j].x;
      int dy = cities[i].y - cities[j].y;
      int dist = (int)(sqrt(dx * dx + dy * dy) * 10000);
      struct edge e = {i, j, dist};
      GraphInsertEdge(g, e);
    }

    int dx = cities[i].x - powerPlant.x;
    int dy = cities[i].y - powerPlant.y;
    int dist = (int)(sqrt(dx * dx + dy * dy) * 10000);
    struct edge e = {i, numCities, dist};
    GraphInsertEdge(g, e);
  }

  Graph mst = GraphMst(g);
  GraphFree(g);

  if (mst == NULL) {
    return 0;
  }

  int count = 0;
  for (int v = 0; v < totalPlaces; v++) {
    for (int w = v + 1; w < totalPlaces; w++) {
      int weight = (int)(GraphIsAdjacent(mst, v, w));
      if (weight > 0) {
        struct powerLine line;
        if (v == numCities) {
          line.p1 = powerPlant;
          line.p2 = cities[w];
        } else if (w == numCities) {
          line.p1 = powerPlant;
          line.p2 = cities[v];
        } else {
          line.p1 = cities[v];
          line.p2 = cities[w];
        }
        powerLines[count] = line;
        count++;
      }
    }
  }

  GraphFree(mst);
  return count;
}

////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(struct place cities[], int numCities,
              struct place powerPlants[], int numPowerPlants,
              struct powerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
