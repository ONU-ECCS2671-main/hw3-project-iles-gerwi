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
	 // overload to all adding a song also with the artist name
	void addSong(const string addedSongName, const int songOrder, const string artistName); 

	void deleteSong(const string deletedSongName); // deletes a SongNode based on the song name if present
	 // overload to also delete a song in the given position in the play list. Delete first if < 2 or delete last if >= numSongs
	void deleteSong(const int songNumInList);

	void deleteLastSong(); // deletes the last song in the play list (at the tail)
	
	int getSongNum(const string searchedSongName); // searches for the song in the play list and returns the number it is at in the play list or -1 if not present
	string getSongName(const int songNumInList); // searches for the songNumInList and should return the name of the song; returns first if < 2 or last if >= numSongs, or "Empty Play List" if empty.

	int getNumSongs(); // returns numSongs

	// overload << operator to print the MusicPlayList song names in the order of the play list
	friend ostream& operator<<(ostream& outputStream, const MusicPlayList& musicList);
};

// Student 1 Member Functions go here

// Student 2 Member functions go here

MusicPlayList::SongNode* MusicPlayList::getSongNode(const string song) {
    if (numSongs == 0) {
        return nullptr;
    }

    SongNode* current = head;
    while (current != nullptr) {
        if (current->songName == song) {
            return current; 
        }
        current = current->next;
    }

    return nullptr;
}


void MusicPlayList::addSong(const string addedSongName, const int songOrder, const string artistName) {
    SongNode* newNode = new SongNode(addedSongName, songOrder, artistName, nullptr, nullptr);
    
    if (numSongs == 0) {
        head = newNode;
        tail = newNode;
    } 
	else if (songOrder <= 1) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } 
	else if (songOrder > numSongs) {
        
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } 
	else {
        
        SongNode* current = head;
        for (int i = 1; i < songOrder - 1; ++i) {
            current = current->next;
        }
        
        newNode->next = current->next;
        newNode->prev = current;
        current->next = newNode;
        newNode->next->prev = newNode;
    }

    numSongs++;
    
    if (songOrder > 1 && songOrder <= numSongs) {
        SongNode* prevNode = nullptr;
        SongNode* currentNode = head;
        int currentNum = 1;
        
        while (currentNode != nullptr) {
            if (currentNode == newNode) {
                prevNode = currentNode->prev;
                currentNode = currentNode->next;
                continue;
            }
            
            currentNode->songNum = currentNum++;
            currentNode = currentNode->next;
        }
        
        if (prevNode != nullptr) {
            prevNode->songNum = currentNum - 1;
        }
    }

    
    if (newNode->next != nullptr) {
        SongNode* temp = newNode->next;
        int num = newNode->songNum + 1;
        while (temp != nullptr) {
            temp->songNum = num++;
            temp = temp->next;
        }
    }
}


void MusicPlayList::deleteLastSong() {
    if (numSongs == 0) {
        return;
    }

    if (numSongs == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        numSongs = 0;
    } 
	else {
        
        SongNode* temp = tail;
        if (temp->prev != nullptr) {
            temp->prev->next = nullptr;
        }
        delete temp;
        
      
        tail = temp->prev;
        tail->next = nullptr;

        numSongs--;
    }
}


void MusicPlayList::deleteSong(const int songNumInList) {
    if (numSongs == 0 || songNumInList < 1 || songNumInList > numSongs) {
        return;
    }

    SongNode* current = head;
    for (int i = 1; i < songNumInList; ++i) {
        current = current->next;
    }

    // Delete the node at the specified position
    if (current == nullptr) {
        return; // Invalid position
    }

    SongNode* temp = current;
    if (temp == head) {
        head = head->next;
    } else {
        current->prev->next = current->next;
    }

    if (temp != tail) {
        temp->next->prev = temp->prev;
    }

    delete temp;
    numSongs--;

    if (songNumInList > 1 && songNumInList < numSongs) {
        SongNode* prevNode = nullptr;
        SongNode* currentNode = head;
        int currentNum = 1;
        
        while (currentNode != nullptr) {
            currentNode->songNum = currentNum++;
            currentNode = currentNode->next;
        }
        
        currentNode = head;
        for (int i = 1; i < songNumInList - 1; ++i) {
            currentNode = currentNode->next;
        }
        currentNode->songNum = currentNum - 1;
    }
}



string MusicPlayList::getSongName(const int songNumInList) {
    if (numSongs == 0) {
        return "Empty Play List";
    }

    if (songNumInList < 2) {
        return head->songName;
    }

    if (songNumInList >= numSongs) {
        return tail->songName;
    }

    SongNode* current = head;
    int count = 1;

    while (current != nullptr && count < songNumInList) {
        current = current->next;
        count++;
    }

    if (current == nullptr || count != songNumInList) {
        return "Song not found";
    }

    return current->songName;
}



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
//	list1.addSong("Gel"); // Student 1 member function
//	list1.addSong("Shine", 3); // Student 1 member function
//	list1.addSong("Beatin' the Odds", 2); // Student 1 member function
	list1.addSong("Penthouse Pauper", 1, "Molly Hatchet"); // Student 2 member function
//	list1.addSong("Can't Touch This", 72); // Student 1 member function

	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;
//	cout << "The song number for Billie Jean is " << list1.getSongNum("Billie Jean") << endl; // Student 1 member function
	cout << "The song in position 2 is " << list1.getSongName(2) << endl; // Student 2 member functions

	list1.deleteLastSong(); // Student 2 member function
	cout << "After deleting the last song: " << list1.getNumSongs() << " songs, including: " << list1 << endl; 
     // Student 1 member function
//	cout << "The song number for Can't Touch This is now " << list1.getSongNum("Can't Touch This") << " since it's not in the list anymore." << endl;

	list1.deleteSong(-2); // Student 2 member function
	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;

	list1.deleteSong(80); // Student 2 member function
	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;

//	list1.deleteSong("Shine"); // Student 1 member function
	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;

//	list1.addSong("Back in Black", 10); // Student 1 member function
	list1.deleteSong(2); // Student 2 member function
	cout << "The play list has " << list1.getNumSongs() << " songs, including: " << list1 << endl;

}
