#include "harness.h"
#include <queue>
#include <map>

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal) {
    vector<Cell> visited;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = { 0, 0, -1, 1};

    priority_queue<pair<int,Cell>, vector<pair<int,Cell>>, greater<>> pq;
    map<Cell, int> dist;

    dist[start] = 0;
    came_from[start] = start;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cost, current] = pq.top();
        pq.pop();

        if (cost > dist[current]) continue;

        visited.push_back(current);

        if (current == goal) break;

        for (int k = 0; k < 4; k++) {
            int nr = current.first  + dr[k];
            int nc = current.second + dc[k];

            if (!inBounds(nr, nc)) continue;
            if (isWall(grid[nr][nc])) continue;

            Cell neighbor = {nr, nc};
            int newCost = cost + cellCost(grid[nr][nc]);

            if (!dist.count(neighbor) || newCost < dist[neighbor]) {
                dist[neighbor] = newCost;
                came_from[neighbor] = current;
                pq.push({newCost, neighbor});
            }
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