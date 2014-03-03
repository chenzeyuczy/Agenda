// Copyright [2013] chenzy
#include "Meeting.h"

Meeting::Meeting() {}
Meeting::Meeting(std::string sponsor, std::string participator,
          Date startTime, Date endTime, std::string title):
  sponsor_(sponsor), participator_(participator),
  startDate_(startTime), endDate_(endTime), title_(title) {}
std::string Meeting::getSponsor() {return sponsor_;}
void Meeting::setSponsor(std::string sponsor) {sponsor_ = sponsor;}
std::string Meeting::getParticipator() {return participator_;}
void Meeting::setParticipator(std::string participator) {
  participator_ = participator;
}
Date Meeting::getStartDate() {return startDate_;}
void Meeting::setStartDate(Date StartTime) {startDate_ = StartTime;}
Date Meeting::getEndDate() {return endDate_;}
void Meeting::setEndDate(Date endTime) {endDate_ = endTime;}
std::string Meeting::getTitle() {return title_;}
void Meeting::setTitle(std::string title) {title_ = title;}
