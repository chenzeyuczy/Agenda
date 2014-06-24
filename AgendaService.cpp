#include "AgendaService.h"

AgendaService::AgendaService() {
  serviceRunning_ = 0;
  storage_.GetInstance();
}

AgendaService::AgendaService() {
  serviceRunning_--;
}

