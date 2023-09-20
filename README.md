# hw3-doublyLinkedList
Contains the skeleton code for the HW 3 assignment on implementing a doubly linked list.

### Disclaimers:
This is a pairwise group assignment (please speak to us if considering working alone). 

In order to complete this assignment, be sure to accept the GitHub Classroom assignment, clone the repo, and produce a local copy of the cloned repo on your computer. 

Decide who wants to complete the member functions to implement for Student 1 and who wants to complete the member functions in the list of Student 2 (we made sure to balance them so there is not a significant difference between the two), and record your names in the cpp file that is submitted. 

Branch the repo using your last name as part of the branch name to distinguish the branch, and commit to your branch once your individual member functions are complete (you are encouraged to divide your work into multiple commits, for example, after you have successfully tested a couple of member functions and know you have a working partial solution), and then perform a pull request for your teammate’s review prior to each merging the code. The branches must be merged back to the main branch before the final push is done, which submits the assignment. Please refer to the GitHub guide for branching and pull requests. 

The breakdown of your individual grade will be 90% for your individual member function implementations and 10% for following the branching and pull requests procedures, and overall class functionality in the code. 

This homework is only submitted through GitHub by pushing the commits your team make. The deadline is Friday, September 29.

### Assignment Motivation

Linked lists are a linear data structure that can be used for many applications, including as an implementation for other data structures (as we will see). One direct application is music playlists. Linked lists make good containers for managing such playlists because they are:

1.	Dynamic – Linked lists can vary in size easily, allowing songs to be added or deleted from the playlist. These additions and deletions are also efficiently handled in terms of memory. When adding to the end of the list (the tail), it only requires constant time to add the song. Nodes in a linked list can be reordered easily as well. 

2.	Low Overhead – Linked lists do not have a lot of additional memory overhead required for maintaining the data structure. 

3.	Simple – Working with linked lists is easier than some other more complex data structures.

Most playlist user interfaces have the next song and previous song buttons to make it easy to traverse the list in either direction, which matches well the linking members in a doubly linked list. One drawback of linked lists is the inability for random access (as you will see in your implementation), like indexing in arrays. If you want to go to the 5th song in the playlist, you have to traverse the linked list to the 5th song.

# Assignment Overview

The playlist should be set up so that the head of the list has song number 1, the second node has song number 2, and so on until the tail has the last song number of numSongs (the total number of songs in the playlist). This attribute of the playlist must be carefully maintained as songs are added or deleted.

The following member functions should be implemented by Student 1:

1.	`SongNode* getSongNode(const string song);`
2.	`void addSong(const string addedSongName);`
3.	`void addSong(const string addedSongName, const int songOrder);`
4.	`void deleteSong(const string deletedSongName);`
5.	`int getSongNum(const string searchedSongName);`

The following member functions should be implemented by Student 2:

1.	`SongNode* getSongNode(const int songNumber);`
2.	`void addSong(const string addedSongName, const int songOrder, const string artistName);`
3.	`void deleteLastSong();`
4.	`void deleteSong(const int songNumInList);`
5.	`string getSongName(const int songNumInList);`

There are several features fully implemented for you that do not require any modification, including the class body, main (although you may choose to comment out some of the commands in main to debug member functions as you implement them), the constructor, destructor, a simple getter function to return the number of songs in the playlist, and a friend function of our class that overloads the insertion operator to print out the contents in the music playlist object. This example of operator overloading in C++ uses the concept of a friend function, which can access private (and protected) members of a class even though it is not a member function of the class. It is needed so the output stream objects play nicely with our linked list class objects. Operator overloading is not part of this course and you will not be tested on this topic; it is just for your information. Feel free to add examples to the main to test your code more comprehensively.  

It is highly recommended each student tests their member functions as they go, using cout statements to view the state of certain variables as needed. Comment out necessary statements in main while debugging.

# Student 1 Member Function Descriptions

For Student 1, a brief description of what each member function should do is given below:

1.	`SongNode* getSongNode(const string song);`

Traverses the linked list looking for the given song name (string) and returns a node pointer to the first node with a given song name if present, or nullptr otherwise. It’s a private helper function.

2.	`void addSong(const string addedSongName);`

Should add a new song node with the given string as the song name, at the head of the play list. All other song numbers should be incremented since this added song is the top of the play list (number 1). Also be sure to update the number of songs in the list. Since no artist is given, let it be an empty string.

3.	`void addSong(const string addedSongName, const int songOrder);`
4.	
Should add a new song node with the given string as the song name, at the point in the playlist given by the `int` `songOrder` (if `songOrder` is valid given the list, between 1 and the number of songs). All songs at `songOrder` and beyond (because the new song will supplant the place of the old song at `songOrder`) should have their song numbers incremented and all pointers should be handled correctly. Note that if `songOrder < 2`, the song should be placed at the head, or if `songOrder > numSongs`, it should be placed at the tail. Since no artist is given, let it be an empty string. Be sure that your code can handle all special cases (empty list, single node list, placing at head, placing at tail, etc.).

5.	`void deleteSong(const string deletedSongName);`

Deletes a `SongNode` based on the song name, if present. If the song isn’t in the playlist, there is nothing to delete. Be sure to handle all special cases (empty list, deleting the only node in a single node list, deleting at the head, deleting at the tail, deleting in the middle, etc.). Be sure to handle the pointers around the node to be deleted correctly (no memory leaks or dangling pointers), and be sure to decrement the appropriate song numbers after deleting the node.

5.	`int getSongNum(const string searchedSongName);`

Searches for the song in the playlist with `searchedSongName` and returns its song number if it is found. If there is no song with the searched song name, then the function returns -1 (must return an `int`).
 
# Student 2 Member Function Descriptions

For Student 2, a brief description of what each member function should do is given below:

1. `SongNode* getSongNode(const int songNumber);`

Traverses the linked list looking for the node with the given song number (`int`). For dealing with all ints, it returns `head` if `songNumber < 2`, `tail` if `songNumber ≥ numSongs`, or the first node pointer to a node whose song number is at least the value of `songNumber`. It’s a private helper function.

2. `void addSong(const string addedSongName, const int songOrder, const string artistName);`

Should add a new song node with the given string as the song name, at the point in the playlist given by the int `songOrder` (if `songOrder` is valid given the list, between 1 and the number of songs), and the artist `artistName`. All songs at `songOrder` and beyond (because the new song will supplant the place of the old song at `songOrder`) should have their song numbers incremented and all pointers should be handled correctly. Note that if `songOrder < 2`, the song should be placed at the head, or if `songOrder > numSongs`, it should be placed at the tail. Since no artist is given, let it be an empty string. Be sure that your code can handle all special cases (empty list, single node list, placing at head, placing at tail, etc.).

3. `void deleteLastSong();`

Should delete the last song in the playlist (at the tail). 

4. `void deleteSong (const int songNumInList);`

Deletes a `SongNode` based on its position in the list (given by `songNumInList`). It should delete the first song if `songNumInList < 2` or the last node if `songNumInList ≥ numSongs`. Be sure to handle the pointers around the node to be deleted correctly (no memory leaks or dangling pointers), and be sure to decrement the appropriate song numbers after deleting the node.

5. `int getSongName(const int songNumInList);`

Searches for the song in the playlist with the song number given by `songNumInList`. It should return the head if `songNumInList < 2`, and the tail if `songNumInList ≥ numSongs`. For the special case of an empty list, return the string “Empty Play List” (must return a string).



