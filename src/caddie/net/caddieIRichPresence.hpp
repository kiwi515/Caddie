#ifndef CADDIE_NET_I_RICH_PRESENCE_H
#define CADDIE_NET_I_RICH_PRESENCE_H
#include "types_caddie.hpp"

#include <revolution/OS.h>

namespace caddie {

/**
 * @brief Rich presence interface (common functionality between console/emu)
 */
class IRichPresence {
public:
    IRichPresence(const char* client)
        : mClient(client),
          mDetails(""),
          mState(L""),
          mLargeImageKey(""),
          mLargeImageText(""),
          mSmallImageKey(""),
          mSmallImageText(""),
          mStartTime(0),
          mEndTime(0),
          mPartyNum(0),
          mPartyMax(0) {}
    virtual ~IRichPresence() {}

    virtual bool IsConnected() const = 0;
    virtual u64 GetTimeNow() const = 0;

    virtual void UpdateClient() const = 0;
    virtual void UpdatePresence() const = 0;

    void SetDetails(const char* details) { mDetails = details; }
    void SetState(const wchar_t* state) { mState = state; }

    void SetLargeImageKey(const char* key) { mLargeImageKey = key; }
    void SetLargeImageText(const char* text) { mLargeImageText = text; }

    void SetSmallImageKey(const char* key) { mSmallImageKey = key; }
    void SetSmallImageText(const char* text) { mSmallImageText = text; }

    void SetStartTime(u64 start) { mStartTime = start; }
    void SetStartTimeNow() { mStartTime = GetTimeNow(); }

    void SetPartyNum(int num) { mPartyNum = num; }
    void SetPartyMax(int max) { mPartyNum = max; }

protected:
    // Client ID
    const char* mClient;

    // Presence info
    const char* mDetails;
    const wchar_t* mState;

    // Large image
    const char* mLargeImageKey;
    const char* mLargeImageText;

    // Small image
    const char* mSmallImageKey;
    const char* mSmallImageText;

    // Gameplay timestamps
    u64 mStartTime;
    u64 mEndTime;

    // Party size
    int mPartyNum;
    int mPartyMax;
};

} // namespace caddie

#endif
