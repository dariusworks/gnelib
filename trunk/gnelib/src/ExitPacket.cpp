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

#include "../include/gnelib/gneintern.h"
#include "../include/gnelib/ExitPacket.h"
#include "../include/gnelib/Packet.h"
#include "../include/gnelib/RawPacket.h"

namespace GNE {

//##ModelId=3C7071E0016F
const int ExitPacket::ID = 2;

//##ModelId=3C7071E00170
ExitPacket::ExitPacket() : Packet(ID) {
}

//##ModelId=3C7071E00171
ExitPacket::~ExitPacket() {
}

//##ModelId=3C7071E00173
Packet* ExitPacket::makeClone() const {
  return new ExitPacket(*this);
}

//##ModelId=3C7071E00178
int ExitPacket::getSize() const {
  return Packet::getSize();
}

//##ModelId=3C7071E0017A
void ExitPacket::writePacket(RawPacket& raw) const {
  Packet::writePacket(raw);
}

//##ModelId=3C7071E0017D
void ExitPacket::readPacket(RawPacket& raw) {
  Packet::readPacket(raw);
}

//##ModelId=3C7071E00180
Packet* ExitPacket::create() {
  return new ExitPacket;
}

}
