
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class ImageUsageApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void mouseUp( MouseEvent event ) override;
	void mouseMove( MouseEvent event ) override;
	bool up = false;
	bool down = false;
	ivec2 mMousePos;


	void update() override;
	void draw() override;
    void twirl(Surface8u *surface, Area area, float maxAngle);
    void warp(Surface8u *surface, float mloc);
    
	ci::Surface8u space;


	ci::Surface8u ship;

	gl::TextureRef Gspace;
	gl::TextureRef Gship;

    float               mWidth;
    float               mHeight;
    gl::GlslProgRef     mShader;
};

void ImageUsageApp::setup()
{
    mWidth = 400.f;
    mHeight = 300.f;


    
    ci::app::setWindowSize(glm::vec2(1280.f, 720.f));
    try {
        // loadAsset will go asset folder
        // loadResources will go resource folder
        // loadImage will return image source
        space = loadImage(ci::app::loadAsset("maxres.jpg"));

        ship = loadImage(ci::app::loadAsset("tie.png"));

        mShader = gl::GlslProg::create( loadAsset( "shader.vert" ), loadAsset( "shader.frag" ) );
        
    } catch (exception& e) {
        // standard cinder method of printing stuff
        ci::app::console() << e.what() << std::endl;
    }

    ci::app::console() << space.getBounds() << std::endl;
	/*
	gl::Texture::Format fmt;
	fmt.setWrap( GL_CLAMP_TO_EDGE);
	streakTex = gl::Texture(mTexClouds ,fmt);
	*/
    
    // surface manipulations
	/*
    ci::Surface::Iter iter = mSurface.getIter(mSurface.getBounds());
    while(iter.line()){
        while(iter.pixel()){
            iter.r() = 255.f - iter.r();
            iter.g() = 255.f - iter.g();
            iter.b() = 255.f - iter.b();
        }
    }
	*/
    
    // surface manipulations (b + w)
    // please try this your self first
	/*
    ci::Surface::Iter iterBW = mSurfaceBW.getIter(mSurfaceBW.getBounds());
    while(iterBW.line()){
        while(iterBW.pixel()){
            float averageOfThisPixel = (iterBW.r() + iterBW.g() + iterBW.b()) / 3.f;
            iterBW.r() = averageOfThisPixel;
            iterBW.g() = averageOfThisPixel;
            iterBW.b() = averageOfThisPixel;
        }
    }
	*/
    
    // apply twirl to surface
    //twirl(&hspace, hspace.getBounds(), 10.f);

    
}

void ImageUsageApp::warp(Surface8u *surface, float mloc)	//ivec2 mloc)
{
	ci::Surface8u inputSurface = surface->clone();

	ci::Surface::Iter inputIter(inputSurface.getIter());
	ci::Surface::Iter outputIter(surface->getIter(getWindowBounds()));

	float radius = 150.f; 
	//float dir = mloc.y + 50; 

	while( inputIter.line() && outputIter.line() ) {
			while( inputIter.pixel() && outputIter.pixel() ) {
				// getting the current pixel position, and get the distance between it and image center
				glm::vec2 current = (glm::vec2)inputIter.getPos() - radius;
				// get length of a vec2
				float r = length(current);
				
				float twirlAngle = r / radius * mloc;
				//float twirlAngle = r / radius * dir;
				float angle = atan2(current.x, current.y);
				glm::vec2 outSample(r * cos( angle + twirlAngle  ), r * sin( angle + twirlAngle ));
				glm::vec2 out = outSample - current;
				outputIter.r() = inputIter.rClamped( out.x, out.y );
				outputIter.g() = inputIter.gClamped( out.x, out.y );
				outputIter.b() = inputIter.bClamped( out.x, out.y );
	
			}
		}
}

void ImageUsageApp::twirl(Surface8u *surface, Area area, float maxAngle)
{
    // clone the surface, or any changes make to *surface will affect directly on the variable
    ci::Surface8u inputSurface = surface->clone();
    
    ci::Surface::Iter inputIter(inputSurface.getIter());
    ci::Surface::Iter outputIter(surface->getIter(area));
    
    // get max radius. usually diagnal distance
    float maxDistance = ci::length((glm::vec2)area.getSize());
    
    glm::vec2 mid = (area.getUL() + area.getLR()) / 2;
    
    
    while( inputIter.line() && outputIter.line() ) {
        while( inputIter.pixel() && outputIter.pixel() ) {
            // getting the current pixel position, and get the distance between it and image center
            glm::vec2 current = (glm::vec2)inputIter.getPos() - mid;
            // get length of a vec2
            float r = length(current);
            
            float twirlAngle = r / maxDistance * maxAngle;
            float angle = atan2(current.x, current.y);
            glm::vec2 outSameple(r * cos( angle + twirlAngle  ), r * sin( angle + twirlAngle ));
            glm::vec2 out = outSameple - current;
            outputIter.r() = inputIter.rClamped( out.x, out.y );
            outputIter.g() = inputIter.gClamped( out.x, out.y );
            outputIter.b() = inputIter.bClamped( out.x, out.y );

        }
    }
}

Rectf ImageUsageApp::getRectf(glm::vec2 startingPoint, glm::vec2 size, glm::vec2 scale)
{
    return Rectf(startingPoint.x, startingPoint.y, (size.x + startingPoint.x) * scale.x, (size.y + startingPoint.y) * scale.y);
}

void ImageUsageApp::mouseDown( MouseEvent event )
{
    if(event.isLeft()){
		up = false;
		down = true;
	}
	/*
	else if(event.isRight()){

		gl::draw(Gspace, getWindowBounds());
		//up = true;
		//down = false;
	}
	*/
	//mouseMove( event);
}
void ImageUsageApp::mouseUp( MouseEvent event )
{
    if(event.isLeft()){
		down = false;
		up = true;
	}
}

//isn't used vvv
void ImageUsageApp::mouseMove( MouseEvent event ) 
{
	mMousePos = event.getPos();
}
// ^^^

void ImageUsageApp::update()
{
    
}

void ImageUsageApp::draw()
{

	Gspace = gl::Texture::create(space);
	gl::draw(Gspace, getWindowBounds());

	Gship = gl::Texture::create(ship);
	gl::draw(Gship, getWindowBounds());

	if(down){
		warp(&space, 10.f);		//mMousePos);
	    twirl(&space, space.getBounds(), 70.f);
	}else if(up){
	    twirl(&space, space.getBounds(), -70.f);
	}
    
}

CINDER_APP( ImageUsageApp, RendererGl )
