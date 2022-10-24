#pragma once
#include "Post.h"
#include<vector>
class PostRepo {

private:
	std::string filename;
	std::vector<Post> posts;

public:
	PostRepo(std::string& filename);
	std::vector<Post> getPosts() { return this->posts; };
	~PostRepo();
	void readFromFile();

	void writeToFile();

	void updatePost(std::string old_text,std::string new_text);

	void addPost(int id, std::string text, std::string time, std::string user);

	int findPost(std::string description);

	




};
