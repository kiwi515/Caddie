#ifndef RP_SYSTEM_FONT_MANAGER_H
#define RP_SYSTEM_FONT_MANAGER_H
#include "types_caddie.hpp"

#include <nw4r/ut.h>

/**
 * @brief RP engine font manager
 * @details Responsible for loading and setting up the rom font and any res
 * fonts needed (Whether specific fonts are used is determined at compile time)
 * @wfuname
 */
class RPSysFontManager {
public:
    enum EResFont {
        ResFont_Auto,
        ResFont_WS2_nRodB_32_IA4,
        ResFont_WS2_nRodEb_60_IA4,

        ResFont_Max
    };

public:
    static RPSysFontManager* CreateInstance();

    static RPSysFontManager& GetInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    void LoadRomFont();
    void LoadResFonts();

    void* GetResFontData(const char* name) const;

    nw4r::ut::RomFont& GetRomFont() const { return *mRomFont; }

private:
    RPSysFontManager();
    virtual ~RPSysFontManager();

private:
    //! @brief Deserialized rom font
    nw4r::ut::RomFont* mRomFont; // at 0x4
    //! @brief Deserialized res fonts
    nw4r::ut::ResFont* mResFonts[ResFont_Max]; // at 0x8
    //! @brief Serialized res fonts
    void* mResFontData[ResFont_Max]; // at 0x24

    static RPSysFontManager* sInstance;
};

#endif
