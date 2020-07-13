// Compilation example for GCC (v8 and up), Clang (v7 and up) and MSVC
// g++ -std=c++17 -Wall -pedantic test_fs_watcher.cpp -o test_fs_watcher -lstdc++fs
// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic test_fs_watcher.cpp -o test_fs_watcher -lc++fs
// cl /W4 /EHsc /std:c++17 /permissive- test_fs_watcher.cpp


#include <iostream>
#include "FileWatcher.h"

int main(int argc, char *argv[]) {
	// Create a FileWatcher instance that will check the current folder for changes every 5 seconds

	if (argc != 2)
	{
		std::cout << "B³¹d. Proszê podaæ œcie¿kê do katalogu jako agrgument przy uruchomieniu programu!";
		return 0;
	}

	FileWatcher fw{ argv[1], std::chrono::milliseconds(500) };

	// Start monitoring a folder for changes and (in case of changes)
	// run a user provided lambda function
	fw.start();
}