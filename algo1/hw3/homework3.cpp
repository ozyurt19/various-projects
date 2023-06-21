#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

struct Node
{
    std::string processId;
    int vruntime;
    int remaining;
    int color;
    Node *parent;
    Node *left;
    Node *right;
};

class RedBlackTree
{
private:
    Node *root;
    Node *TNULL;

    // fixup routine for deletion
    void deleteFixup(Node *node)
    {
        Node *sibling;
        while (node != root && node->color == 0) // terminate if the node is the root or its color is red
        {
            if (node == node->parent->left) // If the node is the left child
            {
                sibling = node->parent->right; // get sibling
                if (sibling->color == 1)       // if sibling is red, color sibling black and parent red
                {
                    sibling->color = 0;
                    node->parent->color = 1;
                    rotateLeft(node->parent);
                    sibling = node->parent->right; // fix sibling
                }

                if (sibling->left->color == 0 && sibling->right->color == 0) // if siblings children are both black
                {
                    // make sibling red and get ref to parent
                    sibling->color = 1;
                    node = node->parent;
                }
                else
                {
                    if (sibling->right->color == 0) // If the sibling's right child is black
                    {
                        sibling->left->color = 0; // make siblings left child black
                        sibling->color = 1;       // and sibling red
                        rotateRight(sibling);
                        sibling = node->parent->right; // fix sibling
                    }
                    // color the sibling the same color as the parent
                    sibling->color = node->parent->color;
                    node->parent->color = 0;   // color the parent black.
                    sibling->right->color = 0; // color the siblings right child black.
                    rotateLeft(node->parent);
                    node = root; // set the current node as the root.
                }
            }
            else // If the node is the right child, do same but symmetrical
            {
                sibling = node->parent->left;
                if (sibling->color == 1)
                {
                    sibling->color = 0;
                    node->parent->color = 1;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }

                if (sibling->right->color == 0 && sibling->right->color == 0)
                {
                    sibling->color = 1;
                    node = node->parent;
                }
                else
                {
                    if (sibling->left->color == 0)
                    {
                        sibling->right->color = 0;
                        sibling->color = 1;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = 0;
                    sibling->left->color = 0;
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }
        node->color = 0;  //finally assign nodes color as black
    }

    // insertion fixup routine
    void insertFix(Node *node)
    {
        Node *uncle;
        while (node->parent->color == 1) // iterate till the nodes parent is a black nod
        {
            // If the node's parent is a right child
            if (node->parent == node->parent->parent->right)
            {
                // get a reference to the current node's the uncle
                uncle = node->parent->parent->left;
                if (uncle->color == 1) // If the uncle is red
                {
                    // Color the uncle and the parent black
                    uncle->color = 0;
                    node->parent->color = 0;
                    // Color the grandparent red
                    node->parent->parent->color = 1;
                    // get reference to grandparent 
                    node = node->parent->parent;
                }
                else
                {
                    // If the current node is a left child
                    if (node == node->parent->left)
                    {
                        // get ref to parent
                        node = node->parent;
                        // rotate it right
                        rotateRight(node);
                    }
                    // color the parent black
                    node->parent->color = 0;
                    // color the grandparent red
                    node->parent->parent->color = 1;
                    // rotate the grandparent left
                    rotateLeft(node->parent->parent);
                }
            }
            else
            {
                // If the current node's parent is a left child do same but symmetrical
                uncle = node->parent->parent->right;
                if (uncle->color == 1)
                {
                    uncle->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->right)
                    {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    rotateRight(node->parent->parent);
                }
            }
            // If the current node is the root, break
            if (node == root) break;
        }
        // color the root black.
        root->color = 0;
    }

public:
    RedBlackTree() // constructor
    {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void inorderTraverse(Node *node) // in order traverse method implemented recursively
    {
        if (node != TNULL)
        {
            inorderTraverse(node->left); // this will print one ';' more i hope it is not a problem
            std::cout << node->processId << ":" << node->vruntime << "-" << (node->color ? "Red" : "Black") << ";";
            inorderTraverse(node->right);
        }
    }

    Node *getMinNode(Node *node) // returns task with mininmum vruntime when the argument is the root
    {
        while (node != TNULL && node->left != TNULL) // till reaching to null, go left
        {
            node = node->left;
        }
        return node;
    }

    void rotateLeft(Node *node)  //method performs a left rotate
    {
        Node *tmp = node->right;  
        node->right = tmp->left;  

        if (tmp->left != TNULL) tmp->left->parent = node;

        tmp->parent = node->parent;

        if (node->parent == nullptr) this->root = tmp;
        else if (node == node->parent->left) node->parent->left = tmp;
        else node->parent->right = tmp;

        tmp->left = node;
        node->parent = tmp;
    }

    void rotateRight(Node *node) //method performs a right rotate
    {
        Node *tmp = node->left;
        node->left = tmp->right;

        if (tmp->right != TNULL) tmp->right->parent = node;

        tmp->parent = node->parent;

        if (node->parent == nullptr) this->root = tmp;
        else if (node == node->parent->right) node->parent->right = tmp;
        else node->parent->left = tmp;

        tmp->right = node;
        node->parent = tmp;
    }

    // Inserting a node
    void insert(int key, std::string processId, int remaining)
    {
        Node *node = new Node;

        node->parent = nullptr;
        node->remaining = remaining;
        node->vruntime = key;
        node->processId = processId;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;  //initial color is red

        Node *y = nullptr;

        Node *x = this->root;

        while (x != TNULL)  //get to the place where the node will be inserted
        {
            y = x; // reference y to the nodes parent 

            if (node->vruntime < x->vruntime) x = x->left;
            else x = x->right;
        }

        node->parent = y; // reference parent of node to there as well
        if (y == nullptr) root = node;  // if nodes parent is null node is the root of the tree
        else if (node->vruntime < y->vruntime) y->left = node; 
        else y->right = node; // do the final assignings of node

        if (node->parent == nullptr)  //if node is the root, color it black and return
        {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) return; // if the node's depth is 2, job is done so return

        insertFix(node); // if depth is bigger than 2, finally call insertion fixup routine
    }

    Node *getRoot() // return root of the tree
    {
        return this->root;
    }

    bool checkTNULL() // return true if the root of the tree is null
    {
        return (this->root == TNULL);
    }

    void deleteMin()  //methods deleting the node with the minimum vruntime in the red-black tree
    {
        Node *x;
        Node *z = getMinNode(this->root);
        Node *y = z;

        int is_min_red = y->color;
        if (z->left == TNULL)
        {
            x = z->right;

            if (z->parent == nullptr) root = z->right;
            else if (z == z->parent->left) z->parent->left = z->right;
            else z->parent->right = z->right;
            
            z->right->parent = z->parent;
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            if (z->parent == nullptr) root = z->right;
            else if (z == z->parent->left) z->parent->left = z->right;
            else z->parent->right = z->right;
            
            z->right->parent = z->parent;
        }
        else
        {
            y = getMinNode(z->right);
            is_min_red = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                if (y->parent == nullptr) root = y->right;
                else if (y == y->parent->left) y->parent->left = y->right;
                else y->parent->right = y->right;
            
                y->right->parent = y->parent;

                y->right = z->right;
                y->right->parent = y;
            }

            if (z->parent == nullptr) root = y;
            else if (z == z->parent->left) z->parent->left = y;
            else z->parent->right = y;
            
            y->parent = z->parent;

            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (!is_min_red) deleteFixup(x);
    }
};

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cout << "No file name entered. Please add a command line argument." << std::endl;
        return -1;
    }

    std::ifstream input(argv[1]); // open the file

    if (!input.is_open())
    {
        std::cout << "Couldn't open file.";
        return -1;
    }

    auto start = std::chrono::high_resolution_clock::now(); // start chronometer

    std::string line;
    getline(input, line, ' ');
    int NumProcesses = stoi(line);
    getline(input, line);
    int SimulatorRunTime = stoi(line);
    std::string processId[NumProcesses];
    int TimeOfArrival[NumProcesses];
    int BurstTime[NumProcesses];
    int i = 0;
    RedBlackTree bst;

    while (getline(input, line, ' ')) // reading the input file
    {
        processId[i] = line;
        getline(input, line, ' ');
        TimeOfArrival[i] = stoi(line);
        getline(input, line);
        BurstTime[i] = stoi(line);
        i++;
    }

    bool running_flag = false; // inital running task parameters
    int running_vruntime = 0;
    int running_remaining = 1;
    std::string running_processId = "P0";
    int running_color = -1;
    i = 0;
    int numFinished = 0;
    std::string finished[NumProcesses];
    while (i < SimulatorRunTime) // our loop representing the time
    {
        std::cout << i << ",";
        for (int m = 0; m < NumProcesses; m++)
        {
            if (TimeOfArrival[m] == i)
            {
                //  inserting new tasks to tree
                bst.insert(0, processId[m], BurstTime[m]);
            }
        }
        if (bst.checkTNULL() && !running_flag) // if tree is empty and no process is running just print this and increment time
        {
            std::cout << "-,-,-,-,-,-" << std::endl;
        }
        else
        {
            if (!running_flag) // if there is no running task
            {
                // as described in pdf file print needed values
                std::cout << bst.getMinNode(bst.getRoot())->processId << "," << bst.getMinNode(bst.getRoot())->vruntime << "," << bst.getMinNode(bst.getRoot())->vruntime << ",";
                bst.inorderTraverse(bst.getRoot()); // print tree using inorder traverse
                // std::cout << "no running tasks, get min and make it running" << std::endl;
                running_vruntime = bst.getMinNode(bst.getRoot())->vruntime + 1;
                running_remaining = bst.getMinNode(bst.getRoot())->remaining - 1;
                running_processId = bst.getMinNode(bst.getRoot())->processId;
                running_color = bst.getMinNode(bst.getRoot())->color; // assign the task we will run this iteration to temporary variables
                bst.deleteMin();                                      // delete it to give the task cpu
                running_flag = true;                                  // turn running flag to true
            }
            else // if there is a running task
            {
                // to tell if it need to stop working look at its vruntime and if it is greater than minvruntime:
                if (bst.getRoot()->processId != "" && running_vruntime > bst.getMinNode(bst.getRoot())->vruntime)
                {
                    // insert it back, get the task need to be running and
                    bst.insert(running_vruntime, running_processId, running_remaining);
                    std::cout << bst.getMinNode(bst.getRoot())->processId << "," << bst.getMinNode(bst.getRoot())->vruntime << "," << bst.getMinNode(bst.getRoot())->vruntime << ",";
                    bst.inorderTraverse(bst.getRoot()); // same prints as described in pdf
                    running_vruntime = bst.getMinNode(bst.getRoot())->vruntime + 1;
                    running_remaining = bst.getMinNode(bst.getRoot())->remaining - 1;
                    running_processId = bst.getMinNode(bst.getRoot())->processId;
                    running_color = bst.getMinNode(bst.getRoot())->color;
                    bst.deleteMin(); // make task with mininmum vruntime run by incrementing vruntime, decrementing remaining and deleting from the tree
                }
                else // if running task should keep running
                {
                    // print wanted variables
                    std::cout << running_processId << "," << running_vruntime << "," << running_vruntime << ",";
                    std::cout << running_processId << ":" << running_vruntime << "-" << (running_color ? "Red" : "Black") << ";";
                    if (bst.getRoot()->processId != "")
                        bst.inorderTraverse(bst.getRoot());
                    // increment vruntime and decrement remaining
                    running_vruntime += 1;
                    running_remaining -= 1;
                }
            }

            if (running_remaining == 0) // after the running of this iteration, if the task runned is finished
            {
                std::cout << ",Complete" << std::endl; // print complete add it to the finished array that we will print at the end of this program
                finished[numFinished] = running_processId;
                numFinished++;
                running_flag = false; // and turn running flag to false
            }
            else
            { // if it is not finished, just print incomplete and go to next iteration
                std::cout << ",Incomplete" << std::endl;
            }
        }
        i++; // increment time
    }

    input.close(); // close the file

    auto stop = std::chrono::high_resolution_clock::now();                               // stop chronometer
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); // calculate time passed during program
    std::cout << "\nScheduling finished in " << duration.count() << " ms" << std::endl;  // print duration in microseconds
    std::cout << numFinished << " of " << NumProcesses << " processes are completed" << std::endl;
    std::cout << "The order of completion of the tasks: ";
    for (int m = 0; m < numFinished; m++) // print number of tasks completed and their order
    {
        if (m == numFinished - 1)
            std::cout << finished[m];
        else
            std::cout << finished[m] << "-";
    }
    std::cout << std::endl;
    return 0; // end of program
}