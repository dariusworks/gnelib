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

//EXINPUT
//This shows some ways to get input in a multithreaded environment using the
//  classes in GNE.  Since I want to show the fact that a program can be
//  using the screen and getting input at the same time, I figure I might as
//  well have some fun with it.  That's what the deal is with the night sky
//  stuff.

//Now this is strange.  I discovered that the MSVC MTCRT has a concept of
// "thread variables," which each thread keeps a copy of.  This is why I call
// srand from each thread -- when the thread is started, it gets a new copy
// some global variables, including the current rand seed.  This means that
// each thread gets the same random numbers, so each thread performs
// identically, meaning they aren't random.  So I generate some seed for each
// star.

#include "../../include/gnelib.h"
#include <stdlib.h>
#include <time.h>

using namespace GNE;
using namespace GNE::Console;

class Star : public Thread {
public:
  Star(int width, int height) : running(true) {
    randSeed = rand();
    x = rand() % width;
    y = rand() % height;
    star = rand() % 2;
    if (star)
      star = '*';
    else
      star = '.';
  }

  virtual ~Star() {
  }

  void stop() {
    running = false;
  }

protected:
  void run() {
    srand(randSeed); //See above on why I do this.
    while (running) {
      mlputchar(x, y, star);
      Thread::sleep(rand() % 3500 + 1000);
      mlputchar(x, y, ' ');
      if (running)
        Thread::sleep(rand() % 500);
    }
  }

private:
  int x, y;
  char star;
  bool running;
  int randSeed; 
};

const int NUM_STARS = 80;
Star* stars[NUM_STARS];

int main(int argc, char* argv[]) {
  initGNE(NO_NET, atexit);
  initConsole(atexit);
  setTitle("GNE Console Input Test");

  int width, height;
  mgetConsoleSize(&width, &height);
  if (width == 0)
    width = 80; //our best guess
  if (height == 0)
    height = 25;//our best guess

  srand(time(0));

  int c;
  for (c = 0; c < NUM_STARS; c++)
    stars[c] = new Star(width, height-2);

  for (c = 0; c < NUM_STARS; c++)
    stars[c]->start();

  mlprintf(0, height-2, "Presumed width: %i and height %i.  Please press a key.", width, height);

  //Normally this is a bad idea, because we cause 100% CPU usage in a busy
  //wait loop, but exinput is also a test of the console I/O functions.
  while (!kbhit()) {}
  int ch = getch();
  
  //Process the key, treating enter and BS specially
  char buf[10];
  if (ch == ENTER)
    sprintf(buf, "ENTER");
  else if (ch == BACKSPACE)
    sprintf(buf, "BACKSPACE");
  else
    sprintf(buf, "%c(%i)", (char)ch, ch);

  mlprintf(0, height-2, "You pressed: %s, now please type up to 30 chars below and hit enter:", buf);
  char str[31];
  int size = lgetString(0, height-1, str, 30);
  //since we don't know the size of the string we clear everything first.
  //We could do it better perhaps using strlen but who cares?
  //We just don't want the screen to scroll though by putting too many spaces.
  mlprintf(0, height-2, "                                                                           ");
  mlprintf(0, height-2, "You typed: \"%s\"(%i == %i). Goodnight stars!", str, size, strlen(str));

  for (c = 0; c < NUM_STARS; c++)
    stars[c]->stop();

  for (c = 0; c < NUM_STARS; c++)
    stars[c]->join();

  for (c = 0; c < NUM_STARS; c++)
    delete stars[c];

  return 0;
}


