#ifndef _EXPACKET_H_
#define _EXPACKET_H_

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

/**
 * This header file is just to split up some of the code in this example, as
 * it is pretty large.  Everything we need included has already been included.
 */

class PersonPacket : public Packet {
public:
  PersonPacket() : Packet(ID) {}
  virtual ~PersonPacket() {}

  static const int ID;

  int getSize() const {
    return Packet::getSize() + RawPacket::getSizeOf(age) +
      RawPacket::getSizeOf(firstName) + RawPacket::getSizeOf(lastName);
  }

  void writePacket(RawPacket& raw) const {
    assert(firstName.length() + 1 <= 10);
    assert(lastName.length() + 1 <= 20);
    Packet::writePacket(raw);
    raw << age << firstName << lastName;
  }

  void readPacket(RawPacket& raw) {
    Packet::readPacket(raw);
    raw >> age >> firstName >> lastName;
  }

  guint8 age;
  string firstName; //max size 10
  string lastName;  //max size 20
};

const int PersonPacket::ID = MIN_USER_ID;

/**
 * This is a packet class we purposely do not register so we can test the
 * error conditions of the PacketParser.  This class also demonstrates the
 * absolute minimum code to derive from Packet.
 */
class UnknownPacket : public Packet {
public:
  UnknownPacket() : Packet(ID) {}
  virtual ~UnknownPacket() {}

  static const int ID;

  int getSize() const {
    return Packet::getSize();
  }

  void writePacket(RawPacket& raw) const {
    Packet::writePacket(raw);
  }

  void readPacket(RawPacket& raw) {
    Packet::readPacket(raw);
  }
};

const int UnknownPacket::ID = MIN_USER_ID + 1;

void packetTest(const PersonPacket&, const PersonPacket&);
void parseTest(const Packet&, const Packet&);

#endif


