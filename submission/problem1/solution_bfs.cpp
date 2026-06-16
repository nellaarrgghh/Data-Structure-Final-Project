#include "harness.h"
// Tambahkan include yang kalian butuhkan, contoh:
#include <queue>
#include <set>
// #include <map>

vector<Cell> solve(vector<vector<char>> &grid, Cell start, Cell goal) {
  vector<Cell> visited; // list of visited cells (ordered) — return this

  // ===================== WRITE YOUR ALGORITHM HERE =====================
  // ===================== BFS =====================
  queue<Cell> q;
  q.push(start);

  set<Cell> seen;
  seen.insert(start);

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};

  while (!q.empty()) {
    Cell current_cell = q.front();
    q.pop();

    visited.push_back(current_cell);

    if (current_cell == goal) {
      break;
    }

    for (int k = 0; k < 4; k++) {
      int nr = current_cell.first + dr[k];
      int nc = current_cell.second + dc[k];
      Cell neighbor = {nr, nc};

      if (inBounds(nr, nc) && !isWall(grid[nr][nc]) &&
          seen.find(neighbor) == seen.end()) {
        seen.insert(neighbor);
        came_from[neighbor] = current_cell;
        q.push(neighbor);
      }
    }
  }
  return visited;
}