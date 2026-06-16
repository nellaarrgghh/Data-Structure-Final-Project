#include "harness.h"
#include <stack>
#include <map>
#include <vector>

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal){
    vector<Cell> visited;
    stack<Cell> s;
    map<Cell, bool> in_stack_or_visited;

    s.push(start);
    in_stack_or_visited[start] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!s.empty()){
        Cell current = s.top();
        s.pop();
        visited.push_back(current);

        if (current == goal) break;

        for (int k = 0; k < 4; k++) {
            int nr = current.first + dr[k];
            int nc = current.second + dc[k];
            Cell neighbor = {nr, nc};

            if (inBounds(nr, nc) && !isWall(grid[nr][nc]) && !in_stack_or_visited[neighbor]) {
                in_stack_or_visited[neighbor] = true;
                came_from[neighbor] = current;
                s.push(neighbor);
            }
        }
    }
    return visited;
}
