// Copyright [2013] chenzy
#include "UserManage.h"
#include <iostream>

bool UserManage::instanceFlag_ = false;
UserManage* UserManage::instance_ = NULL;
UserManage::UserManage() {}
UserManage::~UserManage() {
    users_.clear();
    instanceFlag_ = false;
}  // 实例化单例
UserManage* UserManage::getInstance() {
  if (!instanceFlag_) {
    instance_ = new UserManage();
    instanceFlag_ = true;
  }
  return instance_;
}
void UserManage::initUsersList(std::list<User> users) {
  users_.clear();
  std::list<User>::iterator p;
  for (p = users.begin(); p != users.end(); p++)
    users_.push_back(*p);
}  // 深拷贝
User* UserManage::findUserByName(std::string userName) {
  std::list<User>::iterator p;
  for (p = users_.begin(); p != users_.end(); p++) {
    if (p->getName() == userName) return &(*p);
  }
  return NULL;
}

bool UserManage::createUser(std::string userName, std::string userPassword,
  std::string userEmail, std::string userPhone) {
    bool email = true, phone = true;
    if (findUserByName(userName) != NULL) {
      std::cout << "[error] user name has existed!\n";
      return false;  // 若重名，则失败
    } else {
      if (!User::emailValid(userEmail)) {
        std::cout << "[error] email format error!\n";
        email = false;  // 邮箱格式错误
      }
      if (!User::phoneValid(userPhone)) {
        std::cout << "[error] phone format error!\n";
        phone = false;  // 电话格式错误
      }
      User tem(userName, userPassword, userEmail, userPhone);
      users_.push_back(tem);
      return email && phone;
    }
}
bool UserManage::deleteUser(User user) {
  std::list<User>::iterator p;
  for (p = users_.begin(); p != users_.end(); p++) {
    if (p->getName() ==  user.getName()) {
      users_.erase(p);
      return true;
    }
  }
  return false;
}
bool UserManage::updateUserPassword(User user, std::string newPassword) {
  std::list<User>::iterator p;
  for (p = users_.begin(); p !=users_.end(); p++) {
    if (p->getName() == user.getName()) {
      p->setPassword(newPassword);
      return true;
    }
  }
  return false;
}
bool UserManage::updateUserEmail(User user, std::string newEmail) {
  if (!User::emailValid(newEmail)) return false;
  std::list<User>::iterator p;
  for (p = users_.begin(); p !=users_.end(); p++) {
    if (p->getName() == user.getName()) {
      p->setEmail(newEmail);
      return true;
    }
  }
  return false;
}
bool UserManage::updateUserPhone(User user, std::string newPhone) {
  if (!User::phoneValid(newPhone)) return false;
  std::list<User>::iterator p;
  for (p = users_.begin(); p !=users_.end(); p++) {
    if (p->getName() == user.getName()) {
      p->setPhone(newPhone);
      return true;
    }
  }
  return false;
}

std::list<User> UserManage::listAllUsers() {return users_;}
