#pragma once

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <functional>
#include "Event.cpp"


class FileWatcher {
public:
	std::string path_to_watch;

	std::chrono::duration<int, std::milli> delay;

	
	FileWatcher(std::string path_to_watch, std::chrono::duration<int, std::milli> delay) : path_to_watch{ path_to_watch }, delay{ delay } {
		for (auto &file : std::filesystem::recursive_directory_iterator(path_to_watch)) {
			paths_[file.path().string()] = std::filesystem::last_write_time(file);
		}
	}

	// Monitor "path_to_watch" for changes and in case of a change execute the user supplied "action" function
	void start() {
		while (running_) {
			// Wait for "delay" milliseconds
			std::this_thread::sleep_for(delay);

			auto it = paths_.begin();
			while (it != paths_.end()) {
				if (!std::filesystem::exists(it->first)) {
					new Event(EventType::deleted, it->first);
					it = paths_.erase(it);
				}
				else {
					it++;
				}
			}

			// Check if a file was created or modified
			for (auto &file : std::filesystem::recursive_directory_iterator(path_to_watch)) {
				auto current_file_last_write_time = std::filesystem::last_write_time(file);

				//std::cout << file.path() << std::endl;

				// File creation
				if (!contains(file.path().string())) {
					paths_[file.path().string()] = current_file_last_write_time;
					new Event(EventType::created, file.path().string());
					// File modification
				}
				else {
					if (paths_[file.path().string()] != current_file_last_write_time) {
						paths_[file.path().string()] = current_file_last_write_time;
						new Event(EventType::edited, file.path().string());
					}
				}
			}
		}
	}
private:
	std::unordered_map<std::string, std::filesystem::file_time_type> paths_;
	bool running_ = true;

	// Check if "paths_" contains a given key
	// If your compiler supports C++20 use paths_.contains(key) instead of this function
	bool contains(const std::string &key) {
		auto el = paths_.find(key);
		return el != paths_.end();
	}
};