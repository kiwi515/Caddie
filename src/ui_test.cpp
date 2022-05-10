#include "ui_test.h"
#include "caddieTextBox.h"

using namespace nw4r::math;
using namespace nw4r::ut;

namespace caddie
{
    void UiTest::Configure(RPSysScene*)
    {
        CADDIE_LOG("\nConfiguring the UI test!!!\n");

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
    }

    void UiTest::Calculate(RPSysScene*)
    {
    }

    void UiTest::UserDraw(RPSysScene*)
    {
        // CADDIE_LOG("\nDrawing the UI test!!!\n");
        sTextBox->Draw();
        sTextBoxOutline->Draw();
        sTextBoxShadow->Draw();
    }

    void UiTest::Exit(RPSysScene*)
    {
        delete sTextBox;
        sTextBox = NULL;
        
        delete sTextBoxOutline;
        sTextBoxOutline = NULL;

        delete sTextBoxShadow;
        sTextBoxShadow = NULL;
    }

    TextBox* UiTest::sTextBox = NULL;
    TextBox* UiTest::sTextBoxOutline = NULL;
    TextBox* UiTest::sTextBoxShadow = NULL;
}