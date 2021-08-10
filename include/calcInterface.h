#ifndef CALCINTERFACE_H
    #define CALCINTERFACE_H

    #include <wx/wxprec.h>
    #ifndef WX_PRECOMP
        #include <wx/wx.h>
    #endif

    class Interface : public wxFrame
    {
        public :
            Interface();

            wxTextCtrl *displayWindow = nullptr;

            void OnNumButtonClick(wxCommandEvent &evt);
            void OnOpButtonClick(wxCommandEvent &evt);

            void OnEqButtonClick(wxCommandEvent &evt);

            void SetOpButtonsEnable(wxString toExclude[]);
            void SetNumButtonsEnable(bool isEnabled);

            void ResetButtons();

        private :

            wxString ans = "";

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
            bool eqButtonClick = false;

            int numBrackets = 0;

            static const int numStartID = 2000;
            static const int opsStartID = 3000;         

            static const int numOfOperations = 6;
            wxString operations [numOfOperations] = {plusSymbol, minusSymbol, multSymbol, divideSymbol, openBracSymbol, closeBracSymbol};

            wxString initialEnable [numOfOperations] = {"", minusSymbol, "", "", openBracSymbol, ""};

            wxString numClickToEnable[numOfOperations] = {plusSymbol, minusSymbol, multSymbol, divideSymbol, "", closeBracSymbol};

            wxString pointClickToEnable[numOfOperations] = {"", "", "", "", "", ""};

            wxString opClickToEnable [numOfOperations][numOfOperations] = 
            {
                {"", minusSymbol, "", "", openBracSymbol, ""},
                {"", "", "", "", openBracSymbol, ""},
                {"", minusSymbol, "", "", openBracSymbol, ""},
                {"", minusSymbol, "", "", openBracSymbol, ""},
                {"", minusSymbol, "", "", openBracSymbol, ""},
                {plusSymbol, minusSymbol, multSymbol, divideSymbol, "", closeBracSymbol}
            };
            wxButton **opButtons;
            wxButton *eqButtonPointer;

            wxButton **numButtons;
            wxButton *pointButtonPointer;
    };
#endif