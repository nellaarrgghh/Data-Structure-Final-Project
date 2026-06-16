// solution.cpp — THIS IS WHAT YOU WILL WORK ON.
//
// Write your algorithm ONLY inside the solve() function below.
// Do not add other functions. Do not modify harness.h.
//
// Compile: g++ -O2 -std=c++17 solution.cpp -o solution
// Run:     ./solution ../maps/soal1.txt output.txt
// View:    open engine/index.html, select the question/map, drag output.txt, click Play/Run.

#include "harness.h"
// Tambahkan include yang kalian butuhkan, contoh:
#include <queue>
// #include <set>
#include <map>
#include <vector>

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal){
  vector<Cell> visited;  // list of visited cells (ordered) — return this

  // ===================== WRITE YOUR ALGORITHM HERE =====================
    // priority queue to store pairs of (total_cost, cell)
    // greater<> to ensure the smallest path cost stays at the top
    priority_queue<pair<int, Cell>, vector<pair<int, Cell>>, greater<pair<int, Cell>>> pq;

    // map to remember minimum cost to reach each cell
    map<Cell, int> dist;

    // initialize pathfinder
    dist[start] = 0;
    pq.push({0, start});

    // up down left right movement directions
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!pq.empty()){
        // get cell with lowest cost path found
        pair<int, Cell> current = pq.top();
        pq.pop();

        int current_cost = current.first;
        Cell current_cell = current.second;

        // if a shorter cost exists, skip processing
        if (current_cost > dist[current_cell]) {
            continue;
        }

        // record the shorter cell in the exploration trace when processed
        visited.push_back(current_cell);

        if (current_cell == goal) {
            break;
        }

        // loop k to check all four neighbors
        for (int k = 0; k < 4; k++) {
            int nr = current_cell.first + dr[k];
            int nc = current_cell.second + dc[k];
            Cell neighbor = {nr, nc};

            // check if neighbor is within grid and is not a wall
            if (inBounds(nr, nc) && !isWall(grid[nr][nc])) {
                // calculate total cost to enter this neighboring cell
                int next_cost = current_cost + cellCost(grid[nr][nc]);

                // if neighbor hasn't been checked or if shorter route is found leading to it
                if (dist.find(neighbor) == dist.end() || next_cost < dist[neighbor]) {
                    dist[neighbor] = next_cost;
                    came_from[neighbor] = current_cell; // record parent map for visualization
                    pq.push({next_cost, neighbor});
                }
            }
        }
    }
  // =========================================================================
  return visited;
}
