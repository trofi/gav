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

#ifndef _TEAM_H_
#define _TEAM_H_

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "ControlsArray.h"
#include "ScreenFont.h"
#include "globals.h"

extern ScreenFont *cga;

class Team {
 private:
  vector<Player *> _players;
  int _xmin;
  int _xmax;
  int _ymin;
  int _ymax;
  int _score;
  int _side;
  int _nplayers;
  int _playerNumInc;

 public:
  // side < 0: left, > 0 right
  Team(int side = -1) : _side(side) {
    _score = 0;
    _nplayers = 0;
    _playerNumInc = (side<0)?0:1;
    _xmin = (side<0)?8:(SCREEN_WIDTH() / 2) ;

    //304 the real half field width
    //    _xmax = _xmin + 304 ;
    _xmax = _xmin + (SCREEN_WIDTH() / 2) - 16;
    _ymin = 0;
    _ymax = 0;
  }

  inline void score() {
    _score++;
  }

  inline void setScore(int v) {
    _score = v;
  }

  inline int getScore() {
    return(_score);
  }

  inline Player * addPlayer(string name, pl_type_t type, int speed = 250) {
    Player *p = new Player(this, name, type, _nplayers * 2 + _playerNumInc,
			   speed);
    _players.push_back(p);
    for(unsigned int i = 0; i < _players.size(); i++)
      _players[i]->setX((i+1) * (_xmax + _xmin) / (_players.size()+1) - 
			(p->width() / 2));
    p->setY(GROUND_LEVEL);
    _nplayers++;
    return(p);
 }

  inline vector<Player *> players() {
    return(_players);
  }

  inline int xmax() { return _xmax; }
  inline int xmin() { return _xmin; }
  inline int ymax() { return _ymax; }
  inline int ymin() { return _ymin; }

  inline void xmax(int v) { _xmax = v; }
  inline void xmin(int v) { _xmin = v; }
  inline void ymax(int v) { _ymax = v; }
  inline void ymin(int v) { _ymin = v; }

  void draw(SDL_Surface *scr = screen) {
    SDL_Rect r;
    r.x = (_xmin < (SCREEN_WIDTH()/3))?100:(_xmax - 100);
    r.y = 0;
    for ( vector<Player *>::const_iterator it = _players.begin();
	  it != _players.end(); it++ )
      (*it)->draw(scr);
    char s[100];
    sprintf(s, "%d", _score);
    cga->printXY(scr, &r, s);
  }

  void update(int ticks, ControlsArray *ca) {
    for ( vector<Player *>::const_iterator it = _players.begin();
	  it != _players.end(); it++ ) {
      (*it)->update(ticks, ca);
    }
  }

};


#endif // _TEAM_H_