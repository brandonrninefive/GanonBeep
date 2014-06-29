/***************************************************************
 * Name:      GanonBeepMain.cpp
 * Purpose:   Code for Application Frame
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

#include "GanonBeepMain.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

BEGIN_EVENT_TABLE(GanonBeepFrame, wxFrame)
    EVT_CLOSE(GanonBeepFrame::OnClose)
    EVT_MENU(idMenuNewPlayerTag,GanonBeepFrame::OnNewPlayerTag)
    EVT_MENU(idMenuEditPlayerTag,GanonBeepFrame::OnEditPlayerTag)
    EVT_MENU(idMenuRemovePlayerTag,GanonBeepFrame::OnPlayerRemove)
    EVT_MENU(idMenuQuit, GanonBeepFrame::OnQuit)
    EVT_MENU(idMenuOptions,GanonBeepFrame::OnOptions)
    EVT_MENU(idMenuHowTo,GanonBeepFrame::OnHowTo)
    EVT_MENU(idMenuAbout, GanonBeepFrame::OnAbout)
    EVT_COMBOBOX(idNameBox,GanonBeepFrame::OnPlayerSelect)
    EVT_BUTTON(idP1AddButton,GanonBeepFrame::OnP1Add)
    EVT_BUTTON(idP2AddButton,GanonBeepFrame::OnP2Add)
    EVT_BUTTON(idP3AddButton,GanonBeepFrame::OnP3Add)
    EVT_BUTTON(idP4AddButton,GanonBeepFrame::OnP4Add)
    EVT_BUTTON(idP1RemoveButton,GanonBeepFrame::OnP1Remove)
    EVT_BUTTON(idP2RemoveButton,GanonBeepFrame::OnP2Remove)
    EVT_BUTTON(idP3RemoveButton,GanonBeepFrame::OnP3Remove)
    EVT_BUTTON(idP4RemoveButton,GanonBeepFrame::OnP4Remove)
    EVT_TEXT(idBannerField,GanonBeepFrame::OnBannerText)
    EVT_TEXT_ENTER(idBannerField,GanonBeepFrame::OnBannerSet)
    EVT_BUTTON(idBannerSetButton,GanonBeepFrame::OnBannerSet)
    EVT_BUTTON(idBannerRemoveButton,GanonBeepFrame::OnBannerRemove)
END_EVENT_TABLE()

GanonBeepFrame::GanonBeepFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title,wxPoint(50,50),wxSize(500,550),wxCAPTION | wxMINIMIZE_BOX | wxCLOSE_BOX)
{
    // create a menu bar
    mbar = new wxMenuBar();
    fileMenu = new wxMenu();
    fileMenu->Append(idMenuNewPlayerTag,"Add New Player Tag\tCtrl-N","Add a new player tag");
    fileMenu->Append(idMenuEditPlayerTag,"Edit Player Tag\tCtrl-E","Edit the currently-selected player tag");
    fileMenu->Append(idMenuRemovePlayerTag,"Delete Player Tag\tCtrl-D","Delete the currently-selected player tag");
    fileMenu->AppendSeparator();
    fileMenu->Append(idMenuQuit,"Quit\tAlt-F4","Exit GanonBeep");
    mbar->Append(fileMenu,"File");

    settingsMenu = new wxMenu();
    settingsMenu->Append(idMenuOptions,"Options\tCtrl-O","Open options dialogue");
    mbar->Append(settingsMenu,"Settings");

    helpMenu = new wxMenu();
    helpMenu->Append(idMenuHowTo,"How to Use GanonBeep\tCtrl-H","Show how to use GanonBeep");
    helpMenu->Append(idMenuAbout, "About GanonBeep\tCtrl-?","Show information about GanonBeep");
    mbar->Append(helpMenu,"Help");

    SetMenuBar(mbar);

    CreateStatusBar(2);
    SetStatusText("Welcome to GanonBeep!",0);
    SetStatusText("Version 2.0", 1);

    nameTitle = new wxStaticText(this,idNameTitle,"Change Stream Players:",wxPoint(180,15),wxSize(100,20));
    nameTitle->SetFont(wxFont(10,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT));
    
    long nameBoxStyle = wxCB_READONLY;

#ifndef __APPLE__
    nameBoxStyle |= wxCB_SORT;
#endif
    
    nameBox = new wxComboBox(this,idNameBox,"",wxPoint(20,45),wxSize(450,25),0,NULL,nameBoxStyle);

    p1AddButton = new wxButton(this,idP1AddButton,"Add as P1",wxPoint(10,80),wxSize(100,20));
    p2AddButton = new wxButton(this,idP2AddButton,"Add as P2",wxPoint(130,80),wxSize(100,20));
    p3AddButton = new wxButton(this,idP3AddButton,"Add as P3",wxPoint(260,80),wxSize(100,20));
    p4AddButton = new wxButton(this,idP4AddButton,"Add as P4",wxPoint(380,80),wxSize(100,20));
    p1RemoveButton = new wxButton(this,idP1RemoveButton,"Remove P1",wxPoint(10,110),wxSize(100,20));
    p2RemoveButton = new wxButton(this,idP2RemoveButton,"Remove P2",wxPoint(130,110),wxSize(100,20));
    p3RemoveButton = new wxButton(this,idP3RemoveButton,"Remove P3",wxPoint(260,110),wxSize(100,20));
    p4RemoveButton = new wxButton(this,idP4RemoveButton,"Remove P4",wxPoint(380,110),wxSize(100,20));

    bannerTitle = new wxStaticText(this,idBannerTitle,"Change Stream Banner:",wxPoint(183,150),wxSize(100,20));
    bannerTitle->SetFont(wxFont(10,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT));

    bannerText = wxString("");
    p1Text = wxString("");
    p2Text = wxString("");
    p3Text = wxString("");
    p4Text = wxString("");

    fstream file;
    string line;
    file.open("Banner.txt");
    if(file.is_open())
    {
        while(getline(file,line))
            bannerText<<line;
    }
    else
        wxMessageBox("GanonBeep could not read from Banner.txt!","Error!");
    file.close();

    file.open("Names.txt");
    if(file.is_open())
    {
        while(getline(file,line))
            nameBox->Append(line);
    }
    else
        wxMessageBox("GanonBeep could not red from Names.txt!");
    file.close();
    
    if(nameBox->GetCount() > 0)
    {
        nameBox->SetSelection(0);
    }

    file.open("Player1.txt");
    if(file.is_open())
    {
         while(getline(file,line))
            p1Text<<line;
    }
    else
        wxMessageBox("GanonBeep could not read from Player1.txt!","Error!");
    file.close();

    file.open("Player2.txt");
    if(file.is_open())
    {
         while(getline(file,line))
            p2Text<<line;
    }
    else
        wxMessageBox("GanonBeep could not read from Player2.txt!","Error!");
    file.close();

    file.open("Player3.txt");
    if(file.is_open())
    {
         while(getline(file,line))
            p3Text<<line;
    }
    else
        wxMessageBox("GanonBeep could not read from Player3.txt!","Error!");
    file.close();

    file.open("Player4.txt");
    if(file.is_open())
    {
         while(getline(file,line))
            p4Text<<line;
    }
    else
        wxMessageBox("GanonBeep could not read from Player4.txt!","Error!");
    file.close();

    if(nameBox->GetCurrentSelection() == wxNOT_FOUND || NameIsTaken(nameBox->GetString(nameBox->GetCurrentSelection())))
    {
        p1AddButton->Disable();
        p2AddButton->Disable();
        p3AddButton->Disable();
        p4AddButton->Disable();
    }

    if(p1Text == "")
        p1RemoveButton->Disable();
    if(p2Text == "")
        p2RemoveButton->Disable();
    if(p3Text == "")
        p3RemoveButton->Disable();
    if(p4Text == "")
        p4RemoveButton->Disable();

    bannerField = new wxTextCtrl(this,idBannerField,bannerText,wxPoint(20,180),wxSize(450,20),wxTE_PROCESS_ENTER);

    bannerSetButton = new wxButton(this,idBannerSetButton,"Set as Banner",wxPoint(20,210),wxSize(450,20));
    bannerRemoveButton = new wxButton(this,idBannerRemoveButton,"Remove Banner",wxPoint(20,240),wxSize(450,20));
    bannerSetButton->Disable();
    if(bannerText == "")
        bannerRemoveButton->Disable();

    previewTitle = new wxStaticText(this,idPreviewTitle,"Stream Preview:",wxPoint(200,275),wxSize(100,20));
    previewTitle->SetFont(wxFont(10,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT));

    bannerTitle2 = new wxStaticText(this,idBannerTitle2,"Current Banner:",wxPoint(206,300),wxSize(100,20));
    bannerLabel = new wxStaticText(this,idBannerLabel,bannerText,wxPoint(-5,325),wxSize(500,20),wxALIGN_CENTER);
    bannerLabel->SetForegroundColour(wxColor(0,0,255));

    p1Title = new wxStaticText(this,idP1Title,"Player 1:",wxPoint(50,350),wxSize(100,20));
    p2Title = new wxStaticText(this,idP2Title,"Player 2:",wxPoint(164,350),wxSize(100,20));
    p3Title = new wxStaticText(this,idP3Title,"Player 3:",wxPoint(278,350),wxSize(100,20));
    p4Title = new wxStaticText(this,idP4Title,"Player 4:",wxPoint(390,350),wxSize(100,20));

    p1Label = new wxStaticText(this,idP1Label,p1Text,wxPoint(0,370),wxSize(140,20),wxALIGN_CENTER);
    p2Label = new wxStaticText(this,idP2Label,p2Text,wxPoint(115,370),wxSize(140,20),wxALIGN_CENTER);
    p3Label = new wxStaticText(this,idP3Label,p3Text,wxPoint(229,370),wxSize(140,20),wxALIGN_CENTER);
    p4Label = new wxStaticText(this,idP4Label,p4Text,wxPoint(342,370),wxSize(140,20),wxALIGN_CENTER);

    p1Label->SetForegroundColour(wxColor(0,100,255));
    p2Label->SetForegroundColour(wxColor(0,100,255));
    p3Label->SetForegroundColour(wxColor(0,100,255));
    p4Label->SetForegroundColour(wxColor(0,100,255));

    p1Label->SetLabel(p1Text);
    p2Label->SetLabel(p2Text);
    p3Label->SetLabel(p3Text);
    p4Label->SetLabel(p4Text);

}


GanonBeepFrame::~GanonBeepFrame()
{
}

void GanonBeepFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void GanonBeepFrame::OnNewPlayerTag(wxCommandEvent &event)
{
    wxString tag = wxGetTextFromUser("Please enter a new player tag:","New Player Tag","");
    bool found = false;
    for(unsigned int i = 0;i<nameBox->GetCount();i++)
        if(nameBox->GetString(i) == tag)
            found = true;
    if(!found && tag!="")
    {
        nameBox->Append(tag);
        AppendToFile("Names.txt",tag<<"\n");
    }
    else
        wxMessageBox("You either entered a blank player tag, canceled your entry, or the player tag you entered already exists!","Error!");

    if(nameBox->GetCurrentSelection() == wxNOT_FOUND)
        nameBox->SetSelection(0);

    if(!NameIsTaken(nameBox->GetString(nameBox->GetCurrentSelection())))
    {
        p1AddButton->Enable();
        p2AddButton->Enable();
        p3AddButton->Enable();
        p4AddButton->Enable();
    }
    else
    {
        p1AddButton->Disable();
        p2AddButton->Disable();
        p3AddButton->Disable();
        p4AddButton->Disable();
    }
}

void GanonBeepFrame::OnEditPlayerTag(wxCommandEvent &event)
{
    if(nameBox->GetCurrentSelection() != wxNOT_FOUND)
    {
        wxString tag = wxGetTextFromUser("Please enter a replacement for the tag '" + nameBox->GetString(nameBox->GetCurrentSelection()) + "'.","Edit Tag",nameBox->GetString(nameBox->GetCurrentSelection()));
        if(tag == "")
            wxMessageBox("The new tag you entered was blank!","Error!");
        else if(NameIsTaken(tag))
            wxMessageBox("The new tag you entered is already taken!","Error!");
        else if(tag == nameBox->GetString(nameBox->GetCurrentSelection()))
            wxMessageBox("The new tag you entered was the same as the original!","Error!");
        else
        {
            if(p1Text == nameBox->GetString(nameBox->GetCurrentSelection()))
            {
                p1Text = tag;
                p1Label->SetLabel(p1Text);
                WriteToFile("Player1.txt",p1Text);
            }
            if(p2Text == nameBox->GetString(nameBox->GetCurrentSelection()))
            {
                p2Text = tag;
                p2Label->SetLabel(p2Text);
                WriteToFile("Player2.txt",p2Text);
            }
            if(p3Text == nameBox->GetString(nameBox->GetCurrentSelection()))
            {
                p3Text = tag;
                p3Label->SetLabel(p3Text);
                WriteToFile("Player3.txt",p3Text);
            }
            if(p4Text == nameBox->GetString(nameBox->GetCurrentSelection()))
            {
                p4Text = tag;
                p4Label->SetLabel(p4Text);
                WriteToFile("Player4.txt",p4Text);
            }
            ReplaceWordInFile("Names.txt",nameBox->GetString(nameBox->GetCurrentSelection()),tag);
            nameBox->SetString(nameBox->GetCurrentSelection(),tag);
        }
    }
    else
        wxMessageBox("You have no tag selected to edit!","Error!");
}

void GanonBeepFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void GanonBeepFrame::OnOptions(wxCommandEvent &event)
{

}

void GanonBeepFrame::OnHowTo(wxCommandEvent &event)
{

}

void GanonBeepFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("GanonBeep is a live streaming tool and stat-tracker based around the Super Smash Bros. series.  It is currently being developed by the members of SiG Melee, a 'Special Interest Group' belonging to NJIT's chapter of ACM.  Be sure to check out our live stream at http://www.twitch.tv/sigmelee!\n\nInitial Build Created By: Brandon Ruggles\n\nCurrent Version Contributors: Brandon Ruggles", "About");
}

void GanonBeepFrame::OnPlayerSelect(wxCommandEvent &event)
{
    if(!NameIsTaken(nameBox->GetString(nameBox->GetCurrentSelection())))
    {
        p1AddButton->Enable();
        p2AddButton->Enable();
        p3AddButton->Enable();
        p4AddButton->Enable();
    }
    else
    {
        p1AddButton->Disable();
        p2AddButton->Disable();
        p3AddButton->Disable();
        p4AddButton->Disable();
    }
}

void GanonBeepFrame::OnP1Add(wxCommandEvent &event)
{
        p1Text = nameBox->GetString(nameBox->GetCurrentSelection());
        p1Label->SetLabel(p1Text);
        p1AddButton->Disable();
        p2AddButton->Disable();
        p3AddButton->Disable();
        p4AddButton->Disable();
        p1RemoveButton->Enable();
        WriteToFile("Player1.txt",p1Text);
}

void GanonBeepFrame::OnP2Add(wxCommandEvent &event)
{
        p2Text = nameBox->GetString(nameBox->GetCurrentSelection());
        p2Label->SetLabel(p2Text);
        p1AddButton->Disable();
        p2AddButton->Disable();
        p3AddButton->Disable();
        p4AddButton->Disable();
        p2RemoveButton->Enable();
        WriteToFile("Player2.txt",p2Text);
}

void GanonBeepFrame::OnP3Add(wxCommandEvent &event)
{
        p3Text = nameBox->GetString(nameBox->GetCurrentSelection());
        p3Label->SetLabel(p3Text);
        p1AddButton->Disable();
        p2AddButton->Disable();
        p3AddButton->Disable();
        p4AddButton->Disable();
        p3RemoveButton->Enable();
        WriteToFile("Player3.txt",p3Text);
}

void GanonBeepFrame::OnP4Add(wxCommandEvent &event)
{
        p4Text = nameBox->GetString(nameBox->GetCurrentSelection());
        p4Label->SetLabel(p4Text);
        p1AddButton->Disable();
        p2AddButton->Disable();
        p3AddButton->Disable();
        p4AddButton->Disable();
        p4RemoveButton->Enable();
        WriteToFile("Player4.txt",p4Text);
}

void GanonBeepFrame::OnP1Remove(wxCommandEvent &event)
{
    p1RemoveButton->Disable();
    p1Text = "";
    p1Label->SetLabel(p1Text);
    if(!NameIsTaken(nameBox->GetString(nameBox->GetCurrentSelection())))
    {
        p1AddButton->Enable();
        p2AddButton->Enable();
        p3AddButton->Enable();
        p4AddButton->Enable();
    }
    WriteToFile("Player1.txt",p1Text);
}

void GanonBeepFrame::OnP2Remove(wxCommandEvent &event)
{
    p2RemoveButton->Disable();
    p2Text = "";
    p2Label->SetLabel(p2Text);
    if(!NameIsTaken(nameBox->GetString(nameBox->GetCurrentSelection())))
    {
        p1AddButton->Enable();
        p2AddButton->Enable();
        p3AddButton->Enable();
        p4AddButton->Enable();
    }
    WriteToFile("Player2.txt",p2Text);
}

void GanonBeepFrame::OnP3Remove(wxCommandEvent &event)
{
    p3RemoveButton->Disable();
    p3Text = "";
    p3Label->SetLabel(p3Text);
    if(!NameIsTaken(nameBox->GetString(nameBox->GetCurrentSelection())))
    {
        p1AddButton->Enable();
        p2AddButton->Enable();
        p3AddButton->Enable();
        p4AddButton->Enable();
    }
    WriteToFile("Player3.txt",p3Text);
}

void GanonBeepFrame::OnP4Remove(wxCommandEvent &event)
{
    p4RemoveButton->Disable();
    p4Text = "";
    p4Label->SetLabel(p4Text);
    if(!NameIsTaken(nameBox->GetString(nameBox->GetCurrentSelection())))
    {
        p1AddButton->Enable();
        p2AddButton->Enable();
        p3AddButton->Enable();
        p4AddButton->Enable();
    }
    WriteToFile("Player4.txt",p4Text);
}

void GanonBeepFrame::OnPlayerRemove(wxCommandEvent &event)
{
    if(nameBox->GetCurrentSelection() != wxNOT_FOUND)
    {
        int answer = wxMessageDialog(this,"Are you sure you want to delete the currently-selected player tag?","Alert!",wxCENTER | wxYES_NO).ShowModal();
        if(answer == wxID_YES)
        {
            ReplaceWordInFile("Names.txt",nameBox->GetString(nameBox->GetCurrentSelection()),"");
            if(p1Text == nameBox->GetString(nameBox->GetCurrentSelection()))
            {
                p1Text = "";
                p1Label->SetLabel(p1Text);
                p1RemoveButton->Disable();
                WriteToFile("Player1.txt",p1Text);
            }
            if(p2Text == nameBox->GetString(nameBox->GetCurrentSelection()))
            {
                p2Text = "";
                p2Label->SetLabel(p2Text);
                p2RemoveButton->Disable();
                WriteToFile("Player2.txt",p2Text);
            }
            if(p3Text == nameBox->GetString(nameBox->GetCurrentSelection()))
            {
                p3Text = "";
                p3Label->SetLabel(p3Text);
                p3RemoveButton->Disable();
                WriteToFile("Player3.txt",p3Text);
            }
            if(p4Text == nameBox->GetString(nameBox->GetCurrentSelection()))
            {
                p4Text = "";
                p4Label->SetLabel(p4Text);
                p4RemoveButton->Disable();
                WriteToFile("Player4.txt",p4Text);
            }
            nameBox->Delete(nameBox->GetCurrentSelection());
            
            if(nameBox->GetCount() > 0)
            {
                nameBox->SetSelection(0);
            }

            if(nameBox->GetCurrentSelection() != wxNOT_FOUND && !NameIsTaken(nameBox->GetString(nameBox->GetCurrentSelection())))
            {
                p1AddButton->Enable();
                p2AddButton->Enable();
                p3AddButton->Enable();
                p4AddButton->Enable();
            }
            else
            {
                p1AddButton->Disable();
                p2AddButton->Disable();
                p3AddButton->Disable();
                p4AddButton->Disable();
            }
        }
    }
    else
        wxMessageBox("You have no tag selected to delete!","Error!");
}

void GanonBeepFrame::OnBannerText(wxCommandEvent &event)
{
    if(bannerField->GetValue() == "" || bannerField->GetValue() == bannerText)
        bannerSetButton->Disable();
    else
        bannerSetButton->Enable();
}

void GanonBeepFrame::OnBannerSet(wxCommandEvent &event)
{
    bannerText = bannerField->GetValue();
    bannerLabel->SetLabel(bannerText);
    bannerSetButton->Disable();
    bannerRemoveButton->Enable();
    WriteToFile("Banner.txt",bannerText);
}

void GanonBeepFrame::OnBannerRemove(wxCommandEvent &event)
{
    bannerRemoveButton->Disable();
    bannerText = "";
    bannerLabel->SetLabel(bannerText);
    if(bannerField->GetValue() != "")
        bannerSetButton->Enable();
    WriteToFile("Banner.txt",bannerText);
}

void GanonBeepFrame::WriteToFile(wxString fileName,wxString data)
{
    ofstream file;
    file.open(fileName);
    file<<data;
    file.close();
}

void GanonBeepFrame::AppendToFile(wxString fileName,wxString data)
{
    ofstream file;
    file.open(fileName,ofstream::app);
    file<<data;
    file.close();
}

void GanonBeepFrame::ReplaceWordInFile(wxString fileName,wxString originalWord,wxString newWord)
{
    ifstream inFile;
    inFile.open(fileName);
    string line;
    string inFileContents;
    while(getline(inFile,line))
    {
        inFileContents+=(line+"\n");
    }
    inFile.close();
    int index = inFileContents.find(originalWord);
    inFileContents.replace(index,originalWord.length()+1,newWord);
    ofstream outFile;
    outFile.open(fileName);
    outFile<<inFileContents;
    outFile.close();
}

bool GanonBeepFrame::NameIsTaken(wxString name)
{
    if(p1Text == name || p2Text == name || p3Text == name || p4Text == name)
        return true;
    return false;
}
