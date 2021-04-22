#include "my_library.h"

/*******************************************************************
 
 Authors: Alejandro Calvillo (100384010), Lucia Moreno (100384100)

 This is a library for all the functions to implement the FIB
 information into the corresponding tables and other stuff to make
 the first part of the proyect more easily.

 ******************************************************************/



/*******************************************************************
 This function helps us to generate all needed tables and variables
 of our Tables.
 ******************************************************************/

void generate_memory_table (Tables *table)
{

    table->table_24=calloc(pow(2,24), sizeof(short));
    table->ip_index=0;
    table->ip_extensions=0;

}
/*******************************************************************
 A simple boolean function just to know if I need to add a new
 aux_table entry.
 ******************************************************************/

int entry_aux(Tables* table, uint32_t *IP)
{
    if(table->table_24[(*IP>>8)]>>15 == 0) //Here we focus on the bit 15 because if it is 0 that means it doesnt have an entry on the aux table (UNIQUE USE IS AS A FLAG). 
    { //Nº15 is an extra bit of the interface which correspond to the Maximum Interface 2^(15)=32xxx.
        return 1; //Void
    }else
    {
        return 0;
    }
}
/*******************************************************************
  The goal of this adding the correspondig routes from what we read
  in our FIB file
 ******************************************************************/

void new_route(Tables* table, uint32_t *IP, int *prefix, int *oIf)
{
    int modified_ip=0;
    if (*prefix<=24) //If our Mask is less or equal to 24
    {

        modified_ip=pow(2,24-*prefix); //We calculate the number of positions we are going to have

        for(table->ip_index=0;(table->ip_index<modified_ip); table->ip_index++)
        {
            table->table_24[(*IP>>8) + table->ip_index]=*oIf; //And generate the table with the corresponding Output interface. Also, whe shift for the 24 more significant bits due to in the worst case we only need the 24 first bits
        }

    }else {

            modified_ip=pow(2,32-*prefix);
            if (entry_aux(table, IP))//If aux does not exist
            {
                table->aux_table=realloc(table->aux_table, 256*(table->ip_extensions+1)*sizeof(short));//This will be the variable size of our aux_table. 256 * Nº of extensions. 256 bc is the maximum 2⁸

                for (table->ip_index=0; table->ip_index < 256; table->ip_index++)
                {
                    table->aux_table[table->ip_extensions*256+table->ip_index]=table->table_24[(*IP>>8)];
                }

                for(table->ip_index=(*IP&0x000000FF);table->ip_index<modified_ip+(*IP&0x000000FF); table->ip_index++)
                {
                   table->aux_table[table->ip_extensions*256+table->ip_index]=*oIf; 
                }

                table->table_24[(*IP>>8)]= table->ip_extensions | 0b1000000000000000;
                // Im setting bit 15 to be my flag to check if there is an aux entry or not using bitwise. This concept is from "https://www.tutorialspoint.com/cprogramming/c_bitwise_operators.htm"
                table->ip_extensions++;

            }else
            {//If exist
                int aux=table->table_24[*IP>>8 & 0x00007FFF]; //Base value of the aux_table with respect of Table_24
                for(table->ip_index=(*IP&0x000000FF);table->ip_index<modified_ip+(*IP&0x000000FF); table->ip_index++)
                {
                    table->aux_table[aux*256+table->ip_index]=*oIf;//We take the position from the table_24 + the initial position
                }
            }
    }
}

/***************************************
 The goal of this function is to read from
 the file all FIB entries
 **************************************/

void set_FIB(Tables *table, int check_for_errors){

    int *prefix=calloc(1,sizeof(int));
    int *oIf=calloc(1, sizeof(int));
    uint32_t *IP=calloc(1, sizeof(uint32_t));

    while (check_for_errors == 0)
    {
        check_for_errors=readFIBLine(IP,prefix,oIf);

        if (check_for_errors == 0)
        {
            new_route(table,IP,prefix,oIf);
        }
    }
    free(prefix);
    free(IP);
    free(oIf);
}
