
#include <iostream>
#include <string>
using namespace std;

// Parent class
class Character
{
protected:
    string name;

public:
    Character(string n)
    {
        name = n;
    }

    virtual void speak()
    {
        cout << name << " is speaking.\n";
    }

    string getName()
    {
        return name;
    }

    virtual ~Character() {}
};

// Child class: Detective
class Detective : public Character
{
public:
    Detective(string n) : Character(n) {}

    void speak() override
    {
        cout << "\nDetective " << name
             << ": I will solve this mystery!\n";
    }

    void investigate()
    {
        cout << "Detective " << name
             << " begins investigating the diamond theft.\n";
    }
};

// Child class: Suspect
class Suspect : public Character
{
private:
    string alibi;
    string clue;
    bool guilty;
    bool questioned;

public:
    Suspect(string n, string a, string c, bool g)
        : Character(n)
    {
        alibi = a;
        clue = c;
        guilty = g;
        questioned = false;
    }

    void speak() override
    {
        cout << name << " says: " << alibi << "\n";
        cout << "Evidence found: " << clue << "\n";
        questioned = true;
    }

    bool isGuilty()
    {
        return guilty;
    }

    bool wasQuestioned()
    {
        return questioned;
    }
};

// Main function
int main()
{
    Detective detective("Anu");

    Suspect s1(
        "Rahul",
        "I was reading in the library.",
        "A book was left open on the desk.",
        false
    );

    Suspect s2(
        "Priya",
        "I was near the jewellery room.",
        "A diamond-shaped pendant was found near her.",
        true
    );

    Suspect s3(
        "Kiran",
        "I was preparing dinner in the kitchen.",
        "The kitchen clock stopped at 8 PM.",
        false
    );

    Suspect* suspects[3] = {&s1, &s2, &s3};

    int choice;
    int accusation;
    int questionsLeft = 3;
    bool caseSolved = false;

    cout << "========================================\n";
    cout << "       THE MYSTERY DETECTIVE\n";
    cout << "========================================\n";

    cout << "\nA precious diamond has disappeared!\n";
    cout << "Three people were inside the mansion.\n";
    cout << "Find the culprit before the case goes cold.\n";

    detective.speak();
    detective.investigate();

    while (!caseSolved)
    {
        cout << "\nQuestions remaining: " << questionsLeft << "\n";

        cout << "\n1. Question Rahul\n";
        cout << "2. Question Priya\n";
        cout << "3. Question Kiran\n";
        cout << "4. Accuse a suspect\n";
        cout << "5. View investigation report\n";
        cout << "6. Quit game\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n";
            return 0;
        }

        if (choice >= 1 && choice <= 3)
        {
            if (questionsLeft == 0)
            {
                cout << "No questions remain! Make an accusation.\n";
                continue;
            }

            if (suspects[choice - 1]->wasQuestioned())
            {
                cout << "You have already questioned this suspect.\n";
                continue;
            }

            cout << "\n--- Suspect Interview ---\n";
            suspects[choice - 1]->speak();
            questionsLeft--;
        }
        else if (choice == 4)
        {
            cout << "\nWho stole the diamond?\n";
            cout << "1. Rahul\n";
            cout << "2. Priya\n";
            cout << "3. Kiran\n";
            cout << "Enter suspect number: ";

            if (!(cin >> accusation))
            {
                cout << "Invalid input.\n";
                return 0;
            }

            if (accusation < 1 || accusation > 3)
            {
                cout << "Invalid suspect number!\n";
                continue;
            }

            if (suspects[accusation - 1]->isGuilty())
            {
                cout << "\n*** CASE SOLVED! ***\n";
                cout << suspects[accusation - 1]->getName()
                     << " stole the diamond!\n";
                cout << "Excellent detective work!\n";
                caseSolved = true;
            }
            else
            {
                cout << "\nWrong accusation!\n";
                cout << "That suspect is innocent.\n";

                if (questionsLeft == 0)
                {
                    cout << "You have no questions left.\n";
                    cout << "The case remains unsolved.\n";
                    break;
                }

                cout << "You can continue investigating.\n";
            }
        }
        else if (choice == 5)
        {
            cout << "\n====== INVESTIGATION REPORT ======\n";

            for (int i = 0; i < 3; i++)
            {
                cout << i + 1 << ". "
                     << suspects[i]->getName() << ": ";

                if (suspects[i]->wasQuestioned())
                {
                    cout << "Interview completed.\n";
                }
                else
                {
                    cout << "Not questioned yet.\n";
                }
            }

            cout << "Questions remaining: "
                 << questionsLeft << "\n";
        }
        else if (choice == 6)
        {
            cout << "\nYou left the investigation.\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }
    }

    if (caseSolved)
    {
        cout << "\nCase closed, Detective!\n";
    }
    else
    {
        cout << "\nInvestigation ended.\n";
        cout << "The correct culprit was Priya.\n";
    }

    cout << "Thank you for playing!\n";

    return 0;
}
