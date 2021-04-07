#include "math.h"
#include <stdint.h>
#include <stdlib.h>
#include "io.h"
/*******************************************************************
 
 Authors: Alejandro Calvillo (100384010), Lucia Moreno (100384100)

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


/********************************************************
 A function to initialize the tables

   * @param table struct where we store the two tables

                             Author: Alejandro Calvillo
 *********************************************************/
void generate_memory_table (Tables *table);


/*******************************************************************
 A simple boolean function just to know if I need to add a new
 aux_table entry.

   *@param table struct where we store the two tables
   *@param IP  IP of reference for bit 15

                              Author: Alejandro Calvillo
 ******************************************************************/
int entry_aux(Tables* table, uint32_t *IP);


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



/***********************************************************
 The goal of this function is to read from 
 the file all FIB entries

    @param table struct where we store the two tables
    @param chek_for_errors our error checker.
  
                                      Author: Alejandro Calvillo
 ***********************************************************/
void set_FIB(Tables *table, int check_for_errors);