// Copyright [2013] chenzy
#include "AgendaService.h"
#include <iostream>

AgendaService::AgendaService() {
  userManage_ = UserManage::getInstance();
  meetingManage_ = MeetingManage::getInstance();
  fileManage_ = FileManage::getInstance();
}
AgendaService::~AgendaService() {
  delete userManage_;
  delete meetingManage_;
  delete fileManage_;
  userManage_ = NULL;
  meetingManage_ = NULL;
  fileManage_ = NULL;
}
User* AgendaService::userLogIn(std::string userName, std::string password) {
  User *tem = userManage_->findUserByName(userName);
  if (tem != NULL) {
    if (tem->getPassword() != password) {
      std::cout << "[error] password invalid!\n";  // 密码错误
      tem = NULL;
    }
  } else {
    std::cout << "[error] user name doesn't exist!\n";
  }  // 未注册用户名
  return tem;
}
bool AgendaService::userRegister(std::string userName, std::string password,
  std::string email, std::string phone) {
  return userManage_->createUser(userName, password, email, phone);
}
bool AgendaService::deleteUser(User user) {
  if (meetingManage_->listAllMeetings(user.getName()).empty())
    return userManage_->deleteUser(user);
  return false;
}
std::list<User> AgendaService::listAllUsers() {
  return userManage_->listAllUsers();
}
bool AgendaService::createMeeting(std::string userName, std::string title,
  std::string participator, std::string startTime, std::string endTime) {
  if (userManage_->findUserByName(participator) == NULL)
    return false;  // 参与者不存在则失败
  return  meetingManage_->addMeeting(userName, participator,
    Date::stringToDate(startTime), Date::stringToDate(endTime), title);
}
Meeting* AgendaService::meetingQuery(std::string title) {
  return meetingManage_->queryMeetingByTitle(title);
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName,
  std::string startDate, std::string endDate) {
  return meetingManage_->queryMeetingsByTime(userName,
    Date::stringToDate(startDate), Date::stringToDate(endDate));
}
std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
  return meetingManage_->listAllMeetings(userName);
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(
  std::string userName) {
  return meetingManage_->listAllSponsorMeetings(userName);
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(
  std::string userName) {
  return meetingManage_->listAllParticipateMeetings(userName);
}
bool AgendaService::deleteMeeting(std::string userName, std::string title) {
  return meetingManage_->deleteMeeting(userName, title);
}
bool AgendaService::deleteAllMeetings(std::string userName) {
  return meetingManage_->deleteAllMeetings(userName);
}
void AgendaService::startAgenda() {
  userManage_->initUsersList(fileManage_->readUsersFromFile());
  meetingManage_->initMeetingsList(fileManage_->readMeetingsFromFile());
}
void AgendaService::quitAgenda() {
  fileManage_->writeUsersToFile(userManage_->listAllUsers());
  fileManage_->writeMeetingsToFile(meetingManage_->acquireMeetingsList());
}
bool AgendaService::setPassword(std::string user, std::string password) {
  User *tem = userManage_->findUserByName(user);
  if (tem == NULL)
    return false;
  else
    return userManage_->updateUserPassword(*tem, password);
}
bool AgendaService::setEmail(std::string user, std::string email) {
  User *tem = userManage_->findUserByName(user);
  if (tem == NULL)
    return false;
  else
    return userManage_->updateUserEmail(*tem, email);
}
bool AgendaService::setPhone(std::string user, std::string phone) {
  User *tem = userManage_->findUserByName(user);
  if (tem == NULL)
    return false;
  else
    return userManage_->updateUserPhone(*tem, phone);
}
bool AgendaService::setParticipator(std::string title,
  std::string participator) {
  return meetingManage_->updateMeetingParticipator(title, participator);
}
bool AgendaService::setStartDate(std::string title,
  std::string stime) {
  return meetingManage_->updateMeetingStartDate(title,
    Date::stringToDate(stime));
}
bool AgendaService::setEndDate(std::string title,
  std::string etime) {
  return meetingManage_->updateMeetingEndDate(title, Date::stringToDate(etime));
}
