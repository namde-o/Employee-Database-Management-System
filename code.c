#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10
#define MAX_NAME 50
#define MAX_DEPT 30
#define MAX_COMPANY 100
#define MAX_DEPARTMENTS 20

// Company Structure
typedef struct
{
  char name[MAX_COMPANY];
  char departments[MAX_DEPARTMENTS][MAX_DEPT];
  int deptCount;
  int totalEmployees;
  float totalSalaryExpense;
} Company;

// Employee Structure
typedef struct Employee
{
  int id;
  char name[MAX_NAME];
  char department[MAX_DEPT];
  float salary;
  struct Employee *next; // For chaining (collision handling)
} Employee;

// Hash Table Structure
typedef struct
{
  Employee *table[TABLE_SIZE];
  int count; // Total employees
} EmployeeDB;

// Global company instance
Company company;

// ========== UTILITY FUNCTIONS ==========

void toUpperCase(char *str)
{
  for (int i = 0; str[i]; i++)
  {
    str[i] = toupper(str[i]);
  }
}

void clearInputBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// ========== COMPANY SETUP ==========

void setupCompany()
{
  printf("\n");
  printf("╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║                                                                   ║\n");
  printf("║            EMPLOYEE DATABASE MANAGEMENT SYSTEM                    ║\n");
  printf("║         Using Hash Tables & Linked Lists (Chaining)               ║\n");
  printf("║                                                                   ║\n");
  printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

  printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
  printf("                     COMPANY SETUP & INITIALIZATION\n");
  printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

  printf("📋 Enter Company Name: ");
  fgets(company.name, MAX_COMPANY, stdin);
  company.name[strcspn(company.name, "\n")] = 0;
  toUpperCase(company.name);

  printf("\n🏢 How many departments does %s have? (1-%d): ", company.name, MAX_DEPARTMENTS);
  scanf("%d", &company.deptCount);
  clearInputBuffer();

  if (company.deptCount < 1 || company.deptCount > MAX_DEPARTMENTS)
  {
    company.deptCount = 5;
    printf("⚠ Invalid input! Setting default to 5 departments.\n");
  }

  printf("\n📂 Enter %d Department Names:\n", company.deptCount);
  printf("─────────────────────────────────────────────────────────────────────\n");

  for (int i = 0; i < company.deptCount; i++)
  {
    printf("  %d. ", i + 1);
    fgets(company.departments[i], MAX_DEPT, stdin);
    company.departments[i][strcspn(company.departments[i], "\n")] = 0;
    toUpperCase(company.departments[i]);
  }

  company.totalEmployees = 0;
  company.totalSalaryExpense = 0;

  printf("\n✅ Company setup completed successfully!\n");
  printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║                      COMPANY PROFILE                              ║\n");
  printf("╠═══════════════════════════════════════════════════════════════════╣\n");
  printf("║  Company Name    : %-47s║\n", company.name);
  printf("║  Total Depts     : %-47d║\n", company.deptCount);
  printf("║  Departments     : %-47s║\n", company.departments[0]);
  for (int i = 1; i < company.deptCount; i++)
  {
    printf("║                     %-47s║\n", company.departments[i]);
  }
  printf("╚═══════════════════════════════════════════════════════════════════╝\n");

  printf("\n✓ Database initialized with Hash Table (Size: %d)\n", TABLE_SIZE);
  printf("✓ Ready to add employees!\n");
}

// ========== HASH TABLE OPERATIONS ==========

int hashFunction(int id)
{
  return id % TABLE_SIZE;
}

void initDB(EmployeeDB *db)
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    db->table[i] = NULL;
  }
  db->count = 0;
}

int isDepartmentValid(const char *dept)
{
  for (int i = 0; i < company.deptCount; i++)
  {
    if (strcasecmp(dept, company.departments[i]) == 0)
    {
      return 1;
    }
  }
  return 0;
}

void insertEmployee(EmployeeDB *db, int id, const char *name,
                    const char *dept, float salary)
{

  // Validate department
  if (!isDepartmentValid(dept))
  {
    printf("\n❌ ERROR: Department '%s' not found in company!\n", dept);
    printf("💡 Available departments:\n");
    for (int i = 0; i < company.deptCount; i++)
    {
      printf("   • %s\n", company.departments[i]);
    }
    return;
  }

  int index = hashFunction(id);

  // Create new employee node
  Employee *newEmp = (Employee *)malloc(sizeof(Employee));
  if (!newEmp)
  {
    printf("❌ Memory allocation failed!\n");
    return;
  }

  newEmp->id = id;
  strncpy(newEmp->name, name, MAX_NAME - 1);
  newEmp->name[MAX_NAME - 1] = '\0';
  strncpy(newEmp->department, dept, MAX_DEPT - 1);
  newEmp->department[MAX_DEPT - 1] = '\0';
  toUpperCase(newEmp->department);
  newEmp->salary = salary;
  newEmp->next = NULL;

  // Check for duplicate ID
  if (db->table[index] != NULL)
  {
    Employee *temp = db->table[index];
    while (temp != NULL)
    {
      if (temp->id == id)
      {
        printf("❌ ERROR: Employee ID %d already exists!\n", id);
        free(newEmp);
        return;
      }
      temp = temp->next;
    }
  }

  // Insert at head of chain
  newEmp->next = db->table[index];
  db->table[index] = newEmp;

  db->count++;
  company.totalEmployees++;
  company.totalSalaryExpense += salary;

  printf("\n✅ SUCCESS: Employee added to database!\n");
  printf("┌─────────────────────────────────────────────────────────────────┐\n");
  printf("│  ID         : %-49d│\n", id);
  printf("│  Name       : %-49s│\n", name);
  printf("│  Department : %-49s│\n", newEmp->department);
  printf("│  Salary     : ₹%-48.2f│\n", salary);
  printf("│  Hash Index : %-49d│\n", index);
  printf("└─────────────────────────────────────────────────────────────────┘\n");
}

Employee *searchEmployee(EmployeeDB *db, int id)
{
  int index = hashFunction(id);
  Employee *temp = db->table[index];

  while (temp != NULL)
  {
    if (temp->id == id)
    {
      return temp;
    }
    temp = temp->next;
  }

  return NULL;
}

void deleteEmployee(EmployeeDB *db, int id)
{
  int index = hashFunction(id);
  Employee *temp = db->table[index];
  Employee *prev = NULL;

  while (temp != NULL)
  {
    if (temp->id == id)
    {
      if (prev == NULL)
      {
        db->table[index] = temp->next;
      }
      else
      {
        prev->next = temp->next;
      }

      company.totalEmployees--;
      company.totalSalaryExpense -= temp->salary;

      printf("\n✅ SUCCESS: Employee deleted from database!\n");
      printf("┌─────────────────────────────────────────────────────────────────┐\n");
      printf("│  Deleted: %-54s│\n", temp->name);
      printf("│  ID     : %-54d│\n", temp->id);
      printf("└─────────────────────────────────────────────────────────────────┘\n");

      free(temp);
      db->count--;
      return;
    }
    prev = temp;
    temp = temp->next;
  }

  printf("\n❌ ERROR: Employee ID %d not found!\n", id);
}

// ========== DISPLAY & ANALYTICS ==========

void displayAllEmployees(EmployeeDB *db)
{
  printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║                    %s - EMPLOYEE DIRECTORY", company.name);
  int padding = 52 - strlen(company.name);
  for (int i = 0; i < padding; i++)
    printf(" ");
  printf("║\n");
  printf("╠═══════════════════════════════════════════════════════════════════╣\n");
  printf("║  Total Employees: %-48d║\n", db->count);
  printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

  if (db->count == 0)
  {
    printf("⚠ Database is empty! No employees to display.\n");
    return;
  }

  printf("┌──────┬────────────────────────┬───────────────┬────────────────┐\n");
  printf("│  ID  │         NAME           │  DEPARTMENT   │     SALARY     │\n");
  printf("├──────┼────────────────────────┼───────────────┼────────────────┤\n");

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Employee *temp = db->table[i];
    while (temp != NULL)
    {
      printf("│ %-5d│ %-23s│ %-14s│ ₹%-13.2f│\n",
             temp->id, temp->name, temp->department, temp->salary);
      temp = temp->next;
    }
  }

  printf("└──────┴────────────────────────┴───────────────┴────────────────┘\n");
}

void displayHashTableStructure(EmployeeDB *db)
{
  printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║              HASH TABLE STRUCTURE (Internal View)                 ║\n");
  printf("╠═══════════════════════════════════════════════════════════════════╣\n");
  printf("║  Shows collision chains and hash distribution                     ║\n");
  printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

  int maxChainLength = 0;
  int emptyBuckets = 0;

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Employee *temp = db->table[i];
    int chainLength = 0;

    if (temp == NULL)
    {
      printf("Index [%d]: ∅ (Empty)\n", i);
      emptyBuckets++;
    }
    else
    {
      printf("Index [%d]: ", i);
      while (temp != NULL)
      {
        printf("→ [ID:%d, %s]", temp->id, temp->name);
        temp = temp->next;
        chainLength++;
      }
      printf(" → NULL\n");

      if (chainLength > maxChainLength)
      {
        maxChainLength = chainLength;
      }
    }
  }

  printf("\n📊 Hash Table Statistics:\n");
  printf("  • Total Buckets    : %d\n", TABLE_SIZE);
  printf("  • Used Buckets     : %d\n", TABLE_SIZE - emptyBuckets);
  printf("  • Empty Buckets    : %d\n", emptyBuckets);
  printf("  • Max Chain Length : %d\n", maxChainLength);
  printf("  • Load Factor      : %.2f%%\n", (db->count * 100.0) / TABLE_SIZE);
}

void generateDepartmentReport(EmployeeDB *db)
{
  printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║                  DEPARTMENT-WISE ANALYTICS                        ║\n");
  printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

  int deptCount[MAX_DEPARTMENTS] = {0};
  float deptSalary[MAX_DEPARTMENTS] = {0};
  float deptAvgSalary[MAX_DEPARTMENTS] = {0};

  // Calculate department statistics
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Employee *temp = db->table[i];
    while (temp != NULL)
    {
      for (int j = 0; j < company.deptCount; j++)
      {
        if (strcasecmp(temp->department, company.departments[j]) == 0)
        {
          deptCount[j]++;
          deptSalary[j] += temp->salary;
          break;
        }
      }
      temp = temp->next;
    }
  }

  printf("┌───────────────────┬──────────┬───────────────┬───────────────┐\n");
  printf("│    DEPARTMENT     │ EMP COUNT│  TOTAL SALARY │   AVG SALARY  │\n");
  printf("├───────────────────┼──────────┼───────────────┼───────────────┤\n");

  for (int i = 0; i < company.deptCount; i++)
  {
    if (deptCount[i] > 0)
    {
      deptAvgSalary[i] = deptSalary[i] / deptCount[i];
    }
    printf("│ %-18s│    %-6d│ ₹%-12.2f│ ₹%-12.2f│\n",
           company.departments[i], deptCount[i], deptSalary[i], deptAvgSalary[i]);
  }

  printf("└───────────────────┴──────────┴───────────────┴───────────────┘\n");

  // Find department with highest/lowest average salary
  int highestIdx = 0, lowestIdx = 0;
  for (int i = 1; i < company.deptCount; i++)
  {
    if (deptAvgSalary[i] > deptAvgSalary[highestIdx] && deptCount[i] > 0)
    {
      highestIdx = i;
    }
    if (deptAvgSalary[i] < deptAvgSalary[lowestIdx] && deptCount[i] > 0)
    {
      lowestIdx = i;
    }
  }

  printf("\n💰 Salary Insights:\n");
  if (deptCount[highestIdx] > 0)
  {
    printf("  🔝 Highest Avg Salary: %s (₹%.2f)\n",
           company.departments[highestIdx], deptAvgSalary[highestIdx]);
  }
  if (deptCount[lowestIdx] > 0)
  {
    printf("  📉 Lowest Avg Salary : %s (₹%.2f)\n",
           company.departments[lowestIdx], deptAvgSalary[lowestIdx]);
  }
}

void generateCompanyDashboard(EmployeeDB *db)
{
  printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║                    COMPANY DASHBOARD & METRICS                    ║\n");
  printf("╠═══════════════════════════════════════════════════════════════════╣\n");
  printf("║  Company: %-56s║\n", company.name);
  printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

  float avgSalary = (db->count > 0) ? (company.totalSalaryExpense / db->count) : 0;

  printf("┌─────────────────────────────────────────────────────────────────┐\n");
  printf("│  📊 WORKFORCE METRICS                                           │\n");
  printf("├─────────────────────────────────────────────────────────────────┤\n");
  printf("│  Total Employees          : %-32d│\n", db->count);
  printf("│  Total Departments        : %-32d│\n", company.deptCount);
  printf("│  Total Salary Expense     : ₹%-31.2f│\n", company.totalSalaryExpense);
  printf("│  Average Salary           : ₹%-31.2f│\n", avgSalary);
  printf("└─────────────────────────────────────────────────────────────────┘\n");

  // Calculate salary distribution
  int countBelow50k = 0, count50to70k = 0, countAbove70k = 0;

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Employee *temp = db->table[i];
    while (temp != NULL)
    {
      if (temp->salary < 50000)
        countBelow50k++;
      else if (temp->salary <= 70000)
        count50to70k++;
      else
        countAbove70k++;
      temp = temp->next;
    }
  }

  printf("\n┌─────────────────────────────────────────────────────────────────┐\n");
  printf("│  💵 SALARY DISTRIBUTION                                         │\n");
  printf("├─────────────────────────────────────────────────────────────────┤\n");
  printf("│  Below ₹50,000           : %-32d│\n", countBelow50k);
  printf("│  ₹50,000 - ₹70,000       : %-32d│\n", count50to70k);
  printf("│  Above ₹70,000           : %-32d│\n", countAbove70k);
  printf("└─────────────────────────────────────────────────────────────────┘\n");

  printf("\n┌─────────────────────────────────────────────────────────────────┐\n");
  printf("│  ⚙️  DATABASE PERFORMANCE METRICS                               │\n");
  printf("├─────────────────────────────────────────────────────────────────┤\n");
  printf("│  Hash Table Size         : %-32d│\n", TABLE_SIZE);
  printf("│  Load Factor             : %-31.2f%%│\n", (db->count * 100.0) / TABLE_SIZE);
  printf("│  Search Complexity       : O(1) average, O(n) worst case       │\n");
  printf("│  Insert Complexity       : O(1) average, O(n) worst case       │\n");
  printf("└─────────────────────────────────────────────────────────────────┘\n");
}

void searchByDepartment(EmployeeDB *db, const char *dept)
{
  printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║            EMPLOYEES IN '%s' DEPARTMENT", dept);
  int padding = 52 - strlen(dept);
  for (int i = 0; i < padding; i++)
    printf(" ");
  printf("║\n");
  printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

  int found = 0;
  float totalDeptSalary = 0;

  printf("┌──────┬────────────────────────┬────────────────┐\n");
  printf("│  ID  │         NAME           │     SALARY     │\n");
  printf("├──────┼────────────────────────┼────────────────┤\n");

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Employee *temp = db->table[i];
    while (temp != NULL)
    {
      if (strcasecmp(temp->department, dept) == 0)
      {
        printf("│ %-5d│ %-23s│ ₹%-13.2f│\n",
               temp->id, temp->name, temp->salary);
        totalDeptSalary += temp->salary;
        found++;
      }
      temp = temp->next;
    }
  }

  printf("└──────┴────────────────────────┴────────────────┘\n");

  if (found == 0)
  {
    printf("\n⚠ No employees found in '%s' department.\n", dept);
  }
  else
  {
    printf("\n📊 Department Statistics:\n");
    printf("  • Total Employees: %d\n", found);
    printf("  • Total Salary   : ₹%.2f\n", totalDeptSalary);
    printf("  • Average Salary : ₹%.2f\n", totalDeptSalary / found);
  }
}

// ========== SORTING OPERATIONS ==========

Employee **collectEmployees(EmployeeDB *db, int *size)
{
  *size = db->count;
  if (*size == 0)
    return NULL;

  Employee **arr = (Employee **)malloc(sizeof(Employee *) * (*size));
  int idx = 0;

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Employee *temp = db->table[i];
    while (temp != NULL)
    {
      arr[idx++] = temp;
      temp = temp->next;
    }
  }

  return arr;
}

void sortBySalary(Employee **arr, int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j]->salary > arr[j + 1]->salary)
      {
        Employee *temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void sortByDepartment(Employee **arr, int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (strcmp(arr[j]->department, arr[j + 1]->department) > 0)
      {
        Employee *temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void displaySorted(Employee **arr, int n, const char *sortType)
{
  printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║                  SORTED EMPLOYEE LIST                             ║\n");
  printf("╠═══════════════════════════════════════════════════════════════════╣\n");
  printf("║  Sorted By: %-54s║\n", sortType);
  printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

  printf("┌─────┬──────┬────────────────────────┬───────────────┬──────────────┐\n");
  printf("│ RANK│  ID  │         NAME           │  DEPARTMENT   │    SALARY    │\n");
  printf("├─────┼──────┼────────────────────────┼───────────────┼──────────────┤\n");

  for (int i = 0; i < n; i++)
  {
    printf("│ %-4d│ %-5d│ %-23s│ %-14s│ ₹%-11.2f│\n",
           i + 1, arr[i]->id, arr[i]->name,
           arr[i]->department, arr[i]->salary);
  }

  printf("└─────┴──────┴────────────────────────┴───────────────┴──────────────┘\n");
}

void freeDB(EmployeeDB *db)
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Employee *temp = db->table[i];
    while (temp != NULL)
    {
      Employee *next = temp->next;
      free(temp);
      temp = next;
    }
  }
}

// ========== INTERACTIVE MENU ==========

void displayMenu()
{
  printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║                    EMPLOYEE DATABASE - MAIN MENU                  ║\n");
  printf("╠═══════════════════════════════════════════════════════════════════╣\n");
  printf("║  1. ➕ Add New Employee                                           ║\n");
  printf("║  2. 🔍 Search Employee by ID                                      ║\n");
  printf("║  3. 🔎 Search Employees by Department                            ║\n");
  printf("║  4. 🗑️  Delete Employee                                           ║\n");
  printf("║  5. 📋 Display All Employees                                      ║\n");
  printf("║  6. 🔢 View Hash Table Structure                                  ║\n");
  printf("║  7. 📊 Sort Employees by Salary                                   ║\n");
  printf("║  8. 📂 Sort Employees by Department                               ║\n");
  printf("║  9. 📈 Department-wise Analytics                                  ║\n");
  printf("║ 10. 🎯 Company Dashboard                                          ║\n");
  printf("║ 11. ℹ️  View Time Complexity Analysis                             ║\n");
  printf("║ 12. 🚪 Exit System                                                ║\n");
  printf("╚═══════════════════════════════════════════════════════════════════╝\n");
  printf("\nEnter your choice (1-12): ");
}

// ========== MAIN FUNCTION ==========

int main()
{
  EmployeeDB db;
  initDB(&db);

  // Setup company first
  setupCompany();

  // Interactive menu
  int choice;
  while (1)
  {
    displayMenu();
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice)
    {
    case 1:
    {
      int id;
      char name[MAX_NAME], dept[MAX_DEPT];
      float salary;

      printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
      printf("                    ADD NEW EMPLOYEE\n");
      printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

      printf("📋 Employee ID: ");
      scanf("%d", &id);
      clearInputBuffer();

      printf("👤 Employee Name: ");
      fgets(name, MAX_NAME, stdin);
      name[strcspn(name, "\n")] = 0;

      printf("🏢 Department (");
      for (int i = 0; i < company.deptCount; i++)
      {
        printf("%s", company.departments[i]);
        if (i < company.deptCount - 1)
          printf(", ");
      }
      printf("): ");
      fgets(dept, MAX_DEPT, stdin);
      dept[strcspn(dept, "\n")] = 0;

      printf("💰 Salary (₹): ");
      scanf("%f", &salary);

      insertEmployee(&db, id, name, dept, salary);
      break;
    }

    case 2:
    {
      int id;
      printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
      printf("                 SEARCH EMPLOYEE BY ID\n");
      printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

      printf("🔍 Enter Employee ID: ");
      scanf("%d", &id);

      Employee *emp = searchEmployee(&db, id);
      if (emp)
      {
        printf("\n✅ Employee found!\n");
        printf("┌─────────────────────────────────────────────────────────────────┐\n");
        printf("│  ID         : %-49d│\n", emp->id);
        printf("│  Name       : %-49s│\n", emp->name);
        printf("│  Department : %-49s│\n", emp->department);
        printf("│  Salary     : ₹%-48.2f│\n", emp->salary);
        printf("│  Hash Index : %-49d│\n", hashFunction(emp->id));
        printf("└─────────────────────────────────────────────────────────────────┘\n");
      }
      else
      {
        printf("\n❌ ERROR: Employee ID %d not found in database!\n", id);
      }
      break;
    }

    case 3:
    {
      char dept[MAX_DEPT];
      printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
      printf("              SEARCH EMPLOYEES BY DEPARTMENT\n");
      printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

      printf("🏢 Available Departments:\n");
      for (int i = 0; i < company.deptCount; i++)
      {
        printf("   %d. %s\n", i + 1, company.departments[i]);
      }

      printf("\n🔎 Enter Department Name: ");
      fgets(dept, MAX_DEPT, stdin);
      dept[strcspn(dept, "\n")] = 0;

      searchByDepartment(&db, dept);
      break;
    }

    case 4:
    {
      int id;
      printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
      printf("                    DELETE EMPLOYEE\n");
      printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

      printf("🗑️  Enter Employee ID to delete: ");
      scanf("%d", &id);

      deleteEmployee(&db, id);
      break;
    }

    case 5:
      displayAllEmployees(&db);
      break;

    case 6:
      displayHashTableStructure(&db);
      break;

    case 7:
    {
      int size;
      Employee **arr = collectEmployees(&db, &size);
      if (arr)
      {
        sortBySalary(arr, size);
        displaySorted(arr, size, "SALARY (Ascending Order)");
        printf("\n⏱  Time Complexity: O(n²) - Bubble Sort Algorithm\n");
        free(arr);
      }
      else
      {
        printf("\n⚠ Database is empty! No employees to sort.\n");
      }
      break;
    }

    case 8:
    {
      int size;
      Employee **arr = collectEmployees(&db, &size);
      if (arr)
      {
        sortByDepartment(arr, size);
        displaySorted(arr, size, "DEPARTMENT (Alphabetical Order)");
        printf("\n⏱  Time Complexity: O(n²) - Bubble Sort Algorithm\n");
        free(arr);
      }
      else
      {
        printf("\n⚠ Database is empty! No employees to sort.\n");
      }
      break;
    }

    case 9:
      if (db.count > 0)
      {
        generateDepartmentReport(&db);
      }
      else
      {
        printf("\n⚠ Database is empty! Add employees first.\n");
      }
      break;

    case 10:
      generateCompanyDashboard(&db);
      break;

    case 11:
      printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
      printf("║              TIME & SPACE COMPLEXITY ANALYSIS                     ║\n");
      printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

      printf("┌───────────────────────┬─────────────────┬─────────────────┐\n");
      printf("│      OPERATION        │  AVERAGE CASE   │   WORST CASE    │\n");
      printf("├───────────────────────┼─────────────────┼─────────────────┤\n");
      printf("│ Insert Employee       │      O(1)       │      O(n)       │\n");
      printf("│ Search by ID          │      O(1)       │      O(n)       │\n");
      printf("│ Delete Employee       │      O(1)       │      O(n)       │\n");
      printf("│ Search by Department  │      O(n)       │      O(n)       │\n");
      printf("│ Sort (Bubble Sort)    │      O(n²)      │      O(n²)      │\n");
      printf("│ Display All           │      O(n)       │      O(n)       │\n");
      printf("│ Generate Analytics    │      O(n)       │      O(n)       │\n");
      printf("└───────────────────────┴─────────────────┴─────────────────┘\n");

      printf("\n┌─────────────────────────────────────────────────────────────────┐\n");
      printf("│  SPACE COMPLEXITY ANALYSIS                                      │\n");
      printf("├─────────────────────────────────────────────────────────────────┤\n");
      printf("│  Hash Table          : O(%d) = O(1) constant space           │\n", TABLE_SIZE);
      printf("│  Employee Records    : O(n) where n = number of employees      │\n");
      printf("│  Chaining (Linked)   : O(n) additional space for pointers      │\n");
      printf("│  Total Space         : O(n)                                     │\n");
      printf("└─────────────────────────────────────────────────────────────────┘\n");

      printf("\n💡 OPTIMIZATION NOTES:\n");
      printf("  • Hash collisions handled by chaining (linked lists)\n");
      printf("  • Average O(1) lookup due to good hash distribution\n");
      printf("  • Worst case O(n) when all keys hash to same index\n");
      printf("  • Load factor: %.2f%% (optimal is < 75%%)\n",
             (db.count * 100.0) / TABLE_SIZE);

      if ((db.count * 100.0) / TABLE_SIZE > 75)
      {
        printf("\n⚠ WARNING: High load factor detected!\n");
        printf("  Consider increasing TABLE_SIZE for better performance.\n");
      }
      break;

    case 12:
      printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
      printf("║                    SYSTEM SHUTDOWN                                ║\n");
      printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

      printf("📊 Final Statistics:\n");
      printf("  • Total Employees Managed: %d\n", db.count);
      printf("  • Total Salary Expense   : ₹%.2f\n", company.totalSalaryExpense);
      printf("  • Company: %s\n\n", company.name);

      printf("🧹 Cleaning up database memory...\n");
      freeDB(&db);
      printf("✅ Memory freed successfully!\n");

      printf("\n╔═══════════════════════════════════════════════════════════════════╗\n");
      printf("║         Thank you for using Employee Database System!            ║\n");
      printf("║                    Developed with ❤️                              ║\n");
      printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");

      return 0;

    default:
      printf("\n❌ Invalid choice! Please enter a number between 1-12.\n");
    }

    printf("\n⏸  Press Enter to continue...");
    getchar();
  }

  return 0;
}