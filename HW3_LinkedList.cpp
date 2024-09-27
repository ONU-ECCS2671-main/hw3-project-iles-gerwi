/*
Course: ECCS 2671 -- Data Structures and Algorithms 1
Group Members
Student 1 = Zach Iles
Student 2 = Mitchell Gerwin

Use this code template to submit HW 3.

Implement all of the member functions that have not been implemented based on the functionality in the handout

You are NOT allowed to modify the MusicPlayList class, only complete the class implementation.
*/

#include <iostream>
#include <string>

using namespace std;

class MusicPlayList{

private:
	struct SongNode{
		string songName; // name of the song
		int songNum;   // positive int representing the song's order in the play list
		string songArtist; // musical artist who is associated with the song
		SongNode* next; // forward link
		SongNode* prev; // reverse link
		 // SongNode default constructor
        SongNode() {songName=""; songNum=1; songArtist=""; next=prev=nullptr;}
		 // SongNode parameterized constructor
		SongNode(string sName, int sNum=1, string sArtist = "", SongNode* nSong = nullptr, SongNode* pSong = nullptr)
		{songNum = sNum; songName = sName; songArtist = sArtist; next = nSong; prev = pSong;}
	};

	int numSongs; // number of songs in the play list 
	SongNode* head; // points to first song node in the play list
	SongNode* tail; // points to last song node in the play list

	
	SongNode* getSongNode(const string song); // returns a pointer to the first node with a given song name if present, or nullptr otherwise
	SongNode* getSongNode(const int songNumber); // overloaded to search by song number in the list. Returns head if < 2 and tail if >= numSongs or first node pointer whose Songnum >= songNumber

public:
	MusicPlayList() {numSongs = 0; head=tail=nullptr;} // default constructor
	~MusicPlayList(); // destructor 

	void addSong(const string addedSongName); // inserts a SongNode with just the song name at head 

	// overload to insert the new song node at songOrder if songorder > 1; at head if < 2, or at tail if > numSongs
	// moves the nodes at songOrder to have an incremented value in the order of the list
	void addSong(const string addedSongName, const int songOrder); 

	void addSong(const string addedSongName, const int songOrder, const string artistName); // overload to all adding a song also with the artist name

	void deleteSong(const string deletedSongName); // deletes a SongNode based on the song name if present

	void deleteSong(const int songNumInList); // overload to also delete a song in the given position in the play list. Delete first if < 2 or delete last if >= numSongs

	void deleteLastSong(); // deletes the last song in the play list (at the tail)

	int getSongNum(const string searchedSongName);// searches for the song in the play list and returns the number it is at in the play list or -1 if not present

	string getSongName(const int songNumInList); // searches for the songNumInList and should return the name of the song; returns first if < 2 or last if >= numSongs, or "Empty Play List" if empty.

	int getNumSongs(); // returns numSongs

	// overload << operator to print the MusicPlayList song names in the order of the play list
	friend ostream& operator<<(ostream& outputStream, const MusicPlayList& musicList);
};

// Student 1 Member Functions go here

MusicPlayList:: SongNode* :: MusicPlayList:: getSongNode(const string song){
        SongNode* current = head;
        while(current != nullptr){
            if(current->songName == song){
                return current;
            }
            current = current -> next;
		}
        return nullptr; // Backup for if a song is not found
    }

void MusicPlayList:: addSong(const string addedSongName){
		SongNode* newNode = new SongNode(addedSongName, 1, "", head, nullptr);
		if(head != nullptr){
			head->prev = newNode; // links the head to the newNode
		}
		head = newNode; // sets the head equal to the newNode

		if(tail == nullptr){
			tail = newNode; // sets tail to newNode if list was empty
		}
		
		// incriments the song numbers by 1
		SongNode* current = head->next;
		while(current != nullptr){
			current -> songNum++;
			current = current->next;
		}

		numSongs++; // updates number of songs in the playlist
	} 

void MusicPlayList:: addSong(const string addedSongName, const int songOrder){
		
		//inserts at head
		if(songOrder<2){
			addSong(addedSongName); // uses the other function
		}
		//inserts at tail
		else if(songOrder>numSongs){
			SongNode* newNode = new SongNode(addedSongName, numSongs+1, "", nullptr, tail);
			if(tail!= nullptr){
				tail->next = newNode;
			}
			tail = newNode; // updates tail to newNode
			if(head== nullptr){
				head = newNode; // sets head to newNode if list was empty
			}
		}
		//inserts at songOrder
		else{
			SongNode* current = head; 

			//moves the node to the correct position for insertion
			for(int i; i < songOrder -1 && current != nullptr; i++){
				current = current->next;
			}
			SongNode* newNode = new SongNode(addedSongName, songOrder, "", current -> next, current);
			if(current->next != nullptr){
				current-> next-> prev = newNode; // links the next node back to newNode
			}
			current-> next = newNode; // links current node to newNode

			// increases song number for rest of list
			current = newNode->next;
			while(current!= nullptr){
				current ->songNum++;
				current = current->next;
			}
		}

		//updates number of songs
		numSongs++;
	}

void MusicPlayList :: deleteSong(const string deletedSongName){
	SongNode* toDelete = getSongNode(deletedSongName);

	if(toDelete == nullptr){
		return; // song was not found, so nothing to delete
	}

	// update the pointers
	if(toDelete->prev != nullptr){
	toDelete->prev->next = toDelete->next; // links previous node to next node
	}
	else{
		head = toDelete->next; // updates head if necessary
	}

	if(toDelete->next != nullptr){
		toDelete->next->prev = toDelete->prev; // links next node to previous node
	}
	else{
		tail = toDelete->prev; // updates tail if necessary
	}

	// subtract 1 from remaining song numbers
	SongNode* current = toDelete->next;
	while(current!=nullptr){
		current->songNum--;
		current = current->next;
	}

	delete toDelete; // free memory allocated for the pointers

	// update number of songs
	numSongs--;
}

int MusicPlayList :: getSongNum(const string searchedSongName){
	SongNode* songNode = getSongNode(searchedSongName);
	if(songNode != nullptr){
		return songNode->songNum; // returns the song number if it exists
	}

	return -1; // catch for if song was not found
}

// Student 2 Member functions go here

// *******************************************************************
// Destructor to delete all nodes in the Music Play List
// *******************************************************************
MusicPlayList::~MusicPlayList()
{
	SongNode* deleteNode = head;
	SongNode* nextNode = head;
	while(nextNode!=nullptr)
	{
		nextNode = nextNode->next;
		delete deleteNode;
		deleteNode = nextNode;
	}
	tail = head = nullptr;
	numSongs = 0;
}

// *******************************************************************
// gets the number of songs in the play list
// *******************************************************************
int MusicPlayList::getNumSongs()
{
	return numSongs;
}

// *******************************************************************
// overloading << operator to print the Music Play List
// outputStream variable is output stream (ostream)
// *******************************************************************
ostream& operator<<(ostream& outputStream, const MusicPlayList& playList)
{
	// SongNode structure is defined inside the MusicPlayList class, we need
	// to use the resolution operator :: to access it.
	// That's why we defined this function as a friend function, so
	// we can access the SongNode struct and all private members.

	MusicPlayList::SongNode* current = playList.head;

	int currentSongNum;
	while(current != nullptr){
		currentSongNum = current->songNum;
		outputStream<<"("<< currentSongNum << ") " << current->songName<<", ";
		current = current->next;
	}
	outputStream<<"00"<<endl;

	return outputStream;
}

int main()
{

	MusicPlayList list1;
	
	cout << "We start with: " << list1.getSongName(1) << endl; // Student 2 member function
	list1.addSong("Billie Jean", 3, "Michael Jackson"); // Student 2 member function
	list1.addSong("Ready for It", -1, "Taylor Swift"); // Student 2 member function
	list1.addSong("Gel"); // Student 1 member function
	list1.addSong("Shine", 3); // Student 1 member function
	list1.addSong("Beatin' the Odds", 2); // Student 1 member function
	list1.addSong("Penthouse Pauper", 1, "Molly Hatchet"); // Student 2 member function
	list1.addSong("Can't Touch This", 72); // Student 1 member function

	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;
	cout << "The song number for Billie Jean is " << list1.getSongNum("Billie Jean") << endl; // Student 1 member function
	cout << "The song in position 2 is " << list1.getSongName(2) << endl; // Student 2 member functions

	list1.deleteLastSong(); // Student 2 member function
	cout << "After deleting the last song: " << list1.getNumSongs() << " songs, including: " << list1 << endl; 
     // Student 1 member function
	cout << "The song number for Can't Touch This is now " << list1.getSongNum("Can't Touch This") << " since it's not in the list anymore." << endl;

	list1.deleteSong(-2); // Student 2 member function
	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;

	list1.deleteSong(80); // Student 2 member function
	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;

	list1.deleteSong("Shine"); // Student 1 member function
	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;

	list1.addSong("Back in Black", 10); // Student 1 member function
	list1.deleteSong(2); // Student 2 member function
	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;
}