#include "harness.h"
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

map<Cell, Cell> parent;
map<Cell, int> rank_;

Cell find(Cell x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(Cell a, Cell b) {
    Cell ra = find(a), rb = find(b);
    if (ra == rb) return;
    if (rank_[ra] < rank_[rb]) swap(ra, rb);
    parent[rb] = ra;
    if (rank_[ra] == rank_[rb]) rank_[ra]++;
}

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal) {
    vector<Cell> visited;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = { 0, 0, -1, 1};

    vector<Cell> cells;
    for (int r = 0; r < rows_g; r++)
        for (int c = 0; c < cols_g; c++)
            if (!isWall(grid[r][c])) {
                cells.push_back({r, c});
                parent[{r,c}] = {r,c};
                rank_[{r,c}] = 0;
            }

    vector<tuple<int,Cell,Cell>> edges;
    for (auto& cell : cells) {
        for (int k = 0; k < 4; k++) {
            int nr = cell.first  + dr[k];
            int nc = cell.second + dc[k];
            if (!inBounds(nr, nc)) continue;
            if (isWall(grid[nr][nc])) continue;
            Cell neighbor = {nr, nc};
            int cost = cellCost(grid[nr][nc]);
            edges.push_back({cost, cell, neighbor});
        }
    }

    sort(edges.begin(), edges.end());

    map<Cell, vector<Cell>> mst; 
    for (auto& [cost, u, v] : edges) {
        if (find(u) != find(v)) {
            unite(u, v);
            mst[u].push_back(v);
            mst[v].push_back(u);
        }
    }

    map<Cell, bool> seen;
    queue<Cell> q;
    q.push(start);
    seen[start] = true;
    came_from[start] = start;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        visited.push_back(current);

        if (current == goal) break;

        for (Cell neighbor : mst[current]) {
            if (seen[neighbor]) continue;
            seen[neighbor] = true;
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