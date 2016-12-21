# CS 104 Student Repository

- **Name**: Josue Campos
- **USC ID**: 5763126369
- **Email**: jrcampos@usc.edu

Name: Josue Campos
Username: jrcampos
Assignment: Project 3

Code Description: 

Compiling Instructions: "make" will compile all executables

Running Instructions: ./hw8 dbLarge3.txt words.txt
					  ./hw8 dbSmall3.txt words.txt
					  ./hw8 dbTest.txt words.txt
					  
Overall Notes: In this project I chose to implement a hard coded thesauraus and created a skiplist for my users. For my thesaurus I parse in a text file in the format of original word and synonym on alternating lines. I put the orginal word into a map of strings to set of strings. Then when I add a new product I verify if one of the keywords of the product is in my map. If it is I set union my current set of keywords with the synonyms of matching words. For my skiplist I implement the skiplist in skiplist.cpp. From there I just inherit the skiplist in my dervided data store (store.h)  and store my User* in their. Then wherever I did a lookup using my user vector I replaced the linear search with a splay tree search. I do this in my cartWindow.cpp LoginWindow.cpp MainWindow.cpp and Store.cpp files.