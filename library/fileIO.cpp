#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
/**helper for load books
 * csv string book => struct book*/
book parseBook(std::string line){
	book myBook;
	stringstream streamLine(line);
	string token;
	for(int i=0;getline(streamLine, token, ',');i++){
		switch(i){
			case 0:myBook.book_id=stoi(token);break;
			case 1:myBook.title=token;break;
			case 2:myBook.author=token;break;
			case 3:if(stoi(token)==1){
				myBook.state= IN;
			}else if(stoi(token)==2){//Not exactly sure if thats the right number but well see
				myBook.state = OUT;
			}break;
			case 4:myBook.loaned_to_patron_id=stoi(token);break;
			default:cout<<"pls dont go here (Book) \n";break;
		}
	}
	return myBook;
}
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	ifstream fileStream (filename);
	if(!fileStream.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	for (string line; getline(fileStream,line); ){
		books.push_back(parseBook(line));
	}
	fileStream.close();
	if(books.size()==0){
		return NO_BOOKS_IN_LIBRARY;
	}
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	if(books.size()==0){
		return NO_BOOKS_IN_LIBRARY;
	}
	ofstream fileStream;
	fileStream.open(filename);
	if(!fileStream.is_open() || fileStream.fail()){
		return COULD_NOT_OPEN_FILE;
	}
	for(book myBook:books){
		fileStream 	<< myBook.book_id << ","
					<< myBook.title<< ","
					<< myBook.author<< ","
					<< myBook.state<< ","
					<< myBook.loaned_to_patron_id<< "\n";
	}
	fileStream.close();
	return SUCCESS;
}
/** helper for load patrons
 * csv string patron => struct patron*/
patron parsePatron(std::string line){
	patron myPatron;
	stringstream streamLine(line);
	string token;
	for(int i=0;getline(streamLine, token, ',');i++){
		switch(i){
			case 0:myPatron.patron_id=stoi(token);break;
			case 1:myPatron.name=token;break;
			case 2:myPatron.number_books_checked_out=stoi(token);break;
			default:cout<<"pls dont go here (Patron)\n";break;
		}
	}
	return myPatron;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	ifstream fileStream (filename);
	if(!fileStream.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	for (string line; getline(fileStream,line); ){
		patrons.push_back(parsePatron(line));
	}
	fileStream.close();
	if(patrons.size()==0){
		return NO_PATRONS_IN_LIBRARY;
	}
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	if(patrons.size()==0){
		return NO_BOOKS_IN_LIBRARY;
	}
	ofstream fileStream;
	fileStream.open(filename);
	if(!fileStream.is_open() || fileStream.fail()){
		return COULD_NOT_OPEN_FILE;
	}
	for(patron myPatron:patrons){
		fileStream 	<< myPatron.patron_id << ","
					<< myPatron.name<< ","
					<< myPatron.number_books_checked_out<< "\n";
	}
	fileStream.close();
	return SUCCESS;
}
