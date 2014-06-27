/***************************************************************
 * Name:      GanonBeepMain.h
 * Purpose:   Defines Application Frame
 * Author:    Brandon Ruggles ()
 * Created:   2014-06-23
 * Copyright: Brandon Ruggles ()
 * License:
 **************************************************************/

#ifndef GANONBEEPMAIN_H
#define GANONBEEPMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "GanonBeepApp.h"

class GanonBeepFrame: public wxFrame
{
    public:
        GanonBeepFrame(wxFrame *frame, const wxString& title);
        ~GanonBeepFrame();
    private:
        enum
        {
            idMenuNewPlayerTag = 0,
            idMenuEditPlayerTag,
            idMenuRemovePlayerTag,
            idMenuQuit,
            idMenuOptions,
            idMenuHowTo,
            idMenuAbout,
            idNameTitle,
            idNameBox,
            idP1AddButton,
            idP2AddButton,
            idP3AddButton,
            idP4AddButton,
            idP1RemoveButton,
            idP2RemoveButton,
            idP3RemoveButton,
            idP4RemoveButton,
            idRemoveButton,
            idBannerTitle,
            idBannerField,
            idBannerSetButton,
            idBannerRemoveButton,
            idPreviewTitle,
            idBannerTitle2,
            idBannerLabel,
            idP1Title,
            idP2Title,
            idP3Title,
            idP4Title,
            idP1Label,
            idP2Label,
            idP3Label,
            idP4Label
        };
        void OnClose(wxCloseEvent& event);
        void OnNewPlayerTag(wxCommandEvent& event);
        void OnEditPlayerTag(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnOptions(wxCommandEvent& event);
        void OnHowTo(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPlayerSelect(wxCommandEvent& event);
        void OnP1Add(wxCommandEvent& event);
        void OnP2Add(wxCommandEvent& event);
        void OnP3Add(wxCommandEvent& event);
        void OnP4Add(wxCommandEvent& event);
        void OnP1Remove(wxCommandEvent& event);
        void OnP2Remove(wxCommandEvent& event);
        void OnP3Remove(wxCommandEvent& event);
        void OnP4Remove(wxCommandEvent& event);
        void OnPlayerRemove(wxCommandEvent& event);
        void OnBannerText(wxCommandEvent& event);
        void OnBannerSet(wxCommandEvent& event);
        void OnBannerRemove(wxCommandEvent& event);
        void WriteToFile(wxString fileName,wxString data);
        void AppendToFile(wxString fileName,wxString data);
        void ReplaceWordInFile(wxString fileName,wxString originalWord,wxString newWord);
        bool NameIsTaken(wxString name);
        wxMenuBar* mbar;
        wxMenu* fileMenu;
        wxMenu* settingsMenu;
        wxMenu* helpMenu;
        wxStaticText* nameTitle;
        wxComboBox* nameBox;
        wxButton* p1AddButton;
        wxButton* p2AddButton;
        wxButton* p3AddButton;
        wxButton* p4AddButton;
        wxButton* p1RemoveButton;
        wxButton* p2RemoveButton;
        wxButton* p3RemoveButton;
        wxButton* p4RemoveButton;
        wxStaticText* bannerTitle;
        wxTextCtrl* bannerField;
        wxString bannerText;
        wxString p1Text;
        wxString p2Text;
        wxString p3Text;
        wxString p4Text;
        wxButton* bannerSetButton;
        wxButton* bannerRemoveButton;
        wxStaticText* previewTitle;
        wxStaticText* bannerTitle2;
        wxStaticText* bannerLabel;
        wxStaticText* p1Title;
        wxStaticText* p2Title;
        wxStaticText* p3Title;
        wxStaticText* p4Title;
        wxStaticText* p1Label;
        wxStaticText* p2Label;
        wxStaticText* p3Label;
        wxStaticText* p4Label;
        DECLARE_EVENT_TABLE()
};


#endif // GANONBEEPMAIN_H
