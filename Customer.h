/* Customer.h is a file that lists the functions available to the client. */
/* Author: L. Hamaker lahama9@uw.edu */
/* Created: 29 Feb 2016 */
/* Last edit: 05 Mar 2016 */

#ifndef Customer_H
#define Customer_H
#include <stdio.h>

//Typedef definitions
typedef struct customer_list *cList;
typedef struct customer_struct *Customer;

//Function prototypes found in Customer
cList create();
void add(cList ptr, int i, char* last, char* first, char* item, char* price, int quantity);
int checkList(cList ptr, int i);
void printOrder(cList ptr);
void printRevenue(cList pt);
void sortArray(cList p);
void destroy(cList ptr);

#endif
