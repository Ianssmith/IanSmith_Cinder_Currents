

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <string>
//#include <sstream>
//#include <iostream>
//#include <iomanip>
#include "cinder/Font.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/*
DisplayRef display = Display::getMainDisplay();
int displayWidth = display->getWidth();
*/


class digitalClockApp : public App {
public:
    static void prepare( Settings *settings );
    void setup() override;
    //void mouseDown( MouseEvent event ) override;
    void update() override;
    void draw() override;
    
    
protected:
    string getSecondsSinceMidnight();
    string getMin();
    Font mFont;
};

void digitalClockApp::prepare( Settings *settings )
{
    settings->setTitle( "Digital Clock" );
    settings->setWindowSize( 600, 100 );
}

void digitalClockApp::setup()
{
    //mFont = Font( loadAsset( "font/b2sq.ttf" ), 342 );
    mFont = Font( loadAsset( "font/ShareTechMono-Regular.ttf" ), 142 );

}

//void digitalClockApp::mouseDown( MouseEvent event )
//{
//}

void digitalClockApp::update()
{
}

void digitalClockApp::draw()
{
    auto t = std::time( nullptr );
    auto d = std::localtime( &t );
    
    gl::clear( Color( 0, 0, 0 ) );
    
    //vec2 center = 0.5f * vec2( getWindowSize() );
    
    gl::color( Color::white() );
    
    string seconds = getSecondsSinceMidnight();
    string min = getMin();
    
    gl::drawStringCentered( std::to_string(d->tm_hour) +":" + min + ":" + seconds, vec2( 0.5f * getWindowWidth(), 100.0f ), Color::white(), mFont );


}

string digitalClockApp::getMin()
{
    auto t = std::time( nullptr );
    auto d = std::localtime( &t );
    string ss;
    
    if(d->tm_min <=9){
        ss = "0" + to_string(d->tm_min);
        return ss;
    }else{
        return to_string(d->tm_min);
    }
    
    
    //return int( d->tm_hour * 3600 + d->tm_min * 60 + d->tm_sec );
    
}

string digitalClockApp::getSecondsSinceMidnight()
{
    auto t = std::time( nullptr );
    auto d = std::localtime( &t );
    string ss;
    
    if(d->tm_sec <=9){
        ss = "0" + to_string(d->tm_sec);
        return ss;
        }else{
            return to_string(d->tm_sec);
        }
        
    
    //return int( d->tm_hour * 3600 + d->tm_min * 60 + d->tm_sec );
}

CINDER_APP( digitalClockApp, RendererGl )


