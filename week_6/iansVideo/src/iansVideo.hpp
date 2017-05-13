//
//  iansVideo.hpp
//  iansVideo
//
//  Created by ian s. smith on 5/12/17.
//
//

#pragma once

#include "poNodeContainer.h"
#include "poVideo.h"
#include "poShape.h"
#include "poImage.h"


class iansVideo;
typedef std::shared_ptr<iansVideo> iansVideoRef;

class iansVideo
: public po::scene::NodeContainer
{
public:
    static iansVideoRef create();
    
    void setup();
    
protected:
    iansVideo();
    
private:
    po::scene::VideoGlRef       mVideo;
    void                        spinPlayer();
    void                        resetPlayerRotation();
    
    po::scene::ShapeRef mMask;
    
    //	Mouse event handlers
    void onMouseMove(po::scene::MouseEvent &event);
    
};
