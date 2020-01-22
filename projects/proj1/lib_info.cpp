#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Song { 
    string title;
    int time;  // could also be a string
    int track;
};

struct Album {
    map <int,Song> songs;
    string name;
    int time;
    int nsongs;  // optional variable but makes it easier
};

struct Artist {
    map <string,Album> albums;
    string name;
    int time;
    int nsongs;
};

map <string, Artist> parseMusicData(string filename, map <string, Artist> ars);
void printMusicData(map<string, Artist> ars);
string removeUnderscores(string s);
int convertTime(string time);
string convertTime(int time_in_secs);

int main(int argc, char **argv)
{
	string filename = argv[1];
	map <string, Artist> ars;
    ars = parseMusicData(filename, ars);
	printMusicData(ars);
	return 0;
}

//Written by Brandon, edited by Joshua
map<string, Artist> parseMusicData(string filename, map<string, Artist> ars) {
    //Variable Declarations
    ifstream inFile;
    string sTitle, artName, albName, genre, time;
	int timeSeconds, track;
    //Open File and Check if file valid
    inFile.open(filename.c_str());
    if(!inFile.is_open()) {
        exit(0);
    }

	 //Originally written by Brandon, edited by Joshua
    //Read in Data to Artist map
    while (inFile >> sTitle >> time >> artName >> albName >> genre >> track) {
		 
		//Remove underscores if present and convert time to seconds
		sTitle = removeUnderscores(sTitle);
		artName = removeUnderscores(artName);
		albName = removeUnderscores(albName);
		timeSeconds = convertTime(time);
		
		//Check to See if Artist exists within Library
		int art_exists;
		art_exists = ars.count(artName);
		
		if (art_exists == 0)				//If artist doesn't exist,
			ars[artName].nsongs = 1;	//	set artist's song count to 1.
		else									//If artist does exist,
			ars[artName].nsongs++;		//	increment artist's song count


		//Check to see if album already exists
		int alb_exists;
		alb_exists = ars[artName].albums.count(albName);
		
		if (alb_exists == 0)									//If album doesn't exist,
			ars[artName].albums[albName].nsongs = 1;	//	set album's song count to 1.
		else														//If album does exist,
			ars[artName].albums[albName].nsongs++;		//	increment song count by 1.


		ars[artName].albums[albName].nsongs += 1;				//Increment nsongs by 1 for new song entry
		ars[artName].albums[albName].time += timeSeconds;	//Increment total album time

		ars[artName].albums[albName].songs[track].title = sTitle;
		ars[artName].albums[albName].songs[track].time = timeSeconds;
		ars[artName].albums[albName].songs[track].track = track;

	}
	inFile.close();
	return ars;
}

//Written by Joshua
//Prints out the formatted artist map to stdout.
void printMusicData(map<string, Artist> ars) {
    for (std::map<std::string, Artist>::iterator it_art = ars.begin(); it_art != ars.end(); it_art++) {
		std::cout << it_art->first << ": " << it_art->second.nsongs << std::endl;

		for (std::map<std::string, Album>::iterator it_alb = it_art->second.albums.begin(); it_alb != it_art->second.albums.end(); it_alb++) {
			cout << "        " << it_alb->first << ": " << it_alb->second.nsongs << ", " << convertTime(it_alb->second.time) << endl;
			for (std::map<int, Song>::iterator it_song = it_alb->second.songs.begin(); it_song != it_alb->second.songs.end(); it_song++) {
				cout << "                " << it_song->first << ". " << it_song->second.title << ": " << convertTime(it_song->second.time) << endl;
			}//for loop running through album's songs
		}//for loop running through artist's albums
	}//for loop running through artists
}

//Written by Brandon
//Scans through a string and changes the underscores to spaces
string removeUnderscores(string s) {
	for(unsigned int i = 0; i < s.size(); i++) {
		if(s[i] == '_') {
			s[i] = ' ';
		}
	}
	return s;
}

//Written by Brandon
//Converts a string time in the format MM:SS into an integer of seconds
//Example 13:22 would return an int = 802
int convertTime(string time) {
	string mins, secs;
	int m, s, total;
	int pos = time.find_first_of(':');
	secs = time.substr(pos+1),
	mins = time.substr(0, pos);
	m = stoi(mins);
	s = stoi(secs);
	m *= 60;
	total = m + s;
	return total;
}

//Written by Joshua
//Converts seconds into a time string of minutes and seconds in the format "MM:SS"
//Example: 376 would return a string = "6:16"
string convertTime(int time_in_secs) {
	string mins, secs;

	mins = to_string(time_in_secs/60);

	int temp_secs = time_in_secs%60;

	if (temp_secs < 10)
		secs = "0" + to_string(temp_secs);
	else
		secs = to_string(temp_secs);
		
	return string( mins + ':' + secs );
}
