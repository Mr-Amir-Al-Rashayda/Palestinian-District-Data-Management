# Palestinian District Data Management

This C program manages data about Palestinian districts and their towns, allowing users to perform various operations such as loading data from a file, sorting, adding, deleting, and saving data to a file. The program uses a doubly linked list to store the district information and a singly linked list for towns within each district.

## Features

*   **Data Loading**: Reads district and town data from a `districts.txt` file.

*   **Data Printing**: Prints the data in the same format as the input file or in a sorted, user-friendly format.

*   **Sorting**:
    *   Sorts districts alphabetically using Radix Sort.
    *   Sorts towns within each district by population in ascending order using bubble sort.

*   **Data Manipulation**:
    *   Adds new districts and towns.
    *   Deletes existing districts and towns.
    *   Modifies town populations.

*   **Data Analysis**:
    *   Calculates the total population of Palestine.
    *   Finds the maximum and minimum town populations.

*   **Data Persistence**: Saves the sorted data to a `sorted_districts.txt` file.

*   **Menu-Driven Interface**: Provides a simple menu for users to select operations.

## Data Structures

*   **District List**: A doubly linked list, `District_List`, where each node represents a district. Each district node contains the district name, total population, a pointer to the head of the town list, and pointers to the next and previous district nodes.

*   **Town List**: A singly linked list, `Town_List`, where each node represents a town. Each town node contains the town name, population, and a pointer to the next town node.

## Algorithms

*   **Radix Sort**: Used to sort the districts alphabetically by name. It efficiently sorts strings by processing characters from the least significant to the most significant position.

*   **Bubble Sort**: Used to sort the towns within each district by population.

## File Formats

*   **Input File (districts.txt)**: Contains district and town data in the format:

    `District Name | Town Name | Population`

    Each line represents a town within a district. The pipe symbol "|" separates the fields.

*   **Output File (sorted\_districts.txt)**: Contains the sorted data in the format:

    `District Name District, Population = Total District Population`

    `Town Name, Population`

    Each district is followed by its towns and their populations.

## Usage

1.  **Compile the Program**:

    ```bash
    gcc main.c -o district_manager
    ```

2.  **Run the Program**:

    ```bash
    ./district_manager
    ```

3.  **Interact with the Menu**: Follow the prompts to load data, perform operations, and save the results.

## Menu Options

1.  Load the input file.
2.  Print the list as input file format (without sorting).
3.  Sort District ONLY according to the District's name (Radix Sort with Printing Districts).
4.  Sort Towns ONLY according to town's population (ascending order with printing it).
5.  Print the total sorted list (sorted for Districts and Towns).
6.  Add a new District then sorted (With Printing it sorted).
7.  Add a new Town to a certain district (Without printing).
8.  Delete a town from a specific District (Without Printing).
9.  Delete a District with it's own Towns then sorted (With Printing it sorted).
10. Total population with the Maximum and Minimum Town population.
11. Print the Districts and their total population (without Towns details-unsorted one-).
12. Change the population of specific Town.
13. Save to output file (Sorted List).
14. Exit.
15. Add a new District (without printing it sorted).
16. Delete a District (without printing it sorted).
17. Print the total information (Without Sorting).
18. Save to output file (unsorted List).

## Code Structure

*   **`struct District_List`**: Represents a district in the linked list.
*   **`struct Town_List`**: Represents a town in the linked list.
*   **`readAllTheMatrix(FILE *file, ptrDistrict district)`**: Reads data from the input file and populates the linked list.
*   **`insert(ptrDistrict district, ptrDistrict elements_1st, ptrTown elements_2ed)`**: Inserts a new district and its towns into the linked list.
*   **`print_List_As_Input(ptrDistrict district)`**: Prints the data in the original input file format.
*   **`totalPopulation(ptrDistrict district)`**: Calculates the total population for each district.
*   **`print_List(ptrDistrict district)`**: Prints the district and town information in a user-friendly format.
*   **`add_New_Town(ptrDistrict district)`**: Adds a new town to an existing district.
*   **`delete_Town(ptrDistrict district)`**: Deletes a town from a district.
*   **`add_New_District(ptrDistrict district)`**: Adds a new district to the list.
*   **`delete_District(ptrDistrict district)`**: Deletes a district and its towns.
*   **`population_Max_Min(ptrDistrict district)`**: Calculates and prints the total population, maximum town population, and minimum town population.
*   **`getMax(ptrDistrict district)`**: Returns the length of the longest district name.
*   **`countSort(ptrDistrict district, int position)`**: Performs counting sort for Radix Sort.
*   **`radixSort(ptrDistrict district)`**: Sorts the districts using Radix Sort.
*   **`copyDistrictList(ptrDistrict district)`**: Creates a copy of the district list.
*   **`changeTownPopulation(ptrDistrict district)`**: Modifies the population of a specific town.
*   **`sortTowns(ptrDistrict district)`**: Sorts the towns within each district by population.
*   **`saveToFile(ptrDistrict district, const char *file_Name)`**: Saves the sorted data to the output file.
*   **`sortTownsReturn(ptrDistrict district)`**: Sorts the towns and returns the updated district list.
*   **`removeList(ptrDistrict district)`**: Frees the memory allocated for the district and town lists.

## Notes

*   The program assumes that the input file is correctly formatted.
*   Error handling is included to prevent crashes due to invalid input.
*   The program can handle a large number of districts and towns, limited only by available memory.

## Author

*   Amir Rasmi Al-Rashayda
