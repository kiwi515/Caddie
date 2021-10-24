#ifndef RP_SYSTEM_PROJECT_LOCAL_H
#define RP_SYSTEM_PROJECT_LOCAL_H
#include "types_rp.h"
#include "types_egg.h"

class RPSysProjectLocal
{
public:
    enum eRPNumberSys
    {
        NUMSYS_0,
        NUMSYS_1,
    };

    enum eRPPack
    {
        PACK_SPORTS,
        PACK_PARTY,
        PACK_HEALTH,
        PACK_MUSIC,
        PACK_ALLPACK
    };

    enum eRPLocale
    {
        LOC_ENGLISH_GB,
        LOC_FRENCH,
        LOC_GERMAN,
        LOC_ITALIAN,
        LOC_SPANISH,
        LOC_ENGLISH_NL,
        LOC_JAPANESE,
        LOC_ENGLISH_US,
        LOC_FRENCH_US,
        LOC_SPANISH_US
    };

    eRPNumberSys getNumberSystem() const { return (eRPNumberSys)mNumberSystem; }
    eRPLocale getLocale() const { return (eRPLocale)mLocale; }
    eRPLocale getLanguage() const { return (eRPLocale)mLanguage; }

    void appendLocalDirectory(char *, const char *);

    static RPSysProjectLocal * getInstance() { return sInstance; }
    static RPSysProjectLocal * CreateInstance(EGG::Heap *);

private:
    RPSysProjectLocal(EGG::Heap *);
    virtual ~RPSysProjectLocal();

    EGG::Heap *mHeap; // at 0x4
    u32 mNumberSystem; // at 0x8
    u32 mLocale; // at 0xC
    u32 mLanguage; // at 0x10
    UNKWORD WORD_0x14;
    bool BOOL_0x18;
    u8 mCheckMiiOutUnk; // at 0x18
    bool mMotionPlusVideoSeen; // at 0x1A

    static RPSysProjectLocal *sInstance;
};

#endif