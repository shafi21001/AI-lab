#include <bits/stdc++.h>
using namespace std;
using Board = vector<vector<int>>;
const Board GOAL = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
// Function to find the coordinates of the blank tile (0)
pair<int, int> findBlank(const Board &b)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (b[i][j] == 0)
                return {i, j};
    return {-1, -1};
}
void solve8Puzzle(Board start)
{
    // Queue for BFS: stores {moves, board}
    queue<pair<int, Board>> q;
    map<Board, int> visited;  // Tracks visited states
    map<Board, Board> parent; // To reconstruct path
    q.push({0, start});
    visited[start] = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty())
    {
        int currentG = q.front().first;
        Board currentBoard = q.front().second;
        q.pop();
        // Check Goal
        if (currentBoard == GOAL)
        {
            cout << "Goal Reached in " << currentG << " moves!" << endl;

            // Reconstruct path
            vector<Board> path;
            Board curr = GOAL;
            while (curr != start)
            {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            for (const auto &step : path)
            {
                for (const auto &row : step)
                {
                    for (int val : row)
                        cout << val << " ";
                    cout << endl;
                }
                cout << endl;
            }

            return;
        }
        pair<int, int> blank = findBlank(currentBoard);
        int x = blank.first;
        int y = blank.second;
        // Generate Moves
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
            {
                Board nextBoard = currentBoard;
                swap(nextBoard[x][y], nextBoard[nx][ny]);
                // If not visited, push to queue
                if (visited.find(nextBoard) == visited.end())
                {
                    visited[nextBoard] = currentG + 1;
                    parent[nextBoard] = currentBoard;
                    q.push({currentG + 1, nextBoard});
                }
            }
        }
    }
    cout << "Unsolvable puzzle." << endl;
}
int main()
{
    Board start = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}};
    cout << "Starting 8-Puzzle Solver..." << endl;
    solve8Puzzle(start);
    return 0;
}