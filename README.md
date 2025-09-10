Banking Management System

This is a C++ project that simulates a bank queue management system. It models customer arrivals, teller assignments, and customer relationships to ensure smooth and efficient operations.

✨ Features

Customer Queue Management
Uses a linked list to manage customers waiting to be served, allowing dynamic additions and removals.

Teller Management
Efficiently assigns available tellers to customers and tracks busy tellers using linked lists.

Relationship Tracking
Represents and displays customer-relative relationships with a tree data structure, useful for managing family accounts.

Dynamic Operations
Linked lists ensure flexible and memory-efficient handling of fluctuating customer and teller counts.

Simple Console Interface
Users can add customers, process them, and view their relationships through a text-based menu.

⚙️ How It Works

Linked Lists

Customer arrivals are added to a queue (FIFO order).

Idle tellers are tracked in a separate list.

Customers are assigned to tellers in a first-come, first-served manner.

Tree Structure

Each customer can have relatives linked as nodes.

Relationships (Parent, Sibling, etc.) can be added dynamically.

The tree can be traversed to clearly display all connections.

🚀 Future Enhancements

Graphical User Interface (GUI) for an intuitive experience.

Data Analytics to track peak hours, service times, and teller performance.

Database Integration for persistent storage of customer and teller records.

▶️ How to Run

Compile the code:

g++ main.cpp -o bank_system


Run the executable:

./bank_system


Follow the on-screen menu to interact with the system.

📌 Project Details

Developed by: Vivek Dhotre

Academic Year: 2024–2025

Subject: Data Structures
