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

#ifndef _THEMES_H_
#define _THEMES_H_
#include <string>
#include <iostream>

#include <sys/types.h>
#include <dirent.h>

#define TH_DEFAULT "classic"
#define TH_DIR "themes"

#define TH_NET          "net.png"
#define TH_LEFTMALE     "plml.png"
#define TH_RIGHTMALE    "plmr.png"
#define TH_LEFTFEMALE   "plfl.png"
#define TH_RIGHTFEMALE  "plfr.png"
#define TH_BACKGROUND   "background.png"
#define TH_BALL         "ball.png"
#define TH_FONT         "Font.png"
#define TH_FONTINV      "FontInv.png"

extern std::string ThemeDir;

class Theme {
 private:
    std::string _name;
    bool _hasnet; // To possibly add the image of the net (not used yet)
    std::string _background;
    std::string _net;
    std::string _font;
    std::string _fontinv;
    std::string _leftmale;
    std::string _rightmale;
    std::string _leftfemale;
    std::string _rightfemale;
    std::string _ball;

    bool _checkTheme(); // Theme Validation
    
 public:
    Theme(std::string name) {
	DIR *dir;
	if ((dir = opendir(ThemeDir.c_str())) == NULL) {
	  ThemeDir = "/usr/share/games/gav/" + ThemeDir;
	  if ((dir = opendir(ThemeDir.c_str())) == NULL) {
	    std::cerr << "Cannot find themes directory\n";
	    exit(0);
	  } else
	    closedir(dir);
	} else
	  closedir(dir);

	std::string TD = ThemeDir + "/" + name +  "/";

	_name = name;

	_net = TD + TH_NET;

	_background = TD + TH_BACKGROUND;

	_font    = TD + TH_FONT;
	_fontinv = TD + TH_FONTINV;
	
	_leftmale    = TD + TH_LEFTMALE;
	_rightmale   = TD + TH_RIGHTMALE;
	_leftfemale  = TD + TH_LEFTFEMALE;
	_rightfemale = TD + TH_RIGHTFEMALE;
	
	_ball = TD + TH_BALL;

	_hasnet = Theme::_checkTheme();

    }
#define _CCS(str) ((str).c_str())

    inline const char * name()       { return( _CCS(_name)        );}
    inline bool   hasnet()     { return( _hasnet            );}
    inline const char * background() { return( _CCS(_background)  );}
    inline const char * net()        { return( _CCS(_net)         );}
    inline const char * font()       { return( _CCS(_font)        );}
    inline const char * fontinv()    { return( _CCS(_fontinv)     );}
    inline const char * leftmale()   { return( _CCS(_leftmale)    );}
    inline const char * rightmale()  { return( _CCS(_rightmale)   );}
    inline const char * leftfemale() { return( _CCS(_leftfemale)  );}
    inline const char * rightfemale(){ return( _CCS(_rightfemale) );}
    inline const char * ball()       { return( _CCS(_ball)        );}

};


extern Theme *CurrentTheme;


inline void setThemeDir(std::string h) { ThemeDir = h; }
#endif
