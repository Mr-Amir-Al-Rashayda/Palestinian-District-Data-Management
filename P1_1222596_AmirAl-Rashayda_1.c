
// Name : Amir Rasmi Al-Rashayda
// ID : 1222596
// Sec : 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* General Notes :
 *It's important to note that I've used the same concept scenarios in many common functions within my application because it's the same methodology you are asking for
 *I've included a wide range of cases to address various potential requests, some of which may not have been explicitly mentioned in the project (i've explained what everysingle request does in my program).
 *This is why my menu contains 18 options, not just 14, ensuring it covers all 14 requested with with more specifications  as well as additional ones
 */

typedef struct District_List *ptrDistrict;
typedef struct Town_List *ptrTown;
#define MAX_SIZE 50
// Adjust CHAR_RANGE to cover the ASCII range "upper case and lower case"  // used in radix sort
#define CHAR_RANGE 256

int counter = 0;      // used this counter to sort the district or not when we sort the towns // in sorttowns func
int counterPrint = 0; // used this to print the towns or not // in the prinlist fun
int radixcounter = 1; // used to make a copy of the list in radix func or not // used in radix func

struct District_List // doubly linked list "This should be done using a doubly implementation of the Linked List"
{
    char city[MAX_SIZE];
    int total_District_Population;
    ptrDistrict Next;
    ptrDistrict Previous;
    ptrTown townHead; // represent the head of the town nodes
};

struct Town_List // for town nodes for each single district
{
    char town[MAX_SIZE];
    int population;
    ptrTown Next;
};

void trim(char *str)
{
    // Remove trailing spaces
    int end = strlen(str) - 1;
    while (end >= 0 && isspace((unsigned char)str[end]))
    {                    // isspace used to cheack if the end char is whitespace or not
        str[end] = '\0'; // if it is so then make remove it by \0
        end--;           // decrement the size
    }

    int start = 0;
    while (str[start] != '\0' && isspace((unsigned char)str[start]))
    { // same thing for the start
        start++;
    }

    // Shift all characters to the left to remove the \0 \0 ....
    memmove(str, str + start, end - start + 2);
}

void readAllTheMatrix(FILE *file, ptrDistrict district);
void insert(ptrDistrict district, ptrDistrict elements_1st, ptrTown elements_2ed);
void print_List_As_Input(ptrDistrict district);
void totalPopulation(ptrDistrict district);
void print_List(ptrDistrict district);
void add_New_Town(ptrDistrict district);
void delete_Town(ptrDistrict district);
void add_New_District(ptrDistrict district);
void delete_District(ptrDistrict district);
void population_Max_Min(ptrDistrict district);
void printSortedDistricts(ptrDistrict district);
void radixSort(ptrDistrict district);
void countSort(ptrDistrict district, int position);
int getMax(ptrDistrict district);
void changeTownPopulation(ptrDistrict district);
void sortTowns(ptrDistrict district);
ptrDistrict sortTownsReturn(ptrDistrict district);
ptrDistrict copyDistrictList(ptrDistrict district);
void saveToFile(ptrDistrict district, const char *file_Name);
void removeList(ptrDistrict district);

int main()
{
    ptrDistrict district = (ptrDistrict)malloc(sizeof(struct District_List));

    district->Next = NULL;
    district->Previous = NULL;
    district->townHead = NULL;

    int operation = 0;
    FILE *inFile = fopen("districts.txt", "r");
    if (inFile == NULL)
    {
        printf("Error in opening the file.\n");
        return 1;
    }

    printf("Hello my friend\n");
    while (operation != 14)
    {   // in request 11 i made it for the unsorted list beacuse if you want the sorted one you can just enter 3 
        printf("Which operation you want to do next sir :\n\n1-Load the input file\n2-Print the List as input file format (Wiithout sorting)\n3-Sorted District ONLY according to the District's name (Radix Sort with Printing Districts)\n4-Sort Towns ONLY according to town's population (ascending order with printing it)\n5-Print the total sorted list (sorted for Districts and Towns)");
        printf("\n6-Add a new District then sorted (With Printing it sorted)\n7-Add a new Town to a certain district (Without printing)\n8-Delete a town from a specific District (Without Printing)\n9-Delete a District with it's own Towns then sorted (With Printing it sorted)\n10-Toatal popualtion with the Maximum and Minimum Town population\n11-Print the Districts and their total population (without Towns details-unsorted one-)\n12-Change the population of specific Town");
        printf("\n13-Save to output file (Sorted List)\n14-Exit\n\nAdditional operation you may ask for ...\n20-Add a new District (without printing it sorted)\n21-Delete a District(without printing it sorted)\n22-Print the total information (Without Sorting)\n23-Save to output file (unsorted List)\n");

        int result;
        while (1)
        {
            result = scanf("%d%*c", &operation);

            if (result != 1)
            {
                // Clear input buffer if non-numeric value is entered
                while ((getchar()) != '\n')
                    ;
                printf("Invalid input. Please enter a number.\n");
            }
            else
            {
                // Break the loop if a valid number is entered
                break;
            }
        }
        switch (operation)
        {
        case 1:
            readAllTheMatrix(inFile, district); // loaded file
            break;
        case 2:
            print_List_As_Input(district); // print the loaded as input file
            break;
        case 3:
            counterPrint = 0;
            radixSort(district); // print it sorted for district
            break;
        case 4:
            counter = 0;                           // so it don't sort the district
            counterPrint = 1;                      // so it print the towns also
            sortTowns(copyDistrictList(district)); // printed soted according to towns
            break;
        case 5:
            counter = 1;                           // so it sort the district
            counterPrint = 1;                      // print the towns
            sortTowns(copyDistrictList(district)); // printed the sorted list (towns and districts)
            break;
        case 6:
            add_New_District(district);
            counter = 1;      // so it sort the district
            counterPrint = 1; // print the towns
            sortTowns(copyDistrictList(district));
            break;
        case 7:
            add_New_Town(district);
            break;
        case 8:
            delete_Town(district);
            break;
        case 9: // delete with sorted
            delete_District(district);
            counter = 1;
            counterPrint = 1;
            sortTowns(copyDistrictList(district));
            break;
        case 10:
            population_Max_Min(district);
            break;
        case 11: // print district with total pop without towns
            counterPrint = 0;
            print_List(district);
            break;
        case 12: // change the pop of town
            changeTownPopulation(district);
            break;
        case 13:
        {
            counter = 1;      // sort it
            counterPrint = 1; // print the towns
            radixcounter = 0; // already made the copy
            saveToFile(sortTownsReturn(copyDistrictList(district)), "sorted_districts.txt");
            radixcounter = 1;
            break;
        }
        case 14:
        {
            removeList(district);
            printf("All data has been deleted\n");
            printf("Good Bye Friend....\n");
            break;
        }

        //*********************************************ADDITIONAL*********************************************//
        case 20:
            add_New_District(district);
            break;
        case 21:
            delete_District(district);
            break;
        case 22:
            counterPrint = 1; // with towns
            print_List(district);
            break;
        case 23:
        {
            saveToFile(district, "sorted_districts.txt");
            break;
        }
        default:
            printf("Enter a valid Number From The choices\n\n");
            continue;
        }
    }

    fclose(inFile);
    return 0;
}

void readAllTheMatrix(FILE *file, ptrDistrict district)
{
    struct District_List cities;
    struct Town_List towns;

    // read first in the struct variable ....
    while (fscanf(file, "%[^49|]|%49[^|]|%d\n", cities.city, towns.town, &towns.population) != EOF) // 49 and the 50 for the \0 end of string
    {
        ptrDistrict elements_1st = (ptrDistrict)malloc(sizeof(struct District_List)); // for the district list
        ptrTown elements_2ed = (ptrTown)malloc(sizeof(struct Town_List));             // for the towns nodes

        strcpy(elements_1st->city, cities.city);
        strcpy(elements_2ed->town, towns.town);
        elements_2ed->population = towns.population;
        trim(elements_1st->city); // to cut or remove the white spaces
        trim(elements_2ed->town);
        insert(district, elements_1st, elements_2ed); // link the nodes with the list
    }
    totalPopulation(district); // after loading count the total pop
    printf("Loaded the info successfully\n");
    printf("\n");
}

void print_List_As_Input(ptrDistrict district)
{

    if (district->Next == NULL)
    {
        printf("The district list is empty!\n\n");
        return;
    }

    ptrDistrict temp1;
    ptrTown temp2;
    temp1 = district->Next;

    while (temp1 != NULL)
    {
        if (temp1 != NULL && temp1->townHead != NULL)
        { // check if the distric has any towns
            temp2 = temp1->townHead;
            while (temp1 != NULL && temp1->townHead != NULL)
            { // go through the districts one by one
                while (temp2 != NULL)
                { // go through the towns one by one
                    printf("%s | %s | %d\n", temp1->city, temp2->town, temp2->population);
                    temp2 = temp2->Next;
                }
                temp1 = temp1->Next;
                if (temp1 != NULL && temp1->townHead != NULL)
                    temp2 = temp1->townHead;
            }
        }
        else if (temp1 != NULL && temp1->townHead == NULL)
        { // if it doesn't contain towns
            printf("%s | %s | %d\n", temp1->city, "The District Does Not has any Towns yet", 0);
            temp1 = temp1->Next;
        }
    }
    printf("\n");
}

void insert(ptrDistrict district, ptrDistrict elements_1st, ptrTown elements_2ed)
{
    if (district != NULL && elements_1st != NULL && elements_2ed != NULL) // there's no errors in the inputs
    {
        ptrDistrict temp1 = district;
        ptrTown temp2;

        // Find the district or the end of the list
        if (temp1->Next->city != '\0' || elements_1st->city != '\0')                              // contain values
            while (temp1->Next != NULL && strcasecmp(temp1->Next->city, elements_1st->city) != 0) // go to the last node
                temp1 = temp1->Next;

        // If the district was not found, insert it
        if (temp1->Next == NULL || strcasecmp(temp1->Next->city, elements_1st->city) != 0)
        { // if it's did go to the last then insert it
            elements_1st->Next = temp1->Next;
            temp1->Next = elements_1st;
            elements_1st->townHead = NULL;
            elements_1st->Previous = temp1;
            temp1 = elements_1st;
        }
        else
        {
            temp1 = temp1->Next; // The district already exists, point to it
        }

        // Now, temp1 points to the district where we want to insert the town

        if (temp1->townHead == NULL)
        { // if it doesn't contain any towns then add the first one
            temp1->townHead = elements_2ed;
            elements_2ed->Next = NULL;
        }
        else
        {
            // Find the end of the town list
            for (temp2 = temp1->townHead; temp2->Next != NULL; temp2 = temp2->Next)
                ;

            // Insert the new town at the end of the list
            elements_2ed->Next = NULL;
            temp2->Next = elements_2ed;
        }
    }
    else
        printf("ERROR IN THE INITIAL VALUES !!\n");
}

void totalPopulation(ptrDistrict district)
{
    if (district->Next == NULL)
    {
        printf("The district list is empty!\n\n");
        return;
    }

    ptrTown tempTown = district->townHead;
    ptrDistrict tempDistrict = district;

    while (tempDistrict != NULL)
    {
        tempDistrict->total_District_Population = 0;

        while (tempTown != NULL)
        {
            (tempDistrict->total_District_Population) += (tempTown->population); // counting the total pop
            tempTown = tempTown->Next;
        }
        tempDistrict = tempDistrict->Next;
        if (tempDistrict != NULL) // to avoid the NULL pointer
            tempTown = tempDistrict->townHead;
    }
}

void print_List(ptrDistrict district)
{
    if (district->Next == NULL)
    {
        printf("The district list is empty!\n\n");
        return;
    }

    ptrTown tempTown = district->Next->townHead;
    ptrDistrict tempDistrict = district->Next;

    if (tempDistrict != NULL)
    {

        while (tempDistrict != NULL)
        {
            if (tempDistrict->townHead != NULL)
            {
                printf("%s District, Population = %d\n", tempDistrict->city, tempDistrict->total_District_Population);
                while (tempTown != NULL && counterPrint) // the counter used to modify the print if we want to print the towns or not
                {
                    printf("%s, %d\n", tempTown->town, tempTown->population);
                    tempTown = tempTown->Next;
                }
                tempDistrict = tempDistrict->Next;
                if (tempDistrict != NULL) // avoid the null pointer
                    tempTown = tempDistrict->townHead;
            }

            else
            {
                tempDistrict->total_District_Population = 0;
                printf("%s District, Population = %d\n", tempDistrict->city, tempDistrict->total_District_Population);
                if (counterPrint)
                    printf("No towns added yet\n");
                tempDistrict = tempDistrict->Next;
                if (tempDistrict != NULL)
                    tempTown = tempDistrict->townHead;
            }
        }
    }
    else
        printf("THERE IS NO DISTRICTS !!\n");
    printf("\n");
}

void add_New_Town(ptrDistrict district)
{

    if (district->Next == NULL)
    {
        printf("The district list is empty!\n\n");
        return;
    }
    char city[MAX_SIZE];
    ptrTown elements_2ed = (ptrTown)malloc(sizeof(struct Town_List));
    elements_2ed->Next = NULL;

    // 49 to read up to 49 char and left the last one "50" for the \0 which gives us th max_size
    printf("Enter the name of the city: \n");
    scanf("%49[^\n]%*c", city); //[^\n] read up to the first new line or until it reach th 49 char
    trim(city);                 // trim will handle spaces

    printf("Enter the name of the town: \n");
    scanf("%49[^\n]%*c", elements_2ed->town); // %*c to read and discard the new line so it doesn't miss the next scan
    trim(elements_2ed->town);

    printf("Enter its population: \n");
    scanf("%d%*c", &elements_2ed->population);

    ptrDistrict tempDistrict;
    ptrTown tempTown;

    if (district->Next != NULL && elements_2ed != NULL)
    {
        tempDistrict = district->Next;

        while (tempDistrict != NULL)
        {
            if (strcasecmp(tempDistrict->city, city) == 0)
                break;
            tempDistrict = tempDistrict->Next;
        }

        if (tempDistrict == NULL) // check if it stops because the null not because the match
            printf("The District Does NOT Exist\n\n");

        else
        { // meaning the district does exist
            if (tempDistrict->townHead != NULL)
            { // if there's other towns
                tempTown = tempDistrict->townHead;
                while (tempTown->Next != NULL && strcasecmp(tempTown->town, elements_2ed->town) != 0) // go to the one and then add it at last
                    tempTown = tempTown->Next;

                if (strcasecmp(tempTown->town, elements_2ed->town) == 0)
                    printf("The town is already exist !\n\n");

                else
                {
                    printf("Adding ....\n");
                    elements_2ed->Next = tempTown->Next;
                    tempTown->Next = elements_2ed;
                    totalPopulation(district);
                    printf("Done\n\n");
                }
            }
            else
            { // if there's no towns then add this single one
                printf("Adding ....\n");
                elements_2ed->Next = tempDistrict->townHead;
                tempDistrict->townHead = elements_2ed;
                totalPopulation(district);
                printf("Done\n\n");
            }
        }
    }
    else
        printf("Either that there's none a such city called %s in the system OR You didn't enterd a valid town : \n\n", city);
}

void delete_Town(ptrDistrict district)
{

    if (district->Next != NULL)
    {
        ptrDistrict temp = district->Next;
        ptrTown delet;
        char city[MAX_SIZE];
        char town[MAX_SIZE];

        // 49 to read up to 49 char and left the last one "50" for the \0 which gives us th max_size
        printf("Enter the name of District you want to delete it's town: \n");
        scanf("%49[^\n]%*c", city); //[^\n] read up to the first new line or until it reach th 49 char
        trim(city);                 // trim will handle spaces

        printf("Enter the name of Town you want to delete from it: \n");
        scanf("%49[^\n]%*c", town); // %*c to read and discard the new line so it doesn't miss the next scan
        trim(town);

        while (strcasecmp(city, temp->city) != 0 && temp->Next != NULL)
            temp = temp->Next;
        if (temp->Next == NULL && strcasecmp(city, temp->city) != 0)
            printf("The Name of District you Entered Does NOT Exist !\n\n");
        else
        {
            if (strcasecmp(temp->townHead->town, town) == 0)
            { // the case when it's the first node
                delet = temp->townHead;
                temp->townHead = delet->Next;
                delet->Next = NULL;
                totalPopulation(district); // refind the total pop
                free(delet);
                printf("The town %s deleted successfully\n\n", town);
            }
            else
            { // the case when it's not the fisrt one
                ptrTown temp2 = temp->townHead;

                while (temp2->Next != NULL && strcasecmp(town, temp2->Next->town) != 0) // trying to find it
                    temp2 = temp2->Next;
                if (temp2->Next == NULL)
                    printf("The Name of the town Does NOT Exist !\n\n");
                else
                {
                    delet = temp2->Next;
                    temp2->Next = delet->Next;
                    delet->Next = NULL;
                    free(delet);
                    totalPopulation(district);
                    printf("The town %s deleted successfully\n\n", town);
                }
            }
        }
    }
    else
        printf("There's Nothing to delete !\n\n");
}

void add_New_District(ptrDistrict district)
{

    ptrDistrict element_1st = (ptrDistrict)malloc(sizeof(struct District_List));
    element_1st->Next = NULL;
    ptrDistrict temp;
    char city[MAX_SIZE];

    // 49 to read up to 49 char and left the last one "50" for the \0 which gives us th max_size
    printf("Enter the Name of the District:\n");
    scanf("%49[^\n]%*c", city);
    trim(city);
    strcpy(element_1st->city, city);

    if (district->Next != NULL)
    {
        temp = district->Next;
        while (temp->Next != NULL && strcasecmp(temp->city, city) != 0)
            temp = temp->Next;
        if (strcasecmp(temp->city, city) == 0)
        { // matches
            printf("The District %s is already in the list\n\n", city);
        }
        else
        { // added to the last
            element_1st->Next = temp->Next;
            temp->Next = element_1st;
            element_1st->Previous = temp;
            element_1st->townHead = NULL;
            printf("The District %s has been added\n\n", element_1st->city);
            totalPopulation(district);
        }
    }
    else
    { // added to the first
        element_1st->Next = district->Next;
        district->Next = element_1st;
        element_1st->Previous = district;
        element_1st->townHead = NULL;
        totalPopulation(district);
        printf("The District %s has been added\n\n", element_1st->city);
    }
}

void delete_District(ptrDistrict district)
{
    if (district->Next != NULL)
    {

        char city[MAX_SIZE];
        printf("Enter the Name of the District:\n");
        scanf("%49[^\n]%*c", city);
        trim(city);

        ptrDistrict temp1 = district->Next;
        ptrDistrict temp1_1 = district;

        // Loop to find the district to delete
        while (temp1 != NULL && strcasecmp(temp1->city, city) != 0)
        {
            temp1_1 = temp1;
            temp1 = temp1->Next;
        }

        // Check if the district is found
        if (temp1 != NULL)
        {
            // Free the towns in the district
            ptrTown temp2 = temp1->townHead;
            while (temp2 != NULL)
            {
                ptrTown toDelete = temp2;
                temp2 = temp2->Next;
                free(toDelete);
            }

            // Unlink and free the district
            temp1_1->Next = temp1->Next;
            if (temp1->Next != NULL)
            {
                temp1->Next->Previous = temp1_1;
            }
            free(temp1);
            printf("The district %s has been deleted successfully.\n\n", city);
        }
        else
        {
            printf("The district %s does not exist.\n\n", city);
        }
    }
    else
    {
        printf("There's nothing to delete.\n\n");
    }
}

void population_Max_Min(ptrDistrict district)
{

    if (district->Next != NULL)
    {
        int max;
        int min;
        int totalPopulation = 0;
        char maxCity[MAX_SIZE];
        char minCity[MAX_SIZE];

        ptrDistrict city = district->Next;
        ptrTown town = city->townHead;

        min = town->population;
        max = town->population;
        strcpy(maxCity, town->town);
        strcpy(minCity, town->town);

        while (city != NULL)
        {

            while (town != NULL)
            {

                if (min > town->population)
                {
                    min = town->population;
                    strcpy(minCity, town->town);
                }
                else if (max < town->population)
                {
                    max = town->population;
                    strcpy(maxCity, town->town);
                }
                town = town->Next;
            }
            totalPopulation += city->total_District_Population; // the total pop of palestine
            city = city->Next;
            if (city != NULL)
                town = city->townHead; // avoid null pointer
        }
        printf("The total population of all the District is %d\nThe Maximum poplualtion is in town %s with %d people\nThe Minimum Population is in town %s with %d people\n\n", totalPopulation, maxCity, max, minCity, min);
    }
    else
        printf("There's nothing to calculate !\n\n");
}

int getMax(ptrDistrict district)
{
    int max = 0;
    ptrDistrict temp = district->Next;
    while (temp != NULL)
    {
        int len = strlen(temp->city);
        if (len > max)
        {
            max = len; // make it the max length word
        }
        temp = temp->Next;
    }
    return max;
}

void countSort(ptrDistrict district, int position)
{

    ptrDistrict buckets[CHAR_RANGE];    // one bucket for each character "256"
    int bucketCounts[CHAR_RANGE] = {0}; // count of elements in each bucket

    ptrDistrict temp, nextNode;

    for (int i = 0; i < CHAR_RANGE; i++)
    {
        buckets[i] = (ptrDistrict)malloc(sizeof(struct District_List));
        buckets[i]->Next = NULL;
    }

    // distribute districts into buckets based on the current character
    temp = district->Next; // point at the first one
    while (temp != NULL)
    {
        nextNode = temp->Next; // so we don't lose the distric list

        int index;
        if (position < strlen(temp->city))
        {
            index = (unsigned char)temp->city[position]; // use the character at 'position' in 'city' string
        }
        else
        {
            index = 0; // Default value for city strings shorter than 'position' // or the white spaces...
        }

        ptrDistrict bucketTail = buckets[index]; // it's like a refrence for the array of struct "buckets"
        while (bucketTail->Next != NULL)
        {
            bucketTail = bucketTail->Next; // go to the next if there's other word contains the same letter at the same position
        }
        bucketTail->Next = temp; // connect the bucketTail in other words the buckets with our own node "temp"
        temp->Next = NULL;       // disconnect that node
        temp = nextNode;         // go to next node in the district
        bucketCounts[index]++;
    }

    // Concatenate buckets back to district list
    ptrDistrict last = district;
    for (int i = 0; i < CHAR_RANGE; i++)
    {
        if (bucketCounts[i] > 0)
        {
            last->Next = buckets[i]->Next;
            while (last->Next != NULL)
            {
                last = last->Next;
            }
        }
        free(buckets[i]); // Free the bucket head nodes
    }
}

void radixSort(ptrDistrict district)
{
    if (district->Next == NULL)
    {
        printf("The district list is empty!\n");
        return;
    }

    int max = getMax(district); // Get max length of district names
    ptrDistrict copy;

    if (radixcounter)                      // the radixcounter made only for the case 13 only
        copy = copyDistrictList(district); // Copy the list
    else
        copy = district;

    // Perform counting sort for each character position from the last one (based one the max one) to the fist one
    for (int position = max - 1; position >= 0; position--)
    {
        countSort(copy, position);
    }

    // Print the sorted districts
    printf("Sorted Districts:\n");
    print_List(copy);
    // Free the memory allocated for the copied list
    if (radixcounter)
    { // used to clean the copy from the memory // the radixcounter made only for the case 13 only
        removeList(copy);
    }
}

void printSortedDistricts(ptrDistrict district)
{
    ptrDistrict current = district->Next; // Start from the first district
    while (current != NULL)
    {
        printf("%s\n", current->city); // Print district city name
        current = current->Next;       // Move to the next district
    }
}

ptrDistrict copyDistrictList(ptrDistrict district)
{
    if (district == NULL)
    {
        return NULL;
    }

    ptrDistrict copy = (ptrDistrict)malloc(sizeof(struct District_List));
    ptrDistrict currentCopy = copy;
    ptrDistrict tempDistrict = district->Next;

    while (tempDistrict != NULL)
    {
        currentCopy->Next = (ptrDistrict)malloc(sizeof(struct District_List));
        strcpy(currentCopy->Next->city, tempDistrict->city);
        currentCopy->Next->total_District_Population = tempDistrict->total_District_Population;
        currentCopy->Next->Previous = currentCopy;

        // Copy the town list
        if (tempDistrict->townHead != NULL)
        {
            currentCopy->Next->townHead = (ptrTown)malloc(sizeof(struct Town_List));
            ptrTown fixedTownCopy = currentCopy->Next->townHead;
            ptrTown fixedTowndistrict = tempDistrict->townHead;

            while (fixedTowndistrict != NULL)
            {
                strcpy(fixedTownCopy->town, fixedTowndistrict->town);
                fixedTownCopy->population = fixedTowndistrict->population;

                if (fixedTowndistrict->Next != NULL)
                {
                    fixedTownCopy->Next = (ptrTown)malloc(sizeof(struct Town_List));
                    fixedTownCopy = fixedTownCopy->Next;
                }
                else
                {
                    fixedTownCopy->Next = NULL;
                }

                fixedTowndistrict = fixedTowndistrict->Next;
            }
        }
        else
        {
            currentCopy->Next->townHead = NULL;
        }

        currentCopy = currentCopy->Next;
        tempDistrict = tempDistrict->Next;
    }
    currentCopy->Next = NULL; // Mark the end of the list

    return copy;
}

void changeTownPopulation(ptrDistrict district)
{

    if (district->Next == NULL)
    {
        printf("Can't change since the district is Empty !!\n\n");
        return;
    }
    char city[MAX_SIZE];
    ptrTown elements_2ed = (ptrTown)malloc(sizeof(struct Town_List));
    elements_2ed->Next = NULL;

    printf("Enter the name of the city: \n");
    scanf("%49[^\n]%*c", city);
    trim(city); // trim to remove spaces form the fisrt and end

    printf("Enter the name of the town: \n");
    scanf("%49[^\n]%*c", elements_2ed->town);
    trim(elements_2ed->town); // trim to remove spaces form the fisrt and end

    printf("Enter its population: \n");
    scanf("%d%*c", &elements_2ed->population);

    ptrDistrict tempDistrict;
    ptrTown tempTown;

    if (district->Next != NULL && elements_2ed != NULL)
    { // since the district isn't null because of the above that's mean theat lements_2ed got an error
        tempDistrict = district->Next;

        while (tempDistrict != NULL)
        {
            if (strcasecmp(tempDistrict->city, city) == 0)
                break;
            tempDistrict = tempDistrict->Next;
        }

        if (tempDistrict == NULL) // to check if the problem is with the null not with the match
            printf("The District that contains your town Does NOT Exist\n\n");

        else
        { // the matches case
            if (tempDistrict->townHead != NULL)
            { // now doing the same thing with the towns
                tempTown = tempDistrict->townHead;
                while (tempTown->Next != NULL && strcasecmp(tempTown->town, elements_2ed->town) != 0)
                    tempTown = tempTown->Next;

                if (strcasecmp(tempTown->town, elements_2ed->town) == 0)
                { // found it
                    tempTown->population = elements_2ed->population;
                    totalPopulation(district);
                    printf("The Population changed successfully\n\n");
                }
                else
                {
                    printf("The town Does NOT Exist\n\n");
                }
            }
            else
            {
                printf("The town Does NOT Exist\n\n");
            }
        }
    }
    else
        printf("You didn't enterd a valid answer : \n\n");
}

void sortTowns(ptrDistrict district)
{
    if (district->Next == NULL)
    {
        printf("The list Empty\n\n");
        return;
    }

    ptrDistrict tempDistrict = district->Next;

    while (tempDistrict != NULL)
    {
        ptrTown fixedTown = tempDistrict->townHead;
        while (fixedTown != NULL)
        {
            ptrTown searchTown = fixedTown->Next; // next the fixed one
            while (searchTown != NULL)
            {
                if (fixedTown->population > searchTown->population)
                { // make swap if it's bigger than others

                    // the swap operation
                    int tempPopulation = fixedTown->population;
                    fixedTown->population = searchTown->population;
                    searchTown->population = tempPopulation;

                    char tempTown[MAX_SIZE];
                    strcpy(tempTown, fixedTown->town);
                    strcpy(fixedTown->town, searchTown->town);
                    strcpy(searchTown->town, tempTown);
                }
                searchTown = searchTown->Next; // go to next town to compare it
            }
            fixedTown = fixedTown->Next; // go to next fixed "stable" town
        }
        tempDistrict = tempDistrict->Next; // go to next district to compar it's own towns
    }
    if (counter)
        radixSort(district); // used for the main and the request
    else
        print_List(district);
}

void saveToFile(ptrDistrict district, const char *file_Name)
{
    // fisrt be sure that it contains data
    if (district->Next == NULL)
    {
        printf("can't save to output file since The district list is empty!\n\n");
        return;
    }

    FILE *saveFileOutPut = fopen(file_Name, "w"); // w since we are writing

    if (saveFileOutPut == NULL)
    {
        printf("error happend while opening %s file\n", file_Name);
        return;
    }

    ptrDistrict tempDistrict = district->Next;
    // now go throug the distric and print as the requested format
    while (tempDistrict != NULL)
    {
        fprintf(saveFileOutPut, "%s District, Population: %d\n", tempDistrict->city, tempDistrict->total_District_Population);
        ptrTown fixedTown = tempDistrict->townHead;
        // going throug the towns and print as request format too
        while (fixedTown != NULL)
        {
            fprintf(saveFileOutPut, "%s, %d\n", fixedTown->town, fixedTown->population);
            fixedTown = fixedTown->Next; // increment towns
        }

        tempDistrict = tempDistrict->Next; // increment districts
    }

    fclose(saveFileOutPut);
}

ptrDistrict sortTownsReturn(ptrDistrict district)
{

    if (district->Next == NULL)
    {
        printf("The list Empty\n\n");
        return district;
    }

    ptrDistrict tempDistrict = district->Next;

    while (tempDistrict != NULL)
    {
        ptrTown fixedTown = tempDistrict->townHead;
        while (fixedTown != NULL)
        {
            ptrTown searchTown = fixedTown->Next; // next the fixed one
            while (searchTown != NULL)
            {
                if (fixedTown->population > searchTown->population)
                { // make swap if it's bigger than others

                    // the swap operation
                    int tempPopulation = fixedTown->population;
                    fixedTown->population = searchTown->population;
                    searchTown->population = tempPopulation;

                    char tempTown[MAX_SIZE];
                    strcpy(tempTown, fixedTown->town);
                    strcpy(fixedTown->town, searchTown->town);
                    strcpy(searchTown->town, tempTown);
                }
                searchTown = searchTown->Next; // go to next town to compare it
            }
            fixedTown = fixedTown->Next; // go to next fixed "stable" town
        }
        tempDistrict = tempDistrict->Next; // go to next district to compar it's own towns
    }
    if (counter)
        radixSort(district); // used for the main and the request
    else
        print_List(district);
    return district;
}

void removeList(ptrDistrict district)
{
    if (district == NULL)
        return;

    ptrDistrict currentDistrict = district->Next; // Start from the first district
    while (currentDistrict != NULL)
    {
        ptrTown currentTown = currentDistrict->townHead;
        while (currentTown != NULL)
        {
            ptrTown tempTown = currentTown;
            currentTown = currentTown->Next;
            free(tempTown); // Free each town
        }
        ptrDistrict tempDistrict = currentDistrict;
        currentDistrict = currentDistrict->Next;
        free(tempDistrict); // Free each district
    }
    district->Next = NULL; // Set Next of the head node to NULL after deleting the list
}
