//
//  iansVideo.cpp
//  iansVideo
//
//  Created by ian s. smith on 5/12/17.
//
//


#include "cinder/qtime/QuickTimeGl.h"
#include "iansVideo.hpp"
#include "poShape.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"

using namespace po::scene;

iansVideoRef iansVideo::create()
{
    iansVideoRef node(new iansVideo());
    node->setup();
    return node;
}

iansVideo::iansVideo()
{
}

void iansVideo::setup()
{

    //  create a player that loops video
    mVideo = po::scene::VideoGl::create();
    ci::fs::path moviePath = ci::app::getAssetPath("16bit_scifi.mov");
    
    try {
        ci::qtime::MovieGlRef movieRef;
        
        movieRef = ci::qtime::MovieGl::create(moviePath);
        mVideo->setMovieRef(movieRef);
        mVideo->getMovieRef()->setLoop(true);
        mVideo->getMovieRef()->play();
    } catch (...) {
        ci::app::console() << "PlayerNode::setup: Failed to load movie" << std::endl;
    }
    
    mVideo->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mVideo->setPosition(ci::app::getWindowCenter());
    addChild(mVideo);
    
    //  create the spin button, and connect the mouse signal
    ci::gl::TextureRef spinnerTex = ci::gl::Texture::create(loadImage(ci::app::loadAsset("spinArrows.png")));
    ShapeRef spinner = Shape::create(spinnerTex);
    spinner->setAlignment(po::scene::Alignment::CENTER_CENTER);
    spinner->setPosition(ci::app::getWindowWidth() * 0.5, ci::app::getWindowHeight() * 0.85);
    spinner->getSignal(MouseEvent::Type::DOWN_INSIDE).connect(std::bind(&iansVideo::spinPlayer, this));
    addChild(spinner);
    
    mMask = Shape::createRect(100, 100);
    mMask->setAlignment(Alignment::CENTER_CENTER);
    mMask->setPosition(ci::app::getWindowWidth()/2, ci::app::getWindowHeight()/2);
    ci::app::timeline().apply(&mMask->getRotationAnim(), 0.0f, ci::toRadians(360.0f), 1.0f).loop();
    ci::app::timeline().apply(&mMask->getScaleAnim(), ci::vec2(1.0f, 1.0f), ci::vec2(4.0f, 4.0f), 1.0f).loop().pingPong();
    
    setMask(mMask);
    setAlpha(0.7f);
    mMask->setAlpha(0.7f);
    
    getSignal(MouseEvent::MOVE).connect(std::bind(&iansVideo::onMouseMove, this, std::placeholders::_1));
}
void iansVideo::onMouseMove(po::scene::MouseEvent &event)
{
    // Calculate the mask position based on the mouse
    ci::vec2 maskPos = event.getWindowPos();
    
    //	Set the mask position
    mMask->setPosition(maskPos);
}

void iansVideo::spinPlayer()
{
    ci::app::timeline().apply(&mVideo->getRotationAnim(), (float)M_PI * 2.0f, 2.0f).finishFn(std::bind(&iansVideo::resetPlayerRotation, this));
}

void iansVideo::resetPlayerRotation()
{
    mVideo->setRotation(0.0f);
}
