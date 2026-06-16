#include "harness.h"
// Tambahkan include yang kalian butuhkan, contoh:
#include <stack>
#include <vector>

vector<Cell> solve(vector<vector<char>> &grid, Cell start, Cell goal) {
  vector<Cell> visited; // list of visited cells (ordered) — return this

  // ===================== WRITE YOUR ALGORITHM HERE =====================
  // ===================== DFS =====================
  int dr[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
  int dc[] = {0, 0, -1, 1};

  vector<vector<bool>> seen(rows_g, vector<bool>(cols_g, false));
  stack<Cell> stk;

  stk.push(start);
  seen[start.first][start.second] = true;

  while (!stk.empty()) {
    Cell current = stk.top();
    stk.pop();

    visited.push_back(current);

    if (current == goal) {
      break;
    }

    int r = current.first;
    int c = current.second;

    // LIFO = Up will be popped first.
    for (int k = 3; k >= 0; k--) {
      int nr = r + dr[k];
      int nc = c + dc[k];

      if (!inBounds(nr, nc))
        continue;
      if (isWall(grid[nr][nc]))
        continue;

      if (!seen[nr][nc]) {
        seen[nr][nc] = true;
        Cell neighbor = {nr, nc};

        came_from[neighbor] = current;
        stk.push(neighbor);
      }
    }
  }
  return visited;
}