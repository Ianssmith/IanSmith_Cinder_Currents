//
//  Header.h
//  iansVideo
//
//  Created by ian s. smith on 5/12/17.
//
//


#pragma once

#include "cinder/app/App.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include "cinder/qtime/QuickTimeGl.h"

class iansVideo;

typedef std::shared_ptr<iansVideo> iansVideoRef;
typedef ci::signals::Signal<void()> VideoEndedSignal;

class iansVideo{
public:
    static iansVideoRef create();
    void loadVideo(std::string videoPath);
    void update();
    void draw();
    void stop();
    void play();
    void setLoop(bool bIsLoop);
    void onVideoEnded();
    
    VideoEndedSignal& getVideoEndedSignal(){return mVideoEndedSignal;}
private:
    iansVideo();
    void setup();
    void setPath(std::string path);
    
    VideoEndedSignal        mVideoEndedSignal;
    
    ci::gl::TextureRef      mFrameTexture;
    ci::qtime::MovieGlRef   mMovie;
    ci::fs::path            mMoviePath;
    
};
