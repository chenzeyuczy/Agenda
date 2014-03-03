#ifndef MEETINGMANAGE_H
#define MEETINGMANAGE_H

#include "Meeting.h"
#include <list>
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

class MeetingManage {
 public:
  ~MeetingManage();
  static MeetingManage *getInstance();
  void initMeetingsList(std::list<Meeting> meetings);
  std::list<Meeting> acquireMeetingsList(void);
  bool addMeeting(std::string sponsor, std::string participator,
                  Date stime, Date etime, std::string title);
  bool deleteMeeting(std::string userName, std::string title);
  bool deleteAllMeetings(std::string userName);
  bool updateMeetingParticipator(std::string title,
                                 std::string newParticipator);
  bool updateMeetingStartDate(std::string title, Date newStartDate);
  bool updateMeetingEndDate(std::string title, Date newEndDate);
  Meeting* queryMeetingByTitle(std::string title);
  std::list<Meeting> queryMeetingsByTime(std::string userName,
                                         Date stime, Date etime);
  std::list<Meeting> listAllMeetings(std::string userName);
  std::list<Meeting> listAllSponsorMeetings(std::string userName);
  std::list<Meeting> listAllParticipateMeetings(std::string userName);

 private:
  MeetingManage();
  std::list<Meeting> meetings_;
  static bool instanceFlag_;
  static MeetingManage *instance_;
  DISALLOW_COPY_AND_ASSIGN(MeetingManage);
};

#endif
