#ifndef RP_SYSTEM_PAUSE_MGR_H
#define RP_SYSTEM_PAUSE_MGR_H

class RPSysPauseMgr
{
public:
    static RPSysPauseMgr* getInstance()
    {
        return sInstance;
    }

    void update();

private:
    static RPSysPauseMgr* sInstance;
};

#endif