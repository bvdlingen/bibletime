/*********
*
* In the name of the Father, and of the Son, and of the Holy Spirit.
*
* This file is part of BibleTime's source code, https://bibletime.info/
*
* Copyright 1999-2021 by the BibleTime developers.
* The BibleTime source code is licensed under the GNU General Public License
* version 2.0.
*
**********/

#pragma once

#include <vector>

// Sword includes:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextra-semi"
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#include <osishtmlhref.h>
#include <swbuf.h>
#include <swmodule.h>
#pragma GCC diagnostic pop


namespace Filters {

/**
  \brief OSIS to HTMl conversion filter.
*/
class OsisToHtml: public sword::OSISHTMLHREF {
    protected: /* Types: */
        class UserData: public sword::OSISHTMLHREF::MyUserData {
            public:
                UserData(sword::SWModule const * module,
                         sword::SWKey const * key)
                     : sword::OSISHTMLHREF::MyUserData(module, key)
                     , swordFootnote(1)
                     , inCrossrefNote(false)
                     , entryAttributes(module->getEntryAttributes())
                {}

                unsigned short int swordFootnote;
                bool inCrossrefNote;
                sword::AttributeTypeList entryAttributes;

                enum NoteType {
                    Alternative,
                    CrossReference,
                    Footnote,
                    StrongsMarkup
                };
                std::vector<NoteType> noteTypes;

                struct {
                    sword::SWBuf who;
                } quote;
        };

    public: /* Methods: */
        OsisToHtml();

        /** Reimplemented from sword::OSISHTMLHREF. */
        bool handleToken(sword::SWBuf &buf,
                         const char *token,
                         sword::BasicFilterUserData *userData) override;

    protected: /* Methods: */
        /** Reimplemented from sword::OSISHTMLHREF. */
        sword::BasicFilterUserData * createUserData(
                sword::SWModule const * module,
                sword::SWKey const * key) override
        { return new UserData(module, key); }

};

} // namespace Filters
