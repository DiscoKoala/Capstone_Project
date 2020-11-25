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

void printBooks();
void printMenu();

int main(){

	const double milkAlt = 0.25;
	const double shotsExtra = 0.50;
	double shotsCost;
	int numOfShots;
	double preTaxtotal = 0;
	double total;
	double price;
	double cost;
	string bookName;
	double totalPrice;
	const double tax = 0.08;
	double totalTax;
	int selection;
	int bookSelect;
	char response;
	char response2;
	double payment;
	double payment2;
	double change;
	double grace;
	string itemName;
	string choice;

	cout << "Cafe or Bookstore? " << endl << endl;
	cin >> choice;

	if(choice == "Bookstore" || choice == "bookstore"){
		
		printBooks();

		cout << "Enter the number of the book you'd like to buy: " << endl;
		cin >> bookSelect;

		if(bookSelect == 101){
			cost = 13.00;
			bookName = "Moby Dick";
		}
		if(bookSelect == 102){
			cost = 15.00;
			bookName = "Pride and Prejudice";
		}
		if(bookSelect == 103){
			cost = 17.65;
			bookName = "Harry Potter: Book 1";
		}
		if(bookSelect == 203){
			cost = 17.65;
			bookName = "Harry Potter: Book 2";
		}
		if(bookSelect == 303){
			cost = 19.65;
			bookName = "Harry Potter: Book 3";
		}
		if(bookSelect == 104){
			cost = 12.99;
			bookName = "To Kill a Mockingbird";
		}
		if(bookSelect == 105){
			cost = 12.99;
			bookName = "The Great Gatsby";
		}
		if(bookSelect == 106){
			cost = 14.50;
			bookName = "The Diary of Anne Frank";
		}
		if(bookSelect == 107){
			cost = 22.49;
			bookName = "One Hundred Years of Solitude";
		}
		if(bookSelect == 108){
			cost = 8.99;
			bookName = "Flatland";
		};
		

	}

	printMenu();

	cout << "Please enter your order number here: " << endl;
	cin >> selection;

	
	if(selection == 1){
		price = 1.49;
		itemName = "Black";
	}
	else if(selection == 2){
		price = 3.49;
		itemName = "Mocha";
	}
	else if(selection == 3){
		price = 2.99;
		itemName = "Latte";
	}
	else if(selection == 4){
		price = 3.99;
		itemName = "Chai";
	}
	else if(selection == 5){
		price = 2.99;
		itemName = "Americano";
	}
	else if(selection == 6){
		price = 3.50;
		itemName = "Cappuccino";
	}
	else if(selection == 7){
		price = 4.00;
		itemName = "Espresso";
	}
	else if(selection == 8){
		price = 4.50;
		itemName = "Macchiato";
	}
	else if(selection == 9){
		price = 6.50;
		itemName = "Irish";
	};

	cout << "Would you like to modify your order?(Y/N): " << endl;
	cin >> response;

	if(response == 'Y' || response == 'y'){
		cout << "How many extra shot(s)?" << endl;
		cin >> numOfShots;
		cout << "Milk alternative?(Y/N): " << endl;
		cin >> response2;
	};

	shotsCost = numOfShots * shotsExtra;
	total = price + shotsCost;

		if(response2 == 'Y' || response2 =='y'){
			total = total + milkAlt;
		};
	

	preTaxtotal = total;
	totalTax = preTaxtotal * tax;
	totalPrice = preTaxtotal + totalTax;

	cout << fixed;
	cout << setprecision(2) << "Your total is: " << totalPrice << endl;
	cout << " " << endl;
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
			cout << itemName << ": " << price << endl;
			cout << "--------------------------" << endl;
			cout << "Extra shots: " << "+" << numOfShots << " = " << shotsCost << endl;
			cout << "--------------------------" << endl;
			cout << "Milk Alternative: " << "+" << milkAlt << endl;
			cout << "--------------------------" << endl;
			cout << "Book: " << bookName << " = " << cost << endl;
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

void printMenu(){

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
	cout << "####### Menu ########" << endl;
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

void printBooks(){

		ifstream infile;
		string item;
	

		bookInfo book[9];
	
	infile.open("Library.csv", ios::in);
		
	int i = 0;
	while(!infile.eof()){
		getline(infile, item, ',');
		book[i].bookNum = item;
		getline(infile,item,',');
		book[i].title = item;
		getline(infile, item, ',');
		book[i].author = item;
		getline(infile, item, ',');
		book[i].genre = item;
		getline(infile, item, ',');
		book[i].cover = item;
		getline(infile, item);
		book[i].price = item;;
		i++;
		
	}
	cout << "                     " << endl;
	cout << "####### Choice Books ########" << endl;
	cout << "                     " << endl;

	for(int j = 0; j < 8; j++){
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
