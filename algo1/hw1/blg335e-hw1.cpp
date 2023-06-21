#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std::chrono;

int num_of_partiticions = 0; //global variables to keep track of all of the operations
int num_of_swaps = 0;


std::vector<std::vector<std::string>> readCsv(std::istream &in) //reads the csv file row by row, splits columns by ','
{
  std::vector<std::vector<std::string>> table;
  std::string row;
  while (!in.eof())
  {
    std::getline(in, row);
    if (!in) break;
    std::vector<std::string> fields{""};
    size_t i = 0; 
    for (char c : row) //for every char c in row
    {
      switch (c)
      {
      case ',': 
        fields.push_back("");
        i++;
        break;
      default:
        fields[i].push_back(c);
        break;
      }
    }
    table.push_back(fields);
  }
  return table;
}

void swap(double &i, double &k) //swaps two double values
{
  // if(!i || !k) return;
  double tmp = i;
  i = k;
  k = tmp;
}

void swap_string(std::string &i, std::string &k) //swaps two string values
{
  // if(!i || !k) return;
  std::string tmp = i;
  i = k;
  k = tmp;
}

// arr -> double array containing average_rating values, low -> first index of array
// high -> last index of array, bookIDs -> string array containing bookID column values
double QS1(double *arr, int low, int high, std::string * bookIDs)  
{
  int size = high - low + 1;
  int i = low;
  int j = low;
  double pivot = arr[high];

  if (low < high)
  {
    while (j >= i)
    {
      // if both i and j is lower than pivot, these elements will stay there so increment i and j
      while (arr[i] <= pivot && arr[j] <= pivot) 
      {
        if (j == high) //while doing this if we encounter the highest index of array, break and finish the partition part
        {
          break;
        }
        j++;
        i++;
      }

      while (arr[j] > pivot)
      {
        if (j >= high)
        {
          break;
        }
        j++;
        swap(arr[i], arr[j]);
        swap_string(bookIDs[i], bookIDs[j]);
        num_of_swaps++;
        // if ith value is less than or equal to pivot, than no problem, increment i becasuse that value will stay there
        if (arr[i] <= pivot) i++; 
        // but if it is not, we need to move that element to the right side of the pivot too so we do these steps
        do
        {
          if (j == high)
            goto finish;
          j++;  
        } while (arr[j] > pivot); 
        // increment j till arr[j] is less than pivot, by doing that 
        //we find the element we will swap with the other element that we need to move to the right side of the pivot

        swap(arr[i], arr[j]);
        swap_string(bookIDs[i], bookIDs[j]);
        num_of_swaps++;

        do
        {
          i++;  
        } while (arr[i] <= pivot);

        if (j >= high)
          break;
      }

      if (arr[i] > pivot && arr[j] <= pivot) // this scenario can make the algorithm stuck, so i added it to swap the values
      {
        swap(arr[i], arr[j]);
        swap_string(bookIDs[i], bookIDs[j]);
        num_of_swaps++;
      }

    finish: 

      if (j == high) 
      {
        swap(arr[i], arr[high]);
        swap_string(bookIDs[i], bookIDs[j]);
        num_of_swaps++;
        break;
      }
    }
    
    num_of_partiticions++; // while loop in our code is the partiticion part, 
                          //so we increment the num_of_partiticions after loop broke


    // repeat sorting for low-(i-2) and i-high
    //  sizes will be i-1 and high-i+1

    // i-1 is partition index

    // i did not used i-2 and i-1 for the scenario that algorithm need to find the one lower value than the pivot
    // among many pivot elements, like [2 2 2 2 1.67 2 2 2] if i use i-2, it can step over that element
    QS1(arr, low, i - 1, bookIDs); //call quicksort for lower part and higher part 
    QS1(arr, i, high, bookIDs);
  }
  return i - 1; // return value partition index did not actually used anywhere in my algorithm
}

int main()
{
  std::ifstream data("books.csv"); // declare the data as a variable
  std::vector<std::vector<std::string>> csv_file = readCsv(data); // read and save as a two dimensional string vector
  int size = csv_file.size(); //size of the vector, it is 1 more then the actual 
  std::string bookIDs[size]; // array to keep the book id column
  std::string avg_ratings[size]; // array to keep the average_rating column

  int i = 0;
  for (auto const &string_vec : csv_file)  //from csv file vector, for every string vector
  {
    int m = 0;
    for (auto const &s : string_vec)  // in every string vector (row), declare s as the section
    {
      if(m == 0)        // bookID column
        bookIDs[i-1] = s; 
      if (m == 3)       // average_rating column 
        avg_ratings[i] = s;
      m++;                // to keep track of columns
    }
    i++;      // to keep track of arrays next index
  }

  double avg_double[size - 1];
  
  int l = 0;
  for (int k = 1; k < size; k++)
  {
    if (!avg_ratings[k].empty())
    {
      avg_double[l] = std::stod(avg_ratings[k]);  // convert string array to double array, it starts from 0th index
      l++;
    }
  }
  /*
  QS1(avg_double, 0, size - 2, bookIDs);   //to revert array
  int t = 0;
  int j = size - 2;
  for ( t, j; t < size/2; t++, j--)  
  {     
    int tmp = avg_double[t];  
    avg_double[t] = avg_double[j];  
    avg_double[j] = tmp;  
  }  
  */

  std::cout << "------array before sorting------" << std::endl;
  for (int k = 0; k < size - 1; k++)
  {
    std::cout << k << " -> " << avg_double[k] << std::endl;  //print array before sorting
  }

  auto start = high_resolution_clock::now();  //start chronometer
  QS1(avg_double, 0, size - 2, bookIDs);      //call quicksort recusive function 
  auto stop = high_resolution_clock::now();  //stop chronometer

  auto duration = duration_cast<microseconds>(stop - start);

  std::cout << "------array after sorting------" << std::endl;
  for (int k = 0; k < size - 1; k++)
  {
    std::cout << k << " -> " << avg_double[k] << std::endl; //print array after sorting
  }

  std::cout << "execution time -> " << duration.count() << " microseconds" << std::endl;

  std::cout << "number of partitions -> " << num_of_partiticions << " times" << std::endl;
  std::cout << "number of swaps -> " << num_of_swaps << " times" << std::endl;

  std::ofstream file("sorted_books.txt");   //create new file named sorted_books.txt
  file << "bookID average_rating" << std::endl;  //first row of file
  for (int k = 0; k < size - 1; k++){
    file << std::setw(5) << bookIDs[k] << std::setw(6) << avg_double[k] << std::endl;
     //for every element of our sorted arrays, write them to a row of the file
  }
  file.close();  //close the file

  return 0;
}