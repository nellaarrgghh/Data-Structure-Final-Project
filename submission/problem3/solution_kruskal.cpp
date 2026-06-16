#include "harness.h"
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

struct Edge {
    Cell u, v;
    int weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct DSU {
    map<Cell, Cell> parent;
    Cell find_set(Cell v) {
        if (parent.find(v) == parent.end()) parent[v] = v;
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_sets(Cell a, Cell b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) parent[b] = a;
    }
};

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal){
    vector<Cell> visited;
    vector<Edge> edges;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // extract all edges and assign symmetric weights for the MST
    for (int r = 0; r < rows_g; r++) {
        for (int c = 0; c < cols_g; c++) {
            if (isWall(grid[r][c])) continue;
            Cell u = {r, c};
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (inBounds(nr, nc) && !isWall(grid[nr][nc])) {
                    Cell v = {nr, nc};
                    int weight = cellCost(grid[r][c]) + cellCost(grid[nr][nc]);
                    edges.push_back({u, v, weight});
                }
            }
        }
    }

    // sort edges by weight
    sort(edges.begin(), edges.end());

    // build MST using DSU
    DSU dsu;
    map<Cell, vector<Cell>> mst_adj;
    for (Edge e : edges) {
        if (dsu.find_set(e.u) != dsu.find_set(e.v)) {
            dsu.union_sets(e.u, e.v);
            mst_adj[e.u].push_back(e.v);
            mst_adj[e.v].push_back(e.u);
        }
    }

    // BFS heavily restricted to only the MST edges
    queue<Cell> q;
    map<Cell, bool> seen;
    q.push(start);
    seen[start] = true;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();
        visited.push_back(current);

        if (current == goal) break;

        for (Cell neighbor : mst_adj[current]) {
            if (!seen[neighbor]) {
                seen[neighbor] = true;
                came_from[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    return visited;
}
