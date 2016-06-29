/* Order.h is a file that lists the functions available to the client for the Order class. */
/* Author: L. Hamaker lahama9@uw.edu */
/* Created: 29 Feb 2016 */
/* Last edit: 05 Mar 2016 */

#ifndef Order_H
#define Order_H
#include <stdio.h>

//Typedef definitions
typedef struct order_list *oList;
typedef struct order_struct *Order;

//Function prototypes found in Order
oList createOrder();
void addOrder(oList optr, char* item, char* price, int q);
void printOrders(FILE* out, oList o);
int itemValue(char* price);
int itemExists(oList op, char* item);
float convertPrice(char* price);
float getTotal(oList o);

#endif
