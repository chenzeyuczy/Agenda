#ifndef AGENDASERVICE_H
#define AGENDASERVICE_H

#include "UserManage.h"
#include "MeetingManage.h"
#include "FileManage.h"
#include <list>
#include <string>

class AgendaService {
 public:
  AgendaService();
  ~AgendaService();
  User* userLogIn(std::string userName, std::string password);
  bool userRegister(std::string userName, std::string password,
                    std::string email, std::string phone);
  bool deleteUser(User user);
  std::list<User> listAllUsers(void);
  bool createMeeting(std::string userName, std::string title,
                     std::string participator, std::string startTime,
                     std::string endTime);
  Meeting* meetingQuery(std::string title);
  std::list<Meeting> meetingQuery(std::string userName, std::string startDate,
                                  std::string endDate);
  std::list<Meeting> listAllMeetings(std::string userName);
  std::list<Meeting> listAllSponsorMeetings(std::string userName);
  std::list<Meeting> listAllParticipateMeetings(std::string userName);
  bool deleteMeeting(std::string userName, std::string title);
  bool deleteAllMeetings(std::string userName);

  void startAgenda(void);
  void quitAgenda(void);

  bool setPassword(std::string user, std::string password);
  bool setEmail(std::string user, std::string email);
  bool setPhone(std::string user, std::string phone);
  bool setParticipator(std::string title, std::string participator);
  bool setStartDate(std::string title, std::string stime);
  bool setEndDate(std::string title, std::string etime);

 private:
  UserManage *userManage_;
  MeetingManage *meetingManage_;
  FileManage *fileManage_;
};

#endif
