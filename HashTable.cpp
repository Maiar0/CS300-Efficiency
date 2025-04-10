//============================================================================
// Name        : HashTable.cpp
// Author      : Dennis Ward
// Version     : 1.1
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node *next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    
};

/**
 * Default constructor
 */
HashTable::HashTable() {
  // FIXME (1): Initialize the structures used to hold bids
  // Initalize node structure by resizing tableSize
  nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    // resize nodes size
  this->tableSize = size;
}


/**
 * Destructor
 */
HashTable::~HashTable() {
  // FIXME (2): Implement logic to free storage when class is destroyed
  // erase nodes beginning
  /*for (auto& node : nodes) {
      Node* current = node.next;
      while (current != nullptr) {
          Node* temp = current;
          current = current->next;
          delete temp;
      }
  }*/
  nodes.erase(nodes.begin(), nodes.end());
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // FIXME (3): Implement logic to calculate a hash value
    // return key tableSize
  /* const double A = 0.6180339887; // A constant (golden ratio)
    double fractionalPart = (key * A) - floor(key * A); // Extract fractional part
    return static_cast<unsigned int>(fractionalPart * tableSize); // Scale to table size*/
  return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // FIXME (5): Implement logic to insert a bid
    // create the key for the given bid
   unsigned key = hash(stoi(bid.bidId)); 
    // retrieve node using key
  Node* oldNode = &nodes[key];//changeto nodes[key]----
  if(oldNode == nullptr){// if no entry found for the key
   Node* newNode = new Node(bid, key);// assign this node to the key position
    nodes.insert(nodes.begin()+key, (*newNode));
  }else{// else if node is not used
    if(oldNode->key == UINT_MAX){// assing old node key to UNIT_MAX, set to key, set old node to bid and old node next to null pointer
      oldNode->key = key;
      oldNode->bid = bid;
      oldNode->next = nullptr;
    }else{// else find the next open node
      //collision
      while(oldNode->next != nullptr){//chaining find next open node
        oldNode = oldNode->next;
      }
      oldNode->next = new Node(bid, key);// add new newNode to end
    }
  }
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (6): Implement logic to print all bids
    // for node begin to end iterate
  for(auto it = nodes.begin(); it != nodes.end(); it++){
   if(it->key != UINT_MAX){//   if key not equal to UINT_MAx
    cout <<"Key: " << it->key << " Bid: " << it->bid.bidId << " Title: " << it->bid.title << endl;// output key, bidID, title, amount and fund
     Node* node = it->next;// node is equal to next iter
     while(node != nullptr){// while node not equal to nullptr
       cout <<"Key: " << node->key << " Bid: " << node->bid.bidId << " Title: " << node->bid.title << endl;// output key, bidID, title, amount and fund
       node = node->next;// node is equal to next node
     }
   } 
  }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {//may need to do more ---
    // FIXME (7): Implement logic to remove a bid
  unsigned int key = hash(stoi(bidId));// set key equal to hash atoi bidID cstring
  Node *node = &nodes[key];
  if(node->key != UINT_MAX){//if Node not empty
    if(node->bid.bidId.compare(bidId)==0){//checks if "head" is correct bid
      cout << "Bid removed" << endl;
      nodes.erase(nodes.begin()+key);// erase node begin and key
      if(node->next == nullptr){//if only node in chain
        node->key = UINT_MAX;//set to empty
        return;
      }else{// if not only node in chain
        nodes.at(key) = *node->next;
        return;
      }
    }else{// if "head" is not correct bid
      Node *cur = node->next;
      Node *prev = node;
      while(cur != nullptr){//LOOP THROUGH CHAIN
        if(cur->bid.bidId.compare(bidId)==0){//IF FOUND
          cout << "Bid removed: " << cur->bid.bidId << endl;
          prev->next = cur->next;//UPDATE POINTERS
          delete cur;//DELETE NODE
          return;
        }
        prev = cur;//adjust pointers
        cur = cur->next;//iterate
      }
    }
  }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;

  // FIXME (8): Implement logic to search for and return a bid
  unsigned int key = hash(stoi(bidId));
  Node *node = &nodes[key];// create the key for the given bid
  if(node != nullptr && node->key != UINT_MAX && node->bid.bidId.compare(bidId)==0){// if entry found for the key
    return node->bid;//return node bid
  }
  if(node == nullptr || node->key == UINT_MAX){// if no entry found for the key
    return bid;// return bid
  }
  while(node != nullptr){// while node not equal to nullptr
    if(node->key != UINT_MAX && node->bid.bidId.compare(bidId)==0){// if the current node matches, return it
      return node->bid;//node is equal to next node
    }
    node = node->next;
  }
    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

string getUserInput(string message) {
    string inp;
    cout << message;
    getline(cin, inp);
    return inp;

}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    Bid newBid;
    bidTable = new HashTable();

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  5. Insert Bid" << endl;
        cout << "  6. Search Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey);
            break;

        case 5: 
          cin.ignore();
          newBid.bidId = getUserInput("Enter Bid ID: ");
          newBid.title = getUserInput("Enter Bid Title: ");
          newBid.fund = getUserInput("Enter Bid Fund: ");
          newBid.amount = strToDouble(getUserInput("Enter Bid Amount: "), '$');
          bidTable->Insert(newBid);
          break;
          
        case 6:
          cin.ignore();
          string newBidKey = getUserInput("Enter Id: ");
            bid = bidTable->Search(newBidKey);
            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << newBidKey << " not found." << endl;
            }
          break;
        }
  
    }

    cout << "Good bye." << endl;

    return 0;
}
