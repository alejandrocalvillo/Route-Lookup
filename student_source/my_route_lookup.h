 #include <stdint.h>
 #include <stdio.h>
 #include <math.h>
  

  
 void LookUp(int *numofacc, Tables* table, uint32_t *searchIP,  unsigned int *iOut);
  
 void CalculateTimes();

/********************************************************
 A function to initialize the tables

   * @param table struct where we store the two tables

                             Author: Alejandro Calvillo
 *********************************************************/
void generate_memory_table (Tables *table);


/*******************************************************************
 This function helps us to generate all memory needs for aux_table

    * @param table struct where we store the two tables
    * @param ip_extensions number of extensions we have made.

    Alejandro Calvillo
 ******************************************************************/
void generate_memory_aux(Tables *table, int ip_extensions);
