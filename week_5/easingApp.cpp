#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "cinder/Timeline.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class easingApp : public App {
public:
    void setup() override;
    void mouseDown(MouseEvent event) override;
    void mouseUp(MouseEvent event) override;
    void update() override;
    void draw() override;
    
    ci::Anim<ci::vec2> mBlackPos, mWhitePos;
    ci::Anim<float> mFactor = 1.f;
    ci::Anim<float> mRadius;
    ci::Anim<float> mORadius;
    ci::Anim<Color> mButtonColor;
    //ci::Anim<Color> mButtonChange;
    //ci::Anim<char> on, off;
    //ci::Anim<string> off;
    //char on, off;
    
    bool tog;
    int height;
    int width;
    ci::vec2 center;
    string buttontext;
    
    
};

void easingApp::setup()
{
    height = getWindowHeight();
    width = getWindowWidth();
    
    center = ci::vec2(width/2, height/2);
    
    mBlackPos = ci::app::getWindowCenter();
    mButtonColor = Color( 1.f,0.f,0.f);
    mWhitePos =  mBlackPos;
    mRadius = 20.0f;
    mORadius = 25.0f;
    
    //on = "on";
    //off = "off";
    buttontext = "off";
    
    tog = false;
    
};


void easingApp::draw()
{
    gl::clear(Color::white());
    gl::color(Color(0.8f,0.8f,0.8f));
    gl::drawSolidCircle( mBlackPos.value(), mORadius.value());
    //gl::drawSolidCircle( mBlackPos.value(), mORadius.value());
    gl::color(mButtonColor);
    gl::drawSolidCircle( mBlackPos.value(), mRadius.value());
    gl::drawString( buttontext, vec2(width/2-5,height/2-3),Color(1.0,1.0,1.0));
    //gl::drawString( buttontext, mBlackPos.value(),Color(0.0,0.0,0.0));
}

void easingApp::mouseDown(MouseEvent event)
{
    if(tog == true){
        //Color ButtonColor(1.0f,0.5f,0.5f);
        Color ButtonColor(0.5f,0.5f,1.0f);
        //timeline().apply(&off, &on, 0.1f, ci::EaseInBack());
        //timeline().apply(&mBlackPos, (ci::vec2)event.getPos(), 0.1f, ci::EaseInBack());
        timeline().apply(&mButtonColor, ButtonColor, 0.2f, ci::EaseInCubic());
        //buttontext = "on";
        //timeline().apply(&mButtonColor, &mButtonChange, 1.0f, ci::EaseInCubic());
        //timeline().apply(&off, &on, 1.0f, ci::EaseInCubic());
    }
    else{
        Color ButtonColor(1.0f,0.5f,0.5f);
        //Color ButtonColor(0.5f,0.5f,1.0f);
        //timeline().apply(&mBlackPos, (ci::vec2)event.getPos(), 0.1f, ci::EaseInBack());
        timeline().apply(&mButtonColor, ButtonColor, 0.2f, ci::EaseInCubic());
        
    }
};
void easingApp::mouseUp(MouseEvent event)
{
    if(tog == true){
        Color ButtonColor(1.0f,0.0f,0.0f);
        //timeline().apply(&mBlackPos, (ci::vec2)event.getPos(), 0.2f, ci::EaseInBack());
        timeline().apply(&mButtonColor, ButtonColor, 0.3f, ci::EaseInCubic());
        buttontext = "off";
        tog = false;
        //timeline().apply(&mButtonColor, &mButtonChange, 1.0f, ci::EaseInCubic());
        //timeline().apply(&on, &off, 1.0f, ci::EaseInCubic());
    }else{
        Color ButtonColor(0.0f,0.0f,1.0f);
        //timeline().apply(&mBlackPos, (ci::vec2)event.getPos(), 0.2f, ci::EaseInBack());
        timeline().apply(&mButtonColor, ButtonColor, 0.3f, ci::EaseInCubic());
        buttontext = "on";
        //timeline().apply(&mButtonColor, &mButtonChange, 1.0f, ci::EaseInCubic());
        tog = true;
    }
};

void easingApp::update()
{
}

CINDER_APP( easingApp, RendererGl )


