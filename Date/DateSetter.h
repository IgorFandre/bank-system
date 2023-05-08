#pragma once

#include <chrono>
#include <fstream>

#include "../Filesystem/Filesystem.h"
#include "../JsonParser/json.h"
#include "Date.h"

class DateSetter {

public:
  static void StartSession(Date &system_date, bool write = true);
  static void FinishSession(bool write = true);
};