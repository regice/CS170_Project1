#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

const unsigned NUM_PUZZLE = 8; //size of the puzzle
const unsigned SIZE_SIDE = sqrt(NUM_PUZZLE+1); //size of the side of the puzzle
const vector<int> GOAL_STATE = {1, 2, 3, 4, 5, 6, 7, 8, 0}; //sole goal state of the 8-puzzle
/*
    1 2 3
    4 5 6 Goal State printed out. States will follow this general format when printed.
    7 8 * 
*/

/*
    A node of the search tree. Each node
    consists of the state of the puzzle, the cost 
    to reach that node from the root of the tree,
    and the heuristic evaluated for the node.
*/
struct Node {
    vector<int> state;
    int cost;
    int heuristic;

    Node(vector<int> s, int c, int h) : state(s), cost(c), heuristic(h) { };
};

/*
    Queueing function for Uniform Cost Search.

    Expands the node current and queues its children to queue q.
    Operators also defined in this function.
*/
void queueingFunction_UCS(queue<Node> &q, const Node &current);

/*
    Queueing function for A* with Misplaced Tile Heuristic.

    Expands the node current and queues its children to queue q.
    Operators also defined in this function.
*/
void queueingFunction_MTH(queue<Node> &q, const Node &current);

/*
    Queueing function for A* with Manhattan Distance Heuristic.

    Expands the node current and queues its children to queue q.
    Operators also defined in this function.
*/
void queueingFunction_MDH(queue<Node> &q, const Node &current);

/*
    General Search function. 

    Accepts vector initial, which is the initial state to be solved, and
    the algorithm choice so that it knows which queueing function to use.
    Returns true if search succeeds, false otherwise.
*/
bool generalSearch(const Node &initial, const int &choice);

/*
    A function that takes care of printing out a state appropriately.
*/
void printState(const vector<int> &s);

/*
    A helper function for calculating the Misplaced Tile heuristic.
    Compares the input state to the goal state in order to determine heuristic.
*/
int misplacedTile(const vector<int> &state);

int main() {
    int state_choice = 0; //stores user input choice for initial state
    vector<int> initial(NUM_PUZZLE + 1); //initial state
    cout << "Welcome to Brandon Tran's " + to_string(NUM_PUZZLE) + "-puzzle solver.\n" +
             "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    do {
        cin >> state_choice;

        if(state_choice == 1) { //use hard-coded initial state
            initial = {1, 2, 3, 4, 0, 5, 6, 7, 8}; //default initial state
        }
        else if(state_choice == 2) { //take user-input initial state
            //TO-DO: Implement input collection
            cout << "Enter your puzzle, using a zero to represent the blank.\n";
            cout << "Enter the first row, use space or tabs between numbers:\n";

            cout << "Enter the second row, use space or tabs between numbers:\n";
            cout << "Enter the third row, use space or tabs between numbers:\n";
        }
    } while(state_choice != 1 && state_choice != 2);

    //Pick algorithm
    int algorithm_choice = 0;
    cout << "Enter your choice of algorithm.\n";
    cout << "\t1.  Uniform Cost Search\n";
    cout << "\t2.  A* with the Misplaced Tile heuristic.\n";
    cout << "\t3.  A* with the Manhattan distance heuristic.\n\t";
    do {
        cin >> algorithm_choice;
    } while(algorithm_choice != 1 && algorithm_choice != 2 && algorithm_choice != 3);

    bool success = false;
    //Uniform Cost Search
    if(algorithm_choice == 1) {
        Node start(initial, 0, 0);
        success = generalSearch(start, 1);
    }
    //A* with the Misplaced Tile heuristic
    else if(algorithm_choice == 2) {

    }
    //A* with the Manhattan distance heuristic
    else if(algorithm_choice == 3) {

    }

    if(success) {
        cout << "Goal!!!" << endl;
    }
    else {
        cout << "Could not solve puzzle. ):" << endl;
    }
}

void queueingFunction_UCS(queue<Node> &q, const Node &current) {
    unsigned b = 999; //stores location (index) of the "blank" tile
    //loop finds the location of the blank tile and store it into b
    for(unsigned i = 0; i < current.state.size(); i++) {
        if(current.state.at(i) == 0) {
            b = i;
            break;
        }
    }

    vector<int> temp;

    //MOVE BLANK LEFT
    if(!((b % SIZE_SIDE) == 0)) { //if blank is not on the leftmost column, then it can move left
        temp = current.state;
        swap(temp.at(b), temp.at(b - 1));
        q.push(Node(temp, current.cost + 1, 0));
    }
    
    //MOVE BLANK RIGHT
    if(!(((b+1) % SIZE_SIDE) == 0)) { //if blank is not on the rightmost column, then it can move right
        temp = current.state;
        swap(temp.at(b), temp.at(b + 1));
        q.push(Node(temp, current.cost + 1, 0));
    }

    //MOVE BLANK UP
    if(b >= SIZE_SIDE) { //if blank is not in the top row, then it can move up
        temp = current.state;
        swap(temp.at(b), temp.at(b - SIZE_SIDE));
        q.push(Node(temp, current.cost + 1, 0));
    }
    
    //MOVE BLANK DOWN
    if(b <= (NUM_PUZZLE - SIZE_SIDE)) { //if blank is not in the bottom row, then it can move down
        temp = current.state;
        swap(temp.at(b), temp.at(b + SIZE_SIDE));
        q.push(Node(temp, current.cost + 1, 0));
    }

    return;
}

void queueingFunction_MTH(queue<Node> &q, const Node &current) {
    unsigned b = 999; //stores location (index) of the "blank" tile
    //loop finds the location of the blank tile and store it into b
    for(unsigned i = 0; i < current.state.size(); i++) {
        if(current.state.at(i) == 0) {
            b = i;
            break;
        }
    }

    vector<int> temp;
    int h = 0; 

    //MOVE BLANK LEFT
    if(!((b % SIZE_SIDE) == 0)) { //if blank is not on the leftmost column, then it can move left
        temp = current.state;
        swap(temp.at(b), temp.at(b - 1));
        h = misplacedTile(temp);
        q.push(Node(temp, current.cost + 1, h));
    }
    
    //MOVE BLANK RIGHT
    if(!(((b+1) % SIZE_SIDE) == 0)) { //if blank is not on the rightmost column, then it can move right
        temp = current.state;
        swap(temp.at(b), temp.at(b + 1));
        h = misplacedTile(temp);
        q.push(Node(temp, current.cost + 1, h));
    }

    //MOVE BLANK UP
    if(b >= SIZE_SIDE) { //if blank is not in the top row, then it can move up
        temp = current.state;
        swap(temp.at(b), temp.at(b - SIZE_SIDE));
        h = misplacedTile(temp);
        q.push(Node(temp, current.cost + 1, h));
    }
    
    //MOVE BLANK DOWN
    if(b <= (NUM_PUZZLE - SIZE_SIDE)) { //if blank is not in the bottom row, then it can move down
        temp = current.state;
        swap(temp.at(b), temp.at(b + SIZE_SIDE));
        h = misplacedTile(temp);
        q.push(Node(temp, current.cost + 1, h));
    }

    return;
}

bool generalSearch(const Node &initial, const int &choice) {
    queue<Node> nodes; //the queue to be used for search
    nodes.push(initial);
    Node current = nodes.front(); //the next node to be accessed

    while(!nodes.empty()) { //perform search until we run out of nodes to search or the goal state is reached
        current = nodes.front(); //TO-DO: MODIFY CRITERIA WITH WHICH TO POP THE NEXT NODE BASED ON COST + HEURISTIC
        nodes.pop(); //get next state and pop it from the queue

        cout << "Expanding state with cost " + to_string(current.cost) + ":\n";
        printState(current.state);

        if(current.state == GOAL_STATE) { //if the current state is the goal state, then we are done
            return true;
        }
        else { //otherwise expand on the children of the current state
            if(choice == 1) {
                queueingFunction_UCS(nodes, current);
            }
            else if(choice == 2) {
                //queueingFunction_MTH(nodes, current);
            }
            else {
                //queueingFunction_MDH(nodes, current);
            }
        }
    }

    return false; 
}

void printState(const vector<int> &s) {
    for(unsigned i = 0; i < s.size(); i++) {
        cout << s.at(i);
        if(((i + 1) % SIZE_SIDE) == 0) {
            cout << endl;
        }
        else {
            cout << " ";
        }
    }
}

int misplacedTile(const vector<int> &state) {
    int heuristic = 0;
    for(unsigned i = 0; i < state.size(); i++) {
        if(!(state.at(i) == GOAL_STATE.at(i))) {
            heuristic++;
        }
    }

    return heuristic;
}