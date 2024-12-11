/*
* CONTENT IN THIS FILE WILL UPDATE AS LIBRARY DOES.
*/

#include "EPaths.h"
#include <iostream>

using namespace std;

int main() {
	cout << " ======================== SHOWCASE ==========================\n\n" << endl;

	// GET ALL PATHS
	cout << "Documents : " << getFolderPath(FolderType::DOCUMENTS) << endl;
	cout << "Downloads : " << getFolderPath(FolderType::DOWNLOADS) << endl;
	cout << "Desktop : " << getFolderPath(FolderType::DESKTOP) << endl;
	cout << "Pictures : " << getFolderPath(FolderType::PICTURES) << endl;
	cout << "Music : " << getFolderPath(FolderType::MUSIC) << endl;
	cout << "Videos : " << getFolderPath(FolderType::VIDEOS) << endl;
}
