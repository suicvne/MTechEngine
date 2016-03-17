#include "TitleScreen.h"
#include "global_vars.h"
#include "SoundMixer.h"
#include "MessageBox.h"
#include "ScreenManager.h"

#include <SDL.h>

#include "LevelObject.h"

#include "enginestaticvariables.h"

TitleScreen::TitleScreen()
{
//    _cm = ___cm;
    this->menuOptions.push_back(new Menu("load test world", 295, 310)); //350 is good for bottom option
    this->menuOptions.push_back(new Menu("exit", 295, 340));

    totalOptions = menuOptions.size();
    currentSelection = 0;

    testMessage = new MessageBox("Hey look,\n\nMessage boxes work!");
    showTestMessage = false;

    if(titleLevelExists())
    {
        std::cout << "loading title screen level.." << std::endl;
        loadTitleLevel();
    }
}

void TitleScreen::loadTitleLevel()
{
    LevelObject::LevelSettings st;
    st.debug = false;
    st.width = 800;
    st.height = 600; //kek
    this->levelObject = new LevelObject(st);
}

#include <sys/stat.h> //yeet
bool TitleScreen::titleLevelExists()
{
    struct stat buffer;
    std::string filename = EngineStaticVariables::GetResourcesPath() + "/title.slvl";
    std::cout << "checking for " << filename << std::endl;
    return (stat(filename.c_str(), &buffer) == 0);
}

TitleScreen::~TitleScreen()
{
    delete testMessage;
    for(size_t i = 0; i < menuOptions.size(); i++)
    {
        delete menuOptions[i];
    }
    this->menuOptions.clear();

    delete levelObject;
}

void TitleScreen::draw(SpriteBatch *_sb, ContentManager* cm)
{
    _sb->sbBegin();

    if(levelObject == nullptr) //no level
    {
        drawOldTitleScreen(_sb, cm);
    }
    else
    {
        if(!hasRead)
        {
            //levelObject->loadLevelFile(EngineStaticVariables::GetResourcesPath() + "/title.slvl");
            hasRead = true;
        }
        levelObject->draw(_sb, cm, true); //not gonna bother updating for stylistic reasons :)
    }
    //always draw these
        SDL_Color black{0,0,0,255};
        SDL_Rect boxArea;
        boxArea.w = 300;
        boxArea.h = 100;
        boxArea.x = ((EngineStaticVariables::InternalWidth / 2) - (boxArea.w / 2));
        boxArea.y = ((EngineStaticVariables::InternalHeight / 2) - (boxArea.h / 2)) + 40;

        _sb->sbFillRect(&black, &boxArea);

        drawOptions(_sb, cm);

        drawTitleCopyrightEtc(_sb, cm);
        testMessage->draw(_sb);

    _sb->sbEnd();
}

//backup title screen
void TitleScreen::drawOldTitleScreen(SpriteBatch *_sb, ContentManager *cm)
{
    SDL_Color backgroundBlue {192, 248, 248, 255};
    _sb->sbFillScreen(&backgroundBlue);

    SDL_Texture *bgTex = cm->getTexture("bg_index");
    SDL_Rect texArea {5, 18, 255, 223};
    _sb->sbDrawTextureAreaScaledConstant(bgTex, 0, 0, texArea, 2.0f);
    _sb->sbDrawTextureAreaScaledConstant(bgTex, 255*2, 0, texArea, 2.0f);
    texArea.x = 21;
    texArea.y = 668;
    texArea.w = 128;
    texArea.h = 42;
    _sb->sbDrawTextureAreaScaledConstant(bgTex, -(texArea.w), EngineStaticVariables::InternalHeight - texArea.h * 2, texArea, 2.0f);
    _sb->sbDrawTextureAreaScaledConstant(bgTex, 0, EngineStaticVariables::InternalHeight - texArea.h * 2, texArea, 2.0f);
    _sb->sbDrawTextureAreaScaledConstant(bgTex, texArea.w * 1, EngineStaticVariables::InternalHeight - texArea.h * 2, texArea, 2.0f);
    _sb->sbDrawTextureAreaScaledConstant(bgTex, texArea.w * 2, EngineStaticVariables::InternalHeight - texArea.h * 2, texArea, 2.0f);
    _sb->sbDrawTextureAreaScaledConstant(bgTex, texArea.w * 3, EngineStaticVariables::InternalHeight - texArea.h * 2, texArea, 2.0f);
    _sb->sbDrawTextureAreaScaledConstant(bgTex, texArea.w * 4, EngineStaticVariables::InternalHeight - texArea.h * 2, texArea, 2.0f);
    _sb->sbDrawTextureAreaScaledConstant(bgTex, texArea.w * 5, EngineStaticVariables::InternalHeight - texArea.h * 2, texArea, 2.0f);

}

void TitleScreen::drawOptions(SpriteBatch *_sb, ContentManager* cm)
{
    SDL_Color white{255,255,255,255};
    for(int i = 0; i < menuOptions.size(); i++)
    {
        _sb->sbDrawFont(menuOptions[i]->getText(), menuOptions[i]->getX(), menuOptions[i]->getY(), white, 2.0f, false);
        if(i == currentSelection)
        {
            _sb->sbDrawTextureScaledConstant(cm->getTexture("selection"), menuOptions[i]->getX() - 28, menuOptions[i]->getY(), 2.0f);
        }
    }
}

void TitleScreen::processInput(SDL_Event const &_ih)
{
}

void TitleScreen::update(SDL_Event const &_ih)
{
    //THIS
    //THIS IS HOW YOU DO MENU INPUT
    if(_ih.type == SDL_KEYDOWN)
    {
        switch(_ih.key.keysym.sym)
        {
        case SDLK_UP:
            if(!upPressed)
            {
                currentSelection++;
                if(currentSelection > totalOptions-1)
                    currentSelection = 0;
                upPressed = true;
                EngineStaticVariables::MainSoundMixer->playSoundEffect(1);
            }
            break;
        case SDLK_DOWN:
            if(!downPressed)
            {
                currentSelection--;
                if(currentSelection < 0 )
                    currentSelection = (menuOptions.size() - 1);
                downPressed = true;
                EngineStaticVariables::MainSoundMixer->playSoundEffect(1);
            }
            break;
        case SDLK_m: //music test
            if(EngineStaticVariables::MainSoundMixer->getCurrentPlaying() == true)
            {
                EngineStaticVariables::MainSoundMixer->stopTestSong();
            }
            else
            {
                EngineStaticVariables::MainSoundMixer->playTestMusic(true);
            }
            break;
        case SDLK_RETURN:
        case SDLK_z:
            EngineStaticVariables::MainSoundMixer->playSoundEffect(2);
            if(currentSelection == 0)
                EngineStaticVariables::MainScreenManager->pushScreen(ScreenManager::TESTLEVEL); //TESTSCREEN
            else if(currentSelection == 1)
                EngineStaticVariables::DoQuit = true;
            break;
        case SDLK_o:
            testMessage->setVisible(!testMessage->getVisibility());
            break;
        }
    }
    else if(_ih.type == SDL_KEYUP)
    {
        switch(_ih.key.keysym.sym)
        {
        case SDLK_UP:
            upPressed = false;
            break;
        case SDLK_DOWN:
            downPressed = false;
            break;
        }
    }
}

void TitleScreen::drawTitleCopyrightEtc(SpriteBatch *_sb, ContentManager* cm)
{
    SDL_Color white {255, 255, 255, 255};
    int wLogo, hLogo;
    SDL_QueryTexture(cm->getTexture("sdlbroslogo"), NULL, NULL, &wLogo, &hLogo);

    _sb->sbDrawTextureScaledConstant(cm->getTexture("sdlbroslogo"), ((EngineStaticVariables::InternalWidth / 2) - ((wLogo*2) / 2)), 40, 2.0f);

    //_sb->sbDrawFont("SDL Brothers X", ((__internal_width / 2) - (x / 2)), 40, white, 3.0f, true);
    _sb->sbDrawFont("Press O to test message boxes!", 2, EngineStaticVariables::InternalHeight - 48, white, 2.0f, false);
    _sb->sbDrawFont("Pre Alpha Build", 2, 600-24, white, 2.0f, false);
}
