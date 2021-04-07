#include "my_route_lookup.h"

/********************************************************************************************
  Route Lookup with Binary Search.

    To start the program, please use ./my_route_lookup FIB InputPacketFile

    You can take the example files from /Linear Search/

    This project has been develop by Lucia Moreno(100384100) and Alejandro Calvillo(100384010)
  
 *******************************************************************************************/

Tables my_own_tables;
int *packets_processed;
double *access_to_table;
double *proccessing_time;
int check_for_errors;
struct timespec initialtime, finaltime;

/*******************************************************************
 
    This method frees the tables we are using

******************************************************************/

void FreeTables(Tables *table) {
        free(table->aux_table);
        free(table->table_24);
}

int main(int argc, char *argv[]){
    generate_memory_table(&my_own_tables);
    packets_processed  = calloc(1,sizeof(int));
    access_to_table = calloc(1,sizeof(double));
    proccessing_time  = calloc(1,sizeof(double));
    check_for_errors = 0;

    if (argc == 3){
        check_for_errors=initializeIO(argv[1], argv[2]);

        if (check_for_errors!=0){
			printIOExplanationError(check_for_errors);
			return -1;
    }   

		set_FIB(&my_own_tables, check_for_errors);
		CalculateTimes();
        printSummary(*packets_processed, (*access_to_table / *packets_processed), (*proccessing_time / *packets_processed));
		freeIO();
		free(packets_processed);
		free(access_to_table);
		free(proccessing_time);
        FreeTables(&my_own_tables);
    }else{

      printf("The inputs file should be 2\n");
      return -1;

    }
    return 0;
}


 /*******************************************************************
 This method checks if the IP we are seatching has been previously
 inserted and gives us the numbers of accesses necessary
 ******************************************************************/

 void LookUp(int *numofacc, Tables* table, uint32_t *searchIP,  unsigned int *iOut){
	 *iOut = table->table_24[*searchIP>>8];
	 int auxTable = *iOut>>15;
     if(auxTable == 0){  //we check the IP value we are searching to know if it's auxiliar table exists
         *numofacc = 1;  //if it does we only have to do one acces
         return;
     }else{
         *numofacc = 2; //if it doesn't exist we would need two accesses
         *iOut = table->aux_table[(*iOut & 0x7FFF)*256 + (*searchIP & 0x000000FF)];
         return;
     }
     return;
 }

/*******************************************************************
 This method calculates the times and prints the info
 ******************************************************************/

  void CalculateTimes(){
     uint32_t *searchIP = calloc(1,sizeof(uint32_t));
     unsigned int *interface = calloc(1,sizeof(unsigned int));
     double *s_time = calloc(1,sizeof(double));
     int *numofacc = calloc(1,sizeof(int));
     check_for_errors = 0;//as we use this variable also in readIps we need to reset its value
     while(check_for_errors == 0){
         check_for_errors = readInputPacketFileLine(searchIP);
         if(check_for_errors == 0){
             clock_gettime(CLOCK_MONOTONIC_RAW, &initialtime); //first clock check as indicated by the io.h file we were provided with
             LookUp(numofacc, &my_own_tables, searchIP,  interface); //we call the LookUp function
             clock_gettime(CLOCK_MONOTONIC_RAW, &finaltime); //we call the clock check again as indicated by the io.h file
             printOutputLine(*searchIP, *interface, &initialtime, &finaltime, s_time, *numofacc);  //we print as indicated in io.h
			 //we update the variables:
             *packets_processed = *packets_processed + 1;
             *access_to_table  = *access_to_table + *numofacc;
             *proccessing_time  = *proccessing_time + *s_time;
         }
     }
	 //we free the variables
	 free(interface);
     free(s_time);
     free(searchIP);
     free(numofacc);
 }
