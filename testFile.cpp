#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<iomanip>

using namespace std;

struct menuItem {
	string itemNum;
	string name;
	string description;
	string price;
	string has_shots;
};

struct bookInfo{
	string bookNum;
	string title;
	string author;
	string genre;
	string cover;
	string price;
};

double bookPrices(int& bookSelect);
double prices(int& selection);
int bookStore();
int cafe();
int numOfShot();
char altMilk();
string itemName(int& selection);
string bookNames(int& bookSelect);
void printBooks();
void printMenu();

int main(){

	double shotsCost, total, total2, total3, total4, price, bookPrice, cost, 
	totalPrice, payment, payment2, change, grace, totalTax, milkAlt;
	int numOfShots, selection = 0, bookSelect;
	double preTaxtotal = 0;
	fstream infile;
	string bookName, itemLabel, choice;
	const double tax = 0.08, milkCost = 0.25, shotsExtra = 0.50;
	char response, response2, response3, response4;
	
	cout << "Cafe or Bookstore? " << endl;
	cin >> choice;

	if(choice == "Cafe" || choice == "cafe"){
		selection = cafe();
		price = prices(selection);
		itemLabel = itemName(selection);

		cout << "Would you like to modify your order?(Y/N): " << endl;
		cin >> response;
		if(response == 'Y' || response == 'y'){
			numOfShots = numOfShot();
			milkAlt = altMilk();
		}
		cout << "Would you like to go to the bookstore? (Y/N)" << endl;
		cin >> response4;

		if(response4 == 'Y' || response4 =='y'){
			bookSelect = bookStore();
			bookPrice = bookPrices(bookSelect);
			bookName = bookNames(bookSelect);
		};
	}
	else if(choice == "Bookstore" || choice == "bookstore"){
		total3 = bookStore();
		cout << "Would you like to go to the Cafe? (Y/N) " << endl;
		cin >> response3;

		if(response3 == 'Y' || response3 =='y'){
			selection = cafe();
			price = prices(selection);
			itemLabel = itemName(selection);

		cout << "Would you like to modify your order?(Y/N): " << endl;
		cin >> response;

		if(response == 'Y' || response == 'y'){
			numOfShots = numOfShot();
			milkAlt = altMilk();

		};

	shotsCost = numOfShots * shotsExtra;
	total = bookPrice + price + shotsCost;

		if(milkAlt == 'Y' || milkAlt =='y'){
			total = total + milkCost;
	};
	
	preTaxtotal = total + total3;
	totalTax = preTaxtotal * tax;
	totalPrice = preTaxtotal + totalTax;

	cout << fixed;
	cout << setprecision(2) << "Your total is: " << totalPrice << endl << endl;
	cout << "Please enter your payment amount: ";
	cin >> payment;

	grace = totalPrice - 0.50;

		if(payment > totalPrice){
			change = (payment - totalPrice);
			cout << "Here's your change: " << endl;
			cout << " " << change << endl << endl;
		};

		if(payment == totalPrice){
			cout << "Thank you for your business! " << endl << endl;
		};

		if(payment >= grace && payment < totalPrice){
			cout << "No worries, I've got you this time." << endl << endl;
		};
		
		if(payment < grace){
			cout << "Sorry, maybe next time. " << endl;
		};
			 		
	
			cout << "##########################" << endl;
			cout << "#### Printing Receipt ####" << endl;
			cout << "##########################" << endl << endl;
			cout << itemLabel << ": " << price << endl;
			cout << "--------------------------" << endl;
			cout << "Extra shots: " << "+" << numOfShots << " = " << shotsCost << endl;
			cout << "--------------------------" << endl;
			cout << "Milk Alternative: " << "+" << milkAlt << endl;
			cout << "--------------------------" << endl;
			cout << "Book: " << bookName << " = " << bookPrice << endl;
			cout << "--------------------------" << endl;
			cout << "Pre-tax total: " << preTaxtotal << endl;
			cout << "--------------------------" << endl;
			cout << "Added tax : " << totalTax << endl;
			cout << "--------------------------" << endl;
			cout << "Total cost: " << totalPrice << endl;
			cout << "--------------------------" << endl;
			cout << "WiFi password: C0fFe3" << endl;
			cout << "--------------------------" << endl;
			cout << "##########################" << endl;
		

	return 0;
}

void printMenu();{

		ifstream infile;
		string item;
	

		menuItem menu[8];
	
	infile.open("CafeMenu.csv", ios::in);
		
	int i = 0;
	while(!infile.eof()){
		getline(infile,item,',');
		menu[i].itemNum = item;
		getline(infile, item, ',');
		menu[i].name = item;
		getline(infile, item, ',');
		menu[i].description = item;
		getline(infile, item, ',');
		menu[i].price = item;
		getline(infile, item);
		menu[i].has_shots = item;;
		i++;
		
	}
	cout << "                     " << endl;
	cout << "######### Menu ##########" << endl;
	cout << "                     " << endl;

	for(int j = 0; j < 8; j++){
		cout << "Item Number: " << menu[j].itemNum <<endl;
		cout << "Name:" << menu[j].name << endl;
		cout << "Description:" << menu[j].description << endl;
		cout << "Price:" << menu[j].price << endl;
		cout << "Has Shots::" << menu[j].has_shots << endl;
		cout << "-------------------------------" << endl;
	}

	infile.close();
};

void printBooks();{

		ifstream infile;
		string item;
	
		bookInfo book[10];
	
	infile.open("Library.csv", ios::in);
		
	int i = 0;
	for(i = 0; i < 10; ++i){
		getline(infile, item, ',');
		book[i].bookNum = item;
		getline(infile, item, ',');
		book[i].title = item;
		getline(infile, item, ',');
		book[i].author = item;
		getline(infile, item, ',');
		book[i].genre = item;
		getline(infile, item, ',');
		book[i].cover = item;
		getline(infile, item);
		book[i].price = item;
	}
	cout << "                     " << endl;
	cout << "####### Choice Books ########" << endl;
	cout << "                     " << endl;

	for(int j = 0; j < 10; ++j){
		cout << "Book Number: " << book[j].bookNum << endl;
		cout << "Title: " << book[j].title << endl;
		cout << "Author: " << book[j].author << endl;
		cout << "Genre: " << book[j].genre << endl;
		cout << "Cover: " << book[j].cover << endl;
		cout << "Price: " << book[j].price << endl;
		cout << "-------------------------------" << endl;
	}

	infile.close();

};

int cafe(){
	
	int selection;

	printMenu();

	cout << "Please enter your order number here: " << endl;
	cin >> selection;

	return selection;
};

int numOfShot(){
	int num;

	cout << "How many extra shot(s)?" << endl;
	cin >> num;

	return num;
};

char altMilk(){
	char response20;

	cout << "Milk alternative?(Y/N): " << endl;
	cin >> response20;
	
	return response20;
};

int bookStore(){

	int bookSelect;
	
	printBooks();

	cout << "Enter the number of the book you'd like to buy: " << endl;
	cin >> bookSelect;


	return bookSelect;
};

string bookNames(int bookSelect);{

	int select;
	string bookName;

	if(bookSelect == 101){
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

double bookPrices(int& bookSelect){

	int select;
	double cost;

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

string itemName(int& selection){

	int choice;
	string itemName;

	if(choice == 1){
		itemName = "Black";
	}
	else if(choice == 2){
		itemName = "Mocha";
	}
	else if(choice == 3){
		itemName = "Latte";
	}
	else if(choice == 4){
		itemName = "Chai";
	}
	else if(choice == 5){
		itemName = "Americano";
	}
	else if(choice == 6){
		itemName = "Cappuccino";
	}
	else if(choice == 7){
		itemName = "Espresso";
	}
	else if(choice == 8){
		itemName = "Macchiato";
	}
	else if(choice == 9){
		itemName = "Irish";
	};

	return itemName;
};

double prices(int& selection){

	int selection;
	double price;

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