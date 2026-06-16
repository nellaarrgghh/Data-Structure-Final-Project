#include "harness.h"
#include <queue>
#include <set>

vector<Cell> solve(vector<vector<char>> &grid, Cell start, Cell goal) {
  vector<Cell> visited; // list of visited cells (ordered) — return this

  // ===================== WRITE YOUR ALGORITHM HERE =====================
  // ===================== DIJKSTRA =====================
  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};

  priority_queue<pair<int, Cell>, vector<pair<int, Cell>>,
                 greater<pair<int, Cell>>>
      pq;

  map<Cell, int> dist;
  set<Cell> settled;

  dist[start] = 0;
  pq.push({0, start});

  while (!pq.empty()) {
    auto [cost, current] = pq.top();
    pq.pop();

    if (settled.count(current))
      continue;
    settled.insert(current);

    visited.push_back(current);

    if (current == goal)
      break;

    int r = current.first, c = current.second;

    for (int k = 0; k < 4; k++) {
      int nr = r + dr[k];
      int nc = c + dc[k];

      if (!inBounds(nr, nc))
        continue;
      if (isWall(grid[nr][nc]))
        continue;
      if (settled.count({nr, nc}))
        continue;

      int new_cost = cost + cellCost(grid[nr][nc]);
      Cell neighbor = {nr, nc};

      if (!dist.count(neighbor) || new_cost < dist[neighbor]) {
        dist[neighbor] = new_cost;
        came_from[neighbor] = current;
        pq.push({new_cost, neighbor});
      }
    }
  }

  return visited;
}