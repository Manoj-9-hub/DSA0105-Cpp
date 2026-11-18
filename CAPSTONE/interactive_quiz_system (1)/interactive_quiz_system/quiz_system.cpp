// Interactive Quiz System - C++ console implementation
// Demonstrates inline functions for scoring, percentage and result evaluation.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Question {
    string text;
    string options[4];
    int correct; // 0=A, 1=B, 2=C, 3=D
};

// Module 1: Question Bank Management
void addQuestion(vector<Question>& bank) {
    Question q;
    cout << "\nEnter question: ";
    cin.ignore();
    getline(cin, q.text);
    for (int i = 0; i < 4; i++) {
        cout << "Enter option " << char('A' + i) << ": ";
        getline(cin, q.options[i]);
    }
    cout << "Enter correct option (1-4): ";
    cin >> q.correct;
    q.correct--;
    if (q.correct < 0 || q.correct > 3) {
        cout << "Invalid answer. Question not added.\n";
        return;
    }
    bank.push_back(q);
    cout << "Question added successfully.\n";
}

void displayQuestions(const vector<Question>& bank) {
    for (int i = 0; i < (int)bank.size(); i++)
        cout << i + 1 << ". " << bank[i].text << '\n';
}

// Module 2: Quiz Execution
// Inline function displays one question and returns the selected option.
inline int askQuestion(const Question& q, int number) {
    cout << "\nQ" << number << ". " << q.text << '\n';
    for (int i = 0; i < 4; i++)
        cout << char('A' + i) << ") " << q.options[i] << '\n';
    int answer;
    cout << "Your answer (A=1, B=2, C=3, D=4): ";
    cin >> answer;
    return answer - 1;
}

// Module 3: Scoring & Evaluation
inline int calculateScore(const vector<Question>& bank,
                          const vector<int>& answers) {
    int score = 0;
    for (int i = 0; i < (int)bank.size(); i++)
        if (answers[i] == bank[i].correct) score++;
    return score;
}

inline double calculatePercentage(int score, int total) {
    return total == 0 ? 0.0 : (score * 100.0) / total;
}

inline string evaluateResult(double percentage) {
    return percentage >= 50.0 ? "PASS" : "NEEDS IMPROVEMENT";
}

// Module 4: Report Generation
void generateReport(const string& name, int score, int total) {
    double percentage = calculatePercentage(score, total);
    cout << "\n========== QUIZ REPORT ==========\n";
    cout << "Student Name : " << name << '\n';
    cout << "Score        : " << score << " / " << total << '\n';
    cout << "Percentage   : " << percentage << "%\n";
    cout << "Result       : " << evaluateResult(percentage) << '\n';
    cout << "=================================\n";
}

int main() {
    vector<Question> bank = {
        {"Which function is the entry point of a C++ program?",
         {"start()", "main()", "begin()", "run()"}, 1},
        {"Which keyword requests an inline function?",
         {"static", "friend", "inline", "virtual"}, 2},
        {"Which symbol ends most C++ statements?",
         {";", ":", ".", ","}, 0}
    };

    string studentName;
    int choice;

    cout << "===== INTERACTIVE QUIZ SYSTEM =====\n";
    cout << "Enter student name: ";
    getline(cin, studentName);

    do {
        cout << "\n1. Add Question\n2. View Question Bank\n"
             << "3. Start Quiz\n4. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            addQuestion(bank);
        } else if (choice == 2) {
            displayQuestions(bank);
        } else if (choice == 3) {
            if (bank.empty()) {
                cout << "Question bank is empty.\n";
                continue;
            }
            vector<int> answers;
            for (int i = 0; i < (int)bank.size(); i++)
                answers.push_back(askQuestion(bank[i], i + 1));

            int score = calculateScore(bank, answers);
            generateReport(studentName, score, (int)bank.size());
        } else if (choice != 4) {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    cout << "Thank you for using the quiz system.\n";
    return 0;
}
