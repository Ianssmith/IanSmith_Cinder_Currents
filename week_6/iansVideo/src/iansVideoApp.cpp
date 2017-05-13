#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/app/RendererGl.h"

#include "poScene.h"
#include "iansVideo.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace po::scene;

class iansVideoApp
: public App
{
public:
    void setup();
    void update();
    void draw();
    
    SceneRef scene;
};

void iansVideoApp::setup()
{
    setWindowSize(1024, 768);
    scene = Scene::create(iansVideo::create());
}

void iansVideoApp::update()
{
    scene->update();
}

void iansVideoApp::draw()
{
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) );
    scene->draw();
}

CINDER_APP( iansVideoApp, RendererGl )
