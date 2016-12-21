#include "../llistdbl.h"
#include <iostream>

using namespace std;

int main() {
  LListDbl * list = new LListDbl();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list->insert(0, 3.3);

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3.3) {
    cout << "SUCCESS: 3.3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3.3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  list->insert(0, 5.3);

  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after two insertions." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 2) {
    cout << "SUCCESS: List has size 2 after two insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  if (list->get(0) == 5.3) {
    cout << "SUCCESS: 5.3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 5.3 is not at the oth index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  list->insert(3, 7.6);

  if (list->size() == 2) {
    cout << "SUCCESS: List has size 2 after failed insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after bad insertion.";
    cout << endl;
  }

  list->remove(0);

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one remove." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after remove.";
    cout << endl;
  }

  list->remove(1);

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after failed remove." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after bad remove.";
    cout << endl;
  }

  list->remove(0);

  if (list->size() == 0) {
    cout << "SUCCESS: List has size 0 after one remove." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after remove.";
    cout << endl;
  }

  list->remove(0);
  cout << "SUCCESS: Program has not crashed after removing from empty list";
  cout << endl;// Clean up memory.
  delete list;
}