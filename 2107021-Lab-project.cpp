/*
1. Abstract class
2. Derived class
3. Diamond problem
4. Pure virtual function/ inheritance
5. Friend class
6. Friend function
7. Operator overloading/ polymorphism
8. Template
9. STL
10. File
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <cmath>
#include<cassert>
using namespace std;

class noteApp;
void HighScore(int hs);

// Abstact class
class appScreen
{
protected:
  // Pure virtual function
  // inheritance
  virtual void add() = 0;
  virtual void display() = 0;
  virtual void update() = 0;
  virtual void remove() = 0;
};

class unitNote
{
  string details;

public:
  unitNote()
  {
    details = "Unknown";
  }
  unitNote(string d)
  {
    details = d;
  }
  void display()
  {
    cout << "     " << details << endl;
  }
  string getDetails()
  {
    return details;
  }
  friend class noteApp;
};

// derived-1
// friend class
class noteApp : virtual public appScreen
{
protected:
  // stl
  vector<unitNote> notes;
  string fileName1;

  void save()
  {
    // file
    ofstream outFile(fileName1);
    if (!outFile.is_open())
    {
      cerr << "Error opening the file" << endl;
      return;
    }

    for (int i = 0; i < notes.size(); i++)
    {
      outFile << i + 1 << ". " << notes[i].details << endl;
    }
    outFile.close();
  }
  void load()
  {
    ifstream inFile(fileName1);
    if (inFile.is_open())
    {
      string line;
      while (getline(inFile, line))
      {
        unitNote note2(line.substr(3));
        notes.push_back(note2);
      }
      inFile.close();
    }
    else
    {
      cout << "Unable to open file" << endl;
    }
  }

public:
  // function overwriting
  noteApp()
  {
    fileName1 = "notesProject.txt";
    if (!notes.size())
      load();
  }
  // function overwriting
  noteApp(string f)
  {
    fileName1 = f;
    if (!notes.size())
      load();
  }
  // function overwriting
  noteApp(string f, string n)
  {
    fileName1 = f;
    if (!notes.size())
      load();
    unitNote n2(n);
    notes.push_back(n);
  }
  void add()
  {
    cout << "Enter note content:" << endl;
    string input;
    cin.ignore();
    getline(cin, input);
    unitNote note2(input);
    notes.push_back(note2);
    save();
    cout << "Note added successfully" << endl;
  }
  void display()
  {
    if (notes.size() > 0)
    {
      cout << "Note/s: " << endl;
      for (int i = 0; i < notes.size(); i++)
        cout << i + 1 << ". " << notes[i].details << endl;
    }
    else
      cout << "There are no notes." << endl;
  }
  void remove()
  {
    if (!notes.size())
    {
      cout << "No notes available to remove." << endl;
      return;
    }
    int index;
    cout << "Enter no: " << endl;
    cin >> index;
    if (index >= 0 && index <= notes.size())
    {
      notes.erase(notes.begin() + index - 1);
      cout << "Note removed successfully" << endl;
    }

    else
      cout << "Invalid index." << endl;
    save();
  }
  void update()
  {
    if (!notes.size())
    {
      cout << "No notes available to update." << endl;
      return;
    }
    int index;
    string n;
    cout << "Enter no: " << endl;
    cin >> index;
    if (index < 0 || index > notes.size())
      cout << "Invalid index." << endl;
    else
    {
      cin.ignore();
      cout << "New note: ";
      getline(cin, n);
      notes[index - 1] = n;
      save();
      cout << "Note updated successfully" << endl;
    }
    save();
  }
  void operator++()
  {
    add();
  }
};

// derived-2
class quiz : virtual public appScreen
{
protected:
  vector<string> question;
  vector<string> answer;
  string fileName2;
  void save()
  {
    ofstream outFile(fileName2);
    if (!outFile.is_open())
    {
      cout << "Error opening file." << endl;
      return;
    }
    for (int i = 0; i < question.size(); i++)
    {
      outFile << i + 1 << ". " << question[i] << endl;
      outFile << "Answer: " << answer[i] << endl;
    }
    outFile.close();
  }
  void load()
  {
    ifstream inFile(fileName2);
    if (!inFile.is_open())
    {
      cout << "Error opening file." << std::endl;
      return;
    }
    string line;
    while (getline(inFile, line))
    {
      question.push_back(line.substr(3)); // remove qnNo prefix
      if (getline(inFile, line))
      {
        answer.push_back(line.substr(8)); // Remove "Answer: " prefix
      }
      else
      {
        cout << "Incomplete entry found in file." << endl; // Handle incomplete entry
        break;
      }
    }
    inFile.close();
  }

public:
  quiz()
  {
    fileName2 = "quizProject.txt";
    if (!question.size())
      load();
  }
  quiz(string f)
  {
    fileName2 = f;
    if (!question.size())
      load();
  }
  quiz(string f, string q, string a)
  {
    fileName2 = f;
    question.push_back(q);
    answer.push_back(a);
    if (!question.size())
      load();
    save();
  }
  void display()
  {
    if (question.size())
    {
      cout << "Quiz: " << endl;
      for (int i = 0; i < question.size(); i++)
      {
        cout << i + 1 << ". " << question[i] << endl;
        cout << "Answer: " << answer[i] << endl;
      }
    }
    else
      cout << "There are no questions available for quiz" << endl;
  }
  void add()
  {
    string q, a;
    cin.ignore();
    cout << "Question: ";
    getline(cin, q);
    cout << "Answer: ";
    getline(cin, a);
    question.push_back(q);
    answer.push_back(a);
    save();
    cout << "Quiz added successfully" << endl;
  }
  void add(string q, string a)
  {
    question.push_back(q);
    answer.push_back(a);
    save();
    cout << "Quiz added successfully" << endl;
  }
  void remove()
  {
    if (!question.size())
    {
      cout << "No questions available to remove." << endl;
      return;
    }
    int index;
    cout << "Enter no: " << endl;
    cin >> index;
    if (index >= 0 && index <= question.size())
    {
      question.erase(question.begin() + index - 1);
      answer.erase(answer.begin() + index - 1);
      cout << "Data removed successfully" << endl;
    }
    else
      cout << "Invalid index." << endl;
    save();
  }

  void update()
  {
    if (!question.size())
    {
      cout << "No questions available to update." << endl;
      return;
    }
    int index;
    string q, a;
    cout << "Enter no: " << endl;
    cin >> index;
    if (index < 0 || index > question.size())
      cout << "Invalid index." << endl;
    else
    {
      cin.ignore();
      cout << "New question: ";
      getline(cin, q);
      cout << "New answer: ";
      getline(cin, a);
      question[index - 1] = q;
      answer[index - 1] = a;
      save();
      cout << "Data updated successfully" << endl;
    }
    save();
  }
  // friend function
  friend void HighScore(int hs);
  void takeQuiz()
  {
    string s;
    int result = 0;
    cin.ignore();
    for (int i = 0; i < question.size(); i++)
    {
      cout << i + 1 << ". " << question[i] << endl;
      cout << "Answer: ";
      getline(cin, s);
      if (s == answer[i])
      {
        result++;
      }
      else
      {
        cout << "Incorrect" << endl;
        cout << "Correcr answer: " << answer[i] << endl;
      }
    }
    cout << "*****  Result Sheet  *****" << endl;
    cout << "Result: " << result << "/" << question.size() << endl;
    HighScore(result);
  }
};

class unitSchedule
{
  string date;
  string tasks;
  bool status;

public:
  unitSchedule()
  {
  }
  // constructor initialization before definition
  unitSchedule(string d, string t, bool s = 0) : date(d), tasks(t), status(s) {}
  friend class routine;
  friend ostream &cout(ostream &cout, unitSchedule s)
  {
    cout << "Date: " << s.date << endl;
    cout << "Tasks: " << s.tasks << endl;
    if (!s.status)
      cout << "Status: Incomplete." << endl;
    else
      cout << "Status: Completed." << endl;
    return cout;
  }
};

// diamond problem
class routine : public noteApp, public quiz
{
  vector<unitSchedule> schedule;
  string fileName3;
  void save()
  {
    ofstream outFile(fileName3);
    if (!outFile.is_open())
    {
      cerr << "Error opening the file" << endl;
      return;
    }
    if (!schedule.size())
    {
      outFile.close();
      return;
    }
    else
    {
      for (int i = 0; i < schedule.size(); i++)
      {
        outFile << "Date: " << schedule[i].date << endl;
        outFile << "Tasks: " << schedule[i].tasks << endl;
        outFile << "Status: " << schedule[i].status << endl;
      }
      outFile.close();
    }
  }
  void load()
  {
    ifstream inFile(fileName3);
    if (!inFile.is_open())
    {
      cout << "Error opening file." << std::endl;
      return;
    }
    string line, date, task, s;
    bool status;
    while (getline(inFile, line))
    {
      date = line.substr(6);
      if (getline(inFile, line))
      {
        task = line.substr(7); //
      }
      else
      {
        cout << "Incomplete entry found in file." << endl; // Handle incomplete entry
        break;
      }
      if (getline(inFile, line))
      {
        s = line.substr(8);
        if (s == "0")
          status = 0;
        else
          status = 1;
      }
      else
      {
        cout << "Incomplete entry found in file." << endl; // Handle incomplete entry
        break;
      }
      unitSchedule unit(date, task, status);
      schedule.push_back(unit);
    }
    inFile.close();
  }

public:
  routine()
  {
    fileName3 = "routineP.txt";
    if (!schedule.size())
      load();
  }
  routine(string f)
  {
    fileName3 = f;
    if (!schedule.size())
      load();
  }
  void add()
  {
    cout << "***  Routine ***" << endl;
    string input;
    string d;
    cout << "Enter date: ";
    cin.ignore();
    getline(cin, d);
    cout << "Enter task: ";
    getline(cin, input);
    unitSchedule unit(d, input);
    schedule.push_back(unit);
    save();
    cout << "Routine added successfully" << endl;
  }
  void remove()
  {
    if (!schedule.size())
    {
      cout << "No routine available to remove." << endl;
      return;
    }
    int index;
    cout << "Enter no: " << endl;
    cin >> index;
    if (index >= 0 && index <= schedule.size())
    {
      schedule.erase(schedule.begin() + index - 1);
      cout << "Routine removed successfully" << endl;
    }
    else
      cout << "Invalid index." << endl;
    save();
  }
  void display()
  {
    if (schedule.size() > 0)
    {
      cout << "Routine/s: " << endl;
      for (int i = 0; i < schedule.size(); i++)
      {
        cout << i + 1 << ". ";
        cout << "Date: " << schedule[i].date << endl;
        cout << "Tasks: " << schedule[i].tasks << endl;
        if (!schedule[i].status)
          cout << "Status: Incomplete." << endl;
        else
          cout << "Status: Completed." << endl;
      }
    }
    else
      cout << "There is no routine." << endl;
  }
  void update()
  {
    if (!schedule.size())
    {
      cout << "No routine available to update." << endl;
      return;
    }
    int index;
    string n;
    cout << "Enter no: " << endl;
    cin >> index;
    if (index < 0 || index > schedule.size())
      cout << "Invalid index." << endl;
    else
    {
      string input;
      string d;
      int status;
      cin.ignore();
      cout << "Enter new date: ";
      getline(cin, d);
      cout << "Enter new task: ";
      getline(cin, input);
      cout << "Enter new status(1/0): ";
      cin >> status;
      schedule[index - 1].date = d;
      schedule[index - 1].tasks = input;
      if (!status)
        schedule[index - 1].status = false;
      else
        schedule[index - 1].status = true;
      save();
      cout << "Routine updated successfully" << endl;
    }
    save();
  }
};

class user
{
  string username;
  string password;
  int score;
  vector<string> priorityList;

public:
  user()
  {
    string file = "user.txt";
    ifstream inFile(file);
    inFile >> score;
    inFile >> username;
    inFile >> password;
    inFile.close();
    score = 0;
  }
  user(string u, string p, int s = 0) : username(u), password(p), score(s)
  {
    string file = "user.txt";
    ofstream outFile(file);
    outFile << score << endl;
    outFile << username << endl;
    outFile << password << endl;
    outFile.close();
  }
  friend void HighScore(int hs);
  void createNewAccount()
  {
    cout << "Enter username: ";
    string name, pass;
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;
    // cout << "Account created." << endl;
    cout << "Information changed successfully" << endl;
    username = name;
    password = pass;
    score = 0;
    string file = "highScore.txt";
    ofstream outFile(file);
    outFile << score;
    outFile << username << endl;
    outFile << password << endl;
    outFile.close();
  }
  int userLogin()
  {
    cout << "Enter username: ";
    string name, pass;
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;
    if (username == name && password == pass)
    {
      cout << "Welcome" << endl;
      return 1;
    }
    else
    {
      cout << "Incorrect username or password." << endl;
      return 0;
    }
  }
};

// friend function
void HighScore(int hs)
{
  int score;
  string file = "highScore.txt";
  ifstream inFile(file);
  inFile >> score;
  inFile.close();
  if (score < hs)
  {
    cout << "You have the highest score." << endl;
    ofstream outFile(file);
    outFile << hs;
    outFile.close();
  }
}
// template
template <class T>
class StringCalculator
{
  T var1;
  T var2;

public:
  StringCalculator() {}
  StringCalculator(const T &a, const T &b) : var1(a), var2(b) {}

  int add()
  {
    return var1.length() + var2.length();
  }

  int subtract()
  {
    return var1.length() - var2.length();
  }

  int multiply()
  {
    return var1.length() * var2.length();
  }

  int divide()
  {
    if (var2.length() == 0)
    {
      std::cerr << "Error: Division by zero." << std::endl;
      return 0;
    }
    return var1.length() / var2.length();
  }
  // operator overloading
  // polymorphism
  friend istream &operator>>(istream &cin, StringCalculator &obj)
  {
    cout << "Enter two strings: " << endl;
    cout << "String 1: " << endl;
    cin >> obj.var1;
    cout << "String 2: " << endl;
    cin >> obj.var2;
    return cin;
  }
  friend ostream &operator<<(ostream &cout, StringCalculator &obj)
  {
    cout << "String1: " << obj.var1 << endl;
    cout << "String2: " << obj.var2 << endl;
    return cout;
  }
};
// its not the main function...beware!!!
int menu()
{
  while (true)
  {
    cout << "\nChoose an option:" << endl;
    cout << "1. Manage Notes" << endl;
    cout << "2. Manage Quiz" << endl;
    cout << "3. Manage Routine" << endl;
    cout << "4. String calculator" << endl;
    cout << "5. Exit" << endl;

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
      return 1;
      break;
    case 2:
      return 2;
      break;
    case 3:
      return 3;
      break;
    case 4:
      return 4;
      break;
    case 5:
      cout << "Goodbye!" << endl;
      return 0;
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  }
}

int main()
{
  system("CLS");
  user u;
  int t = 1;
  while (t)
  {
    cout << "\nChoose an option:" << endl;
    cout << "1. Login" << endl;
    cout << "2. Change Info" << endl;
    cout << "3. Exit" << endl;
    int option;
    cin >> option;
    switch (option)
    {
    case 1:
      if (u.userLogin())
      {
        t = 0;
        break;
      }
      else
        cout << "Wrong password or username. Please try again." << endl;
      break;
    case 2:
      if (u.userLogin())
      {
        u.createNewAccount();
        break;
      }
      else
        cout << "Wrong password or username. Please try again." << endl;
      break;
    case 3:
      cout << "Goodbye!" << endl;
      exit(0); // exit(0) to exit the program
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  }
  routine r;
  int option = menu();
  if (!option)
  {
    return 0;
  }

  else if (option == 4)
  {
    while (true)
    {
      cout << "\nChoose an option:" << endl;
      cout << "1. Add" << endl;
      cout << "2. Substract" << endl;
      cout << "3. Multiply" << endl;
      cout << "4. Divide" << endl;
      cout << "5. Exit" << endl;
      int choice;
      cin >> choice;
      StringCalculator<string> obj;
      cin >> obj;
      switch (choice)
      {
      case 1:
        cout << "Addition: " << obj.add() << endl;
        break;
      case 2:
        cout << "Subtraction: " << obj.subtract() << endl;
        break;
      case 3:
        cout << "Multiplication: " << obj.multiply() << endl;
        break;
      case 4:
        cout << "Division: " << obj.divide() << endl;
        break;
      case 5:
        cout << "Goodbye!" << endl;
        exit(0);
      default:
        cout << "Invalid choice. Please try again." << endl;
      }
    }
  }
  else
  {
    while (true)
    {
      cout << "\nChoose an option:" << endl;
      cout << "1. Create" << endl;
      cout << "2. Remove" << endl;
      cout << "3. Update" << endl;
      cout << "4. View" << endl;
      cout << "5. Exit" << endl;
      if (option == 2)
        cout << "6.Take a quiz" << endl;
      int choice;
      cin >> choice;
      if (option == 1)
        switch (choice)
        {
        case 1:
          r.noteApp::add();
          break;
        case 2:
          r.noteApp::remove();
          break;
        case 3:
          r.noteApp::update();
          break;
        case 4:
          r.noteApp::display();
          break;
        case 5:
          cout << "Goodbye!" << endl;
          return 0;
        default:
          cout << "Invalid choice. Please try again." << endl;
        }
      else if (option == 2)
      {
        switch (choice)
        {
        case 1:
          r.quiz::add();
          break;
        case 2:
          r.quiz::remove();
          break;
        case 3:
          r.quiz::update();
          break;
        case 4:
          r.quiz::display();
          break;
        case 6:
          r.takeQuiz();
          break;
        case 5:
          cout << "Goodbye!" << endl;
          return 0;
        default:
          cout << "Invalid choice. Please try again." << endl;
        }
      }
      if (option == 3)
        switch (choice)
        {
        case 1:
          r.routine::add();
          break;
        case 2:
          r.routine::remove();
          break;
        case 3:
          r.routine::update();
          break;
        case 4:
          r.routine::display();
          break;
        case 5:
          cout << "Goodbye!" << endl;
          return 0;
        default:
          cout << "Invalid choice. Please try again." << endl;
        }
    }
  }
}