/***************************************************************
 * Name:      GanonBeepApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Brandon Ruggles ()
 * Created:   2014-06-23
 * Copyright: Brandon Ruggles ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "GanonBeepApp.h"
#include "GanonBeepMain.h"

IMPLEMENT_APP(GanonBeepApp);

bool GanonBeepApp::OnInit()
{
    GanonBeepFrame* frame = new GanonBeepFrame(NULL, _("GanonBeep"));
	
#ifdef __WINDOWS__
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
#endif
	
	frame->Show();

    return true;
}
