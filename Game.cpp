#include "Game.h"
#include "TextureManager.h"
#include <iostream>

bool Game::init(const char *title, int xpos, int ypos,  int width, int height, int flags) 
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (m_pWindow != 0) {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      if (m_pRenderer != 0) {
        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
      } else {
        return false; // 랜더러 생성 실패
      }
    } else {
      return false; // 윈도우 생설 실패 l
    }
  } else {
    return false; // SDL 초기화 실패
  }
  
  //animate.png
  if( !TheTextureManager::Instance()->load("Assets/animate-alpha.png", "animate", m_pRenderer))
  {
    return false;
  }

  //helicopter.png
  if( !TheTextureManager::Instance()->load("Assets/helicopter.png", "helicopter", m_pRenderer))
  {
    return false;
  }

  m_bRunning = true;
  return true;
}

void Game::update()
{
  m_currentFrame = ((SDL_GetTicks() / 100 ) % 6);
  m_helicopterFrame = ((SDL_GetTicks() / 100) % 5);
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);
  TheTextureManager::Instance()->drawFrame("helicopter", 200, 200, 128, 82, 0, m_helicopterFrame, m_pRenderer, SDL_FLIP_HORIZONTAL);
  TheTextureManager::Instance()->drawFrame("animate", 100, 100, 128, 82, 0, m_currentFrame, m_pRenderer);
  SDL_RenderPresent(m_pRenderer);
  SDL_Delay(10);
}

bool Game::running()
{ 
   return m_bRunning; 
}

void Game::handleEvents() 
{
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      m_bRunning = false;
      break;
    // case SDL_KEYDOWN:
    // switch(event.key.keysym.sym){
    //   case SDLK_LEFT: //FLIP
    //     m_destinationRectangle.x -= m_moveSpeed;
    //     m_flip = SDL_FLIP_HORIZONTAL;
    //     break;
    //   case SDLK_RIGHT:
    //     m_destinationRectangle.x += m_moveSpeed;
    //     m_flip = SDL_FLIP_NONE;
    //     break;
    // }
    default:
      break;
    }
  }
}

void Game::clean() 
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}
