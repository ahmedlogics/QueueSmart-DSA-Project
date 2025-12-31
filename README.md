# QueueSmart: Intelligent Queue Management System 🚀

> **Course:** Data Structures and Algorithms (DSA)  
> **Tech Stack:** C++ Backend, Crow Framework, HTML/CSS/JS Frontend

![Project Status](https://img.shields.io/badge/Status-Completed-success)
![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue)
![Data Structures](https://img.shields.io/badge/DSA-Custom%20Implementation-orange)

## 📖 Project Overview
**QueueSmart** is a web-based application designed to digitize physical queuing systems (like those in banks or NADRA offices). It allows users to book tokens remotely, track their wait time in real-time, and enables administrators to serve or undo actions efficiently.

The core highlight of this project is the **manual implementation of Data Structures** from scratch without relying on standard libraries for the core logic, demonstrating the practical application of DSA concepts.

---

## ⚙️ Core Data Structures Implemented
The backend logic relies on the following custom structures:

### 1. Singly Linked List (`LinkedList.hpp`)
* **Role:** The foundational structure for dynamic memory management.
* **Why:** Allows the queue to grow and shrink dynamically without fixed size limits.
* **Complexity:** Insertion and Deletion at ends are **O(1)**.

### 2. Queue (FIFO) (`Queue.hpp`)
* **Role:** Manages the active line of users waiting for service.
* **Logic:** Users are `Enqueued` at the tail and `Dequeued` from the head.

### 3. Stack (LIFO) (`Stack.hpp`)
* **Role:** Manages the history of served tokens to enable the **"Undo"** feature.
* **Logic:** When a token is served, it is Pushed to the stack. If the admin clicks "Undo", the token is Popped and returned to the front of the Queue.

### 4. Hash Maps & Vectors
* **std::map:** Used for $O(\log n)$ routing of requests to specific branch queues (e.g., `NADRA_Gulshan`).
* **std::vector:** Acts as an in-memory database to store registered user details.

---

## 🚀 Key Features
* **User Authentication:** Secure Login and Registration system.
* **Smart Booking:** Users can select Departments and Branches to generate unique tokens.
* **Live Queue Tracking:** Real-time updates on position and estimated wait time.
* **Admin Dashboard:** Capability to Serve tokens and Undo accidental actions.
* **Responsive UI:** Modern Frontend built with HTML5, CSS3, and JavaScript.

---

## 🛠️ Installation & Setup

1.  **Clone the Repository**
    ```bash
    git clone [https://github.com/YourUsername/QueueSmart-DSA-Project.git](https://github.com/YourUsername/QueueSmart-DSA-Project.git)
    cd QueueSmart-DSA-Project
    ```

2.  **Backend Setup (C++)**
    * Ensure you have a C++ Compiler (MinGW or MSVC) and the Crow Framework installed.
    * Open the project in VS Code or Visual Studio.
    * Compile `main.cpp` along with the `src` files.
    * Run the executable. The server will start on `localhost:18080`.

3.  **Frontend Setup**
    * Navigate to the `frontend` folder.
    * Open `index.html` or `login.html` in your browser.
    * **Note:** The backend must be running for the frontend to fetch data.

---

## 📂 Project Structure
```text
├── include/           # Header files for Custom Data Structures
├── src/               # C++ Source Code (Backend Logic)
├── frontend/          # HTML, CSS, JS (User Interface)
└── bin/               # Compiled Executable







