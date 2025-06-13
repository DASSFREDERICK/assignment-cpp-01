#include <iostream>
#include <fstream>
#include <stdlib.h> // For system("CLS") as per example
#include <cstring>
#include <string>

using namespace std;

const int MAX_CARDS = 100;


// first class
class Flashcard {
public:
    char question[250];
    char answer[250];
    int score;

    Flashcard() : score(0) {
        question[0] = '\0';
        answer[0] = '\0';
    }

    void resetScore() {
        score = 0;
    }

    void display() {
        cout << "\n-----------------------------\n";
        cout << "Question: " << question << endl;
        cout << "Press 9 to reveal the answer: ";
        int opt;
        cin >> opt;
        if (opt == 9) {
            cout << "Answer: " << answer << endl;
            cout << "Rate difficulty (1 = Easy, 2 = Medium, 3 = Hard): ";
            int difficulty;
            cin >> difficulty;
            if (difficulty == 1) score += 1;
            else if (difficulty == 2) score += 2;
            else if (difficulty == 3) score += 3;
        }
        cout << "-----------------------------\n";
    }};


// second class
class FlashcardManager {
private:
    Flashcard flashcards[MAX_CARDS];
    int count;

public:
    FlashcardManager() : count(0) {}

    void addFlashcard(string q, string a) {
        if (count < MAX_CARDS) {
            strncpy(flashcards[count].question, q.c_str(), sizeof(flashcards[count].question));
            strncpy(flashcards[count].answer, a.c_str(), sizeof(flashcards[count].answer));
            flashcards[count].score = 0;
            count++;
            cout << "\n* Flashcard added successfully! *\n";
        } else {
            cout << "\n! Max flashcards reached. !\n";
        }}

    void removeFlashcard() {
        if (count == 0) {
            cout << "\nNo flashcards to remove.\n";
            return;
        }

        cout << "\n-- Flashcards List --\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << flashcards[i].question << endl;
        }
        cout << "\nEnter the number to remove: ";
        int index;
        cin >> index;
        if (index > 0 && index <= count) {
            for (int i = index - 1; i < count - 1; i++) {
                flashcards[i] = flashcards[i + 1];
            }
            count--;
            cout << "\n* Flashcard removed successfully. *\n";
        } else {
            cout << "\nInvalid index.\n";
        }}

    void resetAllScores() {
        for (int i = 0; i < count; i++) {
            flashcards[i].resetScore();
        }}

    void reviewFlashcards() {
        system("cls");
        cout << "\n========= Review Flashcards =========\n";
        if (count == 0) {
            cout << "\nNo flashcards available.\n";
            return;
        }
        resetAllScores();  // Reset scores before review
        for (int i = 0; i < count; i++) {
            flashcards[i].display();
        }
        cout << "====================================\n";
    }

    void viewProgress() {
        system("cls");
        cout << "\n========= Progress Report =========\n\n";
        if (count == 0) {
            cout << "No flashcards to show progress.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << "Q: " << flashcards[i].question << "\nScore: " << flashcards[i].score << " ";
            for (int j = 0; j < flashcards[i].score; j++) cout << "*";
            cout << "\n-----------------------------\n";
        }}

    void saveToFile(const string& filename) {
        ofstream file(filename, ios::binary);
        if (!file) {
            cout << "Error saving to file.\n";
            return;
        }
        file.write((char*)&count, sizeof(count));
        file.write((char*)&flashcards, sizeof(Flashcard) * count);
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cout << "Starting fresh.\n";
            return;
        }
        file.read((char*)&count, sizeof(count));
        file.read((char*)&flashcards, sizeof(Flashcard) * count);
        file.close();
    }};


// Third class
class User {
private:
    string name;

public:
    void setName(const string& n) {
        name = n;
    }

    string getName() const {
        return name;
    }

    void greet() const {
        cout << "\nHi " << name << ", Welcome to Flashcards Mania by Frederick.\n";
        cout << "\"Education is the passport to the future, for tomorrow belongs to those who prepare for it today.\"\n";
    }};


// Fourth class
class Helper {
public:
    static void calculator() {
        system("cls");
        cout << "\n========= Mini Calculator =========\n\n";
        double num1, num2;
        char op;

        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter operator (+, -, *, /): ";
        cin >> op;
        cout << "Enter second number: ";
        cin >> num2;

        switch (op) {
            case '+': cout << "Result: " << num1 + num2 << endl; break;
            case '-': cout << "Result: " << num1 - num2 << endl; break;
            case '*': cout << "Result: " << num1 * num2 << endl; break;
            case '/':
                if (num2 != 0)
                    cout << "Result: " << num1 / num2 << endl;
                else
                    cout << "Cannot divide by zero." << endl;
                break;
            default:
                cout << "Invalid operator." << endl;
        }
        cout << "===================================\n";
    }
};


// Fifth class
class App {
private:
    FlashcardManager fm;
    User user;

public:
    void run() {
        system("cls");
        cout << "===============================\n";
        cout << "Enter your name: ";
        string uname;
        getline(cin, uname);
        user.setName(uname);

        user.greet();
        cout << "===============================\n\n";

        fm.loadFromFile("flashcards.dat");

        int choice;
        do {
            cout << "\n========= Flashcard Generator =========\n";
            cout << "1. Add Flashcard\n";
            cout << "2. Remove Flashcard\n";
            cout << "3. Review Flashcards\n";
            cout << "4. View Progress\n";
            cout << "5. Credits\n";
            cout << "6. Mini Calculator\n";
            cout << "7. Save and Exit\n";
            cout << "=======================================\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: {
                    system("cls");
                    string q, a;
                    cout << "\n========= Add Flashcard =========\n";
                    cout << "Enter Question: ";
                    getline(cin, q);
                    cout << "Enter Answer: ";
                    getline(cin, a);
                    fm.addFlashcard(q, a);
                    cout << "=================================\n";
                    break;
                }
                case 2:
                    system("cls");
                    fm.removeFlashcard();
                    fm.saveToFile("flashcards.dat");
                    break;
                case 3:
                    fm.reviewFlashcards();
                    fm.saveToFile("flashcards.dat");
                    break;
                case 4:
                    fm.viewProgress();
                    break;
                case 5:
                    system("cls");
                    cout << "\n========= Credits =========\n";
                    cout << "This is a successful flashcard generating program\n";
                    cout << "created by 2 brilliant MMU students:\n";
                    cout << "1211109968 Frederick\n";
                    cout << "1211109445\n";
                    cout << "For Object Oriented C++ subject assignment\n";
                    cout << "given by Mr. Mohd Haris Lye.\n";
                    cout << "===========================\n";
                    break;
                case 6:
                    Helper::calculator();
                    break;
                case 7:
                    fm.saveToFile("flashcards.dat");
                    cout << "\nGoodbye, " << user.getName() << "!\n";
                    break;
                default:
                    cout << "\nInvalid choice.\n";
            }
        } while (choice != 7);
    }};

int main() {
    App app;
    app.run();
    return 0;
}

