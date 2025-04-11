#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

const int MAX_ITEMS = 100;
const int MAX_ORDERS = 50;

struct MenuItem 
{
    int id;
    string name;
    double price;
};

struct OrderItem 
{
    int itemIndex;
    int quantity;
};

MenuItem menu[MAX_ITEMS];
OrderItem orderList[MAX_ORDERS];
int menuCount = 0;
int orderCount = 0;

double taxRate = 0.05;
double discountRate = 0.10;

void loadMenuFromFile() 
{
    ifstream file("menu.txt");
    menuCount = 0;
    while (file >> menu[menuCount].id) 
	{
        file.ignore();
        getline(file, menu[menuCount].name);
        file >> menu[menuCount].price;
        file.ignore();
        menuCount++;
    }
    file.close();
}

void saveMenuToFile() 
{
    ofstream file("menu.txt");
    for (int i = 0; i < menuCount; i++) 
	{
        file << menu[i].id << "\n" << menu[i].name << "\n" << menu[i].price << "\n";
    }
    file.close();
}

void displayMenu() 
{
    system("cls");
    cout << "\n========= MENU =========\n";
    cout << "ID\t\tItem\t\t\tPrice\n";
    for (int i = 0; i < menuCount; i++) 
	{
        cout << menu[i].id << "\t" << menu[i].name;
        if (menu[i].name.length() < 8) cout << "\t";
        cout << "\tRs. " << menu[i].price << "\n";
    }
    cout << "========================\n";
}

bool adminLogin() 
{
    string username, password;
    cout << "\n=== Admin Login ===\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    if (username == "admin" && password == "1234") 
	{
        cout << "Login successful!\n";
        Sleep(1000);
        return true;
    } 
	else 
	{
        cout << "Invalid credentials.\n";
        Sleep(1000);
        return false;
    }
}

void addMenuItem() 
{
    if (menuCount >= MAX_ITEMS) 
	{
        cout << "Menu is full!\n";
        return;
    }
    cout << "Enter new item ID: ";
    cin >> menu[menuCount].id;
    cin.ignore();
    cout << "Enter item name: ";
    getline(cin, menu[menuCount].name);
    cout << "Enter item price: ";
    cin >> menu[menuCount].price;
    menuCount++;
    saveMenuToFile();
    cout << "Item added successfully!\n";
}

void deleteMenuItem() 
{
    int delID;
    cout << "Enter ID of item to delete: ";
    cin >> delID;
    bool found = false;
    for (int i = 0; i < menuCount; i++) 
	{
        if (menu[i].id == delID) 
		{
            for (int j = i; j < menuCount - 1; j++) 
			{
                menu[j] = menu[j + 1];
            }
            menuCount--;
            saveMenuToFile();
            cout << "Item deleted successfully.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Item not found.\n";
}

void updateMenuItem() 
{
    int updateID;
    cout << "Enter ID of item to update: ";
    cin >> updateID;
    bool found = false;
    for (int i = 0; i < menuCount; i++) 
	{
        if (menu[i].id == updateID) 
		{
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, menu[i].name);
            cout << "Enter new price: ";
            cin >> menu[i].price;
            saveMenuToFile();
            cout << "Item updated successfully.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Item not found.\n";
}

void searchMenuItem() 
{
    string search;
    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, search);
    bool found = false;
    for (int i = 0; i < menuCount; i++) 
	{
        if (menu[i].name.find(search) != string::npos) 
		{
            cout << menu[i].id << "\t" << menu[i].name << "\tRs. " << menu[i].price << "\n";
            found = true;
        }
    }
    if (!found) cout << "No matching items found.\n";
}

void filterMenuByPrice() 
{
    double minPrice;
    cout << "Enter minimum price: ";
    cin >> minPrice;
    bool found = false;
    for (int i = 0; i < menuCount; i++) 
	{
        if (menu[i].price >= minPrice) 
		{
            cout << menu[i].id << "\t" << menu[i].name << "\tRs. " << menu[i].price << "\n";
            found = true;
        }
    }
    if (!found) cout << "No items found in this price range.\n";
}

void adminPanel() 
{
    int choice;
    do 
	{
        system("cls");
        cout << "\n===== Admin Panel =====\n";
        cout << "1. Add Item\n";
        cout << "2. Delete Item\n";
        cout << "3. Update Item\n";
        cout << "4. Search Item\n";
        cout << "5. Filter by Price\n";
        cout << "6. View Menu\n";
        cout << "7. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1: addMenuItem(); break;
            case 2: deleteMenuItem(); break;
            case 3: updateMenuItem(); break;
            case 4: searchMenuItem(); break;
            case 5: filterMenuByPrice(); break;
            case 6: displayMenu(); break;
            case 7: return;
            default: cout << "Invalid choice!\n";
        }
        system("pause");
    } while (true);
}

void takeOrder() 
{
    int id, qty;
    char choice;
    do 
	{
        cout << "Enter item ID to order: ";
        cin >> id;
        bool found = false;
        for (int i = 0; i < menuCount; i++) 
		{
            if (menu[i].id == id) 
			{
                cout << "Enter quantity: ";
                cin >> qty;
                orderList[orderCount].itemIndex = i;
                orderList[orderCount].quantity = qty;
                orderCount++;
                cout << qty << " x " << menu[i].name << " added.\n";
                found = true;
                break;
            }
        }
        if (!found) cout << "Item ID not found.\n";
        cout << "Add more? (y/n): ";
        cin >> choice;
    } while ((choice == 'y' || choice == 'Y') && orderCount < MAX_ORDERS);
}

void generateBill() 
{
    if (orderCount == 0) 
	{
        cout << "No items ordered.\n";
        return;
    }
    double subtotal = 0;
    ofstream bill("bill.txt");
    cout << "\n--------- BILL ---------\n";
    cout << "Item\tQty\tPrice\tTotal\n";
    bill << "--------- BILL ---------\n";
    bill << "Item\tQty\tPrice\tTotal\n";

    for (int i = 0; i < orderCount; i++) 
	{
        int idx = orderList[i].itemIndex;
        int qty = orderList[i].quantity;
        double price = menu[idx].price;
        double total = qty * price;
        subtotal += total;
        cout << menu[idx].name << "\t" << qty << "\t" << price << "\t" << total << "\n";
        bill << menu[idx].name << "\t" << qty << "\t" << price << "\t" << total << "\n";
    }

    double tax = subtotal * taxRate;
    double discount = subtotal * discountRate;
    double finalAmount = subtotal + tax - discount;

    cout << "Subtotal: Rs. " << subtotal << "\n";
    cout << "Tax (5%): Rs. " << tax << "\n";
    cout << "Discount (10%): Rs. " << discount << "\n";
    cout << "Total Amount: Rs. " << finalAmount << "\n";

    bill << "Subtotal: Rs. " << subtotal << "\n";
    bill << "Tax (5%): Rs. " << tax << "\n";
    bill << "Discount (10%): Rs. " << discount << "\n";
    bill << "Total Amount: Rs. " << finalAmount << "\n";
    bill.close();

    cout << "Bill saved to 'bill.txt'\n";
}

int main() 
{
    int choice;
    bool isAdmin = false;
    loadMenuFromFile();

    do 
	{
        system("cls");
        cout << "=== Hotel Menu System ===\n";
        cout << "1. Admin Login\n";
        cout << "2. View Menu\n";
        cout << "3. Place Order\n";
        cout << "4. Generate Bill\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
                isAdmin = adminLogin();
                if (isAdmin) adminPanel();
                break;
            case 2:
                displayMenu();
                system("pause");
                break;
            case 3:
                displayMenu();
                takeOrder();
                system("pause");
                break;
            case 4:
                generateBill();
                system("pause");
                break;
            case 5:
                cout << "Exiting...\n";
                Sleep(1000);
                break;
            default:
                cout << "Invalid choice!\n";
                Sleep(1000);
        }
    } while (choice != 5);

    return 0;
}

