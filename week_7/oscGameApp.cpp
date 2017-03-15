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
    
    string answer;      //answer chosen by judger
    int player = 0;     //player turn tracker
    const int maxGuesses = 9;
    int bodypart = 0;
    char letter;        //letter guessed by player n
    std::vector<bool> playerstatus;     //vector of boolean values to keep track of correct letters and if game is over
    string rLetter;       //char to return to players if guess is incorrect(probably could just recycle the 'letter' variable
    bool correct;       //boolean flag for if the guess is correct
    bool GO = 0;        //boolean flag for if game is over
    bool win = 0;       //boolean flag for players win or lose
    const std::string intro = "Judgment day, pick a word for the defendant: ";      //introductory text for judger
    int numPlayers = 0;
    
};

////create a vector equal to the length of the answer and store a 'false' in each space
void oscGameApp::setAnswer()
{
    answer = "test";
    //answer = inputBox.getInput();     place where judger word is received
    for(int i=0;i<answer.size();i++)
    {
        playerstatus.push_back(0);
    }
    while(numPlayers < 2)
    {
        numPlayers++;
        //app.onPlayerJoin(sendmsg());    place where we wait for and detect new players
    }
}

////adds 1 to player number each time until it equals total players then reset to first player
void oscGameApp::activatePlayer()
{
    player += 1;
    if (player > numPlayers)
    {
        player = 1;
    }
}


////place where we get the char guessed by players
void oscGameApp::recieveChar()
{
    letter = 't';
    //letter = app.getMessage[0];
}


////loop through the answer and compare the guessed char to each one
////if they match change the corresponding vector boolean to 'true'
////and set correct flag
void oscGameApp::compareChar(char guess)
{
    correct = 0;
    for(std::string::size_type i=0;i<answer.size();i++)
    {
        if(answer[i] == guess)
        {
            playerstatus[i] = 1;
            correct = 1;
        }
    }
    rLetter = letter;
}


////check the status array for the presence of a false
////if all elements are true game over and players win
void oscGameApp::compareAnswers()
{
    if(std::all_of(playerstatus.begin(), playerstatus.end(), [](int i){return i==0;}))
    {
        GO = 0;
    }
    else
    {
        GO = 1;
        win = 1;
    }
}


////if players have all body parts gome over and players lose
   void oscGameApp::checkDead()
   {
       if(bodypart == maxGuesses)
       {
           GO = 1;
           compareAnswers();
       }
   }


////run through the above functions appending the generated values to a message for players
       void oscGameApp::makeMessage(osc::Message msg)
    {
       activatePlayer();
       msg.addIntArg(player);
       recieveChar();
       compareChar(letter);
       msg.addStringArg(rLetter);
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
