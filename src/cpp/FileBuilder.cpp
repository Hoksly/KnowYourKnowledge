#include "FileBuilder.h"
#include <cassert>
 bool FileBuilder::toFile(TextNote note, std::string path) {
	 std::ofstream file = createFile(note.title(), path);
	 if (file.fail())
		 return true;

	 writeNote(file, note);
	 file.close();

	 return false;

}

 void FileBuilder::writeNote(std::ofstream& file, TextNote note) {
	 writeTitle(file, note.title());
	 writeCreationTime(file, note.creation_time());
	 writeText(file, note);
 }

 std::ofstream FileBuilder::createFile(std::string name, std::string path) {
	 std::ofstream file;
	 file.open(getFileName(name, path));
	 return file;
 }
 std::string FileBuilder::getFileName(std::string name, std::string path) {
	 return path + name + "." + TEXT_FILE_EXTENSION;
 }


 void FileBuilder::writeTitle(std::ofstream& file, std::string title) {
	 file <<title << "\n";
 }
 void FileBuilder::writeCreationTime(std::ofstream& file, std::time_t creation_time) {
 	 file << toDateFormat(creation_time) << "\n";
 }
 void FileBuilder::writeNote(std::ofstream& file, TextNote note) {
	 file << note.text();
 }

TextNote FileBuilder::fromFile(std::string filename){
	 std::ifstream file = openFile(filename);
	 TextNote note = initTextNote(file);
	 file.close();
	 return note;
 }

std::ifstream FileBuilder::openFile(std::string filename) {
	std::ifstream file;
	file.open(filename);
	assert (!file.fail()); //file exists
	return file;
}

TextNote FileBuilder::initTextNote(std::ifstream& file) {
	std::string title = readTitle(file);
	std::time_t creationTime = readCreationTime(file);
	std::string text = readText(file);

	return TextNote(title, text, creationTime);
}
std::string FileBuilder::readTitle(std::ifstream& file) {
	std::string title;
	std::getline(file, title);
	return title;
}
std::time_t FileBuilder::readCreationTime(std::ifstream& file) {
	std::string line;

	std::getline(file, line);
	std::time_t time = fromDateFormat(line);
	assert (time != -1); //is valid
	return time;
}

std::string FileBuilder::readText(std::ifstream& file) {
	std::string line;
	std::string noteText;

	while (std::getline(file, line)) {
		noteText += line;
		if (!file.eof()) {
			noteText += "\n";
		}
	}
	return noteText;
}

std::string FileBuilder::toDateFormat(std::time_t time) {
	const unsigned int maxChar = 40;
	char date[maxChar];
	std::strftime(date, sizeof(date), "%Y.%m.%d %H:%M:%S", std::localtime(&time));
	return std::string(date);
}

std::time_t FileBuilder::fromDateFormat(std::string str) {
	struct std::tm tm;
	std::sscanf(str.c_str(), "%d.%d.%d %d:%d:%d", &tm.tm_year,
			&tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

	tm.tm_year -= 1900; //1900 -> 0, 2022 -> 122
	tm.tm_mon -= 1; //January = 0
	int a = 0;
	a++;
	return std::mktime(&tm);
}


bool FileBuilder::collectionToFile(TextNoteCollection collection, std::string path) {
	std::ofstream file = createFile(collection.title(), path);
	writeTitle(file, collection.title());
	writeCreationTime(file, collection.creation_time());
	writeCollectionNotes(file, collection);
	return false;
}

void FileBuilder::writeCollectionNotes(std::ofstream& file, TextNoteCollection collection) {
	for (std::size_t i = 0; i < collection.size(); i++) {
		writeNote(file, collection.getNote(i));
	}
}

