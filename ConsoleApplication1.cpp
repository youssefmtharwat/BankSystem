#include <iostream>
#include <string>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;
bool nameflag = false;
bool passflag = false;
bool balsalflag = false;
class Person {
private:
	string name;
	string password;
	int id;
public:
	Person() {
	}
	Person(int id, string name, string password) {
		setID(id);
		setName(name);
		setPassword(password);
	}
	void setName(string name) {
		if (name.size() >= 5 && name.size() <= 20) {
			int count = 0;
			for (int i = 0; i < name.size(); i++) {
				if (isalpha(name[i]) == false) {
					count++;
				}
			}
			if (count == 0) {
				this->name = name;
				nameflag = false;
			}
			else
			{
				cout << "Invalid name" << endl;
				nameflag = true;
			}
		}
		else
		{
			cout << "Invalid name" << endl;
			nameflag = true;
		}
	}
	void setPassword(string password) {
		if (password.size() >= 8 && password.size() <= 20) {
			this->password = password;
			passflag = false;
		}
		else
		{
			cout << "Invalid password" << endl;
			passflag = true;
		}
	}
	void setID(int id) {
		this->id = id;
	}

	string getName() {
		return this->name;
	}
	int getID() {
		return this->id;
	}
	string getPassword() {
		return this->password;
	}
	void Display1() {
		cout << "Name: " << getName() << endl;
		cout << "ID: " << getID() << endl;
		cout << "Password: " << getPassword() << endl;
	}
};
//==================================================================================================
class Client :public Person {
private:
	double balance;
public:
	Client() :Person() {
	}
	Client(int id, string name, string password, double balance) :Person(id, name, password) {
		setBalance(balance);
	}
	void setBalance(double balance) {
		if (balance >= 1500) {
			this->balance = balance;
			balsalflag = false;
		}
		else {
			cout << "invalid balance" << endl;
			balsalflag = true;
		}
	}
	double checkBalance() {
		return this->balance;
	}
	void deposit(double amount) {
		this->balance += amount;
	}
	void withdraw(double amount) {
		if (amount <= this->balance) {
			this->balance -= amount;
		}
		else {
			cout << "Not enough funds" << endl;
		}
	}
	void transferTo(double amount, Client recipient) {
		if (amount <= this->balance) {
			withdraw(amount);
			recipient.deposit(amount);
		}
		else {
			cout << "Not enough funds" << endl;
		}
	}
	void Display() {
		Display1();
		cout << "Balance: " << checkBalance() << endl << "==================" << endl;
	}
};
//CLIENTS
vector<Client> clients;
static inline Client* clntpntr;
//==================================================================================================
class Employee :public Person {
private:
	double salary;
public:
	Employee() :Person() {};
	Employee(int id, string name, string password, double salary) :Person(id, name, password) {
		setSalary(salary);
	}
	void setSalary(double salary) {
		if (salary >= 5000) {
			this->salary = salary;
			balsalflag = false;
		}
		else {
			cout << "Invalid Salary" << endl;
			balsalflag = true;
		}
	}
	double getSalary() {
		return this->salary;
	}
	void Display() {
		Display1();
		cout << "Salary: " << getSalary() << endl << "==================" << endl;
	}
	void addClient(Client& client) {
		if (nameflag == false && passflag == false && balsalflag == false) {
			clients.push_back(client);
		}
		else {
			cout << "invalid" << endl;
		}
	}
	Client* searchClient(int id) {

		for (int i = 0; i < clients.size(); i++) {
			if (clients[i].getID() == id) {
				clntpntr = &clients[i];
				return clntpntr;
				break;
			}
		}
		return nullptr;
	}
	void listClient() {
		clntpntr->Display();
	}
	void editClient(int id, string name, string password, double balance) {
		clntpntr->setID(id);
		clntpntr->setName(name);
		clntpntr->setPassword(password);
		clntpntr->setBalance(balance);
	}
	void listClients() {
		for (int i = 0; i < clients.size(); i++) {
			clients[i].Display();
		}
	}
};
//EMPLOYEES
vector<Employee> employees;
static inline Employee* employeeptr;
//==================================================================================================
class Admin :public Employee {
public:
	Admin() :Employee() {}
	Admin(int id, string name, string password, double salary) :Employee(id, name, password, salary) {
	}
	void addEmployee(Employee& employee) {
		if (nameflag == false && passflag == false && balsalflag == false){
		employees.push_back(employee);
		}
		else {
			cout << "Invalid" << endl;
		}
	}
	Employee* searchEmployee(int id) {
		for (int i = 0; i < employees.size(); i++) {
			if (employees[i].getID() == id) {
				employeeptr = &employees[i];
				return employeeptr;
				break;
			}
		}
		return nullptr;
	}
	void editEmployee(int id, string name, string password, double salary) {
		employeeptr->setID(id);
		employeeptr->setName(name);
		employeeptr->setPassword(password);
		employeeptr->setSalary(salary);
	}
	void listEmployee() {
		employeeptr->Display();
	}
	void listEmployees() {
		for (int i = 0; i < employees.size(); i++) {
			employees[i].Display();
		}
	}
};
//ADMINS
vector<Admin> admins;
static inline Admin* adminptr;
//==================================================================================================
class DataSourceInterface {
public:
	DataSourceInterface() {};
	virtual void addClient(Client c) = 0;
	virtual void addEmployee(Employee e) = 0;
	virtual void addAdmin(Admin a) = 0;
	virtual void getAllClients() = 0;
	virtual void getAllEmployees() = 0;
	virtual void getAllAdmins() = 0;
	virtual void removeAllClients() = 0;
	virtual void removeAllEmployees() = 0;
	virtual void removeAllAdmins() = 0;
};
//==================================================================================================
class Parser {
public:
	static inline vector<string> temps;
	static inline vector<string> split(string line) {
		istringstream s(line);
		string temp;
		temps.clear();
		while (getline(s, temp, ',')) {
			temps.push_back(temp);
		}
		return temps;
	}
	static inline Client parseToClient(string line) {
		split(line);
		Client c = Client(stoi(temps[0]), temps[1], temps[2], stod(temps[3]));
		temps.clear();
		return c;
	}
	static inline Employee parseToEmployee(string line) {
		split(line);
		Employee e = Employee(stoi(temps[0]), temps[1], temps[2], stod(temps[3]));
		temps.clear();
		return e;
	}
	static inline Admin parseToAdmin(string line) {
		split(line);
		Admin a = Admin(stoi(temps[0]), temps[1], temps[2], stod(temps[3]));
		temps.clear();
		return a;
	}
};
//==================================================================================================
class FileManager : public DataSourceInterface {
public:
	void addClient(Client c) {
		fstream file("Clients.txt", ios::app);
		string cli = to_string(c.getID()) + "," + c.getName() + "," + c.getPassword() + "," + to_string(c.checkBalance());
		file << cli << endl;
		file.close();
	}
	void addEmployee(Employee e) {
		fstream file("Employees.txt", ios::app);
		string emp = to_string(e.getID()) + "," + e.getName() + "," + e.getPassword() + "," + to_string(e.getSalary());
		file << emp << endl;
		file.close();
	}
	void addAdmin(Admin a) {
		fstream file("Admins.txt", ios::app);
		string adm = to_string(a.getID()) + "," + a.getName() + "," + a.getPassword() + "," + to_string(a.getSalary());
		file << adm << endl;
		file.close();
	}
	void getAllClients() {
		fstream file("Clients.txt", ios::in);
		string cli;
		while (getline(file, cli)) {
			Parser p;
			Client cc;
			cc = p.parseToClient(cli);
			clients.push_back(cc);
		}
		file.close();
	}
	void getAllEmployees() {
		fstream file("Employees.txt", ios::in);
		string emp;
		while (getline(file, emp)) {
			Parser p;
			Employee ee;
			ee = p.parseToEmployee(emp);
			employees.push_back(ee);
		}
		file.close();
	}
	void getAllAdmins() {
		fstream file("Admins.txt", ios::in);
		string adm;
		while (getline(file, adm)) {
			Parser p;
			Admin aa;
			aa = p.parseToAdmin(adm);
			admins.push_back(aa);
		}
		file.close();
	}
	void removeAllClients() {
		fstream file("Clients.txt", ios::out);
		file.close();
	}
	void removeAllEmployees() {
		fstream file("Employees.txt", ios::out);
		file.close();
	}
	void removeAllAdmins() {
		fstream file("Admins.txt", ios::out);
		file.close();
	}
	void saveAllClients() {
		removeAllClients();
		for (int i = 0; i < clients.size(); i++) {
			addClient(clients[i]);
		}
	}
	void saveAllEmployees() {
		removeAllEmployees();
		for (int i = 0; i < employees.size(); i++) {
			addEmployee(employees[i]);
		}
	}
	void saveAllAdmins() {
		removeAllAdmins();
		for (int i = 0; i < admins.size(); i++) {
			addAdmin(admins[i]);
		}
	}
};
//==================================================================================================
class FilesHelper {
public:
	static inline void saveLast(string fileName, int id) {
		fstream file(fileName, ios::out);
		file << to_string(id) << endl;
		file.close();
	}
	static inline int getLast(string fileName) {
		fstream file(fileName, ios::in);
		string lastID;
		file >> lastID;
		file.close();
		int l = stoi(lastID);
		return l;
	}
	static inline void saveClient(Client c) {
		FileManager f;
		f.addClient(c);
	}
	static void saveEmployee(string fileName, string lastIdFile, Employee e) {
		fstream file(fileName, ios::app);
		fstream file2(lastIdFile, ios::app);
		string emp = to_string(e.getID()) + "," + e.getName() + "," + e.getPassword() + "," + to_string(e.getSalary());
		file << emp << endl;
		string lastID = to_string(e.getID());
		file2 << lastID;
		file.close();
		file2.close();
	}
	static void getClients() {
		FileManager f;
		f.getAllClients();
	}
	static void getEmployees() {
		FileManager f;
		f.getAllEmployees();
	}
	static void getAdmins() {
		FileManager f;
		f.getAllAdmins();
	}
	static void clearFile(string fileName, string lastIdFile) {
		fstream file(fileName, ios::out);
		file.close();
		fstream file2(lastIdFile, ios::out);
		file2.close();
	}
};
//==================================================================================================
class ClientManager {
public:
	static inline void printClientMenu() {
		cout << "Client Menu" << endl;
		cout << "__________________" << endl;
		cout << "1: Deposit" << endl;
		cout << "2: Withdraw" << endl;
		cout << "3: Transfer To" << endl;
		cout << "4: Check Balance" << endl;
		cout << "5: Display Info" << endl;
		cout << "6: Logout" << endl;
		cout << "=======================================" << endl;
	}
	static inline void updatePassword(Person* person) {
		string p;
		cin >> p;
		person->setPassword(p);
	}
	static inline  Client* login(int id, string password) {
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i].getID() == id && clients[i].getPassword() == password) {
				return &clients[i];
			}
		}
		return NULL;
	}
	static inline bool clientOptions(Client* client) {
		printClientMenu();
		Client temp;
		int choice;
		bool isThere = false;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "1: Deposit" << endl;
			cout << "Please enter the amount you want to deposit: " << endl;
			double dep;
			cin >> dep;
			client->deposit(dep);
			return true;
		case 2:
			cout << "2: Withdraw" << endl;
			cout << "Please enter the amount you want to withdraw: " << endl;
			double withdraw;
			cin >> withdraw;
			client->withdraw(withdraw);
			return true;
		case 3:
			cout << "3: Transfer To" << endl;
			cout << "Please enter the ID of the recepient " << endl;
			int id;
			cin >> id;
			for (int i = 0; i < clients.size(); i++) {
				if (clients[i].getID() == id) {
					temp = clients[i];
					isThere = true;
					break;
				}
			}
			if (isThere) {
				cout << "Please enter the amount you want to transfer " << endl;
				int amount;
				cin >> amount;
				client->transferTo(amount, temp);
				return true;
			}
			else {
				return false;
			}
		case 4:
			cout << "4: Check Balance" << endl;
			cout<<client->checkBalance()<<endl;
			return true;
		case 5:
			cout << "5: Display Info" << endl;
			client->Display();
			return true;
		case 6:
			cout << "6: Logout" << endl;
			return false;
		}
	}
};
//==================================================================================================
class EmployeeManager {
public:
	static inline void printEmployeeMenu() {
		cout << "Employee Menu" << endl;
		cout << "__________________" << endl;
		cout << "1: Add Client" << endl;
		cout << "2: Search for a client" << endl;
		cout << "3: List Clients" << endl;
		cout << "4: Edit a Client" << endl;
		cout << "5: Logout" << endl;
		cout << "=======================================" << endl;
	}
	static inline void newClient(Employee* employee) {
		cout << "Please enter the client's information" << endl;
		int id;
		double balance;
		string name, password;
		cout << "ID: ";
		cin >> id;
		cout << endl;
		cout << "Name: ";
		cin >> name;
		cout << endl;
		cout << "Password: ";
		cin >> password;
		cout << endl;
		cout << "Balance: ";
		cin >> balance;
		cout << endl;
		Client nc = Client(id, name, password, balance);
		employee->addClient(nc);
	}
	static inline void listAllClients(Employee* employee) {
		employee->listClients();
	}
	static inline void searchForClient(Employee* employee) {
		cout << "Please enter the client's ID" << endl;
		int id;
		cin >> id;
		employee->searchClient(id);
		employee->listClient();
	}
	static inline void editClientInfo(Employee* employee) {
		cout << "Please enter the client's ID" << endl;
		int id, nid;
		string name, password;
		double balance;
		cin >> id;
		employee->searchClient(id);
		cout << "Please enter the client's New information" << endl;
		cout << "ID: ";
		cin >> nid;
		cout << endl;
		cout << "Name: ";
		cin >> name;
		cout << endl;
		cout << "Password: ";
		cin >> password;
		cout << endl;
		cout << "Balance: ";
		cin >> balance;
		employee->editClient(nid, name, password, balance);
	}
	static inline Employee* login(int id, string password) {
		for (int i = 0; i < employees.size(); i++) {
			if (employees[i].getID() == id && employees[i].getPassword() == password) {
				return &employees[i];
			}
		}
		return NULL;
	}
	static inline bool employeeOptions(Employee* employee) {
		printEmployeeMenu();
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "1: Add Client" << endl;
			newClient(employee);
			return true;
		case 2:
			cout << "2: Search for a client" << endl;
			searchForClient(employee);
			return true;
		case 3:
			cout << "3: List Clients" << endl;
			listAllClients(employee);
			return true;
		case 4:
			cout << "4: Edit a Client" << endl;
			editClientInfo(employee);
			return true;
		case 5:
			cout << "5: Logout" << endl;
			return false;
		}
	}
};
//==========================================================================================
class AdminManager :public EmployeeManager {
public:
	static inline void printAdminMenu() {
		cout << "Admin Menu" << endl;
		cout << "__________________" << endl;
		cout << "1: Add Client" << endl;
		cout << "2: Search for a client" << endl;
		cout << "3: List Clients" << endl;
		cout << "4: Edit a Client" << endl;
		cout << "5: Add Employee" << endl;
		cout << "6: Search for Employee" << endl;
		cout << "7: List Employees" << endl;
		cout << "8: Edit an Employee" << endl;
		cout << "9: Logout" << endl;
		cout << "=======================================" << endl;
	}
	static inline Admin* login(int id, string password) {
		for (int i = 0; i < admins.size(); i++) {
			if (admins[i].getID() == id && admins[i].getPassword() == password) {
				return &admins[i];
			}
		}
		return NULL;
	}
	static inline bool AdminOptions(Admin* admin) {
		printAdminMenu();
		int choice;
		cin >> choice;
		int id;
		double salary;
		string name, password;
		Employee e;
		switch (choice) {
		case 1:
			cout << "1: Add Client" << endl;
			newClient(admin);
			return true;
		case 2:
			cout << "2: Search for a client" << endl;
			searchForClient(admin);
			return true;
		case 3:
			cout << "3: List Clients" << endl;
			listAllClients(admin);
			return true;
		case 4:
			cout << "4: Edit a Client" << endl;
			editClientInfo(admin);
			return true;
		case 5:
			cout << "5: Add Employee" << endl;
			cout << "Please Enter the employee's information." << endl;
			cout << "ID: ";
			cin >> id;
			cout << endl;
			cout << "Name: ";
			cin >> name;
			cout << endl;
			cout << "Password: ";
			cin >> password;
			cout << endl;
			cout << "Salary: ";
			cin >> salary;
			cout << endl;
			e = Employee(id, name, password, salary);
			admin->addEmployee(e);
			return true;
		case 6:
			cout << "6: Search for Employee" << endl;
			cout << "Please enter the Employee's ID" << endl;
			int id;
			cin >> id;
			admin->searchEmployee(id);
			admin->listEmployee();
			return true;
		case 7:
			cout << "7: List Employees" << endl;
			admin->listEmployees();
			return true;
		case 8:
			cout << "8: Edit an Employee" << endl;
			cout << "Please enter the Employee's ID" << endl;
			cin >> id;
			admin->searchEmployee(id);
			cout << "Please enter the client's New information" << endl;
			cout << "ID: ";
			cin >> id;
			cout << endl;
			cout << "Name: ";
			cin >> name;
			cout << endl;
			cout << "Password: ";
			cin >> password;
			cout << endl;
			cout << "Salary: ";
			cin >> salary;
			admin->editEmployee(id, name, password, salary);
			return true;
		case 9:
			cout << "9: Logout" << endl;
			return false;
		}
	}
};
class Screens {
public:
	static inline void bankName() {
		cout << "Route Bank For Illegal Transactions :)" << endl;
		cout << "________________________________________" << endl;
	}
	static inline void welcome() {
		cout << "WELCOME" << endl;
		cout << "_________" << endl;
	}
	static void inline loginOptions() {
		cout << "Please Select The Type Of Your Login Credentials :) " << endl;
		cout << "___________________________________________________" << endl;
		cout << "1: Client" << endl << "2: Employee" << endl << "3: Admin" << endl;
	}
	static int loginAs() {
		int i;
		cin >> i;
		if (i == 1) {
			return 1;
		}
		else if (i == 2) {
			return 2;
		}
		else if (i == 3) {
			return 3;
		}
		else
			return -1;
	}
	static void inline invalid(int c) {
		cout << "INVALID" << endl;
	}
	static void inline logout() {
		cout << "Bye Bye :)" << endl;
	}
	static void loginScreen(int c) {
		int id;
		string pass;
		bool flag = true;
		switch (c) {
		case 1:
			cout << "ID: ";
			cin >> id;
			cout << endl << "Password: ";
			cin >> pass;
			cout << endl;
			ClientManager cm;
			if (cm.login(id, pass) != NULL) {
				Client* c = cm.login(id, pass);
				while (flag == true){
					cm.clientOptions(c);
					flag = cm.clientOptions(c);
				}
				logout();
			}
			else {
				cout << "Wrong ID or Password" << endl;
			}
			break;
		case 2:
			cout << "ID: ";
			cin >> id;
			cout << endl << "Password: ";
			cin >> pass;
			cout << endl;
			EmployeeManager em;
			if (em.login(id, pass) != NULL) {
				Employee* e = em.login(id, pass);
				do {
					em.employeeOptions(e);
					flag = em.employeeOptions(e);
				} while (flag == true);
				logout();
			}
			else {
				cout << "Wrong ID or Password" << endl;
			}
			break;
		case 3:
			cout << "ID: ";
			cin >> id;
			cout << endl << "Password: ";
			cin >> pass;
			cout << endl;
			AdminManager am;
			if (am.login(id, pass) != NULL) {
				Admin* a = am.login(id, pass);
				do {
					am.AdminOptions(a);
					flag = am.AdminOptions(a);
				} while (flag == true);
				logout();
			}
			else {
				cout << "Wrong ID or Password" << endl;
			}
			break;
		case -1:
			invalid(c);
			break;
		}
	}
	static inline void runApp() {;
		FileManager f;
		f.getAllClients();
		f.getAllEmployees();
		f.getAllAdmins();
		bankName();
		welcome();
		loginOptions();
		loginScreen(loginAs());
		f.saveAllClients();
		f.saveAllEmployees();
		f.saveAllAdmins();
	}
};
int main() {
	Screens::runApp();
}