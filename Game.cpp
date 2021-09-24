#include "Game.h"
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
  
  //animate.bmp
  SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/animate.bmp");
  m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
  SDL_FreeSurface(pTempSurface);

  m_sourceRectangle.w = 128;
  m_sourceRectangle.h = 82;

  m_destinationRectangle.w = m_sourceRectangle.w;
  m_destinationRectangle.h = m_sourceRectangle.h;

  m_sourceRectangle.x = 0;
  m_sourceRectangle.y = 0;
  m_destinationRectangle.x = 0;
  m_destinationRectangle.y = 50; 

  m_flip = SDL_FLIP_NONE;
  m_moveSpeed = 10;

  //mario.bmp
  pTempSurface = SDL_LoadBMP("Assets/mario.bmp");
  m_pMario = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
  SDL_FreeSurface(pTempSurface);

  SDL_QueryTexture(m_pMario, NULL, NULL, &m_sRectMario.w, &m_sRectMario.h);

  m_dRectMario.w = 200;
  m_dRectMario.h = 200;

  m_sRectMario.x = m_sRectMario.y = 0;
  m_dRectMario.x = 300;
  m_dRectMario.y = 150;

  m_bRunning = true;
  return true;
}

void Game::update()
{
  m_sourceRectangle.x = 128*((SDL_GetTicks()/100)%6);
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);
  SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0 , 0, m_flip);
  SDL_RenderCopy(m_pRenderer, m_pMario, &m_sRectMario, &m_dRectMario);
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
    case SDL_KEYDOWN:
    switch(event.key.keysym.sym){
      case SDLK_LEFT: //FLIP
        m_destinationRectangle.x -= m_moveSpeed;
        m_flip = SDL_FLIP_HORIZONTAL;
        break;
      case SDLK_RIGHT:
        m_destinationRectangle.x += m_moveSpeed;
        m_flip = SDL_FLIP_NONE;
        break;
    }
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
