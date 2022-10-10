#include <iostream>
#include <string>
#include<algorithm>
#include <assert.h>

using namespace std;

const int MAX_BOOKS = 10;
const int MAX_USERS = 10;

struct Book {
    int id;
    string name;
    int quantity;
    int total_borrowed;
    
    Book()
    {
        id = -1;
        quantity = total_borrowed = 0;
        name = "";
    }

    void read()
    {
        cout << "Enter Book info: id & name & total quantity: ";
        cin >> id >> name >> quantity;

    }
    bool has_prefix(string prefix)
    {
        
        if (prefix.size() > name.size())
            return false;
        for (int i = 0; i < (int)prefix.size(); ++i) {
            if (prefix[i] != name[i])
                return false;
        }
        return true;
    }

    bool borrow()
    {
        if (quantity - total_borrowed == 0)
            return false;

        total_borrowed++;
        return true;
    }
    void return_book()
    {
        assert(total_borrowed > 0);
        total_borrowed--;
    }
    void print()
    {
        cout << "id = " << id << " name = " << name << " total_quantity "
            << quantity << " total_borrowed " << total_borrowed
            << "\n";
    }
};

bool cmp_book_by_name(Book& a, Book& b) {
    return a.name < b.name;
}

bool cmp_book_by_id(Book& a, Book& b) {
    return a.id < b.id;
}

struct user {
    string name;
    int national_id;
    int borrowed_books_ids[MAX_BOOKS];
    int no_of_borrwed_books;
    user()
    {
        name = "";
        national_id = -1;
        no_of_borrwed_books = 0;
    }

    void read()
    {
        cout << "enter usename and natinal id : ";
        cin >> name >> national_id;
        
    }

    void borrow(int book_id)
    {
        borrowed_books_ids[no_of_borrwed_books++] = book_id;
    }

    void return_copy(int book_id) {//**************
        bool removed = false;
        for (int i = 0; i < no_of_borrwed_books; ++i) {
            if (borrowed_books_ids[i] == book_id) {
                // Let's shift the array to the right to remove this entry
                for (int j = i + 1; j < no_of_borrwed_books; ++j)
                    borrowed_books_ids[j - 1] = borrowed_books_ids[j];
                removed = true;
                --no_of_borrwed_books;
                break;
            }
        }
        if (!removed)
            cout << "User " << name << " never borrowed book id " << book_id
            << "\n";
    }
    void return_book(int book_id)
    {
        for (int i = 0; i < no_of_borrwed_books; i++)
        {
            if (book_id == borrowed_books_ids[i])
                cout << "";
        }
    }

    bool is_borrowed(int book_id) {
        for (int i = 0; i < no_of_borrwed_books; ++i) {
            if (book_id == borrowed_books_ids[i])
                return true;
        }
        return false;
    }

    void print_users()
    {
        sort(borrowed_books_ids, borrowed_books_ids + no_of_borrwed_books);

        cout << "user " << name << " id " << national_id << " borrowed books ids: ";
        for (int i = 0; i < no_of_borrwed_books; ++i)
            cout << borrowed_books_ids[i] << " ";
        cout << "\n";
         
    }
};

struct library_system {

    int total_books;
    int total_users;
    Book books[MAX_BOOKS];
    user Users[MAX_USERS];

    library_system()
    {
        total_books = total_users = 0;
    }

    void run() {
        while (true) {
            int choice = menu();
            if (choice == 1)
                add_book();
            else if (choice == 2)
                search_books();
            else if (choice == 3)
                know_who_borrowed_books();
            else if (choice == 4)
                list_books_by_id();
            else if (choice == 5)
                list_books_by_name();
            else if (choice == 6)
                add_user();
            else if (choice == 7)
                borow_book();
            else if (choice == 8)
                return_book();
            else if (choice == 9)
                print();
            else
                break;
        }

    }

    int menu(){
        int choice = -1;
        while (choice == -1){
           
                cout << "Library Menu:\n";
                cout << "1) Add Book\n";
                cout << "2) Search Books By Prefix\n";
                cout << "3) print who borrowed books by name\n";
                cout << "4) print library by id\n";
                cout << "5) print library by name\n";
                cout << "6) add user \n";
                cout << "7) user borrow book\n";
                cout << "8) user return book\n";
                cout << "9) print users\n";
                cout << "10) Exit\n";
            
            cout << "enter your menue choice [1 - 10] : | \n";
            cin >> choice;
            if (!(1 <= choice && choice <= 10))
                {
                    cout << "invalid choice. Please Try again\n";
                    choice = -1;
                }
        }
        return choice;
    }


    void add_book()
    {
        Book b;
        b.read();
        books[total_books++] = b;
    }

    void add_user()
    {
        user u;
        u.read();
        Users[total_users++] = u;
    }

    void search_books(){
        string prefix;
        cout << "enter bookname prefix:\n";
        cin >> prefix;
        int cnt = 0;
        for (int i = 0; i < total_books; i++)
        {
            if (books[i].has_prefix(prefix))
            {
                cout << books[i].name << "\n";
                ++cnt;
            }
        }
        if (!cnt)
            cout << "No such books with this prefix try another one. \n";
    }

    int find_idx_bookname_byName(string bookname)
    {
        for (int i = 0; i < total_books; i++)
        {
            if (books[i].name == bookname)
                return i;
            else
                return -1;
        }
    }
    int find_idx_username_byName(string username)
    {
        for (int i = 0; i < total_users; i++)
        {
            if (Users[i].name == username)
                return i;
            else
                return -1;
        }
    }

    bool read_user_name_and_book_name(int &user_idx, int &book_idx, int trial = 3)
    {
        string username, bookname;
        while (trial--)
        {
            cout << "enter username and book name: ";
            cin >> username >> bookname;

            user_idx = find_idx_username_byName(username);
            if (user_idx == -1)
            {
                cout << "there is no user with this name. Try again\n";
                continue;
            }
            book_idx = find_idx_bookname_byName(bookname);
            if (book_idx == -1)
            {
                cout << "there is no book with this name. Try again\n";
                continue;
            }
            return true;
        }
        cout << "You did several trials! Try later.";
        return false;
    }

    void borow_book()
    {
        int user_idx, book_idx;

        if (!read_user_name_and_book_name(user_idx, book_idx))
            return;
        int user_id = Users[user_idx].national_id;
        int book_id = books[book_idx].id;

        if (!books[book_idx].borrow())//*****************
            cout << "No more copies available right now\n";
        else
            Users[user_idx].borrow(book_id);
        /*string username, bookname;
        cout << "enter username and book name: ";
        cin >> username >> bookname;
        int avalable = 1, j;
        for (j = 0;  j < total_books; j++)
        {
            if (!(bookname == books[j].name && books[j].borrow())) {
                cout << "sorry there is no copies of this book\n";
                avalable = 0;
                break;
            }
            if(bookname == books[j].name && books[j].borrow())
            Book b = books[j];
        }
        if (avalable)
        {
            for (int i = 0; i < total_users; i++)
            {
                if (username == Users[i].name)
                {
                    Users[i].borrow(books[j].id);
                }
            }
        }*/
    }
    
     void list_books_by_id()
     {
         sort(books, books + total_books, cmp_book_by_id);

         cout << "\n";
         for (int i = 0; i < total_books; ++i)
             books[i].print();
     }


     void list_books_by_name()
     {
         sort(books, books + total_books, cmp_book_by_name);

         cout << "\n";
         for (int i = 0; i < total_books; ++i)
             books[i].print();
     }

    void know_who_borrowed_books(){
        string bookname;
        cout << "enter book name\n";
        cin >> bookname;

        int book_idx = find_idx_bookname_byName(bookname);

        if (book_idx == -1) {
            cout << "Invalid book name.\n";
            return;
        }

        int book_id = books[book_idx].id;

        if (books[book_idx].total_borrowed == 0) {
            cout << "No borrowed copies\n";
            return;
        }

        for (int i = 0; i < total_users; i++)
        {
            if (Users[i].is_borrowed(book_id))
            {
                cout << Users[i].name << "\n";
            }
        }
     }
    void return_book()
    {
        int user_idx, book_idx;

        if (!read_user_name_and_book_name(user_idx, book_idx))
            return;

        int book_id = books[book_idx].id;
        books[book_idx].return_book();
        Users[user_idx].return_copy(book_id);
       
    }
   
   

    void print()
    {
        cout << "\n";
        for(int i = 0; i < total_users; i++)
        Users[i].print_users();
    }


};

int main()
{   
    library_system library;
    library.run();
}

// frist day of this project is 18 of Septemper And End of all implementation is 8 of octoper(20 days)
// I want to learn unit testing or search for how to test project apply on this project
// next project focus on two things 1- less time 2- less hints 3- more focus on things that i learned
// from this project