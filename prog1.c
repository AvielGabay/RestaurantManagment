#include "prog1.h"

void main()
{
	FILE* in, *in2, *out;
	TableList tableList;
	List2 Manot;
	Product* ManotToAdd;
	int temp, temp2, quantity, TableNumber, numTables=0, i;
	char TempName[50], *ProductName;

	ManotToAdd = (Product*)malloc(sizeof(Product)); /*Dynamic allocation*/
	if (ManotToAdd == NULL) /*if Dynamic allocation failed*/
		Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/

	Manot.head = NULL;
	Manot.tail = NULL;

	if ((in = fopen("Instructions.txt", "rt")) == NULL) /*in will get value from the file "Instructions.txt". in open the file to read*/
	{
		free(ManotToAdd); /*free Dynamic allocation*/
		Error_Msg("The file did not open"); /*function call, to print Error message and finish the program*/
	}
	
	fscanf(in, "%d", &numTables); /*numTables will get the value form the first digit from the file*/

	tableList.tables = (Table*)malloc(sizeof(Table) * numTables); /*Dynamic allocation*/
	if (tableList.tables == NULL) /*if Dynamic allocation failed*/
	{
		free(ManotToAdd); /*free Dynamic allocation*/
		Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/
	}

	tableList.Quantity = numTables;

	if ((in2 = fopen("Manot.txt", "rt")) == NULL) /*in2 will get value from the file "Manot.txt". in open the file to read*/
	{
		free(ManotToAdd);  /*free Dynamic allocation*/
		free(tableList.tables); /*free Dynamic allocation*/
		Error_Msg("The file did not open"); /*function call, to print Error message and finish the program*/
	}
	if ((out = fopen("output.txt", "w")) == NULL) /*out will get value from the file "output.txt". in open the file to write*/
	{
		free(ManotToAdd);  /*free Dynamic allocation*/
		free(tableList.tables);  /*free Dynamic allocation*/
		Error_Msg("The file did not open"); /*function call, to print Error message and finish the program*/
	}

	for (i = 0; i < tableList.Quantity; i++) /*for loop until i = tableList.Quantity, Initialize the linked list*/
	{
		tableList.tables[i].tail = NULL;
		tableList.tables[i].price = 0;
		tableList.tables[i].NumberTable = i + 1;
	}

	while ((fscanf(in, "%d", &temp)) != EOF) /*while loop until fscanf is equal to EOF, temp will get the value from the digit in the file*/
	{
		if (temp == 1)  /*if temp = 1*/
		{
			temp2 = CreateProduct(ManotToAdd, &Manot, in2, out); /*temp2 will get the value from function call 'CreateProduct'*/
			if (temp2 != 0) /*if temp2!=0*/
				fprintf(out, "%s", "The kitchen was created\n"); /*print- The kitchen was created */
			else
				fprintf(out, "%s", "The kitchen was not created\n"); /*print - The kitchen was not created*/
		}
		else if (temp == 2) /*if temp = 2*/
		{
			fscanf(in, "%s %d", TempName, &quantity); /*received 2 values into TempName and quantity*/
			ProductName = (char*)malloc((strlen(TempName) + 1) * sizeof(char)); /*Dynamic allocation*/
			if (ProductName == NULL) /*if Dynamic allocation failed*/
			{
				free(ManotToAdd); /*free Dynamic allocation*/
				free(tableList.tables); /*free Dynamic allocation*/
				Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/
			}
			strcpy(ProductName, TempName); /*function call, ProductName will get the value from TempName*/
			AddItems(&Manot, ProductName, quantity, out); /*function call to add inventory into the dish in the kitchen*/
		}
		else if (temp == 3) /*if temp = 3*/
		{
			fscanf(in, "%d %s %d", &TableNumber, TempName, &quantity); /*received 3 values into TableNumber, TempName, quantity*/
			ProductName = (char*)malloc((strlen(TempName) + 1) * sizeof(char));  /*Dynamic allocation*/
			if (ProductName == NULL) /*if Dynamic allocation failed*/
			{
				free(ManotToAdd); /*free Dynamic allocation*/ 
				free(tableList.tables); /*free Dynamic allocation*/
				Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/
			}
			strcpy(ProductName, TempName); /*function call, ProductName will get the value from TempName*/
			OrderItem(tableList, &Manot, TableNumber, ProductName, quantity, out); /*function call, to order item into table*/
		}
		else if (temp == 4) /*if temp = 4*/
		{
			fscanf(in, "%d %s %d", &TableNumber, TempName, &quantity); /*received 3 values into TableNumber, TempName, quantity*/
			ProductName = (char*)malloc((strlen(TempName) + 1) * sizeof(char));  /*Dynamic allocation*/
			if (ProductName == NULL)  /*if Dynamic allocation failed*/
			{
				free(ManotToAdd);  /*free Dynamic allocation*/ 
				free(tableList.tables);  /*free Dynamic allocation*/
				Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/
			}
			strcpy(ProductName, TempName); /*function call, ProductName will get the value from TempName*/
			RemoveItem(tableList, &Manot, TableNumber, ProductName, quantity, out); /*function call, to remove item from the table*/
		}
		else if (temp == 5) /*if temp = 5*/
		{
			fscanf(in, "%d", &TableNumber); /*received 1 value into TableNumber*/
			RemoveTable(tableList, &Manot, TableNumber, out);/*function call to remove table*/
		}
	}
	free(ManotToAdd); /*free Dynamic allocation*/ 
	free(tableList.tables); /*free Dynamic allocation*/ 
	fclose(in); /*fclose have to come after fopen*/
	fclose(in2); /*fclose have to come after fopen*/
	fclose(out); /*fclose have to come after fopen*/
	return 0;
}