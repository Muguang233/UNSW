// DFS maze solver

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

bool solve(Maze m) {
    // TODO: Complete this function
    //       Feel free to add helper functions
    struct cell start = MazeGetStart(m);
    int height = MazeHeight(m);
    int width = MazeWidth(m);

    bool **visited = createBoolMatrix(height, width);

    Stack s = StackNew();
    StackPush(s, start);
    visited[start.row][start.col] = true;

    struct cell **parent = createCellMatrix(height, width);

    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    while (!StackIsEmpty(s)) {
        struct cell curr = StackPop(s);

        if (MazeVisit(m, curr)) {
            struct cell trace = curr;
            while (!(trace.row == start.row && trace.col == start.col)) {
                MazeMarkPath(m, trace);
                trace = parent[trace.row][trace.col];
            }
            MazeMarkPath(m, start);
            freeBoolMatrix(visited);
            freeCellMatrix(parent);
            StackFree(s);
            return true;
        }

        for (int i = 0; i < 4; i++) {
            struct cell next = {curr.row + dRow[i], curr.col + dCol[i]};

            if (next.row >= 0 && next.row < height && next.col >= 0 && next.col < width &&
                !visited[next.row][next.col] && !MazeIsWall(m, next)) {
                visited[next.row][next.col] = true;
                parent[next.row][next.col] = curr;
                StackPush(s, next);
            }
        }
    }

    freeBoolMatrix(visited);
    freeCellMatrix(parent);
    StackFree(s);
    return false;
}

