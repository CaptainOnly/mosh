/*
    Mosh: the mobile shell
    Copyright 2012 Keith Winstein

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    In addition, as a special exception, the copyright holders give
    permission to link the code of portions of this program with the
    OpenSSL library under certain conditions as described in each
    individual source file, and distribute linked combinations including
    the two.

    You must obey the GNU General Public License in all respects for all
    of the code used other than OpenSSL. If you modify file(s) with this
    exception, you may extend this exception to your version of the
    file(s), but you are not obligated to do so. If you do not wish to do
    so, delete this exception statement from your version. If you delete
    this exception statement from all source files in the program, then
    also delete it here.
*/

#ifndef TERMINALUSERINPUT_HPP
#define TERMINALUSERINPUT_HPP

#include <string>
#include <vector>
#include "parseraction.h"

namespace Terminal {
  class UserInput {
  public:
    enum UserInputState {
      Ground,
      ESC,
      SS3,
      CSI,
      CSI_AB   /* CSI > (angle bracket) */
    };

  private:
    UserInputState state;
    std::string collector; 	 /* characters seen since last ground state */
    std::vector<std::string> ps; /* paramters parsed in CSI_AB state */

  public:
    UserInput()
      : state( Ground ), collector( "" ), ps()
    {}

    std::string input( const Parser::UserByte *act,
		       bool application_mode_cursor_keys,
		       std::string & client_type,
		       std::string & client_version);

    bool operator==( const UserInput &x ) const { return state == x.state; }
  };
}

#endif
