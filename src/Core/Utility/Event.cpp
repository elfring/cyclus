// Event.cpp

#include "Event.h"
#include "Timer.h"

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
event_ptr Event::addVal(std::string field, boost::any val) {
  vals_[count_].first = field;
  vals_[count_].second = val;
  ++count_;
  return event_ptr(this);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Event::record() {
  vals_.resize(count_);
  manager_->addEvent(event_ptr(this));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Event::Event(EventManager* m, std::string title)
  : title_(title),
    manager_(m),
    count_(0) {
  vals_.resize(10);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Event::~Event() { }

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string Event::title() {
  return title_;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
const Event::List& Event::vals() {
  return vals_;
}

