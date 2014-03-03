// Copyright [2013] chenzy
#include "MeetingManage.h"
#include <iostream>

bool MeetingManage::instanceFlag_ = false;
MeetingManage* MeetingManage::instance_ = NULL;
MeetingManage::MeetingManage() {}
MeetingManage::~MeetingManage() {
  meetings_.clear();
  instanceFlag_ = false;
}  // 实例化单例
MeetingManage* MeetingManage::getInstance() {
  if (!instanceFlag_) {
    instance_ = new MeetingManage();
    instanceFlag_ = true;
  }
  return instance_;
}
void MeetingManage::initMeetingsList(std::list<Meeting> meetings) {
  meetings_.clear();
  std::list<Meeting>::iterator p;
  for (p = meetings.begin(); p != meetings.end(); p++)
    meetings_.push_back(*p);
}  // 深拷贝
std::list<Meeting> MeetingManage::acquireMeetingsList(void) {
  return meetings_;
}
bool MeetingManage::addMeeting(std::string sponsor, std::string participator,
  Date stime, Date etime, std::string title) {
    if (!Date::isValid(stime)) return false;
    if (!Date::isValid(etime)) return false;
    if (stime > etime) return false;
    if (sponsor == participator) {
      std::cout << "[error] cannot invite yourself!\n";
      return false;  // 无法邀请自己
    }
    std::list<Meeting>::iterator p;
    Meeting tem(sponsor, participator, stime, etime, title);
    for (p = meetings_.begin(); p != meetings_.end(); p++) {
      if (p->getTitle() == title) return false;
    }  // 若会议重名则失败
    std::list<Meeting> m1 = listAllMeetings(sponsor),
      m2 = listAllMeetings(participator);
    for (p = m1.begin(); p != m1.end(); p++) {
      if ((p->getStartDate() > stime && p->getStartDate() < etime) ||
        (p->getEndDate() > stime && p ->getStartDate() < etime)) {
        return false;
      }
    }  // 若发起者期间有其他会议则失败
    for (p = m2.begin(); p != m2.end(); p++) {
      if ((p->getStartDate() > stime && p->getStartDate() < etime) ||
        (p->getEndDate() > stime && p ->getStartDate() < etime)) {
        return false;
      }
    }  // 若参与者期间有其他会议则失败
    meetings_.push_back(tem);
    return true;
}
bool MeetingManage::deleteMeeting(std::string userName, std::string title) {
  bool flag = false;
  std::list<Meeting>::iterator p;
  for (p = meetings_.begin(); p != meetings_.end();) {
    if (p->getTitle() == title && p->getSponsor() == userName) {
      meetings_.erase(p++);
      flag = true;
    } else {
      p++;
    }
  }  // title与人名匹配则删除
  return flag;
}
bool MeetingManage::deleteAllMeetings(std::string userName) {
  bool flag = false;
  std::list<Meeting>::iterator p;
  for (p = meetings_.begin(); p != meetings_.end();) {
    if (p->getSponsor() == userName || p->getParticipator() == userName) {
      meetings_.erase(p++);
      flag = true;
    } else {
      p++;
    }
  }  // 未删除则失败
  return flag;
}
bool MeetingManage::updateMeetingParticipator(
  std::string title, std::string newParticipator) {
    std::list<Meeting>::iterator p;
    for (p = meetings_.begin(); p != meetings_.end(); p++) {
      if (p->getTitle() == title) {
        if (p->getSponsor() == newParticipator) {
          std::cout << "[error] cannot invite yourself!\n";
          return false;
        }  // 无法邀请自己
        p->setParticipator(newParticipator);
        return true;
      }
    }
    return false;
}
bool MeetingManage::updateMeetingStartDate(std::string title,
  Date newStartDate) {
  if (!Date::isValid(newStartDate)) return false;
  std::list<Meeting>::iterator p;
  for (p = meetings_.begin(); p != meetings_.end(); p++) {
    if (p->getTitle() == title) {
      if (newStartDate > p->getEndDate())
        return false;  // start晚于end
      p->setStartDate(newStartDate);
      return true;
    }
  }
  return false;
}
bool MeetingManage::updateMeetingEndDate(std::string title,
  Date newEndDate) {
  if (!Date::isValid(newEndDate)) return false;
  std::list<Meeting>::iterator p;
  for (p = meetings_.begin(); p != meetings_.end(); p++) {
    if (p->getTitle() == title) {
      if (p->getStartDate() > newEndDate)
        return false;  // end早于start
      p->setEndDate(newEndDate);
      return true;
    }
  }
  return false;
}
Meeting* MeetingManage::queryMeetingByTitle(std::string title) {
  std::list<Meeting>::iterator p;
  for (p = meetings_.begin(); p != meetings_.end(); p++) {
    if (p->getTitle() == title) {
    return &(*p);
    }
  }
  return NULL;
}
std::list<Meeting> MeetingManage::queryMeetingsByTime(
  std::string userName, Date stime, Date etime) {
  std::list<Meeting>::iterator p;
  std::list<Meeting> tem;
  for (p = meetings_.begin(); p != meetings_.end(); p++) {
    if ((p->getStartDate() > stime || p->getStartDate() < etime) &&
      (p->getEndDate() > stime && p->getEndDate() < etime)) {
      tem.push_back(*p);
    }
  }  // 时间段交叉则push
  return tem;
}
std::list<Meeting> MeetingManage::listAllMeetings(std::string userName) {
  std::list<Meeting>::iterator p;
  std::list<Meeting> tem;
  for (p = meetings_.begin(); p != meetings_.end(); p++) {
    if (p->getSponsor() == userName || p->getParticipator() == userName) {
      tem.push_back(*p);
    }
  }  // 列举所有发起和参与的会议
  return tem;
}
std::list<Meeting> MeetingManage::listAllSponsorMeetings(std::string userName) {
  std::list<Meeting>::iterator p;
  std::list<Meeting> tem;
  for (p = meetings_.begin(); p != meetings_.end(); p++) {
    if (p->getSponsor() == userName) {
      tem.push_back(*p);
    }
  }
  return tem;
}
std::list<Meeting> MeetingManage::listAllParticipateMeetings(
  std::string userName) {
  std::list<Meeting>::iterator p;
  std::list<Meeting> tem;
  for (p = meetings_.begin(); p != meetings_.end(); p++) {
    if (p->getParticipator() == userName) {
      tem.push_back(*p);
    }
  }
  return tem;
}
