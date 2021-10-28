#ifndef RP_SYSTEM_SYS_WINDOW_MGR_H
#define RP_SYSTEM_SYS_WINDOW_MGR_H
#include "types_rp.h"
#include "types_nw4r.h"

#include "caddieAssert.h"

class RPSysSysMsgWinMgr
{
public:
    inline static RPSysSysMsgWinMgr * getInstance()
    {
        return sInstance;
    }

    UNKWORD GetWord0x14() const { return WORD_0x14; }

private:
    virtual ~RPSysSysMsgWinMgr();
    
    char UNK_0x4[0x14 - 0x4];
    UNKWORD WORD_0x14;

    static RPSysSysMsgWinMgr *sInstance;
};

#endif