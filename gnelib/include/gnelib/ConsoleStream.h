#ifndef _CONSOLESTREAM_H_
#define _CONSOLESTREAM_H_

/* GNE - Game Networking Engine, a portable multithreaded networking library.
 * Copyright (C) 2001 Jason Winnebeck (gillius@mail.rit.edu)
 * Project website: http://www.rit.edu/~jpw9607/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

namespace GNE {
class Mutex;

namespace Console {

class ConsoleManipulator {
public:
  virtual ~ConsoleManipulator() {};

  virtual void action(std::ostream& o) const = 0;
};

/**
 * A class for syncronizing the gout stream.  You won't create this class
 * directly, but instead will use the acquire and release variables.
 */
class ConsoleMutex : public ConsoleManipulator {
public:
  ConsoleMutex(bool isAcquiring, Mutex& syncMutex);
  virtual ~ConsoleMutex();

  //Perform a release or an acquire, based on acq.
  void action(std::ostream& o) const;

private:
  //acq is true if we are trying to acquire, false if release.
  bool acq;

  //sync is the mutex we are wrapping
  Mutex& sync;
};

/**
 * A manipulator for gout essentially meant to facilitate a C++ iostream
 * version of mlprintf.  Using moveTo in the gout stream (and ONLY gout),
 * will set the stream to display the next line-buffered text using an
 * mlprintf rather than a normal mprintf.  gout needs to be acquired if other
 * threads might write to gout.  The following code:\n
 * gout << acquire << moveTo(10, 15) << "Hello, World!" << flush << release;
 * \nworks like mlprintf(10, 15, "Hello, World!");.  Other stuff may be
 * before if anything is in the stream -- remember gout, like cout, only
 * displays when it encounters a newline or is explicitly flushed.
 */
class moveTo : public ConsoleManipulator {
public:
  moveTo(int xLoc, int yLoc);
  virtual ~moveTo();

  void action(std::ostream& o) const;
private:
  int x, y;
};

}
}

std::ostream& operator << (std::ostream& o, const GNE::Console::ConsoleManipulator& cm);

#endif
