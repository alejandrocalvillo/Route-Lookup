#include "math.h"
#include <stdint.h>
#include <stdlib.h>
#include "io.h"
/*******************************************************************
 
 Author: Alejandro Calvillo (100384010)

 This is a library for all the functions to implement the FIB
 information into the corresponding tables and other stuff to make
 the first part of the proyect more easily.

 ******************************************************************/
typedef struct
{
    short *table_24; //Table with size of 2^24
    short *aux_table; // Table with variable size
    long ip_index;  //I think this index could be simplified?
    int ip_extensions; // number of extensions that has been made.
}Tables;







/******************************************************
  The goal of this adding the correspondig routes from
 what we read in our FIB file as follows:

    -If our mask is lesser or equals to 24, we will store in the IP
    position the output interface in the table named "my_table".

    -if our mask is greater or equals to 25, we will need to use the
    second table "aux_table":

            *If there is no existing entry 

            *If there is an entry

    

    @param table struct where we store the two tables
    @param IP IP to insert
    @param prefix The network mask prefix
    @param oIf Output interface.

                                       Author: Alejandro Calvillo.
*****************************************************************/
void new_route(Tables* table, uint32_t *IP, int *prefix, int *oIf);



/***************************************
 The goal of this function is to read from 
 the file all FIB entries

    @param table struct where we store the two tables
    @param chek_for_errors our error checker.ç
    
 **************************************/
void set_FIB(Tables *table, int check_for_errors);