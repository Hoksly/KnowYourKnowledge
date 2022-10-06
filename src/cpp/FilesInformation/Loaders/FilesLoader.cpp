//
// Created by Dmytro Klishch on 10/4/22.
//

#include "FilesLoader.h"
#include "../../doctest.h"

Directory *FilesLoader::loadDirectory(const std::string &filepath) {
    Directory *directory = new Directory(filepath);
    for (const auto &entry: std::filesystem::directory_iterator(filepath)) {
        if (entry.is_directory()) {
            directory->add(loadDirectory(entry.path().string()));
        } else {
            directory->add(loadFile(entry.path().string()));
        }
    }
    return directory;
}
