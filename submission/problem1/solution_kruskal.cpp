#include "harness.h"
#include <algorithm>
#include <queue>
#include <set>
#include <vector>

vector<Cell> solve(vector<vector<char>> &grid, Cell start, Cell goal) {
  vector<Cell> visited; // list of visited cells (ordered) — return this
  // ===================== WRITE YOUR ALGORITHM HERE =====================
  // ==================== KRUSKAL'S =====================
  map<Cell, Cell> parent;
  map<Cell, int> rank_;

  for (int r = 0; r < rows_g; r++)
    for (int c = 0; c < cols_g; c++)
      if (!isWall(grid[r][c])) {
        parent[{r, c}] = {r, c};
        rank_[{r, c}] = 0;
      }
  function<Cell(Cell)> find = [&](Cell x) -> Cell {
    if (parent[x] != x)
      parent[x] = find(parent[x]);
    return parent[x];
  };

  auto unite = [&](Cell a, Cell b) {
    Cell ra = find(a), rb = find(b);
    if (ra == rb)
      return;
    if (rank_[ra] < rank_[rb])
      swap(ra, rb);
    parent[rb] = ra;
    if (rank_[ra] == rank_[rb])
      rank_[ra]++;
  };

  int dr[] = {1, 0};
  int dc[] = {0, 1};

  using Edge = tuple<int, Cell, Cell>;
  vector<Edge> edges;

  for (int r = 0; r < rows_g; r++)
    for (int c = 0; c < cols_g; c++) {
      if (isWall(grid[r][c]))
        continue;
      for (int k = 0; k < 2; k++) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if (!inBounds(nr, nc) || isWall(grid[nr][nc]))
          continue;
        int cost = cellCost(grid[r][c]) + cellCost(grid[nr][nc]);
        edges.push_back({cost, {r, c}, {nr, nc}});
      }
    }

  sort(edges.begin(), edges.end());

  map<Cell, vector<Cell>> adj;

  // Build MST
  for (auto &[cost, u, v] : edges) {
    if (find(u) != find(v)) {
      unite(u, v);
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  queue<Cell> q;
  set<Cell> seen;
  q.push(start);
  seen.insert(start);

  while (!q.empty()) {
    Cell curr = q.front();
    q.pop();
    visited.push_back(curr);

    if (curr == goal)
      break;

    for (Cell nxt : adj[curr]) {
      if (!seen.count(nxt)) {
        seen.insert(nxt);
        came_from[nxt] = curr;
        q.push(nxt);
      }
    }
  }

  return visited;
}