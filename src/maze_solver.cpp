#include "maze_solver.h"
#include <stack>
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace std;

bool MazeSolver::dfs(Maze& maze, int r, int c, vector<vector<bool>>& visited) {

    if (!maze.inBounds(r, c) || maze.isWall(r, c) || visited[r][c]) {
        return false;
    }


    cout << "Visiting: (" << r << ", " << c << ")\n";


    if (maze.finish.row == r && maze.finish.col == c) {
        maze.path.push_back({r, c});
        return true;
    }


    visited[r][c] = true;


    const int dr[] = {-1, 0, 1, 0};
    const int dc[] = {0, 1, 0, -1};

    for (int dir = 0; dir < 4; ++dir) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if (dfs(maze, nr, nc, visited)) {
            maze.path.push_back({r, c});
            return true;
        }
    }


    return false;
}

bool MazeSolver::solveDFS(Maze& maze) {
    maze.path.clear();

    vector<vector<bool>> visited(maze.grid.size(),
                                 vector<bool>(maze.grid[0].size(), false));

    bool found = dfs(maze, maze.start.row, maze.start.col, visited);

    cout << "Solving maze started...\n";

    if (found) {
        maze.path.push_back(maze.start);
    }

    return found;
}
