# Library Management System in C

This is a simple console-based Library Management System implemented in the C programming language. The program allows users to perform various library-related tasks, such as borrowing books, returning books, adding books to the inventory, deleting books, and displaying the available books.

## Table of Contents

- [Features](#features)
- [How to Use](#how-to-use)
- [Compiled Executable](#compiled-executable)
- [Code Overview](#code-overview)
- [File Structure](#file-structure)
- [License](#license)

## Features

The Library Management System offers the following features:

1. **Borrow Book:** Users can borrow books from the library. They need to enter the Book ID and the quantity they want to borrow. The system checks the availability of the book and updates the inventory accordingly.

2. **Return Book:** Users can return borrowed books to the library. They need to enter the Book ID and the quantity they want to return. The system updates the inventory with the returned books.

3. **Add Book:** Librarians can add new books to the library's inventory. They can specify the book's title, author, category, and quantity. The system generates a unique Book ID for the new book.

4. **Delete Book:** Librarians can delete books from the inventory. They need to enter the Book ID of the book they want to delete. The system prompts for confirmation before deleting the book.

5. **Display Books:** Users can view a table of available books in the library, including details like Book ID, title, author, category, and quantity.

6. **Data Persistence:** The system stores book data in a CSV file, allowing data to be saved between program runs.

## How to Use

1. Download the compiled executable for Windows from the [library_management_system.exe](https://github.com/TheFastest599/library-managenent-system/releases/) file.

2. Run the executable by double-clicking on it or using the command line.

3. Follow the on-screen menu to perform various library management tasks.

4. Data such as book details and inventory are stored in a CSV file (`Books_data.csv`) for persistence.

## Compiled Executable

You can download the compiled executable for Windows: [library_management_system.exe](https://github.com/TheFastest599/library-managenent-system/releases/).

## Code Overview

The code is organized as follows:

- `struct Books`: Defines a structure to store book information, including Book ID, title, author, category, and quantity.

- `struct node`: Defines a structure for linked list nodes to store book records.

- `loadData()`: Loads book data from a CSV file into a linked list.

- `printData()`: Prints the available book data in a tabular format.

- `clearInputBuffer()`: Clears the input buffer to prevent unwanted input.

- `idGenerator()`: Generates a unique Book ID based on the book's category and a random number.

- `writeInFile()`: Writes book data back to the CSV file for data persistence.

- `main()`: The main function that drives the program. It displays a menu for various library management tasks and handles user input.

## File Structure

- `library_management_system.exe`: The compiled executable for Windows.
- `Books_data.csv`: A CSV file used to store book data for data persistence.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
