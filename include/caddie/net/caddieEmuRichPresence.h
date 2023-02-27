#ifndef CADDIE_NET_EMU_RICH_PRESENCE_H
#define CADDIE_NET_EMU_RICH_PRESENCE_H
#include "caddieIRichPresence.h"
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Rich presence implementation for Dolphin Emulator
 */
class EmuRichPresence : public IRichPresence {
public:
    EmuRichPresence(const char* client);
    virtual ~EmuRichPresence();

    virtual bool IsConnected() const;
    virtual u64 GetTimeNow() const;

    virtual void UpdateClient() const;
    virtual void UpdatePresence() const;

private:
    // Handle to Dolphin device
    s32 mEmuHandle;
};

} // namespace caddie

#endif
