#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//================================================================
// Global definitions visible to all methods and classes
//================================================================

const unsigned int DEFAULT_SIZE = 179;

// define a structure to hold course information
struct Course {
	string courseNum;
	string name;
	vector<string> prereq;
};

//================================================================
// Hash Table class definition
//================================================================

class HashTable {
private:
	// define structure to hold courses
	struct Node {
		Course course;
		unsigned int key;
		Node* next;

		// default constructor
		Node() {
			key = UINT_MAX;
			next = nullptr;
		}

		// initialize with a course
		Node(Course aCourse) : Node() {
			course = aCourse;
		}

		//initialize with a course and a key
		Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
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
	void Insert(Course course);
	void PrintAllAlphaNum();
	Course SearchCourse(string courseNum);
};

/**
* Default constructor
*/
HashTable::HashTable() {
	// initialize node structure by resizing tableSize
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
	nodes.resize(tableSize);
}

/**
 * Destructor: free storage when class is destroyed
 */
HashTable::~HashTable() {
	// erase nodes beginning
	nodes.erase(nodes.begin());
}

unsigned int HashTable::hash(int key) {
	// logic to calculate a hash value
	return key % tableSize;
}

/**
 * Insert a course
 *
 * @param course The course to insert
 */
void HashTable::Insert(Course course) {
	// logic to insert a course
	// create the key for the given bid using the last three course Number integers
	int courseNumLen = course.courseNum.size();
	int courseNumKey = stoi(course.courseNum.substr(courseNumLen - 3, courseNumLen));
	int key = hash(courseNumKey);

	// retrieve node using key
	Node* oldNode = &(nodes.at(key));

	// if no entry found for the key
		// assign this node to the key position
	if (oldNode == nullptr) {
		Node* newNode = new Node(course, key);
		nodes.insert(nodes.begin() + key, (*newNode));
	} 
	else {
		// if node found but empty/not used
			// assign old node key to UINT_MAX, set to key, course, and next to nullptr
		if (oldNode->key == UINT_MAX) {
			oldNode->key = key;
			oldNode->course = course;
			oldNode->next = nullptr;
		}
		else {
			// find the next open node  
				// add new node to the end
			while (oldNode->next != nullptr) {
				oldNode = oldNode->next;
			}
			oldNode->next = new Node(course, key);
		}
	} 
}

/**
 * Print all bids
 */
void HashTable::PrintAllAlphaNum() {
	// logic to print all course alphanumerically from lowest to highest  
	Course course;
	vector <string> courseInfo;
	
	// for node begin to end iterate
	for (auto & node : nodes) {
		int key = node.key;
		course = node.course;
		Node* nextNode = node.next;

		// if key not equal to UINT_MAx
			// add course number to list
		if (key != UINT_MAX) {
			courseInfo.push_back(course.courseNum);

			// while node not equal to nullptr
			while (nextNode != nullptr) {
				courseInfo.push_back(nextNode->course.courseNum);

				// node is equal to next node
				nextNode = nextNode->next;
			} 
		}
	}

	// sort list of course number from lowest to highest 
	sort(courseInfo.begin(), courseInfo.end());

	cout << "Here is a sample schedule:\n" << endl; 
	// loop through course number list 
		// find the matching course with course number
	for (auto& courseNum : courseInfo) {
		course = SearchCourse(courseNum);

		// print course information and prerequisites
		cout << course.courseNum << ": " << course.name << endl;
	} 
}

/**
 * Search for the specified bidId
 *
 * @param courseNum The course num to search for
 */
Course HashTable::SearchCourse(string courseNum) {
	// logic to search for and return a course
	Course course;

	// calculate key for this course number
	int courseNumLen = courseNum.size();
	int courseNumKey = stoi(courseNum.substr(courseNumLen - 3, courseNumLen));
	unsigned key = hash(courseNumKey);

	// try and retrieve node using the key
	Node* node = &nodes.at(key);

	// if no entry found for the key
		 // return empty course
	if (node == nullptr || node->key == UINT_MAX) {
		return course;
	}

	// if node found that matches key
	if (node != nullptr && node->key != UINT_MAX && node->course.courseNum.compare(courseNum) == 0) {
		return node->course;
	}

	// while node not equal to nullptr
		// if the current node matches, return it
		// node is equal to next node
	while (node != nullptr) {
		if (node->key != UINT_MAX && node->course.courseNum.compare(courseNum) == 0) {
			return node->course;
		}
		node = node->next;
	}	
	
	return course;
}

//================================================================
// Static methods used for testing
//================================================================

/**
 * Display the course information to the console
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
	cout << course.courseNum << ": " << course.name;

	if (course.prereq.size() > 0) {
		cout << "\nPrerequisites: ";
		for (unsigned int j = 0; j < course.prereq.size(); ++j) {
			cout << course.prereq.at(j);
			if (j != course.prereq.size() - 1) {
				cout << ", ";
			}
		}
	}

	cout << "\n";
	return;
}

/**
* Load a CSV file containing courses into a container
*
* @param csvPath the path to the CSV file to load
* @return a container holding all the courses read
*/

void loadCourses(string csvPath, HashTable* hashTable) {
	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	ifstream file;
	file.open(csvPath);
	cout << "Loading CSV file " << csvPath << endl;

	// open file 
		// read each row till end of file
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			row.clear();
			stringstream str(line);

			// parse each line by comma delimiter 
				// add to list of words
			while (getline(str, word, ',')) {
				row.push_back(word);
			}

			// add to 2D vector list
			content.push_back(row);
		}
	}
	else {
		cout << "Unable to open the file" << csvPath << "\n" << endl;
		return;
	}

	try {
		for (int i = 0; i < content.size(); ++i) {

			// course structure holding collection of courses
			Course course;
			course.courseNum = content[i][0];
			course.name = content[i][1];

			// if course has prerequisites add to prereq list 
			if (content[i].size() > 2) {
				for (unsigned int j = 2; j < content[i].size(); ++j) {
					course.prereq.push_back(content[i][j]);
				}
			}

			hashTable->Insert(course);
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}

	file.close();
}

int main() {
	string csvPath = "ABCU_Advising_Program_Input.csv";
	string courseKey;
	HashTable* courseTable;
	
	Course course;
	courseTable = new HashTable();
	string keyStr, keyNum;

	int choice = 0;
	while (choice != 9) {
		cout << "\nWelcome to the course planner" << endl;
		cout << " 1. Load Data Structure." << endl;
		cout << " 2. Print Course List." << endl;
		cout << " 3. Print Course" << endl;
		cout << " 9. Exit\n" << endl;
		cout << "What would you like to do?" << endl;
		cin >> choice;

		switch (choice) {
			case 1:
				loadCourses(csvPath, courseTable);
				break;
			case 2:
				courseTable->PrintAllAlphaNum();
				break;
			case 3:
				cout << "What course would you like to know about?\n";
				cin >> courseKey;
				
				// change user input for course key to uppercase before searching
				if (courseKey.size() > 3) {
					keyStr = courseKey.substr(0, courseKey.size() - 3);
					keyNum = courseKey.substr(courseKey.size() - 3, courseKey.size());
					courseKey = "";
					for (auto& c : keyStr) {
						courseKey += (char)toupper(c);
					}

					courseKey = courseKey + keyNum;
				}
				
				course = courseTable->SearchCourse(courseKey);

				if (!course.courseNum.empty()) {
					displayCourse(course);
				}
				else {
					cout << "Course number " << courseKey << " not found.\n" << endl;
				}
			case 9:
				break;
			default:
				cout << choice << " is not a valid option." << endl;
		}
	}

	cout << "Thank you for using the course planner!" << endl;

	return 0;
}