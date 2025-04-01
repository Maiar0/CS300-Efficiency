# Course Management System

## Overview

This project implements a **Course Management System** that allows users to load, validate, search, and display course information from a structured CSV file. The system is implemented using three different data structures—**Vector**, **Binary Search Tree (BST)**, and **Hash Table**—to analyze and compare performance and behavior.

The system reads course data, validates course and prerequisite consistency, and allows users to query specific courses and list all available courses. Each data structure provides a unique perspective on performance, data ordering, and lookup efficiency.

---

## Purpose

The primary objective of this project is to:

- Parse course information from a file into an internal data structure.
- Ensure data integrity by validating required fields and verifying all listed prerequisites exist.
- Allow interactive user operations such as printing all courses or searching for a specific one.
- Compare and analyze the performance of each data structure under typical operations.

---

## Implementation Details

### 🧮 Common Structure

All implementations use the following core `Course` structure:

```cpp
struct Course {
    string courseId;
    string description;
    vector<string> preReq;

    void print() const;
};
```

Each approach includes file I/O, input validation, and a basic user menu for operations.

---

### 📚 Vector-Based Implementation

**File:** `ProjectOneVector.cpp`

- **Storage:** `vector<Course>`
- **Sorting:** Uses QuickSort to present courses in alphanumeric order.
- **Validation:** Repeatedly cleans the dataset to ensure all prerequisites are valid.
- **Complexity:**  
  - Load & Validate: O(n²) worst-case due to nested loops in validation  
  - Search: O(n)  
  - Print Sorted List: O(n log n)

**Strengths:**  
- Simple structure with clear flow.  
- Sorting guarantees ordered output.

**Limitations:**  
- Slower search times for large datasets.

---

### 🌳 Binary Search Tree (BST) Implementation

**File:** `ProjectOneBST.cpp`

- **Storage:** Dynamically allocated binary tree nodes.
- **Validation:** Recursive tree traversal to remove invalid nodes or missing prerequisites.
- **Search & Insert:** O(log n) average-case for balanced trees.
- **Print:** InOrder traversal ensures alphabetical listing.

**Strengths:**  
- Balanced BST yields fast lookups.  
- Naturally sorted order without explicit sorting.

**Limitations:**  
- Complex validation logic.  
- Unbalanced deletes can reduce performance.

---

### 🗂️ Hash Table Implementation

**File:** `HashTable.cpp`  
**Note:** Adapted from a bid system but applies the same hash mechanics.

- **Storage:** Array of buckets using chaining to resolve collisions.
- **Key Formation:** Derived from course ID.
- **Search & Insert:** O(1) average-case.

**Strengths:**  
- Extremely fast insert and lookup.  
- Efficient for large datasets.

**Limitations:**  
- Poor inherent ordering; requires secondary structure (e.g., vector) for sorted print.  
- Collision-prone with weak hash design.

---

## Runtime Analysis

| Data Structure | Load Time (Big-O) | Search Time | Ordered Print | Notes |
|----------------|-------------------|-------------|----------------|-------|
| Vector         | O(n)              | O(n)        | O(n log n)     | Simple but linear search |
| BST            | O(n log n)        | O(log n)    | O(n)           | Efficient if balanced |
| Hash Table     | O(n)              | O(1)        | O(n)†          | Fastest lookup, poor ordering |

† Requires extra steps to enable sorted output.

---

## Usage

1. Compile any variant with a C++ compiler (e.g., `g++ ProjectOneVector.cpp -o vectorApp`).
2. Run the executable and use the menu:
   - Load Courses
   - Print Courses
   - Search Courses
   - Exit
3. Input CSV should follow format:
   ```
   CSCI100,Introduction to Computer Science,CSCI001
   CSCI200,Data Structures,CSCI100
   ```

---

## Recommendation

For short-term use or simpler systems, **Vectors** provide maintainable and understandable code. For larger datasets requiring frequent lookup, **Hash Tables** offer superior speed. **BSTs** are optimal when consistent ordering and log-time operations are necessary during runtime.
