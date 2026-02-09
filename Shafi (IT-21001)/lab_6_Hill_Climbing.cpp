#include <bits/stdc++.h>
using namespace std;
using Board = vector<vector<int>>;
const Board GOAL = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
map<int, pair<int, int>> goalPos;
void goalMap()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            goalPos[GOAL[i][j]] = {i, j};
}
// Calculate Manhattan Distance
int calculateManhattan(const Board &b)
{
    int dist = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int val = b[i][j];
            if (val != 0)
            {
                dist += abs(i - goalPos[val].first) + abs(j -
                                                          goalPos[val].second);
            }
        }
    }
    return dist;
}
pair<int, int> findBlank(const Board &b)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (b[i][j] == 0)
                return {i, j};
    return {-1, -1};
}

void printBoard(const Board &b)
{
    for (const auto &row : b)
    {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
    cout << endl;
}
void solveHillClimbing(Board start)
{
    Board current = start;
    int currentH = calculateManhattan(current);
    int moves = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    cout << "Initial State (h=" << currentH << "):" << endl;
    printBoard(current);
    while (true)
    {
        if (currentH == 0)
        {
            cout << "Goal Reached in " << moves << " moves!" << endl;
            return;
        }
        pair<int, int> blank = findBlank(current);
        int x = blank.first;
        int y = blank.second;
        Board bestNeighbor;
        int minNeighborH = INT_MAX;

        // Generate all neighbors
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
            {
                Board neighbor = current;
                swap(neighbor[x][y], neighbor[nx][ny]);

                int h = calculateManhattan(neighbor);
                if (h < minNeighborH)
                {
                    minNeighborH = h;
                    bestNeighbor = neighbor;
                }
            }
        }
        // Hill Climbing Condition:
        // Only move if we find a STRICTLY better neighbor
        if (minNeighborH < currentH)
        {
            current = bestNeighbor;
            currentH = minNeighborH;
            moves++;
            cout << "Move " << moves << " (h=" << currentH << "):" << endl;
            printBoard(current);
        }
        else
        {
            // Local Maximum or Plateau reached
            cout << "Stuck at Local Maximum. Lowest neighbor h=" << minNeighborH
                 << " is not better than current h=" << currentH << endl;
            cout << "Failure." << endl;
            return;
        }
    }
}

int main()
{
    Board start = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}};

    goalMap();
    cout << "Starting 8-Puzzle Solver (Hill Climbing)..." << endl;
    solveHillClimbing(start);
    return 0;
}