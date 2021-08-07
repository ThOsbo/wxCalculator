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

        void OnEqButtonClick(wxCommandEvent &evt);
    
        void SetOpButtonsEnable(wxString toExclude[]);
        void SetNumButtonsEnable(bool isEnabled);

    private :

        const wxString plusSymbol = "+";
        const wxString minusSymbol = "-";
        const wxString multSymbol = "x";
        const wxString divideSymbol = "/";
        const wxString openBracSymbol = "(";
        const wxString closeBracSymbol = ")";
        const wxString equalSymbol = "=";
        const wxString pointSymbol = ".";

        bool minusClick = false;
        bool closeBracClick = false;

        int numBrackets = 0;

        static const int numStartID = 2000;
        static const int opsStartID = 3000;

        static const int numOfOperations = 6;
        wxString operations [numOfOperations] = {plusSymbol, minusSymbol, multSymbol, divideSymbol, openBracSymbol, closeBracSymbol};
        wxString toEnable [numOfOperations][numOfOperations + 1] = 
        {
            {"", minusSymbol, "", "", openBracSymbol, "", ""},
            {"", "", "", "", openBracSymbol, "", ""},
            {"", minusSymbol, "", "", openBracSymbol, "", ""},
            {"", minusSymbol, "", "", openBracSymbol, "", ""},
            {"", minusSymbol, "", "", openBracSymbol, "", ""},
            {plusSymbol, minusSymbol, multSymbol, divideSymbol, "", closeBracSymbol, ""}
        };
        wxButton **opButtons;
        wxButton *eqButtonPointer;

        wxButton **numButtons;
        wxButton *pointButtonPointer;
    };
#endif