#include "prog1.h"

int CreateProduct(Product* ManotToAdd,List2* Manot, FILE* in, FILE* out) /*function definition*/
{
	char name[50];
	Product* temp;
	int i, t=1, flag = 0;
	temp = (Product*)malloc(sizeof(Product)); /*Dynamic allocation*/
	if (temp == NULL) /*if Dynamic allocation failed*/
		Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/
	while ((fscanf(in, "%s", name)) != EOF) /*while loop until fscanf is equal to EOF*/
	{
		fscanf(in, "%d %d", &(temp->Quantity), &(temp->Price)); /*get the quantity and the price of the dish*/
		if ((temp->Price) > 0) /*if the price is positive*/
		{
			if ((temp->Quantity) > 0) /*if the quantity is positive*/
			{
				(temp->Name) = (char*)malloc((strlen(name) + 1) * sizeof(char)); /*Dynamic allocation*/
				if ((temp->Name) == NULL) /* if Dynamic allocation failed*/
				{
					free(temp); /*free Dynamic allocation*/
					Error_Msg("Error"); /*function call, to print Error message and finish the program*/
				}
				temp->QuantitySold = 0; /*QuantitySild will get the value of 0*/
				strcpy(temp->Name, name); /*temp->name will get the string value from name*/
				if ((Manot->head) == NULL) /*If the list is empty*/
				{
					temp->next = NULL;
					Manot->head = temp; 
					ManotToAdd = temp;
				}
				else /*If there are nodes within the list*/
				{
					for (i = 1; i < t; i++) /*for loop until i = t*/
					{
						if ((temp->Name) == (ManotToAdd->Name)) /*If there is a dish in that name*/
							flag = -1; /*flag = -1, to get out from the loop*/
						else
							ManotToAdd = ManotToAdd->next; /*advanced to the next dish*/
					}
					if (flag == 0)
					{
						temp->next = Manot->tail->next;
						Manot->tail->next = temp;
					}
					else /*If the dish is already on the list*/
						fprintf(out, "%s", "The dish is already on the list\n"); /*print - The dish is already on the list*/
				}
				Manot->tail = temp;
				t++;
			}
			else /*if the quantity is negative*/
				fprintf(out, "The quantity received of %s is negative\n", name); /*print - The quantity received is negative*/
		}
		else /*if the price is negative*/
			fprintf(out, "The price received of %s is negative\n", name); /*print - The price recevied is negative*/
		temp = (Product*)malloc(sizeof(Product)); /*Dynamic allocation*/
		if (temp == NULL) /*if Dynamic allocation failed*/
			Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/
		ManotToAdd = Manot->head;
	}
	ManotToAdd = Manot->head;
	free(temp); /*free Dynamic allocation*/
	return 1;
}

void AddItems(List2* Manot, char* ProductName, int Quantity, FILE* out) /*function definition*/
{
	int flag = -1;
	Product* temp = (Manot->head); /*temp will get the value from (Manot->head)*/
	while (temp != NULL && flag == -1) /*while loop until temp = NULL and flag = -1*/
	{
		if (strcmp((temp->Name), ProductName) == 0) /*If there is a dish in that name*/
		{
			if (Quantity > 0) /*if the quantity is positive*/
			{
				temp->Quantity = (temp->Quantity) + Quantity; /*Add the received inventory to the existing inventory in the kitchen*/
				flag = 0; /*flag = 0, to get out of the loop*/
			}
			else /*is the quantity received is negative*/
				fprintf(out, "The quantity received of %s is negative\n", ProductName); /*print - The quantity received is negative*/
		}
		else /*If the dish name does not match the name in the kitchen*/
			temp = temp->next; /*Advanced to the next dish*/
	}
	if (flag == -1) /*if we dont found that dish in the kitchen*/
		fprintf(out, "There is no product named %s\n", ProductName); /*print - There is no product named*/
	else /*if we found that dish in the kitchen*/
		fprintf(out, "%d %s were added to the kitchen\n", Quantity, ProductName); /*print - (The quantity and name) were added to the kitchen*/
}

void OrderItem(TableList tableList, List2* Manot, int TableNumber, char* ProductName, int Quantity, FILE* out) /*function definition*/
{
	Product* temp = Manot->head;
	Product* productForTable;
	int isFound = 0, WrongQuantity = 0;

	productForTable = (Product*)malloc(sizeof(Product)); /*Dynamic allocation*/
	if (productForTable == NULL) /*if Dynamic allocation failed*/
		Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/

	if ((TableNumber < tableList.Quantity) || (TableNumber > 0)) /*If the Table number received is positive, and less than the total quantity of tables*/
	{
		while (temp != NULL && !isFound && !WrongQuantity) /*while loop until temp=NULL, and isFound!=0, and WrongQuantity!=0*/
		{
			if (strcmp(ProductName, temp->Name) == 0) /*If there is a dish in that name*/
			{
				if ((Quantity > 0) && (Quantity <= temp->Quantity)) /*If the quantity received is positive, and less than the total quantity in the kitchen*/
				{
					temp->Quantity = (temp->Quantity) - Quantity; /*Remove the inventory received from existing inventory in the kitchen */
					temp->QuantitySold = (temp->QuantitySold) + Quantity; /* Add the received inventory to the existing inventory at the table*/

					productForTable->Name = ProductName; /*receive the name of the dish*/
					productForTable->Price = Quantity * (temp->Price); /*receive the price of the order*/
					productForTable->Quantity = Quantity; /*receive the quantity of the dish*/
					isFound = 1; /*IsFound = 1 to get out of the loop*/

					if (tableList.tables[TableNumber - 1].price == 0) /*If this is the first order of the table*/
					{
						tableList.tables[TableNumber - 1].tail = (Product*)malloc(sizeof(Product)); /*Dynamic allocation*/
						if (tableList.tables[TableNumber - 1].tail == NULL) /*if Dynamic allocation failed*/
						{
							free(productForTable); /*free Dynamic allocation*/
							Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/
						}
						productForTable->next = NULL;
					}
					else /*If the table has already ordered dishes*/
					{
						productForTable->next = tableList.tables[TableNumber - 1].tail;
					}
					tableList.tables[TableNumber - 1].price = tableList.tables[TableNumber - 1].price + productForTable->Price; /*Calculate the total amount of the table*/
					tableList.tables[TableNumber - 1].tail = productForTable;
				}
				else  /*is the quantity received is negative or bigger then the inventory in the kitchen*/
				{
					fprintf(out, "The quantity received of %s is negative\n", ProductName); /*print - The quantity recived is negative*/
					WrongQuantity = 1; /*WrongQuantity = 1 to get out of the loop*/
				}
			}
			else /*If the dish name does not match the name in the kitchen*/
				temp = temp->next;  /*Advanced to the next dish*/
		}
	}
	else /*if the table number is negative, or bigger then the total quantity of tables*/
		fprintf(out, "%s", "This table number does not exist\n"); /*print - This table number does not exist*/
	if (isFound == 0 && WrongQuantity == 0) /*if we dont fount that dish*/
	{
		fprintf(out, "We don't have %s, sorry!\n", ProductName); /*print - we dont have that dish, sorry!*/
	}
	else if (isFound == 1) /*if we found that dish*/
	{
		fprintf(out, "%d %s were added to the table number %d\n" , Quantity, ProductName, TableNumber); /*print - (The quantity and name) were added to the table number*/
	}
}

void RemoveItem(TableList tableList, List2* Manot, int TableNumber, char* ProductName, int Quantity, FILE* out) /*function definition*/
{
	Product* productToRemove = tableList.tables[TableNumber-1].tail; /*productToRemove will receive the specific table from which the dish should be returned*/
	Product* temp = Manot->head;
	int isFound = 0, WrongQuantity = 0, NotInvited = 0;

	if ((tableList.tables[TableNumber-1].price) != 0) /*Check if the table did order dishes*/
	{
		while ((productToRemove) != NULL && !isFound && !WrongQuantity) /*while loop until productToRemove=NULL, and isFond!=0, and WorngQuantity!=0*/
		{
			if (strcmp((productToRemove->Name), ProductName) == 0) /*If there is a dish in that name in the table*/
			{
				if ((Quantity > 0) && (Quantity <= productToRemove->Quantity)) /*If the quantity received is positive, and less than the total quantity in the table*/
				{
					while (temp != NULL && !isFound) /*while loop until temp=NULL, and isFound!=0*/
					{
						if ((strcmp((temp->Name), ProductName) == 0)) /*If there is a dish in that name in the kitchen*/
						{
							productToRemove->Quantity = (productToRemove->Quantity) - Quantity; /*Subtract the amount of dishes returned from the table*/
							productToRemove->Price = (productToRemove->Price) - (Quantity * temp->Price); /*Return the price of returned dishes*/
							tableList.tables[TableNumber-1].price = (tableList.tables[TableNumber-1].price) - (Quantity * temp->Price); /*Lower the price of returned dishes from the total amount of the table*/
							isFound = 1; /*isFound = 1 to get out of the loop*/
						}
						else /*If the dish name does not match the name in the kitchen*/
							temp = temp->next; /*Advanced to the next dish*/
					}
				}
				else /*is the quantity received is negative or bigger then the inventory in the table*/
				{
					fprintf(out, "The quantity received of %s is negative\n", ProductName); /*print - The quantity received is negative*/
					WrongQuantity = 1; /*WrongQuantity = 1 to get out of the loop*/
				}
			}
			else  /*If the dish name does not match the name in the table*/
				productToRemove = productToRemove->next; /*Advanced to the next dish*/
		}
	}
	else /*if the total price in the table is 0*/
	{
		fprintf(out, "The table number %d is not ordered yet\n", TableNumber); /*print - The table number %d is not ordered yet*/
		NotInvited = 1;
	}
	if (productToRemove == NULL && NotInvited == 0) /*if productToRemove=NULL and NotInvited=0*/
		fprintf(out, "The %s product was not invited to table number %d\n", ProductName,TableNumber); /*print - That product was not invited to that table*/
	else if (isFound == 1) /*if isFound=1*/
		fprintf(out, "%d %s was returend to the kitchen from table number %d\n", Quantity, ProductName, TableNumber); /*print - (The quantity and name) was returend to the kitchen from table number*/
}

void RemoveTable(TableList tableList,List2* Manot, int TableNumber, FILE* out) /*function definition*/
{
	Product* TableToRemove = tableList.tables[TableNumber - 1].tail; /*productToRemove will receive the specific table from which the dish should be removed*/
	Product* temp;
	temp = (Product*)malloc(sizeof(Product)); /*Dynamic allocation*/
	if (temp == NULL) /*if Dynamic allocation failed*/
		Error_Msg("Memmory!"); /*function call, to print Error message and finish the program*/
	int isFound = 0, t = 0, MaxSales = 0, i;
	char* MaxSalesName;
	if (TableToRemove != NULL) /*if TableToRemove!=NULL*/
	{
		fprintf(out, "Account for table number %d :\n", TableNumber); /*print - Account for table number _ :*/
		while (TableToRemove != NULL) /*while loop until TableToRemove = NULL*/
		{
			if (TableToRemove->next == NULL) /*if this is the last dish in the table*/
			{
				fprintf(out, "%d %s. %d nis\n", TableToRemove->Quantity, TableToRemove->Name, TableToRemove->Price); /*print the quantity and name of the dish, and the price*/
				fprintf(out, "Final payment %d nis, please!\n", tableList.tables[TableNumber - 1].price); /*print - Final payment, and the price to pay*/
			}
			else
				fprintf(out, "%d %s. %d nis, ", TableToRemove->Quantity, TableToRemove->Name, TableToRemove->Price); /*print the quantity and name of the dish, and the price*/
			TableToRemove = TableToRemove->next; /*Advanced to the next dish*/
		}
		while (tableList.tables[TableNumber - 1].tail != NULL) /*while loop*/
		{
			TableToRemove = tableList.tables[TableNumber - 1].tail; /*TableToRemove will receive the first dish at the table*/
			tableList.tables[TableNumber - 1].tail = tableList.tables[TableNumber - 1].tail->next; /*Advanced to the next dish*/
			free(TableToRemove); /*free Dynamic allocation*/
		}
	}
	else /*if that table is not ordered yet*/
		fprintf(out, "The table number %d is not ordered yet\n", TableNumber); /*print - That table number is not ordered yet*/

	for (i = 0; i < tableList.Quantity; i++) /*for loop until i = tableList.Quantity*/
		if (tableList.tables[i].tail != NULL) /*if is pointer to NULL*/
			t++; /*t = t + 1*/
	if (t == 0) /*if t = 0, its mean we dont have more tables in the restuant*/
	{
		while (Manot->head != NULL) /*while loop until Manot->head = NULL*/
		{
			if (Manot->head->QuantitySold > MaxSales) /*if the QuantitySold of that dish is bigger then MaxSales*/
			{
				temp = Manot->head; /*temp will be pointer of that dish*/
				MaxSales = temp->QuantitySold; /*MaxSales will get the value from temp->QuantitySold*/
			}
			Manot->head = Manot->head->next; /*Advanced to the next dish*/
		}
		fprintf(out, "The most popular dish today is %s! (was ordered %d times)\n", temp->Name, temp->QuantitySold); /*print The most popular dish today is (and the name), and how many times she was invited */
	}
	free(temp); /*free Dynamic allocation*/
}

void Error_Msg(char* msg) /*function definition*/
{
	printf("\n%s", msg); /*print Error message*/
	exit(1); /*finish the program*/
}