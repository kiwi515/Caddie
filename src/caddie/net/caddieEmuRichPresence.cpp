#include "caddieEmuRichPresence.hpp"

#include <cstdlib>
#include <cstring>
#include <revolution/IPC.h>

namespace caddie {
namespace {

template <typename T>
inline void MakePrimVector(const T& prim, IPCIOVector& vec) {
    vec.base = (void*)&prim;
    vec.length = sizeof(T);
}

inline void MakeStrVector(const char* str, IPCIOVector& vec) {
    vec.base = (void*)str;
    vec.length = std::strlen(str);
}

/**
 * @brief Dolphin device IOCTL IDs
 */
enum {
    IOCTLV_RPC_SET_CLIENT = 0x07,
    IOCTLV_RPC_SET_PRESENCE = 0x08,
    IOCTLV_RPC_RESET = 0x09,
    IOCTLV_GET_SYSTEM_TIME = 0x0A,
};

} // namespace

EmuRichPresence::EmuRichPresence(const char* client)
    : IRichPresence(client), mEmuHandle(-1) {
    // Dolphin emulated device
    mEmuHandle = IOS_Open("/dev/dolphin", IPC_OPEN_NONE);
    CADDIE_WARN(!IsConnected(), "Failed to connect to Dolphin device!");
    UpdateClient();
}

EmuRichPresence::~EmuRichPresence() {
    if (mEmuHandle >= 0) {
        IOS_Close(mEmuHandle);
    }
}

/**
 * @brief Whether there is an ongoing connection with Dolphin
 */
bool EmuRichPresence::IsConnected() const { return mEmuHandle >= 0; }

/**
 * @brief Retreive the current Unix epoch time (in seconds)
 */
u64 EmuRichPresence::GetTimeNow() const {
    if (!IsConnected()) {
        CADDIE_LOG("Not connected to Dolphin device!");
        return;
    }

    // Get system time from Dolphin
    u64 time;
    IPCIOVector output[1];
    MakePrimVector(time, output[0]);

    const int result = IOS_Ioctlv(mEmuHandle, IOCTLV_GET_SYSTEM_TIME, 0,
                                  ARRAY_LENGTH(output), output);
    if (result < 0) {
        CADDIE_LOG_EX("GetTimeNow error: %d", result);
        return 0;
    }

    // Convert milliseconds to seconds
    return time / 1000;
}

/**
 * @brief Update Discord client/app ID
 */
void EmuRichPresence::UpdateClient() const {
    if (!IsConnected()) {
        CADDIE_LOG("Not connected to Dolphin device!");
        return;
    }

    IPCIOVector input[1];
    MakeStrVector(mClient, input[0]);

    const int result = IOS_Ioctlv(mEmuHandle, IOCTLV_RPC_SET_CLIENT,
                                  ARRAY_LENGTH(input), 0, input);
    if (result < 0) {
        CADDIE_LOG_EX("UpdateClient error: %d", result);
    }
}

/**
 * @brief Update Discord presence status
 */
void EmuRichPresence::UpdatePresence() const {
    if (!IsConnected()) {
        CADDIE_LOG("Not connected to Dolphin device!");
        return;
    }

    // Convert state text from UTF-16 to ANSI for Discord
    char mbstate[512];
    std::wcstombs(mbstate, mState, sizeof(mbstate));

    IPCIOVector input[10];
    // Presence info
    MakeStrVector(mDetails, input[0]);
    MakeStrVector(mbstate, input[1]);
    // Large image
    MakeStrVector(mLargeImageKey, input[2]);
    MakeStrVector(mLargeImageText, input[3]);
    // Small image
    MakeStrVector(mSmallImageKey, input[4]);
    MakeStrVector(mSmallImageText, input[5]);
    // Gameplay timestamps
    MakePrimVector(mStartTime, input[6]);
    MakePrimVector(mEndTime, input[7]);
    // Party size
    MakePrimVector(mPartyNum, input[8]);
    MakePrimVector(mPartyMax, input[9]);

    const int result = IOS_Ioctlv(mEmuHandle, IOCTLV_RPC_SET_PRESENCE,
                                  ARRAY_LENGTH(input), 0, input);
    if (result < 0) {
        CADDIE_LOG_EX("UpdatePresence error: %d", result);
    }
}

} // namespace caddie
