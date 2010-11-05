/*******************************************************************************
** Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
**
** This library is free software; you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by the Free
** Software Foundation; either version 2.1 of the License, or (at your option)
** any later version.
**
** This library is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
** details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this library; if not, write to the Free Software Foundation, Inc.,
** 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*******************************************************************************/


#include "SS_Input_Manager.hxx"


using namespace OpenSpeedShop::cli;

int ExperimentObject::Determine_Status() {
  int expstatus = ExpStatus_NonExistent;
  if (FW() == NULL) {
    ExpStatus = expstatus;
  } else {
    ThreadGroup tgrp = FW()->getThreads();
    if (tgrp.empty()) {
      expstatus = ExpStatus_Paused;
    } else {
      ThreadGroup::iterator ti;
      for (ti = tgrp.begin(); ti != tgrp.end(); ti++) {
        Thread t = *ti;
        try {
          if (t.getState() == Thread::Running) {
           // if any thread is Running, the experiment is also.
            expstatus = ExpStatus_Running;
            break;
          } else if (t.getState() == Thread::Suspended) {
           // Paused can override Terminated
            expstatus = ExpStatus_Paused;
          } else if (t.getState() == Thread::Terminated) {
           // The experiment is terminated only if all the threads are.
            if (expstatus != ExpStatus_Paused) {
              expstatus = ExpStatus_Terminated;
            }
          } else if ((t.getState() == Thread::Connecting) ||
                     (t.getState() == Thread::Disconnected) ||
                     (t.getState() == Thread::Nonexistent)) {
           // These are 'Don't care" states at the user level.
           // Note: we might default to ExpStatus_NonExistent.
          } else {
            expstatus = ExpStatus_InError;
            break;
          }
        }
        catch(const Exception& error) {
         // Don't really care why.
         // Mark the experiment with an error and continue on.
          expstatus = ExpStatus_InError;
          break;
        }
      }
    }
    ExpStatus = expstatus;
  }
  return expstatus;
}

std::string ExperimentObject::ExpStatus_Name () {
  int expstatus = Status();
  if ((this == NULL) || (ExpStatus == ExpStatus_NonExistent)) return std::string("NonExistent");
  if (expstatus == ExpStatus_Paused) return std::string("Paused");
  if (expstatus == ExpStatus_Running) return std::string("Running");
  if (expstatus == ExpStatus_Terminated) return std::string("Terminated");
  if (expstatus == ExpStatus_InError) return std::string("Error");
  return std::string("Unknown");
}

void ExperimentObject::Print_Waiting (std::ostream &mystream) {
  Assert(pthread_mutex_lock(&Experiment_Lock) == 0);
  if (waiting_cmds.begin() != waiting_cmds.end()) {
    mystream << "  Waiting Commands" << std::endl;
    std::list<CommandObject *>::iterator wi;
    for (wi = waiting_cmds.begin(); wi != waiting_cmds.end(); wi++) {
      CommandObject *cmd = *wi;
      mystream << "    " << cmd->Clip()->Command() << std::endl;
    }
  }
  Assert(pthread_mutex_unlock(&Experiment_Lock) == 0);
}

void ExperimentObject::Print(std::ostream &mystream) {
  mystream << "Experiment " << ExperimentObject_ID() << " " << ExpStatus_Name() << " data->";
  if (TS_Lock()) {
    mystream << ((FW_Experiment != NULL) ? FW_Experiment->getName() : "(null)") << std::endl;
    if (FW_Experiment != NULL) {
      ThreadGroup tgrp = FW_Experiment->getThreads();
      ThreadGroup::iterator ti;
      bool atleastone = false;
      for (ti = tgrp.begin(); ti != tgrp.end(); ti++) {
        Thread t = *ti;
        std::string host = t.getHost();
        pid_t pid = t.getProcessId();
        if (!atleastone) {
          atleastone = true;
        }
        mystream << "    -h " << host << " -p " << pid;
        std::pair<bool, int> pthread = t.getOpenMPThreadId();
        if (pthread.first) {
          mystream << " -t " << pthread.second;
        } else {
          std::pair<bool, pthread_t> pthread = t.getPosixThreadId();
          if (pthread.first) {
            mystream << " -t " << pthread.second;
          }
        }
        std::pair<bool, int> rank = t.getMPIRank();
        if (rank.first) {
          mystream << " -r " << rank.second;
        }
        CollectorGroup cgrp = t.getCollectors();
        CollectorGroup::iterator ci;
        int collector_count = 0;
        for (ci = cgrp.begin(); ci != cgrp.end(); ci++) {
          Collector c = *ci;
          Metadata m = c.getMetadata();
          if (collector_count) {
            mystream << ",";
          } else {
            mystream << " ";
            collector_count = 1;
          }
          mystream << " " << m.getUniqueId();
        }
        mystream << std::endl;
      }

      CollectorGroup cgrp = FW_Experiment->getCollectors();
      CollectorGroup::iterator ci;
      atleastone = false;
      for (ci = cgrp.begin(); ci != cgrp.end(); ci++) {
        Collector c = *ci;
        ThreadGroup tgrp = c.getThreads();
        if (tgrp.empty()) {
          Metadata m = c.getMetadata();
          if (atleastone) {
            mystream << ",";
          } else {
            mystream << "   ";
            atleastone = true;
          }
          mystream << " " << m.getUniqueId();
        }
      }
      if (atleastone) {
        mystream << std::endl;
      }
    }
    Q_UnLock ();
  } else {
    mystream << "(Currently unable to access the database)" << std::endl;
  }
  Print_Waiting (mystream);
}
