# Employee Database Management System
Build A Database

# MINI PROJECT REPORT

---

**"Empowerment through quality technical education"**

## AJEENKYA DY PATIL SCHOOL OF ENGINEERING

**Dr. D. Y. Patil Knowledge City, Charholi Bk., Via. Lohegaon, Pune-412105.**

**Department of Artificial Intelligence and Data Science Engineering**

---

**ACADEMIC YEAR:** 2025-26

**SUBJECT:** Data Structures (PCC-201-AID)

**CLASS:** SE-C **SEMESTER:** III

---

**TITLE OF MINI PROJECT:**

**Implementation of Employee Database Management System Using Hash Tables and Linked Lists**

---

**ROLL NO:** 1. 30 

**NAME OF STUDENT:** 1. Suyash Sonawane 

**NAME AND SIGN OF SUBJECT IN CHARGE:** Prof. Varsha Babar

---

---

# IMPLEMENTATION OF EMPLOYEE DATABASE MANAGEMENT SYSTEM USING HASH TABLES AND LINKED LISTS

---

## 1. INTRODUCTION

### 1.1 Background of the Problem

In modern organizations, efficient management of employee records is crucial for smooth operations. Companies need to store, retrieve, update, and analyze employee information quickly. Traditional linear data structures like arrays suffer from slow search operations (O(n) time complexity), especially when dealing with large datasets containing thousands of employees. As organizations scale, the need for faster data retrieval becomes paramount.

Employee databases must support operations such as quick lookup by employee ID, filtering by department, salary-based sorting, and generating analytical reports. These requirements demand a data structure that combines speed, flexibility, and efficient memory utilization.

### 1.2 Importance of Data Structures in Solving It

Data structures play a vital role in optimizing database operations. Hash tables provide average O(1) time complexity for insertion, deletion, and search operations, making them ideal for employee ID-based lookups. When combined with linked lists for collision resolution (chaining), the system maintains efficiency even with hash collisions.

Linked lists provide dynamic memory allocation, eliminating the need for pre-defined array sizes and allowing the database to grow as needed. This combination ensures that the system remains fast, scalable, and memory-efficient.

### 1.3 Objectives of the Project

The primary objectives of this project are:

1. To implement a hash table-based employee database with O(1) average-case search complexity
2. To handle hash collisions efficiently using chaining with linked lists
3. To provide comprehensive employee management operations (insert, delete, search, update)
4. To generate department-wise analytics and salary reports for management decision-making
5. To demonstrate practical applications of data structures in real-world scenarios
6. To analyze time and space complexity of various database operations
7. To develop a user-friendly menu-driven interface for database interactions

### 1.4 Scope and Limitations

**Scope:**

- Support for multiple departments within a single company
- Storage of employee information including ID, name, department, and salary
- Fast retrieval using hash-based indexing
- Department-wise filtering and analytics
- Sorting capabilities by salary and department
- Company-wide dashboard with workforce metrics
- Memory-efficient storage using dynamic allocation

**Limitations:**

- Hash table size is fixed at compile time (TABLE_SIZE = 10)
- No persistent storage (data is lost after program termination)
- Simple hash function may cause uneven distribution for certain ID patterns
- Bubble sort (O(n²)) used for sorting; can be optimized with merge/quick sort
- No support for concurrent access (single-user system)
- Limited to text-based console interface (no GUI)

---

## 2. PROBLEM DEFINITION

**Problem Statement:**

Organizations require an efficient system to manage employee records that supports fast insertion, retrieval, deletion, and analytical operations. Traditional array-based systems suffer from O(n) search time, which becomes impractical for large employee databases. The challenge is to design a system that provides near-constant time access while handling potential collisions gracefully.

**Why Hash Tables with Linked List Chaining?**

1. **Hash Tables:** Provide O(1) average-case time complexity for lookups using a hash function that maps employee IDs to array indices
2. **Linked List Chaining:** Efficiently resolves hash collisions by maintaining a linked list at each hash table index, allowing multiple employees to share the same hash value
3. **Dynamic Memory:** Linked lists eliminate fixed-size limitations, enabling the database to grow dynamically
4. **Space Efficiency:** Only allocates memory when needed, unlike pre-allocated arrays

This combination offers the best balance between speed (O(1) average search), flexibility (dynamic sizing), and collision handling (chaining).

---

## 3. SYSTEM ANALYSIS AND DESIGN

### 3.1 System Requirements

#### (a) Hardware Requirements:

- **Processor:** Intel Core i3 or higher (any modern processor)
- **RAM:** Minimum 2 GB (4 GB recommended)
- **Storage:** 50 MB free space for source code and executable
- **Display:** Standard console/terminal output (80x25 minimum)

#### (b) Software Requirements:

- **Operating System:** Windows 10/11, Linux (Ubuntu 20.04+), macOS 10.15+
- **Compiler:** GCC (GNU Compiler Collection) version 7.0 or higher
- **Programming Language:** C (ANSI C99 standard)
- **Text Editor/IDE:** VS Code, Code::Blocks, or any C-compatible editor
- **Terminal:** Command prompt, PowerShell, or Linux terminal

### 3.2 Input / Output Description

#### Input:

1. **Company Setup (Initial):**

   - Company name (string, max 100 characters)
   - Number of departments (integer, 1-20)
   - Department names (strings, max 30 characters each)

2. **Employee Data:**

   - Employee ID (integer, unique identifier)
   - Employee name (string, max 50 characters)
   - Department (string, must match predefined departments)
   - Salary (float, in rupees)

3. **Operations:**
   - Menu choices (integers 1-12)
   - Search queries (ID or department name)
   - Delete requests (employee ID)

#### Output:

1. **Formatted Tables:**

   - Employee directory with ID, name, department, salary
   - Department-wise analytics showing count, total salary, average salary
   - Sorted employee lists (by salary or department)

2. **Analytics & Reports:**

   - Company dashboard with workforce metrics
   - Salary distribution analysis
   - Hash table structure visualization
   - Time complexity analysis

3. **Status Messages:**
   - Success confirmations (employee added/deleted)
   - Error messages (duplicate ID, invalid department)
   - System information (load factor, memory usage)

### 3.3 Algorithms / Logic

#### Algorithm 1: Hash Function

```
ALGORITHM hashFunction(id)
INPUT: Employee ID (integer)
OUTPUT: Hash index (0 to TABLE_SIZE-1)

1. index ← id % TABLE_SIZE
2. RETURN index

Time Complexity: O(1)
```

#### Algorithm 2: Insert Employee

```
ALGORITHM insertEmployee(db, id, name, dept, salary)
INPUT: Database, employee details
OUTPUT: Success/Failure message

1. Validate department against company departments
2. IF department invalid THEN
     Display error and return
3. index ← hashFunction(id)
4. Create newEmployee node with given details
5. IF memory allocation fails THEN
     Display error and return
6. temp ← db.table[index]
7. WHILE temp ≠ NULL DO
     IF temp.id == id THEN
        Display "Duplicate ID" error
        Free newEmployee
        RETURN
     temp ← temp.next
8. newEmployee.next ← db.table[index]
9. db.table[index] ← newEmployee
10. Increment db.count
11. Update company statistics
12. Display success message

Time Complexity: O(1) average, O(n) worst (all collisions)
```

#### Algorithm 3: Search Employee by ID

```
ALGORITHM searchEmployee(db, id)
INPUT: Database, employee ID
OUTPUT: Employee pointer or NULL

1. index ← hashFunction(id)
2. temp ← db.table[index]
3. WHILE temp ≠ NULL DO
     IF temp.id == id THEN
        RETURN temp
     temp ← temp.next
4. RETURN NULL (not found)

Time Complexity: O(1) average, O(n) worst
```

#### Algorithm 4: Delete Employee

```
ALGORITHM deleteEmployee(db, id)
INPUT: Database, employee ID
OUTPUT: Success/Failure message

1. index ← hashFunction(id)
2. temp ← db.table[index]
3. prev ← NULL
4. WHILE temp ≠ NULL DO
     IF temp.id == id THEN
        IF prev == NULL THEN
           db.table[index] ← temp.next
        ELSE
           prev.next ← temp.next
        Update company statistics
        Free temp
        Decrement db.count
        Display success
        RETURN
     prev ← temp
     temp ← temp.next
5. Display "Not found" error

Time Complexity: O(1) average, O(n) worst
```

#### Algorithm 5: Sort by Salary (Bubble Sort)

```
ALGORITHM sortBySalary(arr, n)
INPUT: Array of employee pointers, size n
OUTPUT: Sorted array (ascending order)

1. FOR i = 0 TO n-2 DO
     FOR j = 0 TO n-i-2 DO
        IF arr[j].salary > arr[j+1].salary THEN
           Swap arr[j] and arr[j+1]

Time Complexity: O(n²)
Space Complexity: O(1) (in-place sorting)
```

#### Algorithm 6: Search by Department

```
ALGORITHM searchByDepartment(db, dept)
INPUT: Database, department name
OUTPUT: List of employees in that department

1. found ← 0
2. totalSalary ← 0
3. FOR i = 0 TO TABLE_SIZE-1 DO
     temp ← db.table[i]
     WHILE temp ≠ NULL DO
        IF temp.department == dept THEN
           Display temp details
           found ← found + 1
           totalSalary ← totalSalary + temp.salary
        temp ← temp.next
4. IF found > 0 THEN
     Display statistics (count, total, average)
   ELSE
     Display "No employees found"

Time Complexity: O(n) - must scan entire database
```

### 3.4 Flowchart / Block Diagram

```
                    START
                      |
                      ▼
          ┌─────────────────────┐
          │  Initialize Database│
          │   (Hash Table + LL) │
          └──────────┬──────────┘
                     ▼
          ┌─────────────────────┐
          │   Company Setup:    │
          │  - Name             │
          │  - Departments      │
          └──────────┬──────────┘
                     ▼
          ┌─────────────────────┐
          │   Display Menu      │
          │   (12 Options)      │
          └──────────┬──────────┘
                     ▼
          ┌─────────────────────┐
          │  Get User Choice    │
          └──────────┬──────────┘
                     ▼
         ┌──────────────────────────┐
         │   Switch (choice)        │
         └───┬──────────────────────┘
             │
    ┌────────┼────────┬────────┬────────┬────────┐
    ▼        ▼        ▼        ▼        ▼        ▼
┌───────┐ ┌──────┐ ┌──────┐ ┌──────┐ ┌──────┐ ┌──────┐
│INSERT │ │SEARCH│ │DELETE│ │DISPLAY│ │SORT  │ │ANALYTICS│
└───┬───┘ └───┬──┘ └───┬──┘ └───┬──┘ └───┬──┘ └───┬───┘
    │         │        │        │        │        │
    │         ▼        ▼        ▼        ▼        ▼
    │   ┌─────────────────────────────────────────┐
    │   │      Calculate Hash Index               │
    │   │      index = id % TABLE_SIZE            │
    │   └─────────────┬───────────────────────────┘
    │                 ▼
    │   ┌─────────────────────────────────────────┐
    │   │   Access Hash Table at index            │
    │   │   Handle Collisions (Chaining)          │
    │   └─────────────┬───────────────────────────┘
    │                 ▼
    │   ┌─────────────────────────────────────────┐
    │   │   Perform Operation on Linked List      │
    │   │   (Insert/Search/Delete at chain)       │
    │   └─────────────┬───────────────────────────┘
    │                 ▼
    └─────────────────┼─────────────────────────────┐
                      ▼                             ▼
          ┌─────────────────────┐      ┌────────────────┐
          │  Display Result/    │      │   Exit = 12?   │
          │  Error Message      │      │                │
          └──────────┬──────────┘      └───────┬────────┘
                     │                         │ Yes
                     ▼                         ▼
          ┌─────────────────────┐   ┌──────────────────┐
          │  Continue? (Menu)   │   │  Free Memory     │
          └──────────┬──────────┘   │  Show Statistics │
                     │               └────────┬─────────┘
                     │                        ▼
                     └────────────────────►  END
```

### 3.5 Data Structure Used

#### Primary Data Structure: **Hash Table with Chaining**

**Structure Definition:**

```c
// Employee Node (Linked List)
typedef struct Employee {
    int id;                    // Primary key
    char name[50];             // Employee name
    char department[30];       // Department
    float salary;              // Salary
    struct Employee* next;     // Pointer to next (chaining)
} Employee;

// Hash Table
typedef struct {
    Employee* table[TABLE_SIZE];  // Array of LL heads
    int count;                     // Total employees
} EmployeeDB;
```

**Why This Data Structure?**

1. **Hash Table Benefits:**

   - O(1) average-case search/insert/delete
   - Direct access using computed index
   - Efficient memory usage with dynamic sizing

2. **Linked List Chaining Benefits:**

   - Handles collisions elegantly
   - No need for probing or rehashing
   - Dynamic growth without table resizing
   - Simple implementation

3. **Combined Advantages:**
   - Fast lookups (hash table)
   - Flexible collision handling (linked lists)
   - No wasted space (dynamic allocation)
   - Scalable to thousands of records

**Operations Supported:**

| Operation          | Description          | Time Complexity      |
| ------------------ | -------------------- | -------------------- |
| `hashFunction(id)` | Compute hash index   | O(1)                 |
| `insertEmployee()` | Add new employee     | O(1) avg, O(n) worst |
| `searchEmployee()` | Find by ID           | O(1) avg, O(n) worst |
| `deleteEmployee()` | Remove employee      | O(1) avg, O(n) worst |
| `searchByDept()`   | Filter by department | O(n)                 |
| `sortBySalary()`   | Sort employees       | O(n²)                |
| `displayAll()`     | Show all records     | O(n)                 |

**Hash Function:**

```
h(k) = k mod TABLE_SIZE
```

- Simple division method
- Distributes keys across TABLE_SIZE buckets
- Example: ID=105 → 105%10 = Index 5

**Collision Resolution:**

- **Method:** Chaining (linked lists at each index)
- **Example:** IDs 101 and 111 both hash to index 1
  - Index[1] → [111] → [101] → NULL

---

## 4. IMPLEMENTATION

### 4.1 Code Structure

The implementation consists of the following components:

1. **Data Structures:** Employee struct, EmployeeDB struct, Company struct
2. **Hash Operations:** hashFunction, insertEmployee, searchEmployee, deleteEmployee
3. **Utility Functions:** Company setup, input validation, memory management
4. **Display Functions:** Formatted tables, analytics reports, dashboard
5. **Sorting Functions:** Bubble sort by salary/department
6. **Analytics Functions:** Department reports, company metrics
7. **Main Menu:** Interactive user interface

### 4.2 Input/Output Snapshots

#### Snapshot 1: Company Initialization

```
╔═══════════════════════════════════════════════════════════╗
║     EMPLOYEE DATABASE MANAGEMENT SYSTEM                   ║
║  Using Hash Tables & Linked Lists (Chaining)              ║
╚═══════════════════════════════════════════════════════════╝

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
              COMPANY SETUP & INITIALIZATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

📋 Enter Company Name: TECH SOLUTIONS PVT LTD

🏢 How many departments does TECH SOLUTIONS have? (1-20): 4

📂 Enter 4 Department Names:
  1. IT
  2. HR
  3. FINANCE
  4. MARKETING

✅ Company setup completed successfully!

╔═══════════════════════════════════════════════════════════╗
║                   COMPANY PROFILE                         ║
╠═══════════════════════════════════════════════════════════╣
║  Company Name    : TECH SOLUTIONS PVT LTD                 ║
║  Total Depts     : 4                                      ║
║  Departments     : IT                                     ║
║                     HR                                     ║
║                     FINANCE                                ║
║                     MARKETING                              ║
╚═══════════════════════════════════════════════════════════╝

✓ Database initialized with Hash Table (Size: 10)
✓ Ready to add employees!
```

#### Snapshot 2: Adding Employee

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
                  ADD NEW EMPLOYEE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

📋 Employee ID: 101
👤 Employee Name: Rajesh Kumar
🏢 Department (IT, HR, FINANCE, MARKETING): IT
💰 Salary (₹): 65000

✅ SUCCESS: Employee added to database!
┌─────────────────────────────────────────────────────────┐
│  ID         : 101                                       │
│  Name       : Rajesh Kumar                              │
│  Department : IT                                        │
│  Salary     : ₹65000.00                                 │
│  Hash Index : 1                                         │
└─────────────────────────────────────────────────────────┘
```

#### Snapshot 3: Display All Employees

```
╔═══════════════════════════════════════════════════════════╗
║        TECH SOLUTIONS - EMPLOYEE DIRECTORY                ║
╠═══════════════════════════════════════════════════════════╣
║  Total Employees: 7                                       ║
╚═══════════════════════════════════════════════════════════╝

┌──────┬────────────────────────┬───────────────┬──────────────┐
│  ID  │         NAME           │  DEPARTMENT   │    SALARY    │
├──────┼────────────────────────┼───────────────┼──────────────┤
│ 101  │ Rajesh Kumar           │ IT            │ ₹65000.00    │
│ 102  │ Priya Sharma           │ HR            │ ₹55000.00    │
│ 103  │ Amit Patel             │ FINANCE       │ ₹70000.00    │
│ 104  │ Sneha Reddy            │ IT            │ ₹68000.00    │
│ 105  │ Vikram Singh           │ MARKETING     │ ₹60000.00    │
│ 111  │ Anjali Mehta           │ IT            │ ₹72000.00    │
│ 112  │ Rohan Gupta            │ HR            │ ₹58000.00    │
└──────┴────────────────────────┴───────────────┴──────────────┘
```

#### Snapshot 4: Hash Table Structure

```
╔═══════════════════════════════════════════════════════════╗
║          HASH TABLE STRUCTURE (Internal View)             ║
╠═══════════════════════════════════════════════════════════╣
║  Shows collision chains and hash distribution             ║
╚═══════════════════════════════════════════════════════════╝

Index [0]: ∅ (Empty)
Index [1]: → [ID:111, Anjali Mehta] → [ID:101, Rajesh Kumar] → NULL
Index [2]: → [ID:112, Rohan Gupta] → [ID:102, Priya Sharma] → NULL
Index [3]: → [ID:103, Amit Patel] → NULL
Index [4]: → [ID:104, Sneha Reddy] → NULL
Index [5]: → [ID:105, Vikram Singh] → NULL
Index [6]: ∅ (Empty)
Index [7]: ∅ (Empty)
Index [8]: ∅ (Empty)
Index [9]: ∅ (Empty)

📊 Hash Table Statistics:
  • Total Buckets    : 10
  • Used Buckets     : 5
  • Empty Buckets    : 5
  • Max Chain Length : 2
  • Load Factor      : 70.00%
```

#### Snapshot 5: Department Analytics

```
╔═══════════════════════════════════════════════════════════╗
║              DEPARTMENT-WISE ANALYTICS                    ║
╚═══════════════════════════════════════════════════════════╝

┌───────────────────┬──────────┬───────────────┬─────────────┐
│    DEPARTMENT     │ EMP COUNT│  TOTAL SALARY │ AVG SALARY  │
├───────────────────┼──────────┼───────────────┼─────────────┤
│ IT                │    3     │ ₹205000.00    │ ₹68333.33   │
│ HR                │    2     │ ₹113000.00    │ ₹56500.00   │
│ FINANCE           │    1     │ ₹70000.00     │ ₹70000.00   │
│ MARKETING         │    1     │ ₹60000.00     │ ₹60000.00   │
└───────────────────┴──────────┴───────────────┴─────────────┘

💰 Salary Insights:
  🔝 Highest Avg Salary: FINANCE (₹70000.00)
  📉 Lowest Avg Salary : HR (₹56500.00)
```

#### Snapshot 6: Company Dashboard

```
╔═══════════════════════════════════════════════════════════╗
║             COMPANY DASHBOARD & METRICS                   ║
╠═══════════════════════════════════════════════════════════╣
║  Company: TECH SOLUTIONS PVT LTD                          ║
╚═══════════════════════════════════════════════════════════╝

┌─────────────────────────────────────────────────────────┐
│  📊 WORKFORCE METRICS                                   │
├─────────────────────────────────────────────────────────┤
│  Total Employees          : 7                           │
│  Total Departments        : 4                           │
│  Total Salary Expense     : ₹448000.00                  │
│  Average Salary           : ₹64000.00                   │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│  💵 SALARY DISTRIBUTION                                 │
├─────────────────────────────────────────────────────────┤
│  Below ₹50,000           : 0                            │
│  ₹50,000 - ₹70,000       : 5                            │
│  Above ₹70,000           : 2                            │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│  ⚙️  DATABASE PERFORMANCE METRICS                       │
├─────────────────────────────────────────────────────────┤
│  Hash Table Size         : 10                           │
│  Load Factor             : 70.00%                       │
│  Search Complexity       : O(1) average, O(n) worst     │
│  Insert Complexity       : O(1) average, O(n) worst     │
└─────────────────────────────────────────────────────────┘
```

#### Snapshot 7: Sorted by Salary

```
╔═══════════════════════════════════════════════════════════╗
║                SORTED EMPLOYEE LIST                       ║
╠═══════════════════════════════════════════════════════════╣
║  Sorted By: SALARY (Ascending Order)                      ║
╚═══════════════════════════════════════════════════════════╝

┌─────┬──────┬────────────────────────┬─────────────┬────────────┐
│ RANK│  ID  │         NAME           │ DEPARTMENT  │   SALARY   │
├─────┼──────┼────────────────────────┼─────────────┼────────────┤
│ 1   │ 102  │ Priya Sharma           │ HR          │ ₹55000.00  │
│ 2   │ 112  │ Rohan Gupta            │ HR          │ ₹58000.00  │
│ 3   │ 105  │ Vikram Singh           │ MARKETING   │ ₹60000.00  │
│ 4   │ 101  │ Rajesh Kumar           │ IT          │ ₹65000.00  │
│ 5   │ 104  │ Sneha Reddy            │ IT          │ ₹68000.00  │
│ 6   │ 103  │ Amit Patel             │ FINANCE     │ ₹70000.00  │
│ 7   │ 111  │ Anjali Mehta           │ IT          │ ₹72000.00  │
└─────┴──────┴────────────────────────┴─────────────┴────────────┘

⏱  Time Complexity: O(n²) - Bubble Sort Algorithm
```

---

## 5. APPLICATIONS

### 5.1 Real-World Applications of Hash Tables

1. **Database Management Systems:**

   - Employee databases (as implemented in this project)
   - Customer relationship management (CRM) systems
   - Inventory management systems
   - Student information systems

2. **Caching Systems:**

   - Web browser caches (URL → cached page)
   - DNS resolution (domain name → IP address)
   - Database query caching
   - Content delivery networks (CDN)

3. **Symbol Tables in Compilers:**

   - Variable name lookup during compilation
   - Function address resolution
   - Type checking and scope management

4. **Password Storage:**

   - User authentication systems
   - Hashing passwords before database storage
   - Session management in web applications

5. **Dictionary Implementations:**
   - Spell checkers
   - Language translation tools
   - Autocomplete suggestions
   - Search engines (keyword indexing)

### 5.2 Real-World Applications of Linked Lists

1. **Dynamic Memory Management:**

   - Operating system memory allocation
   - Garbage collection in programming languages
   - Free memory pool management

2. **Undo/Redo Functionality:**

   - Text editors (Microsoft Word, VS Code)
   - Photo editing software (Photoshop)
   - Browser history (back/forward navigation)

3. **Music/Video Playlists:**

   - Media players (Spotify, YouTube)
   - Circular linked lists for repeat mode
   - Doubly linked lists for previous/next track

4. **Task Scheduling:**

   - Operating system process scheduling
   - Print job queues
   - Network packet queuing

5. **Blockchain Technology:**
   - Each block points to the previous block
   - Cryptocurrency transaction chains
   - Distributed ledger systems

### 5.3 Applications Specific to This Project

1. **Human Resources Management:**

   - Employee onboarding and offboarding
   - Payroll processing systems
   - Performance review tracking

2. **Corporate Analytics:**

   - Department-wise budget allocation
   - Salary benchmarking and analysis
   - Workforce planning and forecasting

3. **Recruitment Systems:**

   - Candidate database management
   - Resume parsing and storage
   - Applicant tracking systems (ATS)

4. **Attendance and Payroll:**
   - Employee time tracking
   - Salary calculation engines
   - Leave management systems

---

## 6. ADVANTAGES AND LIMITATIONS

### 6.1 Advantages

#### Performance Benefits:

1. **Fast Lookups:** O(1) average-case search time for employee ID queries
2. **Efficient Insertion:** Adding new employees takes constant time on average
3. **Quick Deletion:** Removing employees is fast with hash-based access
4. **Scalable:** Can handle thousands of records efficiently with proper hash table sizing

#### Memory Benefits:

1. **Dynamic Allocation:** Memory grows only when needed (no wasted space)
2. **Flexible Sizing:** Linked lists eliminate fixed-size array limitations
3. **Efficient Storage:** Only stores actual employee records without gaps

#### Functional Benefits:

1. **Collision Handling:** Chaining gracefully manages hash collisions
2. **Easy Traversal:** Can iterate through all employees linearly
3. **Department Filtering:** Linear search supports department-based queries
4. **Comprehensive Analytics:** Generates detailed reports and metrics

#### User Experience:

1. **Interactive Interface:** Menu-driven system with clear options
2. **Input Validation:** Checks for duplicate IDs and invalid departments
3. **Professional Output:** Formatted tables with box-drawing characters
4. **Real-time Statistics:** Company dashboard shows live metrics

### 6.2 Limitations

#### Design Limitations:

1. **Fixed Hash Table Size:** TABLE_SIZE is defined at compile time (requires recompilation to change)
2. **Simple Hash Function:** Division method may cause clustering for certain ID patterns
3. **No Rehashing:** Table doesn't automatically resize when load factor exceeds threshold
4. **Bubble Sort Inefficiency:** O(n²) sorting algorithm; slow for large datasets

#### Functional Limitations:

1. **No Data Persistence:** Database is lost when program terminates (no file/database storage)
2. **Single-User System:** No support for concurrent access or multi-threading
3. \*\*Limite
