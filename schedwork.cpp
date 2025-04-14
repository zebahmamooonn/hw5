#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper
  (const AvailabilityMatrix& avail,
  size_t dailyNeed,
  size_t maxShifts,
  DailySchedule& sched,
  vector<size_t>& shiftCounts,
  size_t day){

    if(day == avail.size()){
      return true; 
    }

    size_t numWorkers = avail[0].size();
    vector<Worker_T>& today = sched[day]; 

    for(size_t i =0; i < numWorkers; i++){
      if(avail[day][i] && shiftCounts[i] < maxShifts && find(today.begin(), today.end(), i) == today.end()){
        today.push_back(i);
        shiftCounts[i]++;
        if (today.size() == dailyNeed){
          if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, day + 1)){
            return true; 
          }
        }
        else{
          if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, day)){
            return true; 
          }
        }
        today.pop_back();
        shiftCounts[i]--; 
      }
    }
  return false; 
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t numDays = avail.size(); 
    size_t numWorkers = avail[0].size(); 
    sched.resize(numDays);
    for(auto& day : sched){
      day.reserve(dailyNeed); 
    }

    vector<size_t> shiftCounts(numWorkers, 0); 

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, 0); 



}

