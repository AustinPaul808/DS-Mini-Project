
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

const int CATEGORY_COUNT = 5;
const int BUCKET_COUNT = 5;

const string CATEGORIES[CATEGORY_COUNT] = {
    "Web Development",
    "Graphic Design",
    "Accounting",
    "Cybersecurity",
    "Data Analysis"
};

// Stores all information about one opportunity.
struct Opportunity {
    int id;
    string title;
    string category;
    string type;
    string organisation;
    string location;
    string duration;
};

// Remove leading and trailing spaces.
string trim(const string& text) {
    size_t first = text.find_first_not_of(" \t\r\n");

    if (first == string::npos) {
        return "";
    }

    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

// Convert text to lowercase for category comparison.
string toLowerCase(const string& text) {
    string result = text;

    for (size_t i = 0; i < result.size(); i++) {
        result[i] = static_cast<char>(
            tolower(static_cast<unsigned char>(result[i]))
        );
    }

    return result;
}

// Return the standard spelling of a supported category.
// Return an empty string if the category is unsupported.
string normaliseCategory(const string& input) {
    string cleaned = trim(input);

    for (int i = 0; i < CATEGORY_COUNT; i++) {
        if (toLowerCase(cleaned) == toLowerCase(CATEGORIES[i])) {
            return CATEGORIES[i];
        }
    }

    return "";
}

// Read a non-empty string. Spaces inside names are allowed.
bool readRequiredText(const string& prompt, string& value) {
    while (true) {
        cout << prompt;

        if (!getline(cin, value)) {
            return false;
        }

        value = trim(value);

        if (!value.empty()) {
            return true;
        }

        cout << "Input cannot be empty. Please try again.\n";
    }
}

// Read one integer from a complete input line.
// Extra characters, such as "2abc", are rejected.
bool readInteger(const string& prompt, int& value) {
    string line;

    cout << prompt;

    if (!getline(cin, line)) {
        return false;
    }

    stringstream input(line);
    char extra;

    if (!(input >> value) || (input >> extra)) {
        cout << "Invalid input. Please enter a whole number.\n";
        return false;
    }

    return true;
}

// A node in a singly linked list.
struct Node {
    Opportunity data;
    Node* next;

    Node(const Opportunity& opportunity)
        : data(opportunity), next(nullptr) {
    }
};

class JobSkillMatcher {
private:
    // Each bucket points to the first node of its linked list.
    Node* buckets[BUCKET_COUNT];

    // Hash the category using the sum of its character codes.
    // The result is always between 0 and BUCKET_COUNT - 1.
    int hashCategory(const string& category) const {
        unsigned int sum = 0;

        for (size_t i = 0; i < category.size(); i++) {
            sum += static_cast<unsigned char>(category[i]);
        }

        return static_cast<int>(sum % BUCKET_COUNT);
    }

    // Find an ID in every bucket.
    // IDs are unique across the entire directory.
    bool idExists(int id) const {
        for (int i = 0; i < BUCKET_COUNT; i++) {
            Node* current = buckets[i];

            while (current != nullptr) {
                if (current->data.id == id) {
                    return true;
                }

                current = current->next;
            }
        }

        return false;
    }

    // Insert a record at the beginning of its category's bucket chain.
    void insertRecord(const Opportunity& opportunity) {
        int index = hashCategory(opportunity.category);

        Node* newNode = new Node(opportunity);
        newNode->next = buckets[index];
        buckets[index] = newNode;
    }

    // Release all nodes in every linked list.
    void clearAll() {
        for (int i = 0; i < BUCKET_COUNT; i++) {
            Node* current = buckets[i];

            while (current != nullptr) {
                Node* nodeToDelete = current;
                current = current->next;
                delete nodeToDelete;
            }

            buckets[i] = nullptr;
        }
    }

    void printOpportunity(const Opportunity& opportunity) const {
        cout << "  ID: " << opportunity.id << '\n';
        cout << "  Title: " << opportunity.title << '\n';
        cout << "  Category: " << opportunity.category << '\n';
        cout << "  Type: " << opportunity.type << '\n';
        cout << "  Organisation: " << opportunity.organisation << '\n';
        cout << "  Location: " << opportunity.location << '\n';
        cout << "  Duration / Work arrangement: "
             << opportunity.duration << '\n';
        cout << "----------------------------------------\n";
    }

public:
    JobSkillMatcher() {
        for (int i = 0; i < BUCKET_COUNT; i++) {
            buckets[i] = nullptr;
        }

        loadSampleData();
    }

    // Copying is disabled to prevent accidental shallow copies
    // of owned linked-list nodes.
    JobSkillMatcher(const JobSkillMatcher&) = delete;
    JobSkillMatcher& operator=(const JobSkillMatcher&) = delete;

    ~JobSkillMatcher() {
        clearAll();
    }

    void loadSampleData() {
        Opportunity samples[] = {
            {101, "Frontend Web Developer", "Web Development",
             "Full-time job", "BrightWeb Solutions", "Mumbai",
             "Full-time"},

            {102, "Junior Web Developer", "Web Development",
             "Entry-level job", "PixelTech Studio", "Navi Mumbai",
             "Full-time"},

            {103, "Web Development Trainee", "Web Development",
             "Trainee position", "CodeBridge Academy", "Online",
             "8 weeks"},

            {104, "Graphic Designer", "Graphic Design",
             "Full-time job", "CreativeNest Studio", "Mumbai",
             "Full-time"},

            {105, "Graphic Design Intern", "Graphic Design",
             "Internship", "DesignStart Academy", "Online",
             "2 months"},

            {106, "Accounts Assistant", "Accounting",
             "Full-time job", "FinEdge Services", "Mumbai",
             "Full-time"},

            {107, "Junior Accountant", "Accounting",
             "Entry-level job", "SkillPoint Institute", "Mumbai",
             "Full-time"},

            {108, "Cybersecurity Analyst", "Cybersecurity",
             "Full-time job", "SecureNet Labs", "Mumbai",
             "Full-time"},

            {109, "Security Operations Centre (SOC) Analyst - L1",
             "Cybersecurity", "Entry-level job", "CyberLearn Academy",
             "Mumbai", "Full-time"},

            {110, "Data Analyst", "Data Analysis",
             "Full-time job", "InsightWorks", "Mumbai",
             "Full-time"},

            {111, "Junior Data Analyst", "Data Analysis",
             "Entry-level job", "DataSkills Hub", "Navi Mumbai",
             "Full-time"},

            {112, "Data Analyst Intern", "Data Analysis",
             "Internship", "QueryWorks", "Online",
             "3 months"}
        };

        int sampleCount =
            static_cast<int>(sizeof(samples) / sizeof(samples[0]));

        for (int i = 0; i < sampleCount; i++) {
            insertRecord(samples[i]);
        }
    }

    void displayCategories() const {
        for (int i = 0; i < CATEGORY_COUNT; i++) {
            cout << "  " << i + 1 << ". " << CATEGORIES[i] << '\n';
        }
    }

    // Add an opportunity after validating every required field.
    void addOpportunity() {
        Opportunity opportunity;

        cout << "\n========== ADD OPPORTUNITY ==========\n";

        while (true) {
            if (!readInteger("Enter unique positive ID: ",
                             opportunity.id)) {
                return;
            }

            if (opportunity.id <= 0) {
                cout << "ID must be a positive integer.\n";
                continue;
            }

            if (idExists(opportunity.id)) {
                cout << "ID already exists. Please enter a different ID.\n";
                continue;
            }

            break;
        }

        if (!readRequiredText("Enter opportunity title: ",
                              opportunity.title)) {
            return;
        }

        string categoryInput;

        while (true) {
            if (!readRequiredText(
                    "Enter skill category (use one of the five listed "
                    "categories): ", categoryInput)) {
                return;
            }

            opportunity.category = normaliseCategory(categoryInput);

            if (!opportunity.category.empty()) {
                break;
            }

            cout << "Unsupported category. Choose from:\n";
            displayCategories();
        }

        if (!readRequiredText("Enter opportunity type: ",
                              opportunity.type)) {
            return;
        }

        if (!readRequiredText("Enter organisation: ",
                              opportunity.organisation)) {
            return;
        }

        if (!readRequiredText("Enter location: ",
                              opportunity.location)) {
            return;
        }

        if (!readRequiredText("Enter duration/work arrangement: ",
                              opportunity.duration)) {
            return;
        }

        insertRecord(opportunity);

        cout << "\nOpportunity added successfully.\n";
        cout << "Current total records: ";
        cout << countAllOpportunities() << '\n';
    }

    // Search the chain for the selected category.
    void searchBySkill() const {
        cout << "\n========== SEARCH BY SKILL ==========\n";
        displayCategories();

        int choice;

        while (true) {
            if (!readInteger("Choose a category (1-5): ", choice)) {
                return;
            }

            if (choice >= 1 && choice <= CATEGORY_COUNT) {
                break;
            }

            cout << "Invalid category choice. Enter a number from 1 to 5.\n";
        }

        string selectedCategory = CATEGORIES[choice - 1];
        int index = hashCategory(selectedCategory);

        Node* current = buckets[index];
        int found = 0;

        cout << "\nResults for: " << selectedCategory << "\n";
        cout << "========================================\n";

        while (current != nullptr) {
            if (current->data.category == selectedCategory) {
                printOpportunity(current->data);
                found++;
            }

            current = current->next;
        }

        if (found == 0) {
            cout << "No opportunities found for "
                 << selectedCategory << ".\n";
        } else {
            cout << "Matching opportunities: " << found << '\n';
        }
    }

    // Display all records grouped by category.
    void displayAll() const {
        cout << "\n========== ALL OPPORTUNITIES ==========\n";

        int total = 0;

        for (int c = 0; c < CATEGORY_COUNT; c++) {
            int index = hashCategory(CATEGORIES[c]);
            Node* current = buckets[index];
            int categoryCount = 0;

            cout << "\n[" << CATEGORIES[c] << "]\n";

            while (current != nullptr) {
                if (current->data.category == CATEGORIES[c]) {
                    printOpportunity(current->data);
                    categoryCount++;
                }

                current = current->next;
            }

            if (categoryCount == 0) {
                cout << "No opportunities in this category.\n";
            }

            total += categoryCount;
        }

        if (total == 0) {
            cout << "\nThe directory is empty. Add an opportunity to begin.\n";
        }

        cout << "\nTotal opportunities displayed: " << total << '\n';
    }

    // Locate an ID by traversing all chains, then unlink its node.
    void deleteOpportunity() {
        cout << "\n========== DELETE OPPORTUNITY ==========\n";

        int id;

        if (!readInteger("Enter the ID to delete: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID must be a positive integer.\n";
            return;
        }

        for (int i = 0; i < BUCKET_COUNT; i++) {
            Node* current = buckets[i];
            Node* previous = nullptr;

            while (current != nullptr) {
                if (current->data.id == id) {
                    // If this is the first node, update the bucket head.
                    if (previous == nullptr) {
                        buckets[i] = current->next;
                    } else {
                        previous->next = current->next;
                    }

                    delete current;

                    cout << "Opportunity ID " << id
                         << " deleted successfully.\n";
                    cout << "Remaining records: "
                         << countAllOpportunities() << '\n';
                    return;
                }

                previous = current;
                current = current->next;
            }
        }

        cout << "No opportunity found with ID " << id << ".\n";
    }

    int countAllOpportunities() const {
        int total = 0;

        for (int i = 0; i < BUCKET_COUNT; i++) {
            Node* current = buckets[i];

            while (current != nullptr) {
                total++;
                current = current->next;
            }
        }

        return total;
    }
};

void displayMenu() {
    cout << "\n========================================\n";
    cout << "       LOCAL JOB SKILL MATCHER\n";
    cout << "========================================\n";
    cout << "1. Add a new opportunity\n";
    cout << "2. Search opportunities by preferred skill\n";
    cout << "3. Display all opportunities\n";
    cout << "4. Delete an outdated opportunity by ID\n";
    cout << "5. Exit\n";
    cout << "========================================\n";
}

int main() {
    JobSkillMatcher matcher;

    cout << "Welcome to Local Job Skill Matcher!\n";
    cout << "Notice: Initial listings are fictional demo data, "
            "not verified vacancies.\n";

    while (true) {
        displayMenu();

        int choice;

        if (!readInteger("Enter your choice (1-5): ", choice)) {
            if (cin.eof()) {
                cout << "\nInput ended. Exiting safely.\n";
                break;
            }

            // A malformed menu entry has already been reported.
            continue;
        }

        switch (choice) {
            case 1:
                matcher.addOpportunity();
                break;

            case 2:
                matcher.searchBySkill();
                break;

            case 3:
                matcher.displayAll();
                break;

            case 4:
                matcher.deleteOpportunity();
                break;

            case 5:
                cout << "\nThank you for using Local Job Skill Matcher.\n";
                cout << "Releasing memory and exiting...\n";
                return 0;

            default:
                cout << "Invalid menu option. Please choose 1, 2, 3, 4, or 5.\n";
        }
    }

    // The destructor releases every remaining linked-list node.
    return 0;
}
