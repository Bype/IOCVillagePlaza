//
//  defines.h
//  IOCStadium
//
//  Created by Douglas Edric Stanley on 01|24|2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once


enum photobooth_state {
    PHOTO_IDLE=0, PHOTO_HELLO, PHOTO_LANGUAGE_SELECT, PHOTO_LANGUAGE_SELECTED, PHOTO_BADGE_REQUEST, PHOTO_PLEASE_ID, PHOTO_PAPARAZZI, PHOTO_CLICHE, PHOTO_ERROR, PHOTO_SLIDESHOW, PHOTO_CLICHE_SELECTED, PHOTO_POSTURE, PHOTO_PLAY, PHOTO_ABORT
};


// for the photobooth
#define TILT_DELAY          0.1f
#define PRESENCE_DELAY      1.f
#define ABSENCE_DELAY       1.f
#define PAPARAZZI_DELAY     3.f
#define PHOTO_DELAY         1.5f
#define PHOTO_ERROR_DELAY   5.f

#define PHOTO_COUNT         5

#define MAX_TILT             20
#define MIN_TILT            -30


