/* Customer.c is the file that defines an customer list and order struct */
/* Author: L. Hamaker lahama9@uw.edu */
/* Created: 29 Feb 2016 */
/* Last edit: 08 Mar 2016 */

#include "Customer.h"
#include "Order.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Customer Struct
struct customer_struct{
	int id;				//Variable for the customer id.
	char last_name[20];	//Char pointer for the last name.
	char first_name[15];	//Char pointer for the first name.
	oList orders;		//Points to the Order list for this customer.
};

//Customer List Struct
struct customer_list{
	int size;		//Tracks the number of customer structs in the list.
	int capacity;
	Customer list;	//Points to the first struct in the list. Array List.
};

//Creates a Customer List
cList create(){
	cList cListPtr = malloc(sizeof(cList)); //FREE
	if(cListPtr != NULL){ //If pointer points to memory
		cListPtr->size=0;
		cListPtr->capacity = 10;
		cListPtr->list = malloc(sizeof(struct customer_struct)*10);//FREE
	} 
}

//Adds a customer to the list.
void add(cList ptr, int i, char* last, char* first, char* item, char* price, int quantity){
	int eID;
	eID = checkList(ptr, i);//Working

	if(eID >= 0){//Working
		addOrder(ptr->list[eID].orders, item, price, quantity); 
	}else{
		//The id does not exist int the list and needs to be added
		if(ptr->size >= ptr->capacity){
			
			//Create a temperary pointer 
			Customer temp = malloc(sizeof(struct customer_struct) * (ptr->capacity + 50)); //NEEDS TO BE FREE
			
			//Copy list and add new customer
			if(temp != NULL){

				//Increase the capacity by 200
				ptr->capacity += 50; //WORKS
				memcpy(temp, ptr->list, sizeof(struct customer_struct) * (ptr->size));
				free(ptr->list); 
				ptr->list = temp;

				//Create the order list			
				ptr->list[ptr->size].orders = createOrder();

				//Add the new customer to the array
				ptr->list[ptr->size].id = i;
				strcpy(ptr->list[ptr->size].last_name, last);
				strcpy(ptr->list[ptr->size].first_name, first);

				//Need to add the new items to the order array.
				addOrder(ptr->list[ptr->size].orders, item, price, quantity);
				
				//Increase the size.
				ptr->size++;
				free(temp);
			}
		}else{
			//Add the new customer to the array list
			ptr->list[ptr->size].id = i;
			strcpy(ptr->list[ptr->size].last_name, last);
			strcpy(ptr->list[ptr->size].first_name, first);

			//Add the new order to the customer's order array
			ptr->list[ptr->size].orders = createOrder();
			addOrder(ptr->list[ptr->size].orders, item, price, quantity);

			//Need to add the new items to the order array.
			ptr->size++;
		}
	}
}

//Checks the Customer list for an existing customer by using the id.
int checkList(cList ptr, int i){
	int result = -1, count = 0;

	//Checks the whole list, if needed.
	while(count < ptr->size){
		if(ptr->list[count].id == i){
			result = count;
			break;
		}
		count++;
	}
	return result;
}

//Prints to order.txt
void printOrder(cList pt){
	int i,j;

	//Opens the file. 
	FILE *outfile = fopen("order.txt", "wb");

	//Iterates through the whole list and prints to the file.
	for(i = 0; i < pt->size; i++){
		fprintf(outfile, "%d %s %s\n", pt->list[i].id, pt->list[i].last_name, pt->list[i].first_name);
		
		//Calls the function in Order.c to print contents of order array.
		printOrders(outfile, pt->list[i].orders);

		//Extra return to meet the output requirement
		fprintf(outfile, "\n");
	}
	fclose(outfile);
}


void printRevenue(cList pt){
	int m,n;
	float total;
	
	//Need to sort the list (Highest to Lowest totals)
	sortArray(pt);

	
	//Opens the file. 
	FILE *outfile = fopen("revenue.txt", "wb");

	//Iterates through the whole list and prints to the file.
	for(m = 0; m < pt->size; m++){
		total =  getTotal(pt->list[m].orders);
		
		fprintf(outfile, "%d Total order: %.2f\n", pt->list[m].id, total);
		
		
		//Calls the function in Order.c to print contents of order array.
		printRev(outfile, pt->list[m].orders);

		//Extra return to meet the output requirement
		fprintf(outfile, "\n");
	}
	fclose(outfile);
}

//Function sorts the array in descending order (grand total)
void sortArray(cList p){
	struct customer_struct c;
	int s,t;

	for(s = 0; s < p->size; s++){
		for(t = 0; t < p->size; t++){
			if(getTotal(p->list[s].orders) >= getTotal(p->list[t].orders)){
					c = p->list[s];
					p->list[s] = p->list[t];
					p->list[t] = c;	
			}
		}
	}
}  

void destroy(cList ptr) {
	int i;
	//free the order list
	for(i = 0; i < ptr->size; i++){
		destroyList(ptr->list[i].orders);
	}

	//free the customer list	
  	free(ptr->list);
  	free(ptr);
  	ptr = NULL;
}
