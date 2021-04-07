 #include <stdint.h>
 #include <stdio.h>
 #include <math.h>
 #include "my_library.h" 

/**************************************************************************************************
  Route Lookup with Binary Search.

    First of all, the program generates the memory of the tables and initialize
    the output variables (). If there is no erros, the tables are filled with the 
    input arguments. Then the program will use a binary search to find the output
    interface for the incommings arguments IPs. Finally, it writes the desired 
    parameters of each test in it's output file. It will also print on screen this
    file.

    To start the program, please use ./my_route_lookup FIB InputPacketFile

    You can take the example files from /Linear Search/

    This project has been develop by Lucia Moreno(100384100) and Alejandro Calvillo(100384010)
 **********************************************************************************************/
int main(int argc, char *argv[]);


/**********************************************************************************
  This method frees the memory of the tables we are using

    * @param table struct where we store the two tables

                                                        Author: Lucia Moreno
**********************************************************************************/
void FreeTables(Tables *table);

/**********************************************************************************************
  This method checks if the IP we are seatching has been previously
 inserted and gives us the numbers of accesses necessary

    * @param numofacc Number of access to the tables needed to find the IP we are looking for
    * @param table struct where we store the two tables
    * @param searchIP IP we are looking for
    * @param iOut Output interface
    
                                                                     Author: Lucia Moreno
 ******************************************************************************************/
 void LookUp(int *numofacc, Tables* table, uint32_t *searchIP,  unsigned int *iOut);
  

/***************************************************************************
 This method calculates the times and prints the info

                                                    Author: Lucia Moreno
 ***************************************************************************/
 void CalculateTimes();