#ifndef RP_SYSTEM_SCENE_H
#define RP_SYSTEM_SCENE_H
#include "types_rp.h"

#include <RP/RPGraphics.h>
#include <egg/core.h>

class RPSysScene : public EGG::Scene, public IRPGrpDrawObject {
public:
    enum Kind {
        Kind_System = 'SYS_',
        Kind_Base = 'BASE',
        Kind_Game = 'GAME',
        Kind_Sequence = 'SEQ_'
    };

    enum IslandType {
        IslandType_Day,
        IslandType_Evening,
        IslandType_Night,
        IslandType_Auto
    };

protected:
    void* PTR_0x30;

public:
    RPSysScene();

    virtual ~RPSysScene();                // at 0x8
    virtual void calc();                  // at 0xC
    virtual void draw();                  // at 0x10
    virtual void enter();                 // at 0x14
    virtual void exit();                  // at 0x18
    virtual void reinit();                // at 0x1C
    virtual void incoming_childDestroy(); // at 0x20
    virtual void outgoing_childCreate();  // at 0x24

    virtual EGG::Heap* getDebugSceneHeap(); // at 0x3C
    virtual Kind getKind();                 // at 0x40
    virtual void pauseCallBack(bool pause); // at 0x44
    virtual IslandType getIslandType();     // at 0x48

    virtual void Enter();         // at 0x4C
    virtual void Configure();     // at 0x50
    virtual void LoadResource();  // at 0x54
    virtual void Reset();         // at 0x58
    virtual void Calculate();     // at 0x5C
    virtual void Exit();          // at 0x60
    virtual void CalculateGyro(); // at 0x64
    virtual void taskAsyncFunc(); // at 0x68

    EGG::Heap* getHeapMem1() const { return mHeapMem1; }

    void setCreatorSceneID(int id);
    bool isTaskAsyncFinish();

    char _38[0x48 - 0x38];

    EGG::Heap* mHeapMem1;               // at 0x48
    EGG::Heap* mHeapMem1DependOnTarget; // at 0x4C

    char _50[0x80 - 0x50];
};

#endif
