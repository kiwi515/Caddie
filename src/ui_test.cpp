#include "ui_test.h"
#include "caddieTextBox.h"
#include "caddieMenuOption.h"
#include <egg/core/eggController.h>

using namespace nw4r::math;
using namespace nw4r::ut;
using namespace EGG;

namespace caddie
{
    static void LogClick()
    {
        CADDIE_LOG("\nOption clicked!!!\n");
    }

    void UiTest::Configure(RPSysScene*)
    {
        if (sTextBox == NULL) {
            sTextBox = new TextBox();
            CADDIE_ASSERT(sTextBox != NULL);
            sTextBox->SetPosition(VEC2(100, 20));
            sTextBox->SetText("Text Test 1");
            sTextBox->SetTextColor(Color(255, 0, 0, 255));
        }

        if (sTextBoxOutline == NULL) {
            sTextBoxOutline = new TextBox();
            CADDIE_ASSERT(sTextBoxOutline != NULL);
            sTextBoxOutline->SetStroke(TextBox::STROKE_OUTLINE);
            sTextBoxOutline->SetPosition(VEC2(100, 50));
            sTextBoxOutline->SetTextFmt("Text Test %d", 2);
            sTextBoxOutline->SetStrokeColor(Color(0, 255, 0, 255));
        }

        if (sTextBoxShadow == NULL) {
            sTextBoxShadow = new TextBox();
            CADDIE_ASSERT(sTextBoxShadow != NULL);
            sTextBoxShadow->SetStroke(TextBox::STROKE_SHADOW);
            sTextBoxShadow->SetPosition(VEC2(100, 80));
            sTextBoxShadow->SetTextFmt("%s 3", "Text Test");
            sTextBoxShadow->SetStrokeColor(Color(0, 0, 255, 255));
        }

        if (sIntOption == NULL) {
            sIntOption = new MenuActionOption("Action Log Test", LogClick);
            sIntOption->SetPosition(VEC2(100.0f, 110.0f));
        }
    }

    void UiTest::Calculate(RPSysScene*)
    {
        // Update player input
        CoreControllerMgr* contMgr = CoreControllerMgr::getInstance();
        CADDIE_ASSERT(contMgr != NULL);
        // Only use player 1 input
        CoreController* cont = contMgr->getNthController(0);
        CADDIE_ASSERT(cont != NULL);

        const u32 btn = cont->getButtons();
        if (btn & BTN_RIGHT) {
            sIntOption->Increment();
        }
        else if (btn & BTN_LEFT) {
            sIntOption->Decrement();
        }
        else if (btn & BTN_A) {
            sIntOption->OnClick();
        }
    }

    void UiTest::UserDraw(RPSysScene*)
    {
        sTextBox->Draw();
        sTextBoxOutline->Draw();
        sTextBoxShadow->Draw();

        sIntOption->Draw();
    }

    void UiTest::Exit(RPSysScene*)
    {
        // delete sTextBox;
        // sTextBox = NULL;
        
        // delete sTextBoxOutline;
        // sTextBoxOutline = NULL;

        // delete sTextBoxShadow;
        // sTextBoxShadow = NULL;

        // delete sIntOption;
        // sIntOption = NULL;
    }

    TextBox* UiTest::sTextBox = NULL;
    TextBox* UiTest::sTextBoxOutline = NULL;
    TextBox* UiTest::sTextBoxShadow = NULL;
    IMenuOption* UiTest::sIntOption = NULL;
}