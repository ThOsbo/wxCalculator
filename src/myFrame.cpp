#include <myFrame.h>

#if !defined(X_MAIN_FRAME_DIMENSION)
    #define X_MAIN_FRAME_DIMENSION 400
#endif

#if !defined(Y_MAIN_FRAME_DIMENSION)
    #define Y_MAIN_FRAME_DIMENSION 400
#endif

MyFrame :: MyFrame() : wxFrame(NULL, wxID_ANY, "Calculator", wxPoint(10, 10), wxSize(X_MAIN_FRAME_DIMENSION, Y_MAIN_FRAME_DIMENSION)) 
{
    
    wxBoxSizer *displaySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *controlSizer = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer *numbersSizer = new wxGridSizer(4, 3, 5, 5);
    wxGridSizer *opsSizer = new wxGridSizer(ceil((numOfOperations + 1) / 3.0), 3, 5, 5);

    wxFont font(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    displayWindow = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 10), wxSize(X_MAIN_FRAME_DIMENSION, 50), wxTE_READONLY);
    displayWindow -> SetFont(font);

    displaySizer -> Add(displayWindow, 0, wxEXPAND | wxALL, 5);

    numButtons = new wxButton*[10];

    for (int i = 1; i <= 10; i++) 
    {
        wxButton *numButton = new wxButton(this, numStartID + i, std :: to_string(i % 10), wxPoint(0, 0), wxSize(40, 40));
        numButton -> SetFont(font);
        numButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, MyFrame :: OnNumButtonClick, this);

        numButtons[i - 1] = numButton;
        numbersSizer -> Add(numButton, 1, wxEXPAND | wxALL, 2.5);                       
    }

    wxButton *pointButton = new wxButton(this, numStartID + 11, ".", wxPoint(0, 0), wxSize(40, 40));
    pointButton -> SetFont(font);
    pointButton -> Enable(false);
    pointButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, MyFrame :: OnNumButtonClick, this);
    
    pointButtonPointer = pointButton;
    numbersSizer -> Add(pointButton, 1, wxEXPAND | wxALL, 2.5);

    controlSizer -> Add(numbersSizer, 1, wxEXPAND | wxALL, 5);

    opButtons = new wxButton*[numOfOperations + 1];

    for (int i = 0; i < numOfOperations; i++) 
    {
        wxButton *opButton = new wxButton(this, opsStartID + i, operations[i], wxPoint(0, 0), wxSize(40, 40));
        opButton -> SetFont(font);
        if (operations[i] != "(" && operations[i] != "-") 
        {
            opButton -> Enable(false);
        }        
        opButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, MyFrame :: OnOpButtonClick, this);

        opButtons[i] = opButton;
        opsSizer -> Add(opButton, 1, wxEXPAND | wxALL, 2.5);
    }

    wxButton *eqButton = new wxButton(this, 3999, "=", wxPoint(0, 0), wxSize(40, 40));
    eqButton -> SetFont(font);
    eqButton -> Enable(false);
    eqButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, MyFrame :: OnEqButtonClick, this);

    eqButtonPointer = eqButton;
    opsSizer -> Add(eqButton, 1, wxEXPAND | wxALL, 2.5);

    controlSizer -> Add(opsSizer, 1, wxEXPAND | wxALL, 5);

    displaySizer -> Add(controlSizer, 1, wxEXPAND | wxALL, 5);

    this -> SetSizer(displaySizer);
    this -> Layout();
}

void MyFrame :: OnNumButtonClick(wxCommandEvent &evt) 
{
    int numClicked = evt.GetId() - numStartID;
    if (numClicked <= 10) 
    {
        wxString toEnableOps[numOfOperations] = {"+", "-", "x", "/", "", ")"};
        SetOpButtonsEnable(toEnableOps);
        eqButtonPointer -> Enable(true);
        pointButtonPointer -> Enable(true);
        displayWindow -> AppendText(std :: to_string(numClicked % 10));
    }
    else if (evt.GetId() == pointButtonPointer -> GetId()) 
    {
        wxString toEnableOps[numOfOperations] = {"", "", "", "", "", ""};
        SetOpButtonsEnable(toEnableOps);
        eqButtonPointer -> Enable(false);
        pointButtonPointer -> Enable(false);
        displayWindow -> AppendText(".");
    }
}

void MyFrame :: OnOpButtonClick(wxCommandEvent &evt) 
{
    int opClicked = evt.GetId() - opsStartID;
    SetOpButtonsEnable(toEnable[opClicked]);
    pointButtonPointer -> Enable(false);
    if (operations[opClicked] == ")") 
    {
        eqButtonPointer -> Enable(true);
        SetNumButtonsEnable(false);
    }
    else 
    {
        eqButtonPointer -> Enable(false);
        SetNumButtonsEnable(true);
    }
    displayWindow -> AppendText(operations[opClicked]);
}

void MyFrame :: OnEqButtonClick(wxCommandEvent &evt) 
{

}

void MyFrame :: SetOpButtonsEnable(wxString toEnable[]) 
{
    for (int i = 0; i < numOfOperations; i++) 
    {
        bool isEnabled = false;

        wxButton *opButton = opButtons[i];
        wxString operation = opButton -> GetLabel();

        for (int i = 0; i < numOfOperations; i++) 
        {
            if (operation == toEnable[i]) 
            {
                isEnabled = true;
                break;
            }
        }           
        
        opButton -> Enable(isEnabled);       
    }
}

void MyFrame :: SetNumButtonsEnable(bool isEnabled) 
{
    for (int i = 0; i < 10; i++) 
    {
        wxButton *numButton = numButtons[i];
        numButton -> Enable(isEnabled);
    }
}