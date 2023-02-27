#ifndef CADDIE_NET_RICH_PRESENCE_MGR_H
#define CADDIE_NET_RICH_PRESENCE_MGR_H
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Discord rich presence (console/dolphin) manager
 */
class RichPresenceMgr {
public:
    static RichPresenceMgr& GetInstance() {
        static RichPresenceMgr instance;
        return instance;
    }

    void Configure();

private:
    RichPresenceMgr();
    virtual ~RichPresenceMgr();

private:
    IRichPresence* mRichPresence;
    Message* mMessage;

    // Caddie Discord app ID (client ID)
    static const char* scCaddieAppId;
};

} // namespace caddie

#endif
