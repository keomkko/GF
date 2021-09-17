#include <SDL.h>
#include <cstdlib>
#include <ctime>

//Update 함수에서 RGB값을 각각 0 또는 255의 값으로 랜덤으로 정하고 render 함수에서 변경된 화면을 갱신하고 5번의 루프를 실행한뒤 종료한다.

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
bool g_bRunning = false; //초기화 제대로 동작했는지 확인하고 게임 루프를 빠져나오게 하는 역할이다.

bool init(const char* title, int xpos, int ypos, 
          int height, int width, int flags);

void Update(int &_rep);

void render();

int main(int argc, char* argv[])
{
    if (init("Hello_SDL", 
              SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED, 
              720, 480,
              SDL_WINDOW_BORDERLESS))
    {
        g_bRunning = true;
    }
    else
    {
        return 1; // something's wrong
    }

    srand((unsigned int)time(NULL)); //난수 생성
    int rep = 0; //반복횟수

    while (g_bRunning)
    {
        Update(rep);
        render();
        SDL_Delay(1000); //1초 지연
    }

    SDL_Quit();
    return 0;
}

bool init(const char* title, int xpos, int ypos, 
          int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {

        g_pWindow = SDL_CreateWindow( title, 
                                      xpos, ypos, 
                                      height, width, flags);

        if (g_pWindow != 0)
        {
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
        }

    }
    else
    {
        return false;
    }

    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

    return true;
}

void Update(int &_rep)
{
  SDL_SetRenderDrawColor(g_pRenderer, (rand()%2)*255, (rand()%2)*255, (rand()%2)*255, 255);
  _rep++;

  if(_rep > 5)
  {
    g_bRunning = false;
  }
}

void render()
{
    SDL_RenderClear(g_pRenderer);
    SDL_RenderPresent(g_pRenderer);
}