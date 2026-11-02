# Nethra Bookshop Quotation Preparation System

## Project Overview
The Nethra Bookshop Quotation Preparation System is a C++ application developed to automate book management and quotation preparation. It aims to improve the accuracy, efficiency, and user-friendliness of bookshop operations by reducing the limitations of manual processes.

## Features
- User registration and login
- Customer and administrator access
- Add, view, and search books
- Admin book management
- Prepare and print quotations
- Calculate total prices and discounts
- Store user, book, and quotation details in text files

## Technologies Used
- **Programming Language:** C++
- **Data Structures:** Structures (`struct`) and vectors
- **File Handling:** Text-file storage
- **Programming Concepts:** Functions, modularization, selection, and repetition

## User Roles

### Customer
- View and search books
- Prepare quotations
- View and print quotation details

### Administrator
- Add and manage books
- View book details
- Manage and view quotations

## Discount System
The application includes quantity-based discounts:
- 5% discount for quantities below 5
- 10% discount for quantities above 5

## Data Storage
The system stores information using text files:
- `user.txt` – User details
- `bookDetails.txt` – Book information
- `order.txt` – Quotation and order details

## Getting Started

### Prerequisites
- A C++ compiler (such as GCC or MinGW)
- An IDE or code editor (such as Visual Studio Code)

### Run the Project
1. Clone the repository:
   ```bash
   git clone YOUR_REPOSITORY_URL
   ```
2. Open the project folder in your IDE.
3. Compile the C++ source file:
   ```bash
   g++ main.cpp -o nethra_bookshop
   ```
4. Run the application:
   ```bash
   ./nethra_bookshop
   ```

   On Windows:
   ```bash
   nethra_bookshop.exe
   ```

> Replace `main.cpp` with the actual name of your C++ source file if it is different.

## Project Objectives
- Automate bookshop quotation preparation
- Improve book and quotation management
- Reduce manual errors and processing time
- Provide a simple interface for customers and administrators

## Author
**D. M. Chathurya Hiruni Gunathilaka**
