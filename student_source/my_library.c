#include "my_library.h"
#include "my_route_lookup.h"

/*******************************************************************
 A simple boolean function just to know if I need to add a new 
 aux_table entry.
 ******************************************************************/

int entry_aux(Tables* table, uint32_t *IP)
{
    if(table->table_24[(*IP>>8)]>>15 == 0) //Here we focus on the bit 15 because if it is 0 that means it doesnt have an entry on the aux table.
    {
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

        modified_ip=pow(2,24 - *prefix); //We calculate the number of positions we are going to have

        for(table->ip_index=0;(table->ip_index<modified_ip); table->ip_index++)
        {
            
            table->table_24[(*IP>>8) + table->ip_index]=*oIf; //And generate the table with the corresponding Output interface. Also, whe shift for the 24 more significant bits due to in the worst case we only need the 24 first bits
        }

    }else {

            modified_ip=pow(2,32 - *prefix);
            int exist =entry_aux(table, IP);
            if (exist == 1)//This means aux_table does not exist
            {
                void generate_memory_aux(Tables *table, int ip_extensions);//This will be the variable size of our aux_table. 256 * Nº of extensions.
                //lo mismo con * 2 sale
                for (table->ip_index=0; table->ip_index < 255; table->ip_index++)
                {   
                    table->aux_table[table->ip_extensions*256+table->ip_index]=table->table_24[(*IP>>8)];
                }

                for(table->ip_index=(*IP&0xFF);table->ip_index<modified_ip+(*IP & 0xFF); table->ip_index++) //I have changed the interfaces of the range of IP so it will start at (*IP&0xFF) using Bitwise
                {
                   table->aux_table[table->ip_extensions*256+table->ip_index]=*oIf; 
                }

                table->table_24[(*IP>>8)]= table->ip_extensions | 0b1000000000000000; 
                // Im setting bit 15 to be my flag to check if there is an aux entry or not using bitwise. This concept is from "https://www.tutorialspoint.com/cprogramming/c_bitwise_operators.htm"
                table->ip_extensions++;

            }else
            {//If exist
                for(table->ip_index=(*IP&0xFF);table->ip_index<modified_ip+(*IP&0xFF); table->ip_index++)
                {
                   table->aux_table[(table->table_24[*IP>>8])*256+table->ip_index]=*oIf; /*0x7FFF*/
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

