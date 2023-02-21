//
//  main.c
//  AvP-iOS
//
//  Created by Laurence Trippen on 21.02.23.
//

#include <stdbool.h>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "SDL.h"

int HandleAppEvents(void *userdata, SDL_Event *event)
{
  switch (event->type)
  {
  case SDL_APP_TERMINATING:
    /* Terminate the app.
       Shut everything down before returning from this function.
    */
    return 0;
  case SDL_APP_LOWMEMORY:
    /* You will get this when your app is paused and iOS wants more memory.
       Release as much memory as possible.
    */
    return 0;
  case SDL_APP_WILLENTERBACKGROUND:
      /* Prepare your app to go into the background.  Stop loops, etc.
         This gets called when the user hits the home button, or gets a call.
      */
      return 0;
  case SDL_APP_DIDENTERBACKGROUND:
    /* This will get called if the user accepted whatever sent your app to the background.
       If the user got a phone call and canceled it, you'll instead get an SDL_APP_DIDENTERFOREGROUND event and restart your loops.
       When you get this, you have 5 seconds to save all your state or the app will be terminated.
       Your app is NOT active at this point.
    */
    return 0;
  case SDL_APP_WILLENTERFOREGROUND:
    /* This call happens when your app is coming back to the foreground.
       Restore all your state here.
    */
    return 0;
  case SDL_APP_DIDENTERFOREGROUND:
    /* Restart your loops here.
       Your app is interactive and getting CPU again.
    */
    return 0;
  default:
    /* No special processing, add it to the event queue */
    return 1;
  }
}

void iosRenderCallback(void* window)
{
  // Render
  glClearColor(255.0f, 255.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  SDL_GL_SwapWindow((SDL_Window*)window);
}

int main(int argc, char *argv[])
{
  // Register handler for iOS Lifecycle hooks
  SDL_SetEventFilter(HandleAppEvents, NULL);
  
  // Init SDL Subsystems
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    SDL_Log("Couldn't initialize SDL Video!\n");
  }
  
  SDL_DisplayMode displayMode;
  SDL_GetDesktopDisplayMode(0, &displayMode);
  
  SDL_Window* window = SDL_CreateWindow(NULL, 0, 0, displayMode.w, displayMode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);
  if (!window)
  {
    SDL_Log("Couldn't initialize SDL Window!\n");
  }
  
  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  
  SDL_iPhoneSetAnimationCallback(window, 1, iosRenderCallback, window);
  
  // Game Loop
  SDL_Event event;
  bool done = false;
  
  while (!done)
  {
    SDL_PumpEvents();
    
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          done = true;
          break;
      }
    }
  }
  
  // Cleanup
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}
