#ifndef CADDIE_UI_MENU_LOCALIZED_ENUM_OPTION_H
#define CADDIE_UI_MENU_LOCALIZED_ENUM_OPTION_H
#include "types_caddie.h"
#include "caddieMenuEnumOption.h"
#include "caddieLocalizer.h"

#include <Sp2Util.h>

#include <STL/stdio.h>

namespace caddie
{
    class MenuLocalizedEnumOption : public MenuEnumOption
    {
    public:
        MenuLocalizedEnumOption(const char *names[Localizer::REGION_MAX], int min, int max,
            const char **locale[Localizer::REGION_MAX]) : MenuEnumOption(NULL, min, max, NULL)
        {
            Localizer *local = Localizer::GetInstance();
            CADDIE_ASSERT(local != NULL);

            SetName(names[local->GetGameRegion()]);
            SetTable(locale[local->GetGameRegion()]);
        }

        virtual ~MenuLocalizedEnumOption() {}

    private:
    };
}

#endif