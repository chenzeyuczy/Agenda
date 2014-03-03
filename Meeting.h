#ifndef MEETING_H
#define MEETING_H

#include "Date.h"

class Meeting {
 public:
  Meeting();
  Meeting(std::string sponsor, std::string participator,
          Date startTime, Date endTime, std::string title);
  std::string getSponsor(void);
  void setSponsor(std::string sponsor);
  std::string getParticipator(void);
  void setParticipator(std::string participator);
  Date getStartDate(void);
  void setStartDate(Date startTime);
  Date getEndDate(void);
  void setEndDate(Date endTime);
  std::string getTitle(void);
  void setTitle(std::string title);

 private:
  std::string sponsor_;
  std::string participator_;
  Date startDate_;
  Date endDate_;
  std::string title_;
};

#endif
