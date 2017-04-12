#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/DataSource.h"

#include "poScene.h"
#include "poShape.h"
#include "poTextBox.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class interfaceApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    //virtual void load( ci::DataSourceRef source );
    //char row[389];
    //string rows[11536];
    //int pos = 0;
    volatile float redB;
    volatile float greenB;
    volatile float blueB;
    
    po::scene::TextBoxRef mText;
    
    //string getI(string [],int);
    float red[10],blue[10],green[10];
    int normalize(int val, int max=500){
        //val/max = x/100
        int x = (val*100)/max;
        return x/10;
    }
    
    
    
    
    po::scene::SceneRef mScene;
    po::scene::NodeContainerRef mNodeContainer;
    po::scene::ShapeRef mBackgroundShape;
    
};

void interfaceApp::setup()
{
    //_____Initialize color arrays
    
    for(float i = 0.0, j=0; j<10; i+=0.1, j++)
        red[int(j)] = i, blue[int(j)] = i, green[int(j)] = i;
    
    //_____Create scene
                          
    //load( loadAsset( ".csv" ) );
    setWindowSize(800,600);
    mNodeContainer = po::scene::NodeContainer::create();
    mScene = po::scene::Scene::create(mNodeContainer);
    
    glm::vec2 backgroundSize = ci::app::getWindowSize();
    mBackgroundShape = po::scene::Shape::createRect(backgroundSize.x, backgroundSize.y );
    //mBackgroundShape->setFillColor(Color(0.9f,0.9f,0.9f));
    mBackgroundShape->setFillColor(Color(redB,greenB,blueB));
    mNodeContainer->addChild(mBackgroundShape);
    
    //_____Make slider buttons
        //plus
    
    po::scene::ShapeRef plusR = po::scene::Shape::createCircle(25.f);
    po::scene::ShapeRef plusG = po::scene::Shape::createCircle(25.f);
    po::scene::ShapeRef plusB = po::scene::Shape::createCircle(25.f);
    
    plusR->setPosition(70,40)
        .setFillColor(Color(0.9f,0.9f,0.9f))
        .setAlignment(po::scene::Alignment::CENTER_CENTER);
    plusG->setPosition(70,80)
        .setFillColor(Color(0.9f,0.9f,0.9f))
        .setAlignment(po::scene::Alignment::CENTER_CENTER);
    plusB->setPosition(70,120)
        .setFillColor(Color(0.9f,0.9f,0.9f))
        .setAlignment(po::scene::Alignment::CENTER_CENTER);
        
    mNodeContainer->addChild(plusR);
    mNodeContainer->addChild(plusG);
    mNodeContainer->addChild(plusB);
        //minus
    
    po::scene::ShapeRef minusR = po::scene::Shape::createCircle(25.f);
    po::scene::ShapeRef minusG = po::scene::Shape::createCircle(25.f);
    po::scene::ShapeRef minusB = po::scene::Shape::createCircle(25.f);
    
    minusR->setPosition(530,40)
        .setFillColor(Color(0.9f,0.9f,0.9f))
        .setAlignment(po::scene::Alignment::CENTER_CENTER);
    minusG->setPosition(530,80)
        .setFillColor(Color(0.9f,0.9f,0.9f))
        .setAlignment(po::scene::Alignment::CENTER_CENTER);
    minusB->setPosition(530,120)
        .setFillColor(Color(0.9f,0.9f,0.9f))
        .setAlignment(po::scene::Alignment::CENTER_CENTER);
        
    mNodeContainer->addChild(minusR);
    mNodeContainer->addChild(minusG);
    mNodeContainer->addChild(minusB);
    
    //_____Make slider dashes
    
    for(int i=140; i<500; i+=40){
        
    po::scene::ShapeRef rectR = po::scene::Shape::createRect(2.f, 15.f);
    po::scene::ShapeRef rectG = po::scene::Shape::createRect(2.f, 15.f);
    po::scene::ShapeRef rectB = po::scene::Shape::createRect(2.f, 15.f);
    
    rectR->setPosition(i,40);
    rectG->setPosition(i,80);
    rectB->setPosition(i,120);
        
    mNodeContainer->addChild(rectR);
    mNodeContainer->addChild(rectG);
    mNodeContainer->addChild(rectB);
    
    ci::TextBox ciText;
    ciText.setText(std::to_string(normalize(i)-1));
    
    mText = po::scene::TextBox::create(ciText);
    mText->setAlignment(po::scene::Alignment::CENTER_CENTER)
        .setPosition(i,32);
    mNodeContainer->addChild(mText);
        
    mText = po::scene::TextBox::create(ciText);
    mText->setAlignment(po::scene::Alignment::CENTER_CENTER)
        .setPosition(i,72);
    mNodeContainer->addChild(mText);
        
    mText = po::scene::TextBox::create(ciText);
    mText->setAlignment(po::scene::Alignment::CENTER_CENTER)
        .setPosition(i,112);
    mNodeContainer->addChild(mText);
        
    }
    
    //_____Make slider line
    
    po::scene::ShapeRef lineR = po::scene::Shape::createRect(400.f, 2.f);
    po::scene::ShapeRef lineG = po::scene::Shape::createRect(400.f, 2.f);
    po::scene::ShapeRef lineB = po::scene::Shape::createRect(400.f, 2.f);
    
    lineR->setPosition(100,40);
    lineG->setPosition(100,80);
    lineB->setPosition(100,120);
    
    mNodeContainer->addChild(lineR);
    mNodeContainer->addChild(lineG);
    mNodeContainer->addChild(lineB);
    
    //_____Make slider knob
    
    po::scene::ShapeRef nobR = po::scene::Shape::createRect(5,15);
    po::scene::ShapeRef nobG = po::scene::Shape::createRect(5,15);
    po::scene::ShapeRef nobB = po::scene::Shape::createRect(5,15);
    
    nobR->setPosition(100,40)
        .setFillColor(Color(1.0f,0.0f,0.0f))
        .setAlignment(po::scene::Alignment::CENTER_CENTER);
    nobG->setPosition(100,80)
        .setAlignment(po::scene::Alignment::CENTER_CENTER)
        .setFillColor(Color(0.0f,1.0f,0.0f));
    nobB->setPosition(100,120)
        .setAlignment(po::scene::Alignment::CENTER_CENTER)
        .setFillColor(Color(0.0f,0.0f,1.0f));
    
    mNodeContainer->addChild(nobR);
    mNodeContainer->addChild(nobG);
    mNodeContainer->addChild(nobB);
    
    //_____pass knob position to background color variables
    
    redB = red[normalize(nobR->getPosition().x)];
    greenB = green[normalize(nobG->getPosition().x)];
    blueB = blue[normalize(nobR->getPosition().x)];
    
    
    //ci::app::timeline().apply(&nobR->getPositionAnim(), ci::Vec2f(50.0f, 50.0f), 1.0f);
 
    
    
}



void interfaceApp::mouseDown( MouseEvent event )
{
}

void interfaceApp::update()
{
    mScene->update();
}

void interfaceApp::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    mScene->draw();
}


CINDER_APP( interfaceApp, RendererGl(RendererGl::Options().msaa( 8 )) )


//string getI(string data[], int index){
    //return data[index];
//}

/*
void interfaceApp::load( DataSourceRef source )
{
    ;
    //std::string data = loadString( source );
}
 */

    /*
    ifstream inputfile;
    inputfile.open("eeg.csv", ios::in);
    while(!inputfile.eof()){
        inputfile.getline(row,390);
        rows[pos] = row;
        pos++;
    }
    cout<<getI(rows,0)<<endl;
     */
