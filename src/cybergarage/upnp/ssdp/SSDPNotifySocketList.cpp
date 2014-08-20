/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SSDPNotifySocketList.cpp
*
*  Revision;
*
*  08/14/03
*    - first revision
*  07/17/04
*    - Added the destructor and clear().
*
******************************************************************/

#include <cybergarage/upnp/ssdp/SSDPNotifySocketList.h>

using namespace std;
using namespace CyberLink;
using namespace uHTTP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
  
SSDPNotifySocketList::SSDPNotifySocketList()  {
}

SSDPNotifySocketList::~SSDPNotifySocketList()  {
  stop();
}

////////////////////////////////////////////////
// ControlPoint
////////////////////////////////////////////////

void SSDPNotifySocketList::setControlPoint(ControlPoint *ctrlPoint) {
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPNotifySocket *sock = getSSDPNotifySocket(n);
    sock->setControlPoint(ctrlPoint);
  }
}

////////////////////////////////////////////////
// open/close
////////////////////////////////////////////////
  
bool SSDPNotifySocketList::open() {
  bool isAllHostOpened = true;
  size_t nHostAddrs = GetNHostAddresses();
  for (size_t n = 0; n < nHostAddrs; n++) {
    string bindAddr;
    GetHostAddress(n, bindAddr);
    SSDPNotifySocket *ssdpNotifySocket = new SSDPNotifySocket();
    if (ssdpNotifySocket->open(bindAddr) == false) {
      delete ssdpNotifySocket;
      isAllHostOpened = false;
      continue;
    }
    add(ssdpNotifySocket);
  }
  return isAllHostOpened;
}
  
bool SSDPNotifySocketList::close() {
  bool areAllSocketsClosed = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPNotifySocket *sock = getSSDPNotifySocket(n);
    if (sock->close() == false) {
      areAllSocketsClosed = false;
    }
  }
  clear();
  return areAllSocketsClosed;
}
  
////////////////////////////////////////////////
// start/stop
////////////////////////////////////////////////
  
bool SSDPNotifySocketList::start() {
  bool areAllSocketsStarted = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPNotifySocket *sock = getSSDPNotifySocket(n);
    if (sock->start() == false) {
      areAllSocketsStarted = false;
    }
  }
  return areAllSocketsStarted;
}

bool SSDPNotifySocketList::stop() {
  bool areAllSocketsStopped = true;
  size_t nSockets = size();
  for (size_t n = 0; n < nSockets; n++) {
    SSDPNotifySocket *sock = getSSDPNotifySocket(n);
    if (sock->stop() == false) {
      areAllSocketsStopped = false;
    }
  }
  close();
  return areAllSocketsStopped;
}
