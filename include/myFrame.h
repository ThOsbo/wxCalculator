#ifndef MYFRAME_H
    #define MYFRAME_H

    #include <wx/wxprec.h>
    #ifndef WX_PRECOMP
        #include <wx/wx.h>
    #endif

    class MyFrame : public wxFrame
    {
    public :
        MyFrame();

        wxTextCtrl *displayWindow = nullptr;

        void OnNumButtonClick(wxCommandEvent &evt);
        void OnOpButtonClick(wxCommandEvent &evt);
    
    private :
        wxString operations [4] = {"+", "-", "x", "/"};

    };
#endif