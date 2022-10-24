#include "PostRepo.h"
#include <fstream>

PostRepo::PostRepo(std::string& _filename) {
	this->filename = _filename;
	this->readFromFile();
}


PostRepo::~PostRepo()
{
}

void PostRepo::readFromFile() {

	std::ifstream file(this->filename);
	if (file.is_open() == false)
		return;
	Post p;
	while (file >> p)
		this->posts.push_back(p);
	file.close();

}

void PostRepo::writeToFile() {
	std::ofstream file(this->filename);
	if (!file.is_open())
		return;

	for (auto& t : this->posts) {
		file << t;

	}
	file.close();
}

void PostRepo::updatePost(std::string old_text,std::string new_text) {

	for (int i = 0; i < this->posts.size(); i++)
		if (this->posts[i].getText() == old_text)
		{
			this->posts[i].setText(new_text);
		}

	
	this->writeToFile();
}


void PostRepo::addPost(int id, std::string text, std::string time,std::string user) {
	Post p = Post(id, text, time,user);
	this->posts.push_back(p);
	this->writeToFile();
}

int PostRepo::findPost(std::string description)
{
	for (auto elem : this->posts)
		if (elem.getText() == description)
			return 1;
	return 0;
}

