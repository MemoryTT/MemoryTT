#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Employee 
{
    int id;
    char name[25];
    float salary;
    int order_number;
};

struct Node 
{
    struct Employee data;
    struct Node* next;
};

struct Node* head = NULL;
int employee_count = 0;

void save_employees_to_file() 
{
    FILE *file = fopen("employees.dat", "w");
    
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    
    setvbuf(file, NULL, _IOFBF, 0);
    
    struct Node* current = head;
    
    while (current != NULL)
    {
        for (int i = 0; i < strlen(current->data.name); i++)
        {
            if (!isascii(current->data.name[i]))
            {
                current->data.name[i] = ' ';
            }
        }
        
        fwrite(&current->data, sizeof(struct Employee), 1, file);
        current = current->next;
    }
    
    fclose(file);
    printf("\n*Employees's information has been saved to employees.dat file.\n");
}

void insert_new_employee(int id, const char* name, float salary) 
{
    if (employee_count < 5) 
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data.id = id;
        strncpy(newNode->data.name, name, sizeof(newNode->data.name));
        newNode->data.salary = salary;
        newNode->data.order_number = employee_count + 1;

        if (employee_count == 0) 
        {
            newNode->next = head;
            head = newNode;
        } 
        else 
        {
            struct Node* current = head;
            for (int i = 1; i < employee_count && current->next != NULL; i++) 
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        employee_count++;
        printf("\n*The Employee No.%d Information has been saved.\n", newNode->data.order_number);

        save_employees_to_file();  
    } 
    else 
    {
        printf("\n*The Employee list is full. Cannot add more Employees.\n");
    }
}

void create_list() 
{
    head = NULL;
    employee_count = 0;
}

int is_empty() 
{
    return head == NULL;
}

void get_valid_name(const char* prompt, char* name) 
{
    while (1) 
	{
        printf("%s", prompt);
        fgets(name, 25, stdin);
        name[strcspn(name, "\n")] = 0;

        int valid = 1;
        for (int i = 0; name[i] != '\0'; i++) 
		{
            if (!isalpha(name[i]) && name[i] != ' ') 
			{
                valid = 0;
                break;
            }
        }

        if (valid) 
		{
            break;
        } else 
		{
            printf("\n*Invalid name. Please enter a name with alphabetical characters and spaces only.\n");
            printf("-------------------------------------------------------\n");
        }
    }
}

int get_valid_number(const char* prompt) 
{
    int value;
    char input[20];
    while (1) 
	{
        printf("%s", prompt);
        scanf("%s", input);

        int invalid_input = 0;
        for (int i = 0; input[i] != '\0'; i++) 
		{
            if (!isdigit(input[i])) 
			{
                invalid_input = 1;
                break;
            }
        }

        if (!invalid_input) 
		{
            value = atoi(input);
            break;
        } else 
		{
            printf("\n*Invalid input. Please enter an integer.\n");
            printf("-------------------------------------------------------\n");
        }
    }
    return value;
}



void display_menu() 
{
    printf("Hello! What do you want to do?\n\n");
    printf("-------------------------------------------------------\n");
    printf(" * Press 1: To Create an empty linked list\n");
    printf(" * Press 2: To Insert a new Employee node\n");
    printf(" * Press 3: To Check if List is EMPTY or NOT\n");
    printf(" * Press 4: To Move to Employees linked list\n");
    printf(" * Press 5: To Exit\n");
    printf("\nOther choices won't be accepted!\n");
}

int main() 
{
    display_menu();

    int choice;
    int emp_id;
    char emp_name[25];
    float emp_salary;
    int list_created = 0;

    do 
	{
        printf("-------------------------------------------------------\n");
        choice = get_valid_number("\n** Please enter your choice: ");

        switch (choice) 
		{
            case 1:
                create_list();
                printf("\n*A new empty list has been created.\n");
                list_created = 1;
                break;

            case 2:
                if (!list_created) 
				{
                    printf("\nPlease create an empty linked list first. (Option 1)\n");
                } else 
				{
                    printf("\n*Employee No.%d Information:\n", employee_count + 1);
                    emp_id = get_valid_number("Employee ID: ");
                    while ((getchar()) != '\n');
                    get_valid_name("Employee Name: ", emp_name);
                    emp_salary = get_valid_number("Employee Salary: ");

                    insert_new_employee(emp_id, emp_name, emp_salary);
                }
                break;

            case 3:
                if (!list_created) 
				{
                    printf("\n*There is no linked list at all.\n");
                    printf("*Please create linked list first. (Option 1)\n");
                } else if (is_empty()) 
				{
                    printf("\n*The linked list is empty.\n");
                } else 
				{
                    printf("\n*The linked list is not empty.\n");
                    printf("*There are %d Employees in the list.\n", employee_count);
                }
                break;

            case 4:
                if (!list_created)
				{
                    printf("\n*There is no linked list at all.\n");
                    printf("*Please create linked list first. (Option 1)\n");
                } else 
				{
                    struct Node* emp = head;
                    while (emp != NULL) 
					{
                        printf("\nInformation of Employee No.%d:\n", emp->data.order_number);
                        printf("ID: %d\nName: %s\nSalary: %.2f\n", emp->data.id, emp->data.name, emp->data.salary);
                        emp = emp->next;
                    }
                }
                break;

            case 5:
                printf("\n*Goodbye! See you again.\n");
                break;

            default:
                printf("\n*Invalid choice. Please enter a valid number input.\n");
        }
    } while (choice != 5);

    return 0;
}
