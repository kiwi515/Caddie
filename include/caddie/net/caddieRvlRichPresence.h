#ifndef CADDIE_NET_RVL_RICH_PRESENCE_H
#define CADDIE_NET_RVL_RICH_PRESENCE_H
#include "caddieIRichPresence.h"
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Rich presence implementation for Wii console
 */
class RvlRichPresence : public IRichPresence {
public:
    RvlRichPresence(const char* client);
    virtual ~RvlRichPresence();

    virtual bool IsConnected() const;
    virtual u64 GetTimeNow() const;

    virtual void UpdateClient() const;
    virtual void UpdatePresence() const;

private:
};

} // namespace caddie

#endif
