#include <bits/stdc++.h>
using namespace std;
// Structure to represent a node in the AND-OR graph
struct Node
{
    string name;
    int cost;    // Current estimated cost (initially heuristic)
    bool solved; // Is this node solved?
    // A vector of "Rules". Each rule is a vector of children (AND condition).
    // Different rules in the outer vector represent OR choices.
    vector<vector<Node *>> childrenOptions;
    vector<int> edgeCosts; // Cost associated with each option
    Node(string n, int h) : name(n), cost(h), solved(false) {}
};
// Global list to manage memory (simplified for lab)
vector<Node *> allNodes;
// Function to calculate cost recursively
int calculateCost(Node *u)
{
    if (u->solved || u->childrenOptions.empty())
    {
        return u->cost;
    }
    int bestCost = INT_MAX;
    int bestOptionIndex = -1;
    // Evaluate all OR options
    for (int i = 0; i < u->childrenOptions.size(); ++i)
    {
        int currentOptionCost = u->edgeCosts[i]; // Start with edge cost
        vector<Node *> &option = u->childrenOptions[i];

        // Sum up costs for AND children
        for (Node *child : option)
        {
            currentOptionCost += calculateCost(child);
        }
        if (currentOptionCost < bestCost)
        {
            bestCost = currentOptionCost;
            bestOptionIndex = i;
        }
    }

    // Update current node with the best found cost
    u->cost = bestCost;
    return bestCost;
}
void aoStar(Node *root)
{
    cout << "Expanding Node: " << root->name << " | Initial Heuristic: "
         << root->cost << endl;

    int minCost = calculateCost(root);

    cout << "Updated Cost for " << root->name << ": " << minCost << endl;
    root->solved = true;
}
int main()
{
    // 1. Initialize Nodes with Heuristic values
    Node *A = new Node("A", 100); // Start
    Node *B = new Node("B", 6);
    Node *C = new Node("C", 12);
    Node *D = new Node("D", 10);
    Node *E = new Node("E", 4);
    Node *F = new Node("F", 4);
    // 2. Build the Graph (AND-OR Structure)

    // Option 1 for A: Go to B (Cost 1)
    // A -> B (OR choice 1)
    A->childrenOptions.push_back({B});
    A->edgeCosts.push_back(1);
    // Option 2 for A: Go to C AND D (Cost 1)
    // A -> C + D (OR choice 2, which is an AND node)
    A->childrenOptions.push_back({C, D});
    A->edgeCosts.push_back(1);

    // B -> E + F (AND node)
    B->childrenOptions.push_back({E, F});
    B->edgeCosts.push_back(1);
    // C, D, E, F are leaf nodes (conceptually) for this simple example
    cout << "Starting AO* Search..." << endl;

    // In a full implementation, we loop until the root is solved.
    // For this simple static graph, one pass of calculation demonstrates the logic.
    aoStar(A);
    cout << "Final Cost of Optimal Solution: " << A->cost << endl;
    return 0;
}