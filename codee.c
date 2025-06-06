#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 100

typedef struct {
    int id;
    char title[100];
    char author[100];
    int quantity;
} Book;

typedef struct {
    int id;
    char name[100];
    int borrowedBookId;
} Student;

Book books[MAX_BOOKS];
Student students[MAX_USERS];

int totalBooks = 0;
int totalStudents = 0;

// Function declarations
void loadBooks();
void saveBooks();
void loadStudents();
void saveStudents();
void addBook();
void viewBooks();
void deleteBook();
void searchBook();
void addStudent();
void viewStudents();
void borrowBook();
void returnBook();
void menu();

int main() {
    loadBooks();
    loadStudents();
    menu();
    saveBooks();
    saveStudents();
    return 0;
}

// Menu
void menu() {
    int choice;
    while (1) {
        printf("\n------ Library Management ------\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Delete Book\n");
        printf("4. Search Book\n");
        printf("5. Add Student\n");
        printf("6. View Students\n");
        printf("7. Borrow Book\n");
        printf("8. Return Book\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: deleteBook(); break;
            case 4: searchBook(); break;
            case 5: addStudent(); break;
            case 6: viewStudents(); break;
            case 7: borrowBook(); break;
            case 8: returnBook(); break;
            case 9: return;
            default: printf("Invalid choice!\n");
        }
    }
}

// Load and Save Books
void loadBooks() {
    FILE *fp = fopen("books.dat", "rb");
    if (fp != NULL) {
        fread(&totalBooks, sizeof(int), 1, fp);
        fread(books, sizeof(Book), totalBooks, fp);
        fclose(fp);
    }
}

void saveBooks() {
    FILE *fp = fopen("books.dat", "wb");
    if (fp != NULL) {
        fwrite(&totalBooks, sizeof(int), 1, fp);
        fwrite(books, sizeof(Book), totalBooks, fp);
        fclose(fp);
    }
}

// Load and Save Students
void loadStudents() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp != NULL) {
        fread(&totalStudents, sizeof(int), 1, fp);
        fread(students, sizeof(Student), totalStudents, fp);
        fclose(fp);
    }
}

void saveStudents() {
    FILE *fp = fopen("students.dat", "wb");
    if (fp != NULL) {
        fwrite(&totalStudents, sizeof(int), 1, fp);
        fwrite(students, sizeof(Student), totalStudents, fp);
        fclose(fp);
    }
}

// Book Operations
void addBook() {
    if (totalBooks >= MAX_BOOKS) {
        printf("Book limit reached!\n");
        return;
    }
    Book b;
    b.id = totalBooks + 1;
    printf("Enter title: ");
    fgets(b.title, 100, stdin);
    b.title[strcspn(b.title, "\n")] = 0;
    printf("Enter author: ");
    fgets(b.author, 100, stdin);
    b.author[strcspn(b.author, "\n")] = 0;
    printf("Enter quantity: ");
    scanf("%d", &b.quantity);
    getchar();

    books[totalBooks++] = b;
    printf("Book added successfully.\n");
}

void viewBooks() {
    if (totalBooks == 0) {
        printf("No books available.\n");
        return;
    }
    printf("\n%-5s %-30s %-30s %-10s\n", "ID", "Title", "Author", "Quantity");
    for (int i = 0; i < totalBooks; i++) {
        printf("%-5d %-30s %-30s %-10d\n", books[i].id, books[i].title, books[i].author, books[i].quantity);
    }
}

void deleteBook() {
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);
    int found = 0;

    for (int i = 0; i < totalBooks; i++) {
        if (books[i].id == id) {
            found = 1;
            for (int j = i; j < totalBooks - 1; j++) {
                books[j] = books[j + 1];
            }
            totalBooks--;
            printf("Book deleted.\n");
            break;
        }
    }

    if (!found)
        printf("Book not found.\n");
}

void searchBook() {
    char title[100];
    printf("Enter title to search: ");
    getchar();
    fgets(title, 100, stdin);
    title[strcspn(title, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < totalBooks; i++) {
        if (strstr(books[i].title, title) != NULL) {
            printf("Found: ID %d - %s by %s\n", books[i].id, books[i].title, books[i].author);
            found = 1;
        }
    }

    if (!found)
        printf("Book not found.\n");
}

// Student Operations
void addStudent() {
    if (totalStudents >= MAX_USERS) {
        printf("Student limit reached!\n");
        return;
    }

    Student s;
    s.id = totalStudents + 1;
    printf("Enter student name: ");
    fgets(s.name, 100, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    s.borrowedBookId = -1;

    students[totalStudents++] = s;
    printf("Student added successfully.\n");
}

void viewStudents() {
    if (totalStudents == 0) {
        printf("No students registered.\n");
        return;
    }

    printf("\n%-5s %-30s %-15s\n", "ID", "Name", "Borrowed Book ID");
    for (int i = 0; i < totalStudents; i++) {
        printf("%-5d %-30s %-15d\n", students[i].id, students[i].name, students[i].borrowedBookId);
    }
}

void borrowBook() {
    int sid, bid;
    printf("Enter student ID: ");
    scanf("%d", &sid);
    printf("Enter book ID: ");
    scanf("%d", &bid);

    if (sid < 1 || sid > totalStudents || bid < 1 || bid > totalBooks) {
        printf("Invalid ID.\n");
        return;
    }

    Student *s = &students[sid - 1];
    Book *b = &books[bid - 1];

    if (s->borrowedBookId != -1) {
        printf("Student already borrowed a book.\n");
        return;
    }

    if (b->quantity <= 0) {
        printf("Book not available.\n");
        return;
    }

    s->borrowedBookId = bid;
    b->quantity--;
    printf("Book borrowed successfully.\n");
}



  
   



   

