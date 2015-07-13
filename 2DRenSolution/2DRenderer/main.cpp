#include <SDL/SDL.h>
#include <gl/glew.h>
#include <SDL/SDL_opengl.h>
#include <gl/GLU.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "ResourceManager.h"
#include "SpriteRenderer.h"

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;

const int SCREEN_WIDTH = 1200, SCREEN_HEIGHT = 900;

using namespace std;

bool InitGL();

void MainLoop();

void Update();

void Render(SpriteRenderer& ren);

void Close();

bool Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL initialization error: " << SDL_GetError() << endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    gWindow = SDL_CreateWindow("SimmeGL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );

    if(gWindow == NULL)
    {
        cout << "Window creation error: " << SDL_GetError() << endl;
        return false;
    }

    gContext = SDL_GL_CreateContext(gWindow);
    if(gContext == NULL)
    {
        cout << "OpenGL context creation error: " << SDL_GetError() << endl;
        return false;
    }

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if(glewError != GLEW_OK)
    {
        cout << "GLEW initialization error: " << glewGetErrorString(glewError) << endl;
    }

    //Enable vsync
    if(SDL_GL_SetSwapInterval(1) < 0)
    {
        cout << "Unable to set VSync : " << SDL_GetError() << endl;
    }

    if( !InitGL() )
    {
        cout << "Unable to initialize OpenGL" << endl;
        return false;
    }
    return true;
}

bool InitGL()
{
    glClearColor(0.4f, .2f, .4f, 1.0f);
    return true;
}

void MainLoop()
{
    SDL_Event currentEvent;
    bool run = true;

    ResourceManager::SetShaderFolderPath("Shaders/");
    ResourceManager::LoadShader("spriteVs.glsl", "spriteFs.glsl", "SpriteShader");

    SpriteRenderer ren(ResourceManager::GetShader("SpriteShader"));
    ren.SetProjectionMatrix(glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f));
    

    while(run)
    {
        while(SDL_PollEvent(&currentEvent) != 0)
        {
            if(currentEvent.type == SDL_QUIT)
            {
                run = false;
            }
        }
        Update();
        Render(ren);
    }
}

void Update()
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    if(keyState[SDL_SCANCODE_ESCAPE])
    {
        SDL_Event quitEvent;
        quitEvent.type = SDL_QUIT;
        SDL_PushEvent(&quitEvent);
    }
}

void Render(SpriteRenderer& ren)
{
    glClear(GL_COLOR_BUFFER_BIT);
    ren.DrawSprite(glm::vec2(40.0,40.0), glm::vec2(30,30));
    SDL_GL_SwapWindow(gWindow);
}

void Close()
{
    SDL_GL_DeleteContext(gContext);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if(!Init())
    {
        cout << "Initialization failed." << endl; 
        return -1;
    }
    MainLoop();
    Close();
    return 0;
}