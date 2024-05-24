#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Employee {
private:
    int employeeID;
    string name;
    string department;

public:
    Employee() : employeeID(0), name(""), department("") {}
    Employee(int id, string n, string d) : employeeID(id), name(n), department(d) {}
    Employee(const Employee &e) : employeeID(e.employeeID), name(e.name), department(e.department) {}
    void displayEmployeeInfo() {
        cout << "\nEmployee ID: " << employeeID << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
    }

    int getEmployeeID() {
        return employeeID;
    }

    string getEmployeeName() {
        return name;
    }

    string getEmployeeDepartment() {
        return department;
    }

    virtual double calculatePayroll() = 0;
};

class PermanentEmployee : public Employee {
private:
    double salary;
    double benefits;

public:
    PermanentEmployee() : Employee(), salary(0.0), benefits(0.0) {}

    PermanentEmployee(int id, string n, string d, double s, double b)
        : Employee(id, n, d), salary(s), benefits(b) {}

    PermanentEmployee(const PermanentEmployee &pe)
        : Employee(pe), salary(pe.salary), benefits(pe.benefits) {}

    void displayEmployeeInfo() {
        Employee::displayEmployeeInfo();
        cout << "Salary: " << salary << endl;
        cout << "Benefits: " << benefits << endl;
    }

    double calculatePayroll() override {
        return salary + benefits;
    }
};

class ContractEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;

public:
    ContractEmployee() : Employee(), hourlyWage(0.0), hoursWorked(0) {}

    ContractEmployee(int id, string n, string d, double hw, int hwk)
        : Employee(id, n, d), hourlyWage(hw), hoursWorked(hwk) {}

    ContractEmployee(const ContractEmployee &ce)
        : Employee(ce), hourlyWage(ce.hourlyWage), hoursWorked(ce.hoursWorked) {}

    void displayEmployeeInfo() {
        Employee::displayEmployeeInfo();
        cout << "Hourly Wage: " << hourlyWage << endl;
        cout << "Hours Worked: " << hoursWorked << endl;
    }

    double calculatePayroll() override {
        return hourlyWage * hoursWorked;
}
};

class Manager : public PermanentEmployee {
private:
    double bonus;

public:
    Manager() : PermanentEmployee(), bonus(0.0) {}

    Manager(int id, string n, string d, double s, double b, double bo)
        : PermanentEmployee(id, n, d, s, b), bonus(bo) {}

    Manager(const Manager &m)
        : PermanentEmployee(m), bonus(m.bonus) {}

    void displayEmployeeInfo() {
        PermanentEmployee::displayEmployeeInfo();
        cout << "Bonus: " << bonus << endl;
    }

    double calculatePayroll() override {
        return PermanentEmployee::calculatePayroll() + bonus;
    }
};

class SalesPerson : public PermanentEmployee {
private:
    double salesCommission;

public:
    SalesPerson() : PermanentEmployee(), salesCommission(0.0) {}

    SalesPerson(int id, string n, string d, double s, double b, double sc)
: PermanentEmployee(id, n, d, s, b), salesCommission(sc) {}

    SalesPerson(const SalesPerson &sp)
        : PermanentEmployee(sp), salesCommission(sp.salesCommission) {}

    void displayEmployeeInfo() {
        PermanentEmployee::displayEmployeeInfo();
        cout << "Sales Commission: " << salesCommission << endl;
    }

    double calculatePayroll() override {
        return PermanentEmployee::calculatePayroll() + salesCommission;
    }
};

class Technician : public ContractEmployee {
private:
    double overtimePay;

public:
    Technician() : ContractEmployee(), overtimePay(0.0) {}

    Technician(int id, string n, string d, double hw, int hwk, double op)
        : ContractEmployee(id, n, d, hw, hwk), overtimePay(op) {}

    Technician(const Technician &t)
        : ContractEmployee(t), overtimePay(t.overtimePay) {}

    void displayEmployeeInfo() {
        ContractEmployee::displayEmployeeInfo();
        cout << "Overtime Pay: " << overtimePay << endl;
    }

    double calculatePayroll() override {
        return ContractEmployee::calculatePayroll() + overtimePay;
    }
};

class PayrollSystem {
private:
    vector<Employee*> employeeList;

public:
    PayrollSystem() {}

    PayrollSystem(const PayrollSystem&ps) {
        for (Employee* e : ps.employeeList) {
            employeeList.push_back(e);
        }
    }

    void addEmployee(Employee* e) {
        employeeList.push_back(e);
    }

    void removeEmployee(int id) {
        for (auto it = employeeList.begin(); it!= employeeList.end(); ++it) {
            if ((*it)->getEmployeeID() == id) {
                employeeList.erase(it);
                break;
            }
        }
    }

    void displayPayrollInfo() {
        for (Employee* e : employeeList) {
            e->displayEmployeeInfo();
            cout << "Payroll: " << e->calculatePayroll() << endl;
        }
    }

    void processPayroll() {
        for (Employee* e : employeeList) {
            double payroll = e->calculatePayroll();
            cout << "Processed payroll for Employee ID " << e->getEmployeeID() << ": " << payroll << endl;
        }
    }

    void searchEmployeeByID(int id) {
        for (Employee* e : employeeList) {
            if (e->getEmployeeID() == id) {
                e->displayEmployeeInfo();
                cout << "Payroll: " << e->calculatePayroll() << endl;
                return;
            }
        }
        throw invalid_argument("Employee not found");
    }

    void searchEmployeeByName(string name) {
        for (Employee* e : employeeList) {
            if (e->getEmployeeName() == name) {
                e->displayEmployeeInfo();
                cout << "Payroll: " << e->calculatePayroll() << endl;
                return;
            }
        }
        throw invalid_argument("Employee not found");
    }
};

int main() {
    PayrollSystem payrollSystem;
    int choice, id, hoursWorked, hoursWeekly, hourlyWage, weeklySalary, benefits, salesCommission, bonus, overtimePay;
    string name, department;
    while (true) {
        try {
            cout << "\n1. Add Manager\n2. Add Sales Person\n3. Add Technician\n4. Add Employee\n5. Remove Employee\n6. Display Payroll Info\n7. Process Payroll\n8. Search Employee by ID\n9. Search Employee by Name\n10. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter Employee ID: ";
                    cin >> id;
                    if (id <= 0) {
                        throw invalid_argument("Invalid ID");
                    }
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, name);
                    if (name.empty()) {
                        throw invalid_argument("Name cannot be empty");
                    }
                    cout << "Enter Department: ";
                    getline(cin, department);
                    if (department.empty()) {
                        throw invalid_argument("Department cannot be empty");
                    }
                    cout << "Enter Salary: ";
                    cin >> weeklySalary;
                    if (weeklySalary < 0) {
                        throw invalid_argument("Salary cannot be negative");
                    }
                    cout << "Enter Benefits: ";
                    cin >> benefits;
                    if (benefits < 0) {
                        throw invalid_argument("Benefits cannot be negative");
                    }
                    cout << "Enter Bonus: ";
                    cin >> bonus;
                    if (bonus < 0) {
                        throw invalid_argument("Bonus cannot be negative");
                    }
                    payrollSystem.addEmployee(new Manager(id, name, department, weeklySalary, benefits, bonus));
                    break;
                case 2:
                    cout << "Enter Employee ID: ";
                    cin >> id;
                    if (id <= 0) {
                        throw invalid_argument("Invalid ID");
                    }
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, name);
                    if (name.empty()) {
                        throw invalid_argument("Name cannot be empty");
                    }
                    cout << "Enter Department: ";
                    getline(cin, department);
                    if (department.empty()) {
                        throw invalid_argument("Department cannot be empty");
                    }
                    cout << "Enter Salary: ";
                    cin >> weeklySalary;
                    if (weeklySalary < 0) {
                        throw invalid_argument("Salary cannot be negative");
                    }
                    cout << "Enter Benefits: ";
                    cin >> benefits;
                    if (benefits < 0) {
                        throw invalid_argument("Benefits cannot be negative");
                    }
                    cout << "Enter Sales Commission: ";
                    cin >> salesCommission;
                    if (salesCommission < 0) {
                        throw invalid_argument("Sales Commission cannot be negative");
                    }
                    payrollSystem.addEmployee(new SalesPerson(id, name, department, weeklySalary, benefits, salesCommission));
                    break;
                case 3:
                    cout << "Enter Employee ID: ";
                    cin >> id;
                    if (id <= 0) {
                        throw invalid_argument("Invalid ID");
                    }
                    cout <<"Enter Name: ";
                    cin.ignore();
                    getline(cin, name);
                    if (name.empty()) {
                        throw invalid_argument("Name cannot be empty");
                    }
                    cout << "Enter Department: ";
                    getline(cin, department);
                    if (department.empty()) {
                        throw invalid_argument("Department cannot be empty");
                    }
                    cout << "Enter Hourly Wage: ";
                    cin >> hourlyWage;
                    if (hourlyWage < 0) {
                        throw invalid_argument("Hourly Wage cannot be negative");
                    }
                    cout << "Enter Hours Worked: ";
                    cin >> hoursWorked;
                    if (hoursWorked < 0) {
                        throw invalid_argument("Hours Worked cannot be negative");
                    }
                    cout << "Enter Overtime Pay: ";
                    cin >> overtimePay;
                    if (overtimePay < 0) {
                        throw invalid_argument("Overtime Pay cannot be negative");
                    }
                    payrollSystem.addEmployee(new Technician(id, name, department, hourlyWage, hoursWorked, overtimePay));
                    break;
                case 4:
                    cout << "Enter Employee ID: ";
                    cin >> id;
                    if (id <= 0) {
                        throw invalid_argument("Invalid ID");
                    }
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, name);
                    if (name.empty()) {
                        throw invalid_argument("Name cannot be empty");
                    }
                    cout << "Enter Department: ";
                    getline(cin, department);
                    if (department.empty()) {
                        throw invalid_argument("Department cannot be empty");
                    }
                    cout << "1. Manager\n2. Sales Person\n3. Technician\n";
                    cout << "Enter Employee Type: ";
                    cin >> choice;
                    switch (choice) {
                        case 1:
                            cout << "Enter Salary: ";
                            cin >> weeklySalary;
                            if (weeklySalary < 0) {
                                throw invalid_argument("Salary cannot be negative");
                            }
                            cout << "Enter Benefits: ";
                            cin >> benefits;
                            if (benefits < 0) {
                                throw invalid_argument("Benefits cannot be negative");
                            }
                            cout << "Enter Bonus: ";
                            cin >> bonus;
                            if (bonus < 0) {
                                throw invalid_argument("Bonus cannot be negative");
                            }
                            payrollSystem.addEmployee(new Manager(id, name, department, weeklySalary, benefits, bonus));
                            break;
                        case 2:
                            cout << "Enter Salary: ";
                            cin >> weeklySalary;
                            if (weeklySalary < 0) {
                                throw invalid_argument("Salary cannot be negative");
                            }
                            cout << "Enter Benefits: ";
                            cin >> benefits;
                            if (benefits < 0) {
                                throw invalid_argument("Benefits cannot be negative");
                            }
                            cout << "Enter Sales Commission: ";
                            cin >> salesCommission;
                            if (salesCommission < 0) {
                                throw invalid_argument("Sales Commission cannot be negative");
                            }
                            payrollSystem.addEmployee(new SalesPerson(id, name, department, weeklySalary, benefits, salesCommission));
                            break;
                        case 3:
                            cout << "Enter Hourly Wage: ";
                            cin >> hourlyWage;
                            if (hourlyWage < 0) {
                                throw invalid_argument("Hourly Wage cannot be negative");
                            }
                            cout << "Enter Hours Worked: ";
                            cin >> hoursWorked;
                            if (hoursWorked < 0) {
                                throw invalid_argument("Hours Worked cannot be negative");
                            }
                            cout << "Enter Overtime Pay: ";cin >> overtimePay;
                            if (overtimePay < 0) {
                                throw invalid_argument("Overtime Pay cannot be negative");
                            }
                            payrollSystem.addEmployee(new Technician(id, name, department, hourlyWage, hoursWorked, overtimePay));
                            break;
                        default:
                            cout << "Invalid Employee Type\n";
                    }
                    break;
                case 5:
                    cout << "Enter Employee ID: ";
                    cin >> id;
                    payrollSystem.removeEmployee(id);
                    break;
                case 6:
                    payrollSystem.displayPayrollInfo();
                    break;
                case 7:
                    payrollSystem.processPayroll();
                    break;
                case 8: {
                    cout << "Enter Employee ID: ";
                    cin >> id;
                    try {
                        payrollSystem.searchEmployeeByID(id);
                    } catch (const invalid_argument& e) {
                        cerr << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 9: {
                    cout << "Enter Employee Name: ";
                    cin.ignore();
                    getline(cin, name);
                    try {
                        payrollSystem.searchEmployeeByName(name);
                    } catch (const invalid_argument& e) {
                        cerr << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 10:
                    exit(0);
                default:
                    cout << "Invalid Choice\n";
            }
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    return 0;
}