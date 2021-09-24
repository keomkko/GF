#include "Game.h"
#include <iostream>

bool Game::init(const char *title, int xpos, int ypos,  int width, int height, int flags) 
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (m_pWindow != 0) {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      if (m_pRenderer != 0) {
        SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
      } else {
        return false; // 랜더러 생성 실패
      }

      if(m_pTexture == 0) //Texture 포인트멤버함수에 Bitmap이 로드되지 않았을 경우에만
      {
        SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/rider.bmp");
        m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        SDL_QueryTexture(m_pTexture, NULL, NULL, 
        &m_sourceRectangle.w, &m_sourceRectangle.h);

        m_destinationRectangle.w = m_sourceRectangle.w;
        m_destinationRectangle.h = m_sourceRectangle.h;

        m_sourceRectangle.x = 0;
        m_sourceRectangle.y = 0; 
        m_destinationRectangle.x = 700; //초기 위치 설정(대상 사각형)
        m_destinationRectangle.y = 480;
      } else {
      return false;
      }
    } else {
      return false; // 윈도우 생설 실패 l
    }
  } else {
    return false; // SDL 초기화 실패
  }
  
  m_bRunning = true;
  return true;
}

void Game::update()
{
  SDL_SetRenderDrawColor(m_pRenderer, 102, 204, 255, 255); //배경 색

  if(m_destinationRectangle.x > 480) //(480, 480)까지 이동
  {
    m_destinationRectangle.x--;
  }
  else if(m_destinationRectangle.x > 50 && m_destinationRectangle.y > 50) //(50, 50)까지 이동
  {
    m_destinationRectangle.x--;
    m_destinationRectangle.y--;
  }

  
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer); 
  SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
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