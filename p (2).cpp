#include <iostream>
#include <fstream>

#define MAX 10000

using namespace std;

struct member{
	string name;
	string family;
	string code_melli;
	int tedad_ketab;
	int bedehi;
	string books_code[5];
	string tamas;
};

struct book{
	string name;
	string writer;
	string kind;
	string code;
	int mojodi;
};

void load_files(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void update_files(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void update_bedehi(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void mainMenu(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void add_book(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void add_member(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void remove_book(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void remove_member(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void search_book(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void search_member(member members[], book books[], int &number_of_members, int &number_of_books, string &date);
void borrow_book(member members[], book books[], int &number_of_members, int &number_of_books, string date);
void pay_bedehi(member members[], book books[], int &number_of_members, int &number_of_books, string date);
int date_diference(string date1, string date2);


void load_files(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    ifstream fp, fb;
	fp.open("members.txt");
	if(!fp) {
        cout << "Error loading members file." << endl;
	}else{
        fp >> number_of_members;
        for(int i = 0; i < number_of_members; i++)
        {
            fp >> members[i].name;
            fp >> members[i].family;
            fp >> members[i].code_melli;
            fp >> members[i].tamas;
            fp >> members[i].tedad_ketab;
            for (int j = 0; j < members[i].tedad_ketab; j++)
            {
                fp >> members[i].books_code[j];
            }
            fp >> members[i].bedehi;
        }
    }
    fp.close();
    fb.open("books.txt");
    if(!fb) {
        cout << "Error loading books file." << endl;
	}else{
        fb >> number_of_books;
        for(int i = 0; i < number_of_books; i++)
        {
            fb >> books[i].name;
            fb >> books[i].writer;
            fb >> books[i].kind;
            fb >> books[i].code;
            fb >> books[i].mojodi;
        }
    }
}

void update_files(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    ofstream fp, fb;
	fp.open("members.txt");
	if(!fp) {
        cout << "Error loading members file." << endl;
	}else{
        fp.clear();
        fp << number_of_members << endl;
        for (int i = 0; i < number_of_members; i++){
            fp << members[i].name << " ";
            fp << members[i].family << " ";
            fp << members[i].tamas << " ";
            fp << members[i].code_melli << endl;
            fp << members[i].tedad_ketab << endl;
            for (int j = 0; j < members[i].tedad_ketab; j++){
                fp << members[i].books_code[j] << endl;
            }
            fp << members[i].bedehi << endl << endl;
        }
        fp.close();
	}
	if(!fp) {
        cout << "Error loading books file." << endl;
	}else{
        fb.open("books.txt");
        fb.clear();
        fb << number_of_books << endl;
        for (int i = 0; i < number_of_books; i++){
            fb << books[i].name << " ";
            fb << books[i].writer << " ";
            fb << books[i].kind << " ";
            fb << books[i].code << " ";
            fb << books[i].mojodi << endl;
        }
        fb.close();
	}
}

void update_bedehi(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    cout << "Enter current date in this format(YYMMDD): ";
    cin >> date;
    for (int i = 0; i < number_of_members; i++){
        int bedehi = 0;
        for (int j = 0; j < members[i].tedad_ketab; j++){
            if (date_diference(members[i].books_code[j], date) - 30 > 0){
                bedehi += (date_diference(members[i].books_code[j].substr(0, 6), date) - 30) * 100;
            }
        }
        members[i].bedehi = bedehi;
    }
    update_files(members, books, number_of_members, number_of_books, date);
}

void mainMenu(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    cout << "------------- main menu -------------" << endl;
    cout << "1. add a member" << endl;
    cout << "2. add a book" << endl;
    cout << "3. remove a member" << endl;
    cout << "4. remove a book" << endl;
    cout << "5. search members" << endl;
    cout << "6. search books" << endl;
    cout << "7. borrow a book" << endl;
    cout << "8. pay bedehi" << endl;
    cout << "-------------------------------------" << endl;
    int choice;
    cout << "choose one of options: ";
    cin >> choice;
    if (choice == 1) add_member(members, books, number_of_members, number_of_books, date);
    if (choice == 2) add_book(members, books, number_of_members, number_of_books, date);
    if (choice == 3) remove_member(members, books, number_of_members, number_of_books, date);
    if (choice == 4) remove_book(members, books, number_of_members, number_of_books, date);
    if (choice == 5) search_member(members, books, number_of_members, number_of_books, date);
    if (choice == 6) search_book(members, books, number_of_members, number_of_books, date);
    if (choice == 7) borrow_book(members, books, number_of_members, number_of_books, date);
    if (choice == 8) pay_bedehi(members, books, number_of_members, number_of_books, date);
}

void add_book(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    cout << "---------------- add book ---------------" << endl;
    cout << "Enter book's name: ";
    cin >> books[number_of_books].name;
    cout << "Enter book's writer: ";
    cin >> books[number_of_books].writer;
    cout << "Enter book's kind: ";
    cin >> books[number_of_books].kind;
    cout << "Enter book's code: ";
    cin >> books[number_of_books].code;
    cout << "Enter book's mojodi: ";
    cin >> books[number_of_books].mojodi;
    cout << "-----------------------------------------" << endl;
    cout << "Result: ";
    cout << "book added." << endl;
    number_of_books++;
    update_files(members, books, number_of_members, number_of_books, date);
    mainMenu(members, books, number_of_members, number_of_books, date);
}

void add_member(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    cout << "-------------- add member --------------" << endl;
    cout << "Enter member's name: ";
    cin >> members[number_of_members].name;
    cout << "Enter member's family: ";
    cin >> members[number_of_members].family;
    cout << "Enter member's code_melli: ";
    cin >> members[number_of_members].code_melli;
    cout << "Enter member's tamas: ";
    cin >> members[number_of_members].tamas;
    cout << "-----------------------------------------" << endl;
    cout << "Result: ";
    members[number_of_members].tedad_ketab = 0;
    members[number_of_members].bedehi = 0;
    cout << "member added." << endl;
    number_of_members++;
    update_files(members, books, number_of_members, number_of_books, date);
    mainMenu(members, books, number_of_members, number_of_books, date);
}

void remove_book(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    cout << "------------- remove boook -------------" << endl;
    cout << "Enter book's code to remove: ";
    string book_code;
    cin >> book_code;
    cout << "-----------------------------------------" << endl;
    cout << "Result: ";
    int book_index = -1;
    for (int i = 0; i < number_of_books; i++){
        if (books[i].code == book_code){
            book_index = i;
            break;
        }
    }
    if (book_index == -1){
        cout << "book does not exist." << endl;
    }else{
        for (int i = book_index; i < number_of_books - 1; i++){
            books[i] = books[i + 1];
        }
        number_of_books--;
        cout << "book removed." << endl;
        update_files(members, books, number_of_members, number_of_books, date);
    }
    mainMenu(members, books, number_of_members, number_of_books, date);
}

void remove_member(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    cout << "------------- remove member -------------" << endl;
    cout << "Enter member's code_melli to remove: ";
    string member_code_melli;
    cin >> member_code_melli;
    cout << "-----------------------------------------" << endl;
    cout << "Result: ";
    int member_index = -1;
    for (int i = 0; i < number_of_members; i++){
        if (members[i].code_melli == member_code_melli){
            member_index = i;
            break;
        }
    }
    if (member_index == -1){
        cout << "member does not exist." << endl;
    }else{
        for (int i = member_index; i < number_of_members - 1; i++){
            members[i] = members[i + 1];
        }
        number_of_members--;
        cout << "member removed." << endl;
        update_files(members, books, number_of_members, number_of_books, date);
    }
    mainMenu(members, books, number_of_members, number_of_books, date);
}

void search_book(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    cout << "-------------- search books -------------" << endl;
    cout << "1. search by name" << endl;
    cout << "2. search by code" << endl;
    cout << "3. search by writer" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Result: ";
    int choice;
    cout << "choose one of options: ";
    cin >> choice;
    int book_index;
    if (choice == 1){
        string name;
        cin >> name;
        for (int i = 0; i < number_of_books; i++){
            if (books[i].name == name){
                book_index = i;
            }
        }
    }else if (choice == 2){
        string code;
        cin >> code;
        for (int i = 0; i < number_of_books; i++){
            if (books[i].code == code){
                book_index = i;
            }
        }
    }else if (choice == 3){
        string writer;
        cin >> writer;
        for (int i = 0; i < number_of_books; i++){
            if (books[i].writer == writer){
                book_index = i;
            }
        }
    }
    if (book_index == -1){
        cout << "book does not exist." << endl;
    }else {
        cout << "********** book information **********" << endl;
        cout << "book name: " << books[book_index].name << endl;
        cout << "book writer: " << books[book_index].writer << endl;
        cout << "book kind: " << books[book_index].kind << endl;
        cout << "book mojodi: " << books[book_index].mojodi << endl;
        cout << "book code: " << books[book_index].code << endl;
        cout << "**************************************" << endl;
    }
    mainMenu(members, books, number_of_members, number_of_books, date);
}

void search_member(member members[], book books[], int &number_of_members, int &number_of_books, string &date){
    cout << "------------- search members -------------" << endl;
    cout << "1. search by name & family" << endl;
    cout << "2. search by code_melli" << endl;
    cout << "-----------------------------------------" << endl;
    int choice;
    cout << "choose one of options: ";
    cin >> choice;
    int member_index = -1;
    if (choice == 1){
        string name, family;
        cin >> name >> family;
        for (int i = 0; i < number_of_members; i++){
            if (members[i].name == name && members[i].family == family){
                member_index = i;
            }
        }
    }else if (choice == 2){
        string code_melli;
        cin >> code_melli;
        for (int i = 0; i < number_of_members; i++){
            if (members[i].code_melli == code_melli){
                member_index = i;
            }
        }
    }
    if (member_index == -1){
        cout << "member does not exist." << endl;
    }else {
        cout << "********** member information **********" << endl;
        cout << "member name: " << members[member_index].name << endl;
        cout << "member family: " << members[member_index].family << endl;
        cout << "member code_melli: " << members[member_index].code_melli << endl;
        cout << "member tamas: " << members[member_index].tamas << endl;
        cout << "member tedad_ketab: " << members[member_index].tedad_ketab << endl;
        cout << "member bedehi: " << members[member_index].bedehi << endl;
        if (members[member_index].tedad_ketab > 0){
            cout << "book: ";
        }
        for (int i = 0; i < members[member_index].tedad_ketab; i++){
            cout << members[member_index].books_code[i] << " ";
        }
        cout << endl;
        cout << "****************************************" << endl;
    }
    mainMenu(members, books, number_of_members, number_of_books, date);
}

void borrow_book(member members[], book books[], int &number_of_members, int &number_of_books, string date){
    cout << "------------- borrow book -------------" << endl;
    cout << "Enter member's code_melli: ";
    string member_code_melli;
    cin >> member_code_melli;
    cout << "Enter book's code: ";
    string book_code;
    cin >> book_code;
    cout << "-----------------------------------------" << endl;
    cout << "Result: ";
    int member_index = -1, book_index = -1;
    for (int i = 0; i < number_of_members; i++){
        if (members[i].code_melli == member_code_melli){
            member_index = i;
        }
    }
    for (int i = 0; i < number_of_books; i++){
        if (books[i].code == book_code){
            book_index = i;
        }
    }
    if (member_index == -1){
        cout << "member does not exist." << endl;
    }else if (book_index == -1){
        cout << "book does not exist." << endl;
    }else if (members[member_index].tedad_ketab == 5){
        cout << "member has 5 books already." << endl;
    }else if (books[book_index].mojodi == 0){
        cout << "There is no book with this code left at library." << endl;
    }else if (members[member_index].bedehi > 0){
        cout << "This member has " << members[member_index].bedehi << " Toman bedehi.";
    }else {
        members[member_index].books_code[members[member_index].tedad_ketab] = date + book_code;
        members[member_index].tedad_ketab++;
        books[book_index].mojodi--;
        cout << "Done." << endl;
    }
    mainMenu(members, books, number_of_members, number_of_books, date);
}

void pay_bedehi(member members[], book books[], int &number_of_members, int &number_of_books, string date){
    cout << "------------- borrow book -------------" << endl;
    cout << "Enter member's code_melli: ";
    string member_code_melli;
    cin >> member_code_melli;
    cout << "How much do you want to pay: ";
    int payment;
    cin >> payment;
    cout << "-----------------------------------------" << endl;
    cout << "Result: ";
    int member_index = -1;
    for (int i = 0; i < number_of_members; i++){
        if (members[i].code_melli == member_code_melli){
            member_index = i;
        }
    }
    if (member_index == -1){
        cout << "member does not exist." << endl;
    }else {
        cout << "member bedehi was " << members[member_index].bedehi << " Toman ";
        members[member_index].bedehi -= payment;
        cout << "and now it's " << members[member_index].bedehi << " Toman "<< endl;
    }
}

int date_diference(string date1, string date2){
    int diference = 0;
    diference += (date1[5] - date2[5]);
    diference += (date1[4] - date2[4]) * 10;
    diference += (date1[3] - date2[3]) * 30;
    diference += (date1[2] - date2[2]) * 30 * 10;
    diference += (date1[1] - date2[1]) * 365;
    diference += (date1[0] - date2[0]) * 365 * 10;
    return (diference < 0 ? -1 * diference : diference);
}


int main(){
    int number_of_members = 0, number_of_books = 0;
    string date;
    member members[MAX];
    book books[MAX];
    load_files(members, books, number_of_members, number_of_books, date);
    update_bedehi(members, books, number_of_members, number_of_books, date);
    mainMenu(members, books, number_of_members, number_of_books, date);
    return 0;
}
