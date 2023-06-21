#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std::chrono;

void maxHeapify(double arr[], int n, int i) {  
    int l = 2 * i + 1; //left
    int r = 2 * i + 2; //right
    int largest = i; 
  
    if (l < n && arr[l] > arr[i])
      largest = l;
  
    if (r < n && arr[r] > arr[largest]) //find largest
      largest = r;
  
    if (largest != i){ //if largest is not i swap it
      std::swap(arr[i], arr[largest]);
      maxHeapify(arr, n, largest);   //call it recursively
    }
  }

void buildMaxHeap(double arr[], int n){
  for (int i = floor(n/2) - 1; i >= 0; i--){   //get largest to array[0]
    maxHeapify(arr, n, i);
  }
}
  
void heapSort(double arr[], int n) {  //heap sort method taken from course slides
  buildMaxHeap(arr, n);    
  for (int i = n - 1; i > 0; i--) {
    std::swap(arr[0], arr[i]);
    n--;
    maxHeapify(arr, i, 0);
  }
}

int main(int argc, char *argv[])
{
  if (argc <= 1){
    std::cout << "No file name entered. Please add a command line argument." << std::endl;
    return -1;
  }
  std::ofstream output("output1.txt");   //create new file named output1.txt
  
  std::ifstream input(argv[1]); // open the file
  
  auto start = high_resolution_clock::now();  //start chronometer
  if (input.is_open())
  {
    std::string line;
    getline(input, line); //for every getline get one line of input
    int num_of_estimators = stoi(line); //get num of estimators

    std::string estimators[num_of_estimators];
    for(int m = 0; m < num_of_estimators; m++){
      getline(input, line);
      estimators[m] = line;  //sotre estimators
    }

    getline(input, line);  //space
    getline(input, line, ','); //if ',' is specified, get till the comma
    int num_of_lines = stoi(line);  //get number of lines

    getline(input, line);
    std::string interested_feature = line; // get the feature we will be calculating with, eg. grp
    int selected_feature;
    if(interested_feature == "gap" || interested_feature == " gap") selected_feature = 0;
    else if(interested_feature == "grp" || interested_feature == " grp") selected_feature = 1;
    else if(interested_feature == "v" || interested_feature == " v") selected_feature = 2;
    else if(interested_feature == "gi" || interested_feature == " gi") selected_feature = 3; //accourding to this values we will select and store them after 

    double * array = new double[1000000]; //max num of elements
    int index = 0;
    int first_data_flag = 1;  // initally 1, used to get the first date and time added
    std::string starting_date;
    std::string starting_time;
    std::string ending_date;
    std::string ending_time;
    double total = 0;  // used to calculate mean


    while (getline(input, line)) //line = command (print-add)
    {
      if(line == "print"){ 
        double mean;
        double std_dev = 0;
        double median;
        double k = 100.0 / (index-1);
        int a = 25 / k;
        double firstQ;
        double thirthQ;
        int heap_sort_flag = 0; // used to call heapsort only one time in a print command, and if some feature requires us to sort it
        for(int t = 0; t < num_of_estimators; t++){
          if(estimators[t] == "mean") mean = total/index; // if wanted calculate mean
          if(estimators[t] == "std"){
            for(int p = 0; p < index; p++){
              std_dev += pow((array[p] - mean), 2);
            }
            std_dev = sqrt(std_dev / (index - 1)); // if wanted calculate standart deviation
          }
          if((estimators[t] == "firstq" || estimators[t] == "median" || estimators[t] == "thirdq" || estimators[t] == "min" || estimators[t] == "max") && heap_sort_flag == 0){
            heapSort(array, index); // if one of the feautures above wanted and heapsortflag is 0, call heap sort
            heap_sort_flag++; //heapsortflag = 1
          } 
          if(estimators[t] == "firstq"){
            a = 25 / k; //firstQ calculated according to formulas in homework
            firstQ = array[a] * (1 - (25 - a*k)/k) + array[a+1] * (1 - ((a+1)*k-25)/k);
          } 
          if(estimators[t] == "median"){
            if(index%2 == 0) median = array[index/2] / 2 + array[(index/2) - 1] / 2;
            else median = array[(index/2)];
          }
          if(estimators[t] == "thirdq"){
            a = 75 / k;  //firstQ calculated according to formulas in homework
            thirthQ = array[a] * (1 - (75 - a*k)/k) + array[a+1] * (1 - ((a+1)*k-75)/k);
            //thirthQ += 0.0001;
          }
        }
        // I wanted to split calculation and print phases, it at most loop 7 times so not a problem
        // write dates and times all the time
        output << std::defaultfloat << starting_date << "," << starting_time << "," << ending_date << "," << ending_time << ",";
        for(int k = 0; k < num_of_estimators; k++){ // according to the estimators array, write calculated values
          if(estimators[k] == "mean") output << std::setprecision(7) << mean;
          if(estimators[k] == "std") output << std::setprecision(7) << std_dev;
          if(estimators[k] == "min") output << std::setprecision(4) << array[0];
          if(estimators[k] == "firstq") output << std::setprecision(4) << firstQ;
          if(estimators[k] == "median") output << std::setprecision(4) << median;
          if(estimators[k] == "thirdq") output << std::setprecision(4) << thirthQ;
          if(estimators[k] == "max") output << std::setprecision(4) << array[index-1];
          if(k == num_of_estimators-1) output << std::endl;
          else output << " ,";
        }
        
      }
      else if(line == "add"){
        getline(input, line, ','); //day,time,global active power(gap),global reactive power(grp),voltage(v),global intensity(gi)
        if(first_data_flag == 1) starting_date = line;
        else ending_date = line;

        getline(input, line, ',');
        if(first_data_flag == 1) starting_time = line;
        else ending_time = line;
        first_data_flag = 0;  //assign starting and ending date and time

        getline(input, line, ',');
        for(int k = 0; k < selected_feature; k++){ //use selected feature number to select what value to select
          if(selected_feature == 3 && k == selected_feature - 1) {getline(input, line);}
          else {getline(input, line, ',');}
        }

        array[index] = stod(line); // turn string to double
        total += array[index]; // add to total, we will use it while calculating
        index++; // holds number of elements
        
        if(selected_feature != 3) getline(input, line); //if feature is not gi call getline to finish this line and go next
      }
      else std::cout << "Unknown command." << std::endl;
    }
    delete [] array;
    
  }
  else std::cout << "Couldn't open file.";
  input.close();
  output.close();  //close files
  auto stop = high_resolution_clock::now();  //stop chronometer
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "execution time -> " << duration.count() << " microseconds" << std::endl; //print duration with microseconds
  return 0;
}