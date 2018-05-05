#include "../include/ClearSrc.h"

void clear_screen()
{
#ifdef WINDOWS
    std::system("cls"); ///\brief si on est est sur windows
#else
    std::system ("clear");///\brief si on est sur un autre systéme d'exploitation
#endif
}

void setSleep(int s){
  #ifdef WINDOWS
      Sleep(s*1000); ///\brief si on est est sur windows
  #else

      std::this_thread::sleep_for(std::chrono::milliseconds(s*10));
      //sleep(s);///\brief si on est sur un autre systéme d'exploitation
  #endif
}
