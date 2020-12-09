/* 
	This program simulates an interaction between a customer and an employee
	of a cafe/bookstore. The customer chooses which portion of the store
	they would like to visit. A list of available items is printed for the
	customer to choose from. Once the customer has made their choice, 
	they have the option of visiting the other portion or check out. At 
	checkout, the customer is given the total cost and asked to input 
	their payment amount. Once the payment is input, the program determines
	if the amount is adequate, returns change if necessary, and produces
	a receipt along with a log of the transaction.
*/

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<iomanip>

using namespace std;

//This function is simply to create a file containing transaction information.
void makeFile(string, double, int, double, double, 
	string, double, double, double, double);

// This function intakes all the transaction information and output a receipt.
void printReceipt(string, double, int, double, double, string, double,
	double, double, double, double, double);

//Class containing all of the variables and functions relating to books.
class Books{
	public:
	int select, selection, num, bookSelect;
	double cost;
	char response20;
	string item, bookName;
	fstream onfile;
	
	// Variables for holding onto strings from menu.
	struct bookInfo{
		string bookNum;
		string title;
		string author;
		string genre;
		string cover;
		string price;
	};

	bool validInput(int bookSelect);
	double bookPrices(int bookSelect);
	int bookStore();
	string bookNames(int bookSelect);
	void printBooks();
};

// Contains all the variables and functions relating to the cafe.
class Coffee{
	public:
	int selection, num, choice;
	double price;
	string itemNames, item;
	char response20;
	ifstream infile;
	
	//Variables for holding item info from menu file.
	struct menuItem {
		string itemNum;
		string name;
		string description;
		string price;
		string has_shots;
	};
	
	bool validOrder(int);
	double prices(int);
	int cafe();
	int numOfShot();
	char altMilk();
	string itemName(int);
	void printMenu();
};


int main(){

	Books book;
	Coffee caf;
	double shotsCost, total, total2 = 0, price, bookPrice, 
	totalPrice, payment, change, grace, totalTax, milkAlt;
	int numOfShots, selection = 0, bookSelect;
	double preTaxtotal = 0;
	string bookName, itemLabel, choice, line;
	const double tax = 0.08, milkCost = 0.25, shotsExtra = 0.50;
	char response, response3, response4;
	fstream custFile;
	
	// Gives the user the option to start either in the cafe or the bookstore.
	cout << "Cafe or Bookstore? " << endl;
	cin >> choice;

	// An attempt to implement some resilience.
	if(choice == "Cafe" || choice == "cafe" || choice == "Caf" || choice == "caf"){
		// This function gets the customers order.
		selection = caf.cafe();
		// This function determines the price of selected item.
		price = caf.prices(selection);
		// This function determines the item name and puts it in the variable itemLabel.
		itemLabel = caf.itemName(selection);

		cout << "Would you like to modify your order?(Y/N): " << endl;
		cin >> response;

		// More attempted resilience.
		if(response == 'Y' || response == 'y'){

			// Ask user how many shots they want.
			numOfShots = caf.numOfShot();

			// Ask if the user wants a milk alternative.
			milkAlt = caf.altMilk();
		}

		cout << "Would you like to go to the bookstore? (Y/N)" << endl;
		cin >> response4;

		if(response4 == 'Y' || response4 =='y'){

			// This function prints the menu and retrieves the users selection.
			bookSelect = book.bookStore();

			// Using the users input, the next two function determine the price and name
			// of the books and plugs them into the bookPrice and bookName variables.
			bookPrice = book.bookPrices(bookSelect);
			bookName = book.bookNames(bookSelect);
		}

	}

	// If the user chooses bookstore, the program will begin here.
	else if(choice == "Bookstore" || choice == "bookstore" || choice == "book" || choice == "Book"){
		
		// These functions take the user through the bookstore portion of the simulation.
		bookSelect = book.bookStore();
		bookPrice = book.bookPrices(bookSelect);
		bookName = book.bookNames(bookSelect);

		// Giving the user the option to visit the cafe.
		cout << "Would you like to go to the Cafe? (Y/N) " << endl;
		cin >> response3;

		if(response3 == 'Y' || response3 =='y'){

			// Cafe portion of the simulation.
			selection = caf.cafe();
			price = caf.prices(selection);
			itemLabel = caf.itemName(selection);
		
			cout << "Would you like to modify your order?(Y/N): " << endl;
			cin >> response;

			 
			// If the user wants to alter their drink, the program takes them through
			// these functions.
			
			if(response == 'Y' || response == 'y'){

				// Asks how many extra shots user would like.
				numOfShots = caf.numOfShot();

				// Asks if user wants a milk alternative (Soy, Almond, etc).
				milkAlt = caf.altMilk();

				// If milk alternative is desirable, the cost is added to the total.
				if(milkAlt == 'Y' || milkAlt =='y'){
					total2 = milkCost;
				}
			}

			
		}

	};

	// Smattering of calculations that produce total and subtotal.
	shotsCost = numOfShots * shotsExtra;
	total = bookPrice + price + shotsCost + total2;
	preTaxtotal = total;
	totalTax = preTaxtotal * tax;
	totalPrice = preTaxtotal + totalTax;

	// Envoking "fixed" notation to avoid scientific output.
	cout << std::fixed;

	// Limiting output to two decimal places.
	cout << setprecision(2) << "Your total is: " << totalPrice << endl << endl;
	cout << "Please enter your payment amount: " << endl;
	cin >> payment;
	cout << endl;

	// Grace is just extending kindness to those who are just short of the full payment.
	grace = totalPrice - 0.50;

		// If customer pays more than due amount this statement executes.
		if(payment > totalPrice){
			
			// Create a file with all the transaction information.
			makeFile(itemLabel, price, numOfShots, shotsCost, milkCost, 
			bookName, bookPrice, totalPrice, payment, change);

			// Calculating the change if customer play more than amount due.
			change = (payment - totalPrice);
			cout << "Here's your change:   $" << change << endl << endl;

			// Takes all of the transaction information and puts it in a reciept.
			printReceipt(itemLabel, price, numOfShots, shotsCost, milkCost, bookName, 
					bookPrice, totalPrice, payment, change, preTaxtotal, totalTax);
		};


		// If customer pays the exact amount this statement executes.
		if(payment == totalPrice){

			change = 0;

			makeFile(itemLabel, price, numOfShots, shotsCost, milkCost, bookName, 
					bookPrice, totalPrice, payment, change);

			cout << endl;
			cout << "Thank you for your business! " << endl << endl;
			
		printReceipt(itemLabel, price, numOfShots, shotsCost, milkCost, bookName, 
					bookPrice, totalPrice, payment, change, preTaxtotal, totalTax);
		};

		// If the customer is short $0.50 or less this statement executes.
		if(payment >= grace && payment < totalPrice){

			change = 0;

			makeFile(itemLabel, price, numOfShots, shotsCost, milkCost, bookName, 
					bookPrice, totalPrice, payment, change);
			
			cout << endl;
			cout << "No worries, I've got you this time." << endl << endl;
			
			printReceipt(itemLabel, price, numOfShots, shotsCost, milkCost, bookName, 
					bookPrice, totalPrice, payment, change, preTaxtotal, totalTax);
		};
		
		// If the customer is more than $0.50 short this statement executes.
		if(payment < grace){
			cout << "Sorry, maybe next time. " << endl;
		};
		
		
	return 0;
};

void printReceipt(string itemLabel, double price, int numOfShots, double shotsCost, double milkCost, 
			      string bookName, double bookPrice, double totalPrice, double payment, double change,
				  double preTaxtotal, double totalTax){

			cout << "##############################" << endl;
			cout << "###### Printing Receipt ######" << endl;
			cout << "##############################" << endl << endl;
			cout << itemLabel << ": $" << price << endl;
			cout << "------------------------------" << endl;
			cout << "Extra shots:" << " +" << numOfShots << " = $" << shotsCost << endl;
			cout << "------------------------------" << endl;
			cout << "Milk Alternative: " << "+" << milkCost << endl;
			cout << "------------------------------" << endl;
			cout << bookName << " = $" << bookPrice << endl;
			cout << "------------------------------" << endl;
			cout << "Pre-tax total: $" << preTaxtotal << endl;
			cout << "------------------------------" << endl;
			cout << "Added tax: $" << totalTax << endl;
			cout << "------------------------------" << endl;
			cout << "Total cost: $" << totalPrice << endl;
			cout << "------------------------------" << endl;
			cout << "Payment: $" << payment << endl;
			cout << "------------------------------" << endl;
			cout << "Change: $" << change << endl;
			cout << "------------------------------" << endl;
			cout << "WiFi password: C0fFe3" << endl;
			cout << "------------------------------" << endl << endl;
			cout << "##############################" << endl;
				
};

void makeFile(string itemLabel, double price, int numOfShots, double shotsCost, double milkCost, 
			  string bookName, double bookPrice, double totalPrice, double payment, double change)
{


	fstream custFile;

	custFile.open("Customer.txt", ios::out);
	
	// Inputting transaction information into created customer file. Numerical values
	// are right justified.
	custFile << "    Customer order history:    " << endl;
	custFile << "-------------------------------" << endl;
	custFile << itemLabel << ":" << endl;
	custFile << setw(25) << "$" << price << endl;
	custFile << "Extra shots:" << endl;
	custFile << setw(25) << right <<  "$" << shotsCost << endl;
	custFile << "Milk Alt:" << endl;
	custFile << setw(25) << right << "+" << milkCost << endl;
	custFile << bookName << ":" << endl;
	custFile << setw(25) << right << "$" << bookPrice << endl;
	custFile << "Spendings:" << endl;
	custFile << setw(25) << right << "$" << setprecision(4) << totalPrice << endl;
	custFile << "Payment:" << endl;
	custFile << setw(25) << right << "$" << payment << endl;
	custFile << "Change:" << endl;
	custFile << setw(25) << right << "$" << std::fixed << setprecision(4) << change << endl;

	custFile.close();
};

//
//Cafe defs.
//

// Making sure the user can't break the program with a simple fat finger.
// If input doesn't match valid options the program asks for a different input.
bool Coffee::validOrder(int selection){
	
	switch(selection){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			return true;
		default:
			return false;
	}
}

// Reads the menu csv and outputs the contents in a menu-like fashion.
void Coffee::printMenu(){

		string item;
		fstream infile;
		Coffee::menuItem menu[9];
		
	infile.open("CafeMenu.csv", ios::in);
		
	// Telling the computer to read the file up until it finds a comma.
	// The program then inputs all that it has read up until the comma, (the "item"),
	// into the corresponding menu variable. Starting with the item number
	// and ending at "has_shots". "i" increments and repeats until i = 9.
	for(int i= 0; i < 9; i++){
		getline(infile,item,',');
		menu[i].itemNum = item;
		getline(infile, item, ',');
		menu[i].name = item;
		getline(infile, item, ',');
		menu[i].description = item;
		getline(infile, item, ',');
		menu[i].price = item;
		getline(infile, item);
		menu[i].has_shots = item;
		
	}

	// Just some fun touches.
	cout << "#########################" << endl;
	cout << "######### Menu ##########" << endl;
	cout << "#########################" << endl;

    // This loop outputs the retrieved menu information in a way the user can
	// easily read.
	for(int j = 0; j < 9; j++){
		cout << "Item #:  " << menu[j].itemNum <<endl;
		cout << "Name:   " << menu[j].name << endl;
		cout << "Descrip:" << menu[j].description << endl;
		cout << "Price:  " << menu[j].price << endl;
		cout << "Shots:  " << menu[j].has_shots << endl;
		cout << "-------------------------------" << endl;
	}
	infile.close();
};

// Prints out the cafe menu and retrieves the users input.
int Coffee::cafe(){

	printMenu();
	
	cout << "Please enter your order number here: " << endl;
	cin >> selection;

	// Iteration to make sure the user inputs a valid selection.
	while(Coffee::validOrder(selection) == false){
		cout << "Invalid Input. Please choose from the available options." << endl;
		cin.clear();
		cin.ignore();
		cin >> selection;
	}
	return selection;
};

// Prompts user for desired extra shots and stores it in int "num".
int Coffee::numOfShot(){
	
	cout << "How many extra shot(s)?" << endl;
	cin >> num;

	return num;
};

// Prompts user about milk alternative and stores it in char "response20".
char Coffee::altMilk(){
	
	cout << "Milk alternative?(Y/N): " << endl;
	cin >> response20;
	
	return response20;
};

// Takes user input and checks it against available options and stores the 
// corresponding string in "itemNames" for the receipt.
string Coffee::itemName(int selection){

	choice = selection;

	if(choice == 1){
		itemNames = "Black";
	}
	else if(choice == 2){
		itemNames = "Mocha";
	}
	else if(choice == 3){
		itemNames = "Latte";
	}
	else if(choice == 4){
		itemNames = "Chai";
	}
	else if(choice == 5){
		itemNames = "Americano";
	}
	else if(choice == 6){
		itemNames = "Cappuccino";
	}
	else if(choice == 7){
		itemNames = "Espresso";
	}
	else if(choice == 8){
		itemNames = "Macchiato";
	}
	else if(choice == 9){
		itemNames = "Irish";
	};

	return itemNames;
};

// Takes user input and checks it against available options and stores the 
// corresponding double in "price" for the receipt.
double Coffee::prices(int selection){

	choice = selection;

	if(choice == 1){
		price = 1.49;
	}
	else if(choice == 2){
		price = 3.49;
	}
	else if(choice == 3){
		price = 2.99;
	}
	else if(choice == 4){
		price = 3.99;
	}
	else if(choice == 5){
		price = 2.99;
	}
	else if(choice == 6){
		price = 3.50;
	}
	else if(choice == 7){
		price = 4.00;
	}
	else if(choice == 8){
		price = 4.50;
	}
	else if(choice == 9){
		price = 6.50;
	};
	return price;
};

//
//Books defs.
//

// Making sure the user can't break the program with a simple fat finger.
// If input doesn't match valid options the program asks for a different input.
bool Books::validInput(int bookSelect){
	
	switch(bookSelect){
		case 101:
		case 102:
		case 103:
		case 203:
		case 303:
		case 104:
		case 105:
		case 106:
		case 107:
		case 108:
			return true;
		default:
			return false;
	}
}

// Outputs the menu and retrieves the user input.
int Books::bookStore(){

	printBooks();

	cout << "Enter the number of the book you'd like to buy: " << endl;
	cin >> bookSelect;

	// As long as the user input in invalid, this statement will execute.
	while(Books::validInput(bookSelect) == false){
		cout << "Invalid input. Please choose from available options" << endl;
		cin.clear();
		cin.ignore();
		cin >> bookSelect;
	}

	return bookSelect;
};

// Takes the users selection and stores the corresponding title 
// inside bookName.
string Books::bookNames(int bookSelect){

	select = bookSelect;

	if(select == 101){
		bookName = "Moby Dick";
	}
	else if(select == 102){
		bookName = "Pride and Prejudice";
	}
	else if(select == 103){
		bookName = "Harry Potter: Book 1";
	}
	else if(select == 203){
		bookName = "Harry Potter: Book 2";
	}
	else if(select == 303){
		bookName = "Harry Potter: Book 3";
	}
	else if(select == 104){
		bookName = "To Kill a Mockingbird";
	}
	else if(select == 105){
		bookName = "The Great Gatsby";
	}
	else if(select == 106){
		bookName = "The Diary of Anne Frank";
	}
	else if(select == 107){
		bookName = "One Hundred Years of Solitude";
	}
	else if(select == 108){
		bookName = "Flatland";
	};
		
	return bookName;
};

// Takes the users selection and stores corresponding price
// in cost.
double Books::bookPrices(int bookSelect){

	select = bookSelect;

	if(select == 101){
		cost = 13.00;
	}
	if(select == 102){
		cost = 15.00;
	}
	if(select == 103){
		cost = 17.65;
	}
	if(select == 203){
		cost = 17.65;
	}
	if(select == 303){
		cost = 19.65;
	}
	if(select == 104){
		cost = 12.99;
	}
	if(select == 105){
		cost = 12.99;
	}
	if(select == 106){
		cost = 14.50;
	}
	if(select == 107){
		cost = 22.49;
	}
	if(select == 108){
		cost = 8.99;
	};
		
	return cost;
};

// This function takes the content of the library csv and 
// prints it out on the screen.
void Books::printBooks(){

		fstream onfile;
		string item;
		Books::bookInfo book[10];

	onfile.open("Library.csv", ios::in);
		
	// Telling the computer to read the file up until it finds a comma.
	// The program then inputs all that it has read up until the comma, (the "item"),
	// into the corresponding library variable. Starting with the item number
	// and ending at price. "i" increments and repeats until i = 10.
	for(int i = 0; i < 10; ++i){
		getline(onfile, item, ',');
		book[i].bookNum = item;
		getline(onfile, item, ',');
		book[i].title = item;
		getline(onfile, item, ',');
		book[i].author = item;
		getline(onfile, item, ',');
		book[i].genre = item;
		getline(onfile, item, ',');
		book[i].cover = item;
		getline(onfile, item);
		book[i].price = item;
	}
	cout << "#############################" << endl;
	cout << "####### Choice Books ########" << endl;
	cout << "#############################" << endl;

	// This loop outputs the retrieved book information in a way the user can
	// easily read.
	for(int j = 0; j < 10; ++j){
		cout << "Book #:  " << book[j].bookNum << endl;
		cout << "Title:  " << book[j].title << endl;
		cout << "Author: " << book[j].author << endl;
		cout << "Genre:  " << book[j].genre << endl;
		cout << "Cover:  " << book[j].cover << endl;
		cout << "Price:  " << book[j].price << endl;
		cout << "-------------------------------" << endl;
	}

	onfile.close();

}