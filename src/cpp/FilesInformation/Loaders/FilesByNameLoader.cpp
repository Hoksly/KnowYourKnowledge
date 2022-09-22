//
// Created by Dmytro Klishch on 9/22/22.
//

#include "FilesByNameLoader.h"

File FilesByNameLoader::loadFile(const std::string &filepath) {
    std::string filename = getFileName(filepath);
    size_t point = filename.find_first_of('.');
    if (point == -1) return {filepath, filename, ""};
    return {filepath, filename.substr(0, point), filename.substr(point + 1)};
}

std::string FilesByNameLoader::getFileName(const std::string &filepath) {
    size_t slash = filepath.find_last_of('/');
    if (slash == -1) return {filepath};
    return filepath.substr(slash + 1);
}

TEST_CASE("Full file path") {
    FilesLoader *loader = new FilesByNameLoader();
    File file = loader->loadFile("C:/a/b/c/file.txt");
    CHECK(file.filename() == "file");
    CHECK(file.extension() == "txt");
}

TEST_CASE("Just file name") {
    FilesLoader *loader = new FilesByNameLoader();
    File file = loader->loadFile("file.txt");
    CHECK(file.filename() == "file");
    CHECK(file.extension() == "txt");
}

TEST_CASE("Extension with several dots") {
    FilesLoader *loader = new FilesByNameLoader();
    File file = loader->loadFile("C:/sd/fd/f/file.txt.txt");
    CHECK(file.filename() == "file");
    CHECK(file.extension() == "txt.txt");
}

TEST_CASE("Existing file") {
    FilesLoader *loader = new FilesByNameLoader();
    File file = loader->loadFile("resources/text.txt");
    CHECK(file.exists());
}

TEST_CASE("Non Existing file") {
    FilesLoader *loader = new FilesByNameLoader();
    File file = loader->loadFile("resources/text.txt.txt.txt");
    CHECK(!file.exists());
}