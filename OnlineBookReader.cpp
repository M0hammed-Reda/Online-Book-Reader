#include <bits/stdc++.h>
using namespace std;

void time_date(tm& local_time) {
    time_t now = time(0);

#if defined(_MSC_VER) 
    localtime_s(&local_time, &now);
#else
    local_time = *localtime(&now);
#endif
}

class Book {
private:
    int ID;
    string title;
    string auther_name;
    int number_of_pages;
    int currant_page;
    vector<string> pages;
public:
    Book() : ID(0), currant_page(1), number_of_pages(0) {}

    int get_id() const {
        return ID;
    }
    void set_id(int id) {
        ID = id;
    }

    string get_title() const {
        return title;
    }
    void set_title(string _title) {
        title = _title;
    }

    string get_auther_name() const {
        return auther_name;
    }
    void set_auther_name(string _auther_name) {
        auther_name = _auther_name;
    }

    int get_number_of_pages() const {
        return number_of_pages;
    }
    void set_number_of_pages(int n) {
        number_of_pages = n;
    }

    int get_currant_page() {
        return currant_page;
    }
    void set_currant_page(int cp) {
        currant_page = cp;
    }

    void view_Currant_page() {
        cout << currant_page << '/' << (int)pages.size() << '\n';
    }

    vector<string> get_pages() const {
        return pages;
    }
    void set_pages(vector<string> vec) {
        pages = vec;
    }
};

class Session {
private:
    int ID;
    Book* book;
    int current_page;
    tm start_time;

public:

    Session() : ID(0), current_page(0), book(nullptr) {
        time_date(start_time);
    }

    ~Session() {
        if (book != nullptr) {
            delete book;
            book = nullptr;
        }
    }

    void set_book(Book* _book) {
        book = _book;
        current_page = 1;
    }

    void next_page() {
        if (book == nullptr) {
            cout << "No book assigned to this session." << endl;
            return;
        }
        if (current_page < book->get_number_of_pages()) {
            current_page++;
            cout << "Page " << current_page << ": " << book->get_pages()[current_page - 1] << endl;
        }
        else {
            cout << "You are at the last page." << endl;
        }
    }

    void previous_page() {
        if (book == nullptr) {
            cout << "No book assigned to this session." << endl;
            return;
        }
        if (current_page > 1) {
            current_page--;
            cout << "Page " << current_page << ": " << book->get_pages()[current_page - 1] << endl;
        }
        else {
            cout << "You are at the first page." << endl;
        }
    }

    void stop_reading() {
        cout << "Session ended." << endl;
    }

    int get_current_page() const {
        return current_page;
    }

    Book* get_book() const {
        return book;
    }

    tm get_start_time() const {
        return start_time;
    }
};

class SessionManager {
private:
    vector<Session*> sessions;

public:

    ~SessionManager() {
        for (Session* session : sessions) {
            if (session != nullptr) {
                delete session;
            }
        }
        sessions.clear();
    }

    void start_session(Book* book) {
        if (book == nullptr) {
            cout << "Invalid book!" << endl;
            return;
        }

        Session* session = new Session();
        session->set_book(book);  
        
        assert(session != nullptr);
        
        sessions.push_back(session);
        
        cout << "Started reading: " << book->get_title() << endl;
    }

    void navigate_session(int session_id, int choice) {
        if (session_id < 0 || session_id >= (int)sessions.size()) {
            cout << "Invalid session ID." << endl;
            return;
        }
        Session* session = sessions[session_id];
        if (session == nullptr) {
            cout << "Session is null." << endl;
            return;
        }

        if (choice == 1) {
            session->next_page();
        }
        else if (choice == 2) {
            session->previous_page();
        }
        else if (choice == 3) {
            session->stop_reading();
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }

    void list_sessions() const {
        for (int i = 0; i < (int)sessions.size(); ++i) {
            const Session* session = sessions[i];
            if (session != nullptr && session->get_book() != nullptr) {
                tm start_time = session->get_start_time();
                cout << i + 1 << ". " << session->get_book()->get_title()
                    << " (Page " << session->get_current_page() << ")"
                    << " - Started at: "
                    << (start_time.tm_year + 1900) << '-'
                    << (start_time.tm_mon + 1) << '-'
                    << start_time.tm_mday << " "
                    << start_time.tm_hour << ':'
                    << start_time.tm_min << ':'
                    << start_time.tm_sec << endl;
            }
        }
    }

    vector<Session*> get_sessions() const {
        return sessions;
    }
};

class Admin {
private:
    const string user_name = "mohamed_reda";
    const string password = "1234";
    const string name = "Mohamed Reda";
    const string email = "moreda@gmail.com";
    bool is_admin = false;
    vector<Book*> books;

public:
    ~Admin() {
        for (Book* book : books)
            delete book;
        books.clear();
    }

    void load_books() {
        Book* book1 = new Book();
        book1->set_id(1);
        book1->set_auther_name("Mostafa");
        book1->set_title("C++ how to program");
        book1->set_number_of_pages(5);
        vector<string> pages1 = { "A C++", "B C++", "C C++", "D C++", "E C++" };
        book1->set_pages(pages1);

        books.push_back(book1);

        Book* book2 = new Book();
        book2->set_id(2);
        book2->set_auther_name("Morad");
        book2->set_title("Intro to algo");
        book2->set_number_of_pages(5);
        vector<string> pages2 = { "A Algo", "B Algo", "C Algo", "D Algo", "E " };
        book2->set_pages(pages2);

        books.push_back(book2);

        Book* book3 = new Book();
        book3->set_id(3);
        book3->set_auther_name("Morad");
        book3->set_title("Data Structures in C++");
        book3->set_number_of_pages(5);
        vector<string> pages3 = { "A Data", "B Data", "C Data", "D Data", "E Data" };
        book3->set_pages(pages3);

        books.push_back(book3);
    }

    void view_profile() const {
        cout << setw(40) << left << "" << '\n' << name << " | Profile.\n\n";
        cout << "1. Name: " << name << '\n';
        cout << "2. Email: " << email << '\n';
    }

    void add_book() {
        Book* book = new Book();
        cout << "Enter book title: ";
        string title;
        cin >> title;
        book->set_title(title);

        cout << "Enter author name: ";
        string author;
        cin >> author;
        book->set_auther_name(author);

        cout << "Enter number of pages: ";
        int num_pages;
        cin >> num_pages;
        book->set_number_of_pages(num_pages);

        vector<string> pages(num_pages);
        cin.ignore();
        for (int i = 0; i < num_pages; i++) {
            cout << "Enter content of page " << i + 1 << ": ";
            getline(cin, pages[i]);
        }
        book->set_pages(pages);

        books.push_back(book);
        cout << "Book added successfully!\n";
    }

    vector<Book*> get_books() {
        return books;
    }

    void set_books(vector<Book*> _books) {
        books = _books;
    }

    bool get_is_admin() const {
        return is_admin;
    }
    void set_is_admin(bool is) {
        is_admin = is;
    }

    string get_user_name() const {
        return user_name;
    }

    string get_password() const {
        return password;
    }

};

class User {
private:
    string user_name;
    string password;
    string name;
    string email;
    vector<User*> users;
    vector<Session*> sessions;
    User* current_user = nullptr;
    SessionManager* session_manager;

public:
    User() {
        session_manager = new SessionManager(); 
    }
    
    ~User() {
        for (User* user : users) {
            if (user != nullptr) {
                delete user;
            }
        }
        users.clear();
        delete session_manager;
    }

    void load_users() {
        User* user1 = new User();
        user1->user_name = "reda";
        user1->password = "2284";
        user1->name = "Reda";
        user1->email = "reda@gmail.com";
        users.push_back(user1);

        User* user2 = new User();
        user2->user_name = "ahmed_reda";
        user2->password = "12345";
        user2->name = "Ahmed";
        user2->email = "ahreda@gmail.com";
        users.push_back(user2);

        User* user3 = new User();
        user3->user_name = "ali_reda";
        user3->password = "123456";
        user3->name = "Ali";
        user3->email = "alreda@gmail.com";
        users.push_back(user3);
    }

    void sign_up() {
        User* user = new User();
        cout << "\nEnter user name: ";
        cin >> user->user_name;

        cout << "Enter password: ";
        cin >> user->password;

        cout << "Enter your name: ";
        cin >> user->name;

        cout << "Enter email: ";
        cin >> user->email;

        users.push_back(user);
        current_user = user;
    }

    bool log_in(Admin& admin) {
        string _user_name;
        string _password;

        cout << "\nEnter your user name: ";
        cin >> _user_name;

        cout << "\nEnter your password: ";
        cin >> _password;

        if (_user_name == admin.get_user_name() && _password == admin.get_password()) {
            cout << "Admin login successful!\n";
            admin.set_is_admin(true);
            return true;
        }

        for (const auto& user : users) {
            if (user->user_name == _user_name && user->password == _password) {
                current_user = user;
                cout << "User login successful!\n";
                return true;
            }
        }

        cout << "Invalid user name or password! Try again...\n";
        return log_in(admin);
    }

    void view_profile() const {
        if (current_user != nullptr) {
            cout << "\nUser Name: " << current_user->user_name << '\n';
            cout << "Name: " << current_user->name << '\n';
            cout << "Email: " << current_user->email << '\n';
        }
        else {
            cout << "No user is currently logged in.\n";
        }
    }

    void select_from_available_books() {
        Admin* admin = new Admin();
        admin->load_books();

        cout << "Our current collection of books:\n";
        for (int i = 0; i < (int)admin->get_books().size(); ++i)
            cout << i + 1 << ". " << admin->get_books()[i]->get_title() << '\n';

        cout << "Which book would you like to read?\n";
        cout << "Enter a number in the range 1 to " << admin->get_books().size() << ":\n";

        int num;
        cin >> num;

        if (num < 1 || num >(int)admin->get_books().size()) {
            cout << "Invalid book selection. Please try again.\n";
            return;
        }

        Book* selectedBook = admin->get_books()[num - 1];
        session_manager->start_session(selectedBook);

        int session_id = session_manager->get_sessions().size() - 1;
        int choice;

        while (true) {
            cout << "\nChoose an option:\n";
            cout << "1. Next page\n";
            cout << "2. Previous page\n";
            cout << "3. Stop reading\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 3) {
                session_manager->navigate_session(session_id, choice);
                break;
            }

            session_manager->navigate_session(session_id, choice);
        }
    }

    void list_reading_history() {
        session_manager->list_sessions();
    }
};

class OnlineBookReaderSystem {
private:
    Admin admin;
    User user;

public:
    void run() {
        user.load_users();

        while (true) {
            int choice;
            cout << setw(40) << left << "" << "-------------------\n";
            cout << setw(40) << left << "" << "Main menu\n\n";
            cout << setw(40) << left << "" << "1. Log in.\n";
            cout << setw(40) << left << "" << "2. Sign up.\n";
            cout << setw(40) << left << "" << "3. Exit.\n";
            cout << setw(40) << left << "" << "-------------------\n";
            cout << "\nEnter your choice: ";
            cin >> choice;

            if (choice == 1) {
                if (!user.log_in(admin)) {
                    continue;
                }

                if (admin.get_is_admin()) {
                    while (true) {
                        cout << setw(40) << left << "" << "-------------------\n";
                        cout << setw(40) << left << "" << "Admin view menu\n\n";
                        cout << setw(40) << left << "" << "1. View profile.\n";
                        cout << setw(40) << left << "" << "2. Add book.\n";
                        cout << setw(40) << left << "" << "3. Log out.\n";
                        cout << setw(40) << left << "" << "-------------------\n";
                        cout << "\nEnter your choice: ";
                        cin >> choice;

                        if (choice == 1)
                            admin.view_profile();
                        else if (choice == 2)
                            admin.add_book();
                        else if (choice == 3) {
                            cout << "Logging out...\n";
                            admin.set_is_admin(false);
                            break;
                        }
                        else {
                            cout << "Invalid choice. Try again...\n";
                        }
                    }
                }
                else {
                    while (true) {
                        cout << setw(40) << left << "" << "-------------------\n";
                        cout << setw(40) << left << "" << "User view menu\n\n";
                        cout << setw(40) << left << "" << "1. View profile.\n";
                        cout << setw(40) << left << "" << "2. List & select from my reading history.\n";
                        cout << setw(40) << left << "" << "3. List & select from the available books.\n";
                        cout << setw(40) << left << "" << "4. Log out.\n";
                        cout << setw(40) << left << "" << "-------------------\n";
                        cout << "\nEnter your choice: ";
                        cin >> choice;

                        if (choice == 1)
                            user.view_profile();
                        else if (choice == 2)
                            user.list_reading_history();
                        else if (choice == 3)
                            user.select_from_available_books();
                        else if (choice == 4) {
                            cout << "Logging out...\n";
                            break;
                        }
                        else {
                            cout << "Invalid choice. Please try again.\n";
                        }
                    }
                }
            }
            else if (choice == 2) {
                user.sign_up();
            }
            else if (choice == 3) {
                cout << "Exiting the system...\n";
                break;
            }
            else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

int main() {
    OnlineBookReaderSystem system;
    system.run();
    return 0;
}