/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**********/
// "liveMedia"
// Copyright (c) 1996-2007 Live Networks, Inc.  All rights reserved.
// A simple UDP sink (i.e., without RTP or other headers added); one frame per packet
// C++ header

#ifndef _SIMPLE_UDP_SINK_HH
#define _SIMPLE_UDP_SINK_HH

#ifndef _MEDIA_SINK_HH
#include "MediaSink.hh"
#endif
#ifndef _GROUPSOCK_HH
#include <Groupsock.hh>
#endif

class BasicUDPSink: public MediaSink {
public:
  static BasicUDPSink* createNew(UsageEnvironment& env, Groupsock* gs,
				  unsigned maxPayloadSize = 1450);
protected:
  BasicUDPSink(UsageEnvironment& env, Groupsock* gs, unsigned maxPayloadSize);
      // called only by createNew()
  virtual ~BasicUDPSink();

private: // redefined virtual functions:
  virtual Boolean continuePlaying();

private:
  void continuePlaying1();

  static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  void afterGettingFrame1(unsigned frameSize, unsigned numTruncatedBytes,
			  unsigned durationInMicroseconds);

  static void sendNext(void* firstArg);

private:
  Groupsock* fGS;
  unsigned fMaxPayloadSize;
  unsigned char* fOutputBuffer;
  struct timeval fNextSendTime;
};

#endif
