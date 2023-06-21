#include <fstream>
#include <vector>

using namespace std;

int no_of_cities;
vector<int> visited;
vector<vector<int>> visited_sep;
vector<vector<int>> adjacency_matrix;

// method used to take a step according to prims algorithm, 
// gets starting point and with checking visited arrays determines what city is the next for a bakery 
int prim_step(int starting_point){
    int next_vertex = -1;
    int max_weight = 0;
    int min_index = INT16_MAX;

    for (int i = 0; i < no_of_cities; i++) {
        if (visited_sep[starting_point][i] == 1) {
            for (int j = 0; j < no_of_cities; j++) {
                if (visited[j] == 0 && adjacency_matrix[i][j] >= max_weight) {
                    if(adjacency_matrix[i][j] > max_weight){
                        next_vertex = j;
                        max_weight = adjacency_matrix[i][j];
                        min_index = j;
                    }
                    else if(j < min_index && min_index != INT16_MAX){
                        next_vertex = j;
                        min_index = j;
                    }
                }
            }
        }
    }
    
    // Update the visited and visited_sep arrays
    if (next_vertex != -1) {
        visited[next_vertex] = 1;
        visited_sep[starting_point][next_vertex] = 1;
    }
    
    return next_vertex;
}

int main(int argc, char *argv[]){
    fstream file;                          // open all input and output files
    ofstream output("prim.txt");

    file.open(argv[1]);
    string c;
    if (file.is_open()){
        getline(file, c, ' ');
        no_of_cities = stoi(c);  // read according to the input file format
        getline(file, c, ' ');
        const int no_of_bakeries = stoi(c);
        getline(file, c, '\n');
        double threshold = stod(c);

        int source_index_of_bakeries[no_of_bakeries];
        int i;

        for(i = 0; i < no_of_bakeries-1; i++){
            getline(file, c, ' ');
            source_index_of_bakeries[i] = stoi(c);
        }
        getline(file, c, '\n');
        source_index_of_bakeries[i] = stoi(c);

        int pount_of_cities[no_of_cities];

        for(int n = 0; n < no_of_cities; n++){
            getline(file, c, ' ');
            getline(file, c, ' ');   
            getline(file, c, '\n');
            pount_of_cities[n] = stoi(c);
        }

        visited = vector<int>(no_of_cities, 0); // general visited vector holding if a city is visited or not
        visited_sep = vector<vector<int>>(no_of_cities, vector<int>(no_of_cities, 0)); // seperate visited vector holding if a city visited by a particular bakery 
        adjacency_matrix = vector<vector<int>>(no_of_cities, vector<int>(no_of_cities, 0)); // adjacency amtrix for graph representation
        
        vector<vector<int>> roads = vector<vector<int>>(no_of_bakeries, vector<int>(no_of_cities, 0)); // for every bakery, holds their expansion paths
        vector<int> size_of_roads(no_of_bakeries, 0); // holds size of these paths

        // create adjacency matrix
        for(int m = 0; m < no_of_cities; m++) for(int n = 0; n <= m; n++) if(m != n) adjacency_matrix[n][m] = adjacency_matrix[m][n] = abs(pount_of_cities[m] - pount_of_cities[n]) <= (threshold * (pount_of_cities[m] + pount_of_cities[n])/2) ? abs(pount_of_cities[m] - pount_of_cities[n]) : 0;

        // initiate starting points
        for(int m = 0; m < no_of_bakeries; m++){
            visited[source_index_of_bakeries[m]] = 1;
            visited_sep[source_index_of_bakeries[m]][source_index_of_bakeries[m]] = 1;
            roads[m][0] = source_index_of_bakeries[m];
        }

        // apply prims algorithm to expand bakeries
        for(int k = 1; k < no_of_cities; k++){ // worst case scenario, one bakery takes over all cities and become a monopoly, 
        // so iterate number of cities times to be able to apply prims algorith in that scenario
            for(int m = 0; m < no_of_bakeries; m++){ // bakeries takes turns to take steps.
                if(roads[m][k-1] != -1) {
                    roads[m][k] = prim_step(source_index_of_bakeries[m]);
                    size_of_roads[m]++;
                }
                else roads[m][k] = -1;
            }
        }

        // write to prim.txt file
        for(int m = 0; m < no_of_bakeries; m++){
            output << "k" << m << " " << size_of_roads[m] << endl; 
            output << roads[m][0];
            for(int n = 1; n < size_of_roads[m]; n++){
                output << "->" << roads[m][n];
            }
            output << endl;
        }

    }

    file.close();     // close all files and exit
    output.close();

    exit(0);
}