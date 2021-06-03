#ifndef SP2_GLF_GLOBAL_ACCESSOR_H
#define SP2_GLF_GLOBAL_ACCESSOR_H
#include <types.h>

namespace Glf
{
    enum GlobalVar
    {
        VAR_GAMEMODE,
        VAR_NEXTHOLE,
        
        VAR_BLINDFLAG = 3
    };

    class GameConfig
    {
    public:
        static inline GameConfig *getInstance()
        {
            return sInstance;
        }

        int getGlobalVar(int var, bool b);
        void setGlobalVar(int var, int value, bool b);

    private:
        static GameConfig *sInstance;
    };
}

#endif