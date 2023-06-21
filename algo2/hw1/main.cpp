#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<int>> adjacency_matrix;
int traverse_length = 0;
vector<int> cycle;
bool is_cycled = false;
int source_kid;

class Kid {       // kid object, holds coordinates and power
        int coordinates[2];        
        int p;  
    public:    
        Kid(){}
        Kid(int x, int y, int power){
            coordinates[0] = x;
            coordinates[1] = y;
            p = power;
        }
        int getX(){return coordinates[0];}
        int getY(){return coordinates[1];}
        int get_power(){return p;}
};

/*
 * dfs - Perform depth-first search traversal on a graph and return if there can be a cycle
 * 
 * @param vertex: The current vertex being visited
 * @param visited: A vector indicating whether each vertex has been visited or not
 * 
 * @post cycle vector is populated with the vertices of the cycle if it exists
 *       is_cycled is set to true if a cycle exists, false otherwise
 */
void dfs(int vertex, vector<bool>& visited)
{
    // If cycle is found, return dont do any more recursive calls
    if (is_cycled) return;

    // Add the current vertex to the cycle and increment the traverse length
    traverse_length++;
    cycle.push_back(vertex);

    // If there is an edge between the source_kid and current vertex and
    // the length of the cycle is greater than 2, we have found a cycle
    if (adjacency_matrix[source_kid][vertex] == 1 && traverse_length > 2) {
        is_cycled = true;
        cycle.push_back(source_kid);
        return;
    }

    // Set the current vertex as visited
    visited[vertex] = true;

    // For every adjacent vertex to the current vertex
    for (int i = 0; i < (int)adjacency_matrix[vertex].size(); i++) {

        // If some node is adjacent to the current node
        // and it has not already been visited, visit it
        if (adjacency_matrix[vertex][i] == 1 && (!visited[i])) {
            dfs(i, visited);
            return; // Return after visiting the first adjacent vertex, each kid can pass the ball maximum one time
        }
    }
}

/*
* bfs_shortest_path - Perform breadth-first search traversal on a graph and return shortest path between source kid and target kid
*/
vector<int> bfs_shortest_path(int target_kid) {
    // Initialize visited vector to keep track of visited nodes
    vector<bool> visited(adjacency_matrix.size());

    // Initialize parent vector to keep track of parent nodes
    // parent[i] stores the parent of node i in the BFS tree
    vector<int> parent(adjacency_matrix.size(), -1); 

    vector<int> queue; // queue for BFS

    // Add source node to queue and mark it as visited
    queue.push_back(source_kid);
    visited[source_kid] = true;
  
    int current_kid;
    while (!queue.empty()) {

        // pop current kid
        current_kid = queue[0];     
        queue.erase(queue.begin());
  
        // Check if the target kid has been reached
        if (current_kid == target_kid) break;
  
        // Explore adjacent nodes
        for (int i = 0; i < (int)adjacency_matrix[current_kid].size(); i++) {
            // If neighbor is not visited, add it to queue, mark as visited and set parent
            if (adjacency_matrix[current_kid][i] == 1 && (!visited[i])) { 
                queue.push_back(i);
                visited[i] = true;
                parent[i] = current_kid;
            }
        }
    }
    
    // If the target kid was not reached, there is no path, return empty
    if (!visited[target_kid]) return vector<int>();
    
    // Reconstruct the path from the target kid to the source kid
    vector<int> shortest_path_reversed;
    int curr = target_kid;
    while (curr != source_kid) {
        shortest_path_reversed.push_back(curr);
        curr = parent[curr];
    }
    shortest_path_reversed.push_back(source_kid);
    // this gives shortest path but backwards, we handle it after returned
    
    return shortest_path_reversed;
}


int main(int argc, char *argv[])
{
    fstream file;                          // open all input and output files
    ofstream graph_output("graph.txt");
    ofstream dfs_output("dfs.txt");
    ofstream bfs_output("bfs.txt");
    file.open(argv[1]);
    string c;
    if (file.is_open()){

        getline(file, c, ' ');
        const int no_of_kids = stoi(c);  // read according to the input file format
        getline(file, c, ' ');
        source_kid = stoi(c);
        getline(file, c, '\n');
        int target_kid = stoi(c);

        Kid kids[no_of_kids];
        int i = 0;
        int x, y, p;

        // assign coordinates and powers of kids
        while (getline(file, c, ' ')){ 
            x = stoi(c);
            getline(file, c, ' ');     
            y = stoi(c);
            getline(file, c, '\n');
            p = stoi(c);

            kids[i] = Kid(x, y, p);
            i++;
        }

        adjacency_matrix = vector<vector<int>>(no_of_kids, vector<int>(no_of_kids)); // init adjacency matrix nxn
        
        // create adjacency matrix
        int k = 0;
        for(int m = 0; m < no_of_kids; m++){   
            for(int n = 0; n <= k; n++){
                if(m == n) adjacency_matrix[m][m] = 0;  // a vertex is not adjacent with itself, diagonal values are zero
                else{
                    adjacency_matrix[m][n] = ((pow((kids[m].getX() - kids[n].getX()), 2) + pow((kids[m].getY() - kids[n].getY()), 2)) <= min(kids[m].get_power(), kids[n].get_power())) ? 1 : 0;
                    adjacency_matrix[n][m] = adjacency_matrix[m][n]; // calculate and assign adjacent vertices
                }
            }
            k++;
        }


        // write adjacent matrix to graph.txt file
        graph_output << "Graph:\n";    
        for(int m = 0; m < no_of_kids; m++){
            for(int n = 0; n < no_of_kids; n++){
                if(n == no_of_kids - 1) graph_output << adjacency_matrix[m][n] << "\n";
                else graph_output << adjacency_matrix[m][n] << " ";
            }
        }

        // vector array holding if a vertex is visited or not

        vector<bool> visited(no_of_kids);  // give as an argument and not create inside function because this will be a
        //  recursive call so we dont want to assign memory to it every time

        dfs(source_kid, visited);  // call depth first search function

        // write to dfs.txt file
        dfs_output << "DFS:\n";  
        if(cycle.back() == source_kid){
            dfs_output << traverse_length << " ";
            dfs_output << cycle.front(); // these are just for formatting
            cycle.erase(cycle.begin());
            for (vector<int>::iterator it=cycle.begin(); it != cycle.end(); it++) // iterate over vector array
                dfs_output << "->" << *it;
        } else{
            dfs_output << "-1";
        }
        

        vector<int> shortest_path = bfs_shortest_path(target_kid);  // call breath first search function

        // write to bfs.txt file
        bfs_output << "BFS:\n";  
        if(!shortest_path.empty()){
            bfs_output << shortest_path.size()-1 << " ";

            bfs_output << shortest_path.back();  // these are for formatting as well

            shortest_path.pop_back();
            // reverse iterate over vector array because we traced shortest path back, it is in reverse order
            for (vector<int>::reverse_iterator it=shortest_path.rbegin(); it != shortest_path.rend(); it++) 
                bfs_output << "->" << *it;
        } else{
            bfs_output << "-1";
        }

    }

    file.close();     // close all files
    graph_output.close();
    dfs_output.close();
    bfs_output.close();
    exit(0);
}