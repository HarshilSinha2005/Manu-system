# 🍽️ Hotel Menu Management System (C++)

This is a C++ console-based Hotel Menu Management System that includes **Admin and User functionalities**, persistent data storage via files, and billing features. Designed with simplicity and practicality in mind, it can be used by hotel/restaurant staff to manage menu items and customer orders efficiently.

---

## ✨ Features

### 👨‍💼 Admin Panel (login required)
- 🔐 Admin Login (Default: `admin` / `1234`)
- ➕ Add Menu Items
- 🗑️ Delete Menu Items
- ✏️ Update Menu Items
- 🔍 Search Menu Items by Name
- 📊 Filter Menu Items by Price
- 📁 Persistent Storage (`menu.txt`)

### 👥 User Panel
- 📜 View Menu
- 🛒 Place Order (Multiple Items)
- 🧾 Auto Bill Generation with:
  - ✅ 5% Tax
  - ✅ 10% Discount
- 💾 Save Bill to File (`bill.txt`)

---

## 📁 File Structure

```bash
hotel-menu-system/
├── main.cpp         # Source code
├── menu.txt         # Menu data (read/write)
├── bill.txt         # Bill output (auto-generated)
└── README.md        # Project documentation



🛠️ Technologies Used
Language: C++
File Handling: fstream
Console Control: windows.h (Sleep(), system("cls"))
No STL Used: No <vector>, <iomanip> — static arrays only
Platform: Windows Console Application



Notes
All data is stored in plain .txt files.
No external libraries are needed.
Cross-platform compatible if windows.h functions are replaced or abstracted.
Can be extended with GUI or database features in future.


🤝 Contributing
Contributions are welcome! If you have improvements or bug fixes:
Fork the repository
Make your changes
Submit a pull request

