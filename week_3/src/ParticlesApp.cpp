
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "../include/ParticleSystem.h"
#include "../include/Particle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ParticlesApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void mouseMove(MouseEvent event) override;
	void update() override;
	void draw() override;

    gl::TextureRef mTexture;

    // add particle system
	ParticleSystem mParticleSystem;
};

void ParticlesApp::setup()
{
	    try {
        // loadAsset will go asset folder
        // loadResources will go resource folder
        // loadImage will return image source
        mTexture = gl::Texture::create( loadImage( loadAsset( "stormy.jpg" ) ) );
		}catch (exception& e) {
        // standard cinder method of printing stuff
        ci::app::console() << e.what() << std::endl;
    }
    // set framerate
    ci::app::setFrameRate(60.f);
	ci::app::setWindowSize(glm::vec2(1780.f, 1220.f));
}

void ParticlesApp::mouseDown( MouseEvent event )
{
	
}

void ParticlesApp::mouseMove(MouseEvent event)
{
    // repulse from mouse position
	////mParticleSystem.repulseFrom(event.getPos());
}

void ParticlesApp::update()
{
	mParticleSystem.update();
}

void ParticlesApp::draw()
{    
    //gl::clear( ci::Color::black() );
    gl::clear( ci::Color::white() );
	gl::draw(mTexture,getWindowBounds());
    // draw particle system
	mParticleSystem.draw();    
    gl::drawString( to_string( getAverageFps() ), ci::vec2( 20.f, 20.f ), ci::Color( 0.5f, 0.5f, 0.5f ) );
}

CINDER_APP( ParticlesApp, RendererGl )

