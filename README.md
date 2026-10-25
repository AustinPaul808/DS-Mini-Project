
# Local Job Skill Matcher

## 1. Project Overview

Local Job Skill Matcher is a beginner-friendly C++ console-based Data Structures micro-project. It maintains a directory of job, internship, and training opportunities and allows users to add, search, display, and delete records.

The project demonstrates a custom hash table using separate chaining with singly linked lists.

**Important:** The 12 initial listings and their organisation names are fictional demonstration data. They are not verified real vacancies.

## 2. Problem Statement

Students and job seekers may find it difficult to organise opportunities according to their skills. This project provides a simple local directory where opportunities can be categorised by skill and retrieved through a menu-driven interface.

## 3. Objectives

- Maintain a directory of opportunities.
- Search for opportunities by preferred skill category.
- Add new records with validation and unique IDs.
- Delete outdated records safely.
- Demonstrate hashing, collisions, linked lists, traversal, insertion, and deletion.
- Apply basic memory management in C++.

## 4. Sustainable Development Goal

The project is connected to **UN Sustainable Development Goal 8: Decent Work and Economic Growth**.

SDG 8 focuses on promoting sustained, inclusive and sustainable economic growth, productive employment, and decent work. A directory that organises employment, internship, and training opportunities can support access to information about work and skill development.

This project is an educational prototype. It does not itself provide verified vacancies or guarantee employment.

## 5. Skill Categories

The program supports exactly five categories:

1. Web Development
2. Graphic Design
3. Accounting
4. Cybersecurity
5. Data Analysis

Category matching ignores letter case. For example, `web development` and `Web Development` are treated as the same category. The category must otherwise match one of the five supported names.

## 6. Initial Sample Data

The program loads 12 fictional records at startup.

| Category | IDs | Number of records |
|---|---|---:|
| Web Development | 101, 102, 103 | 3 |
| Graphic Design | 104, 105 | 2 |
| Accounting | 106, 107 | 2 |
| Cybersecurity | 108, 109 | 2 |
| Data Analysis | 110, 111, 112 | 3 |
| **Total** | **101–112** | **12** |

Every record contains an ID, title, skill category, opportunity type, organisation, location, and duration/work arrangement.

## 7. Features

1. Add a new opportunity.
2. Search opportunities by preferred skill.
3. Display all opportunities grouped by category.
4. Delete an opportunity by ID.
5. Exit safely.
6. Reject invalid IDs, duplicate IDs, unsupported categories, and empty required fields.
7. Handle malformed numeric input without an infinite loop.
8. Release dynamically allocated memory on exit.

## 8. Data Structures

### Hash table

The program implements a hash table using a fixed array of five bucket-head pointers.

It does not use `unordered_map` or another built-in container to implement the main data structure.

### Hash function

For a category string, the program adds the character codes and calculates the remainder after division by five:

    hash(category) = sum of character codes % 5

The result is an index from 0 to 4.

The function is simple and suitable for demonstrating hashing. It is not intended to provide an optimal distribution for arbitrary strings.

### Separate chaining

Two or more categories can produce the same hash index. This is called a collision.

Separate chaining handles a collision by storing nodes in the linked list belonging to that bucket.

Each node contains one complete opportunity and a pointer to the next node. During a search, the program traverses the appropriate bucket and checks the exact category. Therefore, a collision does not cause results from another category to be returned.

### Linked list

A singly linked list is used to store opportunity nodes. Insertion takes place at the head of the selected chain.

Deletion handles two cases:

- The target node is the first node: update the bucket head.
- The target node is elsewhere: update the previous node's `next` pointer.

The removed node is deleted from dynamic memory.

### Unique IDs

Before inserting a new opportunity, the program scans all buckets to ensure that its ID does not already exist. This prevents duplicate IDs across categories.

## 9. Assumptions and Limitations

- The directory exists only while the program is running.
- Records are not saved to a file or database.
- The five supported categories are fixed.
- IDs must be positive integers and unique across the directory.
- All required text fields must be non-empty.
- Category matching is case-insensitive but must match a supported category.
- The program does not verify real employers, vacancies, or job offers.
- A record's duration/work arrangement is stored as text to accommodate values such as `Full-time`, `8 weeks`, and `3 months`.
- The program uses dynamically allocated singly linked-list nodes and releases them when deleted or when the program exits.

## 10. Compilation and Execution

Requirements: a C++ compiler such as g++ and a terminal in the project directory.

On Windows using VS Code with MSYS2 UCRT64 configured:

    g++ main.cpp -o main.exe
    .\main.exe

The program uses standard C++ headers only and does not require external libraries.

## 11. Testing

The test suite should cover:

- Searching Web Development and confirming IDs 101, 102, and 103.
- Searching each remaining category and confirming only its records appear.
- Adding an opportunity and subsequently finding it.
- Deleting an opportunity and confirming it no longer appears.
- Searching a category after all its records have been deleted.
- Entering an invalid menu option and non-numeric menu input.
- Attempting to add a duplicate ID.
- Entering an unsupported category or empty required field.
- Deleting a non-existent ID.
- Displaying all opportunities when the directory is empty.

See the test table and sample walkthroughs in the project submission notes.

## 12. Time Complexity

Let:
- N = total number of records.
- L = length of the chain at the selected bucket.
- B = number of buckets, fixed at 5.

| Operation | Average / typical cost | Worst case |
|---|---|---|
| Hash calculation | O(K) | O(K) |
| Linked-list insertion after validation | O(1) | O(1) |
| Add including duplicate-ID check | O(N + K) | O(N + K) |
| Search by skill | O(L + K) | O(N + K) |
| Display all records | O(N + 1) | O(N + 1) |
| Delete by ID | O(N + 1) | O(N + 1) |
| Count all records | O(N + 1) | O(N + 1) |

K is the length of the category string. It is short and bounded for this project.

The average search cost depends on how records are distributed among the buckets. If the chain is short, a search visits fewer nodes. If collisions cause a long chain, search becomes slower. In the worst case, all records can occupy one chain, requiring O(N) traversal.

Adding a record is not strictly O(1) overall because the program checks every chain to prevent duplicate IDs. Deletion by ID also scans the directory because the ID is not itself the hash key.

## 13. SDG 8 Connection

The prototype demonstrates how structured access to opportunity information can support the broader goal of decent work and economic growth. It is an educational demonstration rather than a verified employment service.
