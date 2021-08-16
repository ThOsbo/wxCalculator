#ifndef CALCINTERFACE_H
    #define CALCINTERFACE_H

    #include <wx/wxprec.h>
    #ifndef WX_PRECOMP
        #include <wx/wx.h>
    #endif

    #include <vector>

    class Interface : public wxFrame
    {
        public :
            //constructor
            Interface();

            //button click events
            void OnNumButtonClick(wxCommandEvent &evt);
            void OnOpButtonClick(wxCommandEvent &evt);
            void OnEqButtonClick(wxCommandEvent &evt);
            void OnShiftButtonClick(wxCommandEvent &evt);
            void OnDelButtonClick(wxCommandEvent &evt);
            void OnClearButtonClick(wxCommandEvent &evt);

        private :

            //function for displaying the input
            void DisplayInput(wxString toDisplay);

            //functions for enabling and disabling buttons
            void SetButtonsEnable(int buttonID);
            void SetOpButtonsEnable(bool toEnable[]);
            void SetNumButtonsEnable(bool isEnabled);
            void ResetButtons();

            //stores result of last calculation
            wxString ans = "";

            std :: vector<wxString> buttonsPressed;

            //constant strings for certain keys
            const wxString plusSymbol = "+";
            const wxString minusSymbol = "-";
            const wxString multSymbol = "x";
            const wxString divideSymbol = "/";
            const wxString openBracSymbol = "(";
            const wxString closeBracSymbol = ")";
            const wxString equalSymbol = "=";
            const wxString pointSymbol = ".";

            //bools for checking whether a particular button has been clicked
            bool eqButtonClick = false;
            bool shiftButtonClick = false;

            //integer counting the number of brackets
            int numBrackets = 0;

            //integers containing the start ID for each section
            static const int ctrlStartID = 1000;
            static const int numStartID = 2000;
            static const int opsStartID = 3000;         

            //array for all the operations the calculator can perform
            static const int numOfOperations = 6;
            wxString operations [numOfOperations] = {plusSymbol, minusSymbol, multSymbol, divideSymbol, openBracSymbol, closeBracSymbol};

            //arrays detailing which operations should be on and off when buttons are pressed
            bool initialEnable [numOfOperations] = {false, true, false, false, true, false};

            bool numClickToEnable[numOfOperations] = {true, true, true, true, false, true};

            bool pointClickToEnable[numOfOperations] = {false, false, false, false, false, false};

            bool opClickToEnable [numOfOperations][numOfOperations] = 
            {
                {false, true, false, false, true, false},
                {false, false, false, false, true, false},
                {false, true, false, false, true, false},
                {false, true, false, false, true, false},
                {false, true, false, false, true, false},
                {true, true, true, true, false, true}
            };

            //pointer to the display window
            wxTextCtrl *displayWindow = nullptr;

            //pointers to all the buttons
            wxButton **opButtons;
            wxButton *eqButtonPointer = nullptr;

            wxButton **numButtons;
            wxButton *pointButtonPointer = nullptr;
    };
#endif