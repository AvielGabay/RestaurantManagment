#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _R
#define _R

typedef struct Product { /*struct declaration, Adding dishes to the kitchen*/
	char* Name;
	int Price;
	int Quantity;
	int QuantitySold;
	struct Product* next;
}Product;

typedef struct Table { /*Table struct declaration*/
	Product* tail;
	Product* head;
	int price;
	int NumberTable;
}Table;

typedef struct TableList { /*struct declaration, Tables manager*/
	Table* tables;
	int Quantity;
}TableList;


typedef struct List2 { /*struct declaration, Dishes manager*/
	Product* head;
	Product* tail;
}List2;

int CreateProduct(Product* ManotToAdd, List2* Manot, FILE* in, FILE *out);
/*function declaration
function name : CreateProduct
input : 1 pointer of Product, 1 pointer of List2, 2 pointers of FILE
output: A dish-making function in the kitchen, returns 1 when finished creating the dishes
algoritem: While loop, dynamic allocation to a product type variable, copying the dish name by dynamic allocation and using the strcpy function, 
	       inserting the dish into a linked list of dishes that are in the kitchen*/

void AddItems(List2* Manot, char* ProductName, int Quantity, FILE *out);
/*function declaration
function name : AddItems
input : 1 pointer of List2, 1 pointer of string, 1 intreger number, 1 pointer of FILE
output: Function for adding stock to a dish that exists in the kitchen
algoritem: while loop, Check if the product exists in the kitchen. If so, we will add the stock. 
		   If the quantity / price is negative, or if the dish name is not in the dishes in the kitchen, we will issue an error message.*/

void OrderItem(TableList tableList, List2* Manot, int TableNumber, char* ProductName, int Quantity, FILE *out); 
/*function declaration
function name : OrderItem
input : 1 pointer of TableList, 1 pointer of List2, 2 intreger number, 1 pointer of string, 1 pointer of FILE
output: Function for ordering dishes from the kitchen to the table
algoritem: Dynamic allocation to a product-type variable (to insert a specific dish into a specific table), 
		   while loop, while the loop is doing tests on the ordered dish. If the dish name actually exists in the kitchen, and the quantity is not greater than the amount in the kitchen, 
		   we will add the dish to the table in a linked list for all dishes ordered in this table, otherwise, we will issue an error message.*/

void RemoveItem(TableList tableList, List2* Manot, int TableNumber, char* ProductName, int Quantity, FILE* out); 
/*function declaration
function name : RemoveItem
input : 1 pointer of TableList, 1 pointer of List2, 2 intreger number, 1 pointer of string, 1 pointer of FILE
output: Dish return function. Removing an existing dish from the table
algoritem: while loop, while the loop is doing tests on the ordered dish. If the dish name actually exists in the table, and the quantity is not greater than the amount in the table, 
		   we will remove the dish from the table, otherwise, we will issue an error message.*/

void RemoveTable(TableList tableList,List2* Manot, int TableNumber, FILE* out); 
/*function declaration
function name : RemoveTable
input : 1 pointer of TableList, 1 pointer of List2, 1 intreger number, 1 pointer of FILE
output: Function for closing a Table account
algoritem: Dynamic allocation to a product-type variable (to save the best-selling dish), 
		   while loop, prints the summoned dishes to the table, and the total amount to pay for the table, and we release the table. 
		   If this is the last table in the restaurant, we'll put out a message with the best-selling dish.*/

void Error_Msg(char* msg);
/*function declaration
function name : Error_Msg
input : 1 pointer of string
output: issued an error message, and the program ended.
algoritem: issued an error message, and the program ended.*/

#endif // !_R