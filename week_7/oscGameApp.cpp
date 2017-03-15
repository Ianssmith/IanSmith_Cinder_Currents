#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/System.h"
#include "OscSender.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class oscGameApp : public App {
public:
    
    int 		mMouseLocX;
    osc::Sender sender;
    //std::string host;
    //int 		port;

    void setup();
    void update();
    void draw();
    void mouseMove( MouseEvent event );
    void mouseDrag( MouseEvent event );
    
    //osc::SenderTcp sender;
    float 		positionX;
    //const std::string host = "";
    std::string host;
    const uint16_t port = 3000;
    //int 		port;
    
    //void onSendError( asio::error_code error );
    bool mIsConnected;
    
    //// game functions v
    void setAnswer();
    void activatePlayer();
    void recieveChar();
    void compareChar(char);
    void compareAnswers();
    void checkDead();
    void makeMessage(osc::Message);
    
    //// game vars v
        //answer chosen by judger
    string answer;
        //player turn tracker
    int player = 0;
    const int maxGuesses = 9;
    int bodypart = 0;
        //letter guessed by player n
    char letter;
        //vector of boolean values to keep track of correct letters and if game is over
    std::vector<bool> playerstatus;
        //char to return to players if guess is incorrect
    char wrongLetter;
        //boolean flag for if the guess is correct
    bool correct;
        //boolean flag for if game is over
    bool GO = 0;
        //boolean flag for players win or lose
    bool win = 0;
        //introductory text for judger
    const std::string intro = "Judgment day, pick a word for the defendant: ";
    int numPlayers = 0;
    
};

void oscGameApp::setAnswer()
{
    answer = "test";
    //answer = inputBox.getInput();     place where judger word is received
    for(int i=0;i<answer.size();i++)
    {//create a vector equal to the length of the answer and store a 'false' in each space
        playerstatus.push_back(0);
    }
    while(numPlayers < 2)
    {
        numPlayers++;
        //app.onPlayerJoin(sendmsg());    place where we wait for and detect new players
    }
}


void oscGameApp::activatePlayer()
{
    player += 1;
    if (player > numPlayers)
    {//adds 1 to player number each time until it equals total players then reset to first player
        player = 1;
    }
}

void oscGameApp::recieveChar()
{
    letter = 't';
    //letter = app.getMessage[0];   place where we get the char guessed by players
}

void oscGameApp::compareChar(char guess)
{
    correct = 0;
    for(int i=0;i<answer.size();i++)
    {//loop through the answer and compare the guessed char to each one
        if(answer[i] == guess)
        {//if they match change the corresponding vector boolean to 'true'
            playerstatus[i] = 1;
            //and set correct flag to 'true'
            correct = 1;
        }
    }
}

void oscGameApp::compareAnswers()
{
    if(std::all_of(playerstatus.begin(), playerstatus.end(), [](int i){return i==0;}))
    {//check the status array for the presence of a false
        GO = 0;
    }
    else
    {//if all elements are true gane over and players win
        GO = 1;
        win = 1;
    }
}
       
   void oscGameApp::checkDead()
   {
       if(bodypart == maxGuesses)
       {//if players have all body parts gome over and players lose
           GO = 1;
           compareAnswers();
       }
   }
       
       void oscGameApp::makeMessage(osc::Message msg)
    {//run through the above functions appending the generated values to a message for players
       activatePlayer();
       msg.addIntArg(player);
       recieveChar();
       compareChar(letter);
       msg.addIntArg(correct);
        for(int i=0;i<playerstatus.size();i++)
        {
            msg.addIntArg(playerstatus[i]);
        }
       if(correct == 0)
       {
           bodypart += 1;
           msg.addIntArg(bodypart);
       }
       compareAnswers();
       msg.addIntArg(GO);
       if(GO == 1)
       {
           msg.addIntArg(win);
       }
   }
       
////gamecode ^^^
       
////osc example code vvv

void oscGameApp::setup()
{
    
                   
    mMouseLocX = getWindowCenter().x;
    //port = 3000;
    
    // assume the broadcast address is this machine's IP address but with 255 as the final value
    // so to multicast from IP 192.168.1.100, the host should be 192.168.1.255
    //

    host = System::getIpAddress();
    if( host.rfind( '.' ) != string::npos )
        host.replace( host.rfind( '.' ) + 1, 3, "255" );
    sender.setup( host, port, 1 );
}

void oscGameApp::update()
{
    float freq = mMouseLocX / (float)getWindowWidth() * 10.0f;
    positionX = cos(freq * getElapsedSeconds()) / 2.0f + .5f;
    
    osc::Message message;
    message.setAddress("/cinder/osc/1");
    message.addFloatArg(positionX);
    makeMessage(message);
    cout<<&message<<endl;
    sender.sendMessage(message);
}

void oscGameApp::mouseMove( MouseEvent event )
{
    mMouseLocX = event.getX();
}

void oscGameApp::mouseDrag( MouseEvent event )
{
    mouseMove(event);
}

void oscGameApp::draw()
{
    gl::clear();
    gl::drawString(intro, vec2(getWindowHeight(),getWindowWidth()),Color(1.0,0.0,0.0));
    setAnswer();
    //gl::color( Color::gray( 0.5f ) );
    //gl::drawSolidRect(Rectf(vec2(0), vec2(positionX * getWindowWidth(), getWindowHeight())));
}

CINDER_APP( oscGameApp, RendererGl )
