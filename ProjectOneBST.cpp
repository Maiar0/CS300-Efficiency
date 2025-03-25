//============================================================================
// Name        : ProjectOneBST.cpp
// Author      : Dennis Ward
// Version     : 1.0
//============================================================================
#include <algorithm> // For std::find_if
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Course {
  string courseId;
  string description;
  vector<string> preReq;

  void print() const {
    cout << "Course Department: " << courseId << endl;
    cout << "Description: " << description << endl;
    if (preReq.size() > 0) {
      cout << "Pre-requisites: ";
      for (const auto &i : preReq) {
        cout << i;
        if (i != preReq.back()) {
          cout << ", ";
        }
      }
      cout << endl;
    }
    cout << endl;
  }
};

// Internal structure for tree node
struct Node {
  Course course;
  Node *left;
  Node *right;

  // default constructor
  Node() {
    left = nullptr;
    right = nullptr;
  }

  // initialize with a Course
  Node(Course aCourse) : Node() { course = aCourse; }
};

class BinarySearchTree {

private:
  Node *root;
  void addNode(Node *node, Course course);
  void inOrder(Node *node);
  void postOrder(Node *node);
  void destroyTree(Node *node);
  Node *removeNode(Node *node, string courseId);
  bool validateHelper(Node *node);

public:
  BinarySearchTree();
  virtual ~BinarySearchTree();
  void InOrder();
  void PostOrder();
  void ValidateBST();
  void Insert(Course course);
  void Remove(string courseId);
  Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
  // FixMe (1): initialize housekeeping variables
  // root is equal to nullptr
  root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
  // recurse from root deleting every node
  destroyTree(root);
}

// post order deletion of tree
void BinarySearchTree::destroyTree(Node *node) {
  if (node != nullptr) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}
/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
  // FixMe (2): In order root
  // call inOrder fuction and pass root
  this->inOrder(root);
}
void BinarySearchTree::PostOrder(){
  this->postOrder(root);
}

void BinarySearchTree::ValidateBST() {
  bool changed = validateHelper(root);
  if(!changed) {
    ValidateBST();
  }
}
/**
 * Insert a Course
 */
void BinarySearchTree::Insert(Course Course) {
  // FIXME (5) Implement inserting a Course into the tree
  if (root == nullptr) {         // if root equarl to null ptr
    root = new Node(Course);     // root is equal to new node Course
  } else {                       // else
    this->addNode(root, Course); // add Node root and Course
  }
}

/**
 * Remove a Course
 */
void BinarySearchTree::Remove(string CourseId) {
  // FIXME (6) Implement removing a Course from the tree
  // remove node root CourseID
  this->removeNode(root, CourseId);
}

/**
 * Search for a Course
 */
Course BinarySearchTree::Search(string courseId) {
  // FIXME (7) Implement searching the tree for a course
  Node *cur = root;        // set current node equal to root
  while (cur != nullptr) { // while current node is not equal to null ptr
    if (cur->course.courseId.compare(courseId) ==
        0) {              // if current node courseID is equal to courseId
      return cur->course; // if match found, return current course
    }

    if (courseId.compare(cur->course.courseId) <
        0) { // if course is smaller than current node then traverse left
      cur = cur->left;
    } else { // else larger so traverse right
      cur = cur->right;
    }
  }

  Course course;
  return course;
}
/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node *node, Course course) {
  // FIXME (8) Implement inserting a course into the tree
  if (node->course.courseId.compare(course.courseId) >
      0) {                           // if node is larger then add to left
    if (node->left == nullptr) {     // if no left node
      node->left = new Node(course); // this node becomes left
    } else {                         // else recurse down the left node
      this->addNode(node->left, course);
    }
  } else {                                // else
    if (node->right == nullptr) {         // if no right node
      node->right = new Node(course);     // this node becomes right
    } else {                              // else
      this->addNode(node->right, course); // recurse down the left node
    }
  }
}

void BinarySearchTree::inOrder(Node *node) {
  // FixMe (9): Pre order root
  if (node != nullptr) { // if node is not equal to null ptr
    inOrder(node->left); // call on left
    // output courseID, title, amount, fund
    node->course.print();

    inOrder(node->right); // call on right
  }
}

void BinarySearchTree::postOrder(Node *node) {
  // FixMe (9): Pre order root
  if (node != nullptr) { // if node is not equal to null ptr
    postOrder(node->left); // call on left
    postOrder(node->right); // call on right
    Remove(node->course.courseId); // remove node courseID)
    
  }
}

bool BinarySearchTree::validateHelper(Node *node) {
  if (node == nullptr) {
    return true;
  }

  bool leftTree = validateHelper(node->left);
  bool rightTree =validateHelper(node->right);

  if (node->course.courseId.empty() || node->course.description.empty()) {
    //cout << "Invalid course: " << node->course.courseId << endl;
    Remove(node->course.courseId);
    return false;
  }
  if(node->course.preReq.empty()){
    return leftTree && rightTree;
  }
  for (const auto &preReq : node->course.preReq) {
    Course foundCourse = Search(preReq);
    //cout << "Found " << foundCourse.courseId << " == " << preReq << endl;
    if (foundCourse.courseId != preReq) {
      //cout << "Error: Course " << node->course.courseId << " has a prerequisite " << preReq << " which does not exist" << endl;
      Remove(node->course.courseId);
      return false;
    }
  }
  return leftTree && rightTree;
}

Node *BinarySearchTree::removeNode(Node *node, string courseId) {
  if (node == nullptr) { // if node is equal to null ptr
    return node;
  }
  // if node is larger then recurse left
  if (courseId.compare(node->course.courseId) < 0) {
    node->left = removeNode(node->left, courseId);
  } else if (courseId.compare(node->course.courseId) > 0) {
    node->right = removeNode(node->right, courseId);
  } else {
    if (node->left == nullptr && node->right == nullptr) { // if no children
      delete node;                                         // delete node
      node = nullptr;
    } else if (node->left != nullptr &&
               node->right == nullptr) { // one child left
      Node *tmp = node;
      node = node->left;
      delete tmp;
    } else if (node->right != nullptr &&
               node->left == nullptr) { // one child right
      Node *tmp = node;
      node = node->right;
      delete tmp;
    } else { // two children
      Node *tmp = node->right;
      while (tmp->left != nullptr) {
        tmp = tmp->left;
      }
      node->course = tmp->course;
      node->right = removeNode(node->right, tmp->course.courseId);
    }
  }
  return node;
}

/*******************************************************************/
string trim(const std::string &str) {
  size_t first = str.find_first_not_of(" \t\n\r");
  if (std::string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of(" \t\n\r");
  return str.substr(first, (last - first + 1));
}

// read file directly into bst
void readInFileBst(const string &filename, BinarySearchTree *bst) {
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Error opening file: " << filename << endl;
  }
  string line;
  while (getline(file, line)) {
    Course course;
    stringstream ss(line);
    getline(ss, course.courseId, ',');
    getline(ss, course.description, ',');
    string preReq;
    while (getline(ss, preReq, ',')) {
      course.preReq.push_back(trim(preReq));
    }
    bst->Insert(course);
  }
}

string getUserInput(string message) {
    string inp;
    cout << message;
    getline(cin, inp);
    return inp;
}

int main() {
  BinarySearchTree *bst;
  bst = new BinarySearchTree();
  string filename = "info.csv";
  readInFileBst("info.csv", bst);
  bst->ValidateBST();
  //bst->InOrder();

  clock_t ticks;
  int choice = 0;
  while (choice != 9) {
    cout << "Menu:" << endl;
    cout << "  1. Load Courses" << endl;
    cout << "  2. Print Courses" << endl;
    cout << "  3. Search Courses" << endl;
    cout << "  9. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {

    case 1: {
      cin.ignore();
      filename = getUserInput("Enter filename: ");
      ticks = clock();
      readInFileBst(filename, bst);
      bst->ValidateBST();

      // Calculate elapsed time and display result
      ticks = clock() - ticks; // current clock ticks minus starting clock ticks
      cout << "time: " << ticks << " clock ticks" << endl;
      cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
      cout << "File loaded" << endl;
      break;
    }
    case 2: {
      cout << endl;
      bst->InOrder();
      break;
    }
    case 3: {
      cin.ignore();
      Course course = bst->Search(getUserInput("Please input course ID of course to search: "));
      cout << endl;
      if(course.courseId.empty()){
        cout << "Course not found" << endl;
      }else{
        course.print();
      }
      break;
    }
    case 9: {
      cout << "Good Bye!" << endl;
      return 0;
      break;
    }
    }
  }
    cout << "Good Bye!" << endl;
    return 0;
}
