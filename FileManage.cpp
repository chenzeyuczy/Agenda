// Copyright [2013] chenzy
#include "FileManage.h"
#include <iostream>
#include <fstream>

FileManage* FileManage::instance_ = NULL;
bool FileManage::instanceFlag_ = false;
FileManage::FileManage() {
  userFileName_ = "user.dat";
  meetingFileName_ = "meeting.dat";
}
FileManage::~FileManage() {
  instanceFlag_ = false;
}
FileManage* FileManage::getInstance() {
  if (!instanceFlag_) {
    instance_ = new FileManage();
    instanceFlag_ = true;
  }
  return instance_;
}
std::list<User> FileManage::readUsersFromFile() {
  std::ifstream in(userFileName_.c_str());
  std::string name, password, email, phone;
  std::list<User> tem;
  while (in >> name >> password >> email >> phone) {
    tem.push_back(User(name, password, email, phone));
  }
  in.close();
  return tem;
}
void FileManage::writeUsersToFile(std::list<User> users) {
  std::ofstream out(userFileName_.c_str(), std::ios::trunc);
  std::list<User>::iterator p;
  for (p = users.begin(); p != users.end(); p++) {
    out << p->getName() <<' ' << p->getPassword() << ' '
        << p->getEmail() << ' ' << p->getPhone() << std::endl;
  }
  out.close();
}
std::list<Meeting> FileManage::readMeetingsFromFile() {
  std::ifstream in(meetingFileName_.c_str(), std::ios::in);
  std::string sponsor, participator, stime, etime, title;
  std::list<Meeting> tem;
  while (in >> sponsor >> participator >> stime >> etime >> title) {
    tem.push_back(Meeting(sponsor, participator,
      Date::stringToDate(stime), Date::stringToDate(etime), title));
  }
  in.close();
  return tem;
}
void FileManage::writeMeetingsToFile(std::list<Meeting> meetings) {
  std::ofstream out(meetingFileName_.c_str(), std::ios::trunc);
  std::list<Meeting>::iterator p;
  for (p = meetings.begin(); p != meetings.end(); p++) {
    out << p->getSponsor() << ' ' << p->getParticipator() << ' '
        << Date::dateToString(p->getStartDate()) << ' '
        << Date::dateToString(p->getEndDate()) << ' '
        << p->getTitle() << std::endl;
  }
  out.close();
}
