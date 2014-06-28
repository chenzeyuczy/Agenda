#include "Storage.h"
#include<fstream>

Storage *Storage::instance_ = nullptr;

Storage::Storage() {
  if (readFromFile("agenda.data") == false) {
    userList_.clear();
    meetingList_.clear();
  }
}

Storage* Storage::getInstance(void) {
  if (!instance_) {
  	instance_ = new Storage();
  }
  return instance_;
}

Storage::~Storage() {
  writeToFile("agenda.data");
}

bool Storage::sync(void) {
  return writeToFile("agenda.data");
}

void Storage::createUser(const User& user_) {
  userList_.push_back(user_);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
  std::list<User> v;
  for (auto i : userList_) {
  	if (filter(i))
  	  v.push_back(i);
  }
  return v;
}

int Storage::updateUser(std::function<bool(const User&)> filter, std::function<void(User&)> switcher) {
  int result = 0;
  for (auto i : userList_) {
  	if (filter(i)) {
      switcher(i);
  	  result++;
  	}
  }
  return result;
}

int Storage::deleteUser(std::function<bool(const User&)> filter) {
  int result = 0;
  for (auto i = userList_.begin(); i != userList_.end(); ++i) {
  	if (filter(*i)) {
  	  userList_.erase(i);
  	  result++;
  	}
  }
  return result;
}

void Storage::createMeeting(const Meeting& meeting_) {
  meetingList_.push_back(meeting_);
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) {
  std::list<Meeting> v;
  for (auto i : meetingList_) {
  	if (filter(i))
  	  v.push_back(i);
  }
  return v;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter, std::function<void(Meeting&)> switcher) {
  int result = 0;
  for (auto i : meetingList_) {
  	if (filter(i)) {
      switcher(i);
  	  result++;
  	}
  }
  return result;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
  int result = 0;
  for (auto i = meetingList_.begin(); i != meetingList_.end(); ++i) {
  	if (filter(*i)) {
  	  meetingList_.erase(i);
  	  result++;
  	}
  }
  return result;
}

bool Storage::readFromFile(const char *filename) {
	std::ifstream in(filename, std::ios::in);
	if (in.good())  {
		//  Read operations.
		std::string line, sub;
		int num;
		size_t front, back;
		getline(in, line, '\n');
		front = line.find_first_of("0123456789");
		back = line.find_last_of("0123456789");
		sub = line.substr(front, back - front + 1);
		num = std::stoi(sub);
		for (int i = 0; i < num; i++) {
			std::string userAttr[4];
			getline(in, line, '\n');
			for (int j = 0; j < 4; j++) {
				front = back = 0;
				front = line.find_first_of("\"", back + 1);
				back = line.find_first_of("\"", front + 1);
				userAttr[j] = line.substr(front + 1, back - front - 1);
			}
			User temp(userAttr[0], userAttr[1], userAttr[2], userAttr[3]);
			userList_.push_back(temp);
		}
		getline(in, line, '\n');
		front = line.find_first_of("0123456789");
		back = line.find_last_of("0123456789");
		sub = line.substr(front, back - front + 1);
		num = std::stoi(sub);
		for (int i = 0; i < num; i++) {
			std::string meetingAttr[5];
			getline(in, line, '\n');
			for (int j = 0; j < 4; j++) {
				front = back = 0;
				front = line.find_first_of("\"", back + 1);
				back = line.find_first_of("\"", front + 1);
				meetingAttr[j] = line.substr(front + 1, back - front - 1);
			}
			Meeting temp(meetingAttr[0], meetingAttr[1], Date::stringToDate(meetingAttr[2]), Date::stringToDate(meetingAttr[3]), meetingAttr[4]);
			meetingList_.push_back(temp);
		}
		in.close();
		return true;
	}
	return false;
}

bool Storage::writeToFile(const char *filename) {
	std::ofstream out(filename, std::ios::trunc);
	if (out.good()) {
		//  Write operations.
		out << "{collection:\"User\",total:" << userList_.size() << "}\n";
		for (auto i : userList_) {
			out << "{name:\"" << i.getName() << "\",pwd:\"" << i.getPassword()
				<< "\",phone:\"" << i.getPhone() << "\"}\n";
		}
		out << "{collection:\"Meeting\",total:" << meetingList_.size() << "}\n";
		for (auto i : meetingList_) {
			out << "{sponsor:\"" << i.getSponsor() << "\",participator:\""
				<< i.getParticipator() << "\",sdate:" << Date::dateToString(i.getStartDate())
				<< "\",edate:\"" << Date::dateToString(i.getEndDate())
				<< "\",title:\"" << i.getTitle() << "\"}\n";
		}
		out.close();
		return true;
	}
	return false;
}
