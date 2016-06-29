/* main.c is the program file that directs the processes. */
/* Author: L. Hamaker lahama9@uw.edu */
/* Created: 29 Feb 2016 */
/* Last edit: 08 Mar 2016 */

#include <stdio.h>
#include "Customer.h"

//Program start
int main(void){

	//Variables to capture file input
	char filename[30], last[20], first[15], item[20], price[10];
	int id, quantity;

	//Ask for the file name
	printf("Enter the name of the file containing purchases: ");
	scanf("%s", filename);

	//Open text file for reading
	FILE *infile = fopen(filename, "rb");
	
	//Create customer list
	cList list1 = create();

	//Scan the file and distribute data
	while((fscanf(infile, "%d %s %s %s %s %d", &id, last, first, item, price, &quantity)) == 6){
		add(list1, id, last, first, item, price, quantity); //add the entry to the list
	}

	//Prints to orders.txt
	printOrder(list1);
	
	//Prints to revenue.txt
	printRevenue(list1);

	//End Statement
	printf("Done. Check files orders.txt and revenue.txt\n");	

	//Close the file
	close(infile);	

	//Destroy
	destroy(list1);

	//End Program	
	return 0;	
}
