#include <vector>
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <iomanip>
#include "imdb.h"
//#include "path.h"
using namespace std;

/**
* Using the specified prompt, requests that the user supply
* the name of an actor or actress.  The code returns
* once the user has supplied a name for which some record within
* the referenced imdb existsif (or if the user just hits return,
* which is a signal that the empty string should just be returned.)
*
* @param prompt the text that should be used for the meaningful
*               part of the user prompt.
* @param db a reference to the imdb which can be used to confirm
*           that a user's response is a legitimate one.
* @return the name of the user-supplied actor or actress, or the
*         empty string.
*/

static int promptForActor(const string& prompt, const imdb& db)
{
	int response;

	while (true) {
		cout << prompt << " [or enter -1 to quit]: ";
		std::cin >> response;
		vector<film> films;
		if (db.getPlayer(response, films)) return response;
		cout << "We couldn't find " << response << "th player in imdb. ";
			//<< "Please try again." << endl;
		return -1;
	}
}

static int promptForFilm(const string& prompt, const imdb& db)
{
	int response;

	while (true) {
		cout << prompt << " [or enter -1 to quit]: ";
		std::cin >> response;
		vector<string> actors;
		if (db.getFilm(response, actors)) return response;
		cout << "We couldn't find " << response << "th movie in imdb. ";
		//<< "Please try again." << endl;
		return -1;
	}
}


/**
* Serves as the main entry point for the six-degrees executable.
* There are no parameters to speak of.
*
*/

int main(int argc, const char *argv[])
{
	//Specify the db folder

    
	imdb db("little-endian");
	if (!db.good()) {
		cout << "Failed to properly initialize the imdb database." << endl;
		cout << "Please check to make sure the source files exist and that you have permission to read them." << endl;
		exit(1);
	}

	while (true) {
		int source = promptForActor("Index of Actor or actress", db);
		if (source == -1) break;

		 source = promptForFilm("Index of Film", db);
		if (source == -1) break;

	}

	cout << "Thanks for playing!" << endl;
	return 0;
}

