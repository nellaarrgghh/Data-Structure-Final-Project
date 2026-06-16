#include "harness.h"
#include <queue>
#include <map>
#include <vector>

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal){
    vector<Cell> visited;
    queue<Cell> q;
    map<Cell, bool> seen;

    q.push(start);
    seen[start] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()){
        Cell current = q.front();
        q.pop();
        visited.push_back(current);

        if (current == goal) break;

        for (int k = 0; k < 4; k++) {
            int nr = current.first + dr[k];
            int nc = current.second + dc[k];
            Cell neighbor = {nr, nc};

            if (inBounds(nr, nc) && !isWall(grid[nr][nc]) && !seen[neighbor]) {
                seen[neighbor] = true;
                came_from[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    return visited;
}
