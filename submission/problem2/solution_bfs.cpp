#include "harness.h"
#include <queue>

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal) {
    vector<Cell> visited;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = { 0, 0, -1, 1};

    queue<Cell> q;
    q.push(start);
    came_from[start] = start;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        visited.push_back(current);

        if (current == goal) {
            cerr << "GOAL REACHED at " << goal.first << "," << goal.second << "\n";
            break;
        }

        for (int k = 0; k < 4; k++) {
            int nr = current.first  + dr[k];
            int nc = current.second + dc[k];

            if (!inBounds(nr, nc)) continue;
            if (isWall(grid[nr][nc])) continue;

            Cell neighbor = {nr, nc};
            if (came_from.count(neighbor)) continue;

            came_from[neighbor] = current;
            q.push(neighbor);
        }
    }
    int totalCost = 0;
    Cell cur = goal;
    while (!(cur == start)) {
        totalCost += cellCost(grid[cur.first][cur.second]);
        cur = came_from[cur];
    }
    totalCost += cellCost(grid[start.first][start.second]);
    cerr << "TotalCost=" << totalCost << "\n";

    return visited;
}