/* -*- C++ -*- */
/*
  GAV - Gpl Arcade Volleyball
  
  Copyright (C) 2002
  GAV team (http://sourceforge.net/projects/gav/)

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef __CONTROLSARRAY_H__
#define __CONTROLSARRAY_H__

#include <string.h>
#include "InputState.h"
#include "globals.h"

class Team;

typedef struct {
  int left_key;
  int right_key;
  int jump_key;
} controls_t;

typedef enum { CNTRL_LEFT = 1, CNTRL_RIGHT = 2, CNTRL_JUMP = 4} cntrl_t;

class ControlsArray {
  triple_t _inputs[MAX_PLAYERS];
  controls_t _keyMapping[MAX_PLAYERS];
  Uint8 _f[12];

public:
  ControlsArray() {
    memset(_inputs, 0, MAX_PLAYERS * sizeof(triple_t));
    memset(_f, 0, 12);
    initializeControls();
  }
  
  controls_t getControls(int plId) {
    return _keyMapping[plId];
  }
  
  void setControls(int plId, controls_t ctrls) {
    _keyMapping[plId] = ctrls;
  }

  //  void addChannel(){}
  void setControl(int plId, cntrl_t cntrl, int keysym) {
    controls_t *t =  &_keyMapping[plId];
    switch ( cntrl ) {
    case CNTRL_LEFT:
      t->left_key = keysym;
      break;
    case CNTRL_RIGHT:
      t->right_key = keysym;
      break;
    case CNTRL_JUMP:
      t->jump_key = keysym;
      break;
    }
  }
  void initializeControls();
  void setControlsState(InputState *is, Team * tl, Team * tr);
  inline triple_t getCommands(int idx) { return _inputs[idx];}

};

#endif // __CONROLSARRAY_H__

