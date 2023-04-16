#pragma once

#include <chrono>
#include <fstream>

#include "Date.h"
#include "../Filesystem/Filesystem.h"
#include "../JsonParser/json.h"

class DateSetter {

 public:

  static void StartSession(Date& system_date);
  static void FinishSession();

};