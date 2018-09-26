#include "Meeting.h"
using std::string;
Meeting::Meeting() {}
Meeting::Meeting(string s, string p, Date sd, Date ed, string t) {
  sponsor_ = s;
  participator_ = p;
  startDate_ = sd;
  endDate_ = ed;
  title_ = t;
}
string Meeting::getSponsor() const {
  return sponsor_;
}
void Meeting::setSponsor(string s) {
  sponsor_ = s;
}
string Meeting::getParticipator() const {
  return participator_;
}
void Meeting::setParticipator(string s) {
  participator_ = s;
}
Date Meeting::getStartDate() const {
  return startDate_;
}
void Meeting::setStartDate(Date d) {
  startDate_ = d;
}
Date Meeting::getEndDate() const {
  return endDate_;
}
void Meeting::setEndDate(Date d) {
  endDate_ = d;
}
string Meeting::getTitle() const {
  return title_;
}
void Meeting::setTitle(string s) {
  title_ = s;
}
