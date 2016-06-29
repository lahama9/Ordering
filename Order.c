/* Order.c is the file that defines an order list and order struct */
/* Author: L. Hamaker lahama9@uw.edu */
/* Created: 29 Feb 2016 */
/* Last edit: 08 Mar 2016 */

#include "Order.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Order Struct
struct order_struct{
	char item[20];	
	char price[20];
	int quantity;
	float order_total;
};

//Order List
struct order_list{
	int size;	
	int capacity;	//Tracks the number of order structs in the list.
	float grand_total;
	Order list;		//Points to the first order struct in the list. 
};

oList createOrder(){
	oList oListPtr = malloc(sizeof(struct order_list)); //FREE
	oListPtr->size = 0;
	oListPtr->capacity = 10;
	oListPtr->list = malloc(sizeof(struct order_struct)*10);//FREE
}

void addOrder(oList optr, char* item, char* price, int q){//importing correctly.
	int i;
	float total;
	
	//No room to add. Need to reallocate
	if(optr->size >= optr->capacity){	
		Order otemp = malloc(sizeof(struct order_struct) * (optr->capacity + 10)); //NEEDS TO BE FREE
		
		//Copy list and add new customer
		if(otemp != NULL){
			
		//Increase the capacity by 200
			optr->capacity += 20;
			memcpy(otemp, optr->list, sizeof(struct order_struct) * (optr->size));
			free(optr->list); //Free to reset to the new pointer, temp
			optr->list = otemp;

			//Add the new order to the array
			strcpy(optr->list[optr->size].item, item);
			strcpy(optr->list[optr->size].price, price);
			optr->list[optr->size].quantity = q;
			free(otemp);
		}

	}else{
		//Add the new order to the array
		strcpy(optr->list[optr->size].item, item);
		strcpy(optr->list[optr->size].price, price);
		optr->list[optr->size].quantity = q;
	}
	
	total = convertPrice(price) * q;
	optr->list[optr->size].order_total = total;
	optr->grand_total += total;
	optr->size++;
}

//Function that calculates the value of a price string
int itemValue(char* price){
	int result;
	return 0;
}

void printOrders(FILE* outfile, oList o){
	int i;
	for(i = 0; i < o->size; i++){
		fprintf(outfile, "%s %s %d\n", o->list[i].item, o->list[i].price, o->list[i].quantity);
	}
}

void printRev(FILE* outfile, oList o){
	int j;
	for(j = 0; j < o->size; j++){
		fprintf(outfile, "%s %s %d = %.2f\n", o->list[j].item, o->list[j].price, o->list[j].quantity, o->list[j].order_total);
	}
}

float convertPrice(char* price){
	float result = 0.00;
	char p[20];

	memcpy(p, &price[1], 19);
	result = atof(p);
	return result;
}

float getTotal(oList o){
	return o->grand_total;
}

void destroyList(oList o) {
	int j;	
  	free(o->list);
	free(o);
 	o = NULL;
}

