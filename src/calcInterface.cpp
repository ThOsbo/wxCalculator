#include <calcInterface.h>
#include <calculate.h>

#if !defined(X_MAIN_FRAME_DIMENSION)
    #define X_MAIN_FRAME_DIMENSION 400
#endif

#if !defined(Y_MAIN_FRAME_DIMENSION)
    #define Y_MAIN_FRAME_DIMENSION 400
#endif

Interface :: Interface() : wxFrame(NULL, wxID_ANY, "Calculator", wxPoint(10, 10), wxSize(X_MAIN_FRAME_DIMENSION, Y_MAIN_FRAME_DIMENSION)) 
{
    
    wxBoxSizer *displaySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *controlSizer = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer *numbersSizer = new wxGridSizer(4, 3, 5, 5);
    wxGridSizer *opsSizer = new wxGridSizer(ceil((numOfOperations + 1) / 3.0), 3, 5, 5);

    wxFont font(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    displayWindow = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 10), wxSize(X_MAIN_FRAME_DIMENSION, 50), wxTE_READONLY);
    displayWindow -> SetFont(font);

    displaySizer -> Add(displayWindow, 0, wxEXPAND | wxALL, 5);

    numButtons = new wxButton*[10] { nullptr };

    for (int i = 1; i <= 10; i++) 
    {
        wxButton *numButton = new wxButton(this, numStartID + i, std :: to_string(i % 10), wxPoint(0, 0), wxSize(40, 40));
        numButton -> SetFont(font);
        numButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, Interface :: OnNumButtonClick, this);

        numButtons[i - 1] = numButton;
        numbersSizer -> Add(numButton, 1, wxEXPAND | wxALL, 2.5);                 
    }

    wxButton *pointButton = new wxButton(this, numStartID + 11, pointSymbol, wxPoint(0, 0), wxSize(40, 40));
    pointButton -> SetFont(font);
    pointButton -> Enable(false);
    pointButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, Interface :: OnNumButtonClick, this);
    
    pointButtonPointer = pointButton;
    numbersSizer -> Add(pointButton, 1, wxEXPAND | wxALL, 2.5);

    controlSizer -> Add(numbersSizer, 1, wxEXPAND | wxALL, 5);

    opButtons = new wxButton*[numOfOperations + 1] { nullptr };

    for (int i = 0; i < numOfOperations; i++) 
    {
        wxButton *opButton = new wxButton(this, opsStartID + i, operations[i], wxPoint(0, 0), wxSize(40, 40));
        opButton -> SetFont(font);
        if (operations[i] != openBracSymbol && operations[i] != minusSymbol) 
        {
            opButton -> Enable(false);
        }        
        opButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, Interface :: OnOpButtonClick, this);

        opButtons[i] = opButton;
        opsSizer -> Add(opButton, 1, wxEXPAND | wxALL, 2.5);
    }

    wxButton *eqButton = new wxButton(this, 3999, equalSymbol, wxPoint(0, 0), wxSize(40, 40));
    eqButton -> SetFont(font);
    eqButton -> Enable(false);
    eqButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, Interface :: OnEqButtonClick, this);

    eqButtonPointer = eqButton;
    opsSizer -> Add(eqButton, 1, wxEXPAND | wxALL, 2.5);

    controlSizer -> Add(opsSizer, 1, wxEXPAND | wxALL, 5);

    displaySizer -> Add(controlSizer, 1, wxEXPAND | wxALL, 5);

    this -> SetSizer(displaySizer);
    this -> Layout();

}

void Interface :: OnNumButtonClick(wxCommandEvent &evt) 
{
    if (eqButtonClick) 
    {
        displayWindow -> Clear();
        eqButtonClick = false;
    }

    int numClicked = evt.GetId() - numStartID;
    if (numClicked <= 10) 
    {
        SetOpButtonsEnable(numClickToEnable);
        if (numBrackets == 0) 
        {
            eqButtonPointer -> Enable(true);
        }
        else 
        {
            eqButtonPointer -> Enable(false);
        }
        
        pointButtonPointer -> Enable(true);
        displayWindow -> AppendText(std :: to_string(numClicked % 10));
    }
    else if (evt.GetId() == pointButtonPointer -> GetId()) 
    {
        SetOpButtonsEnable(pointClickToEnable);
        eqButtonPointer -> Enable(false);
        pointButtonPointer -> Enable(false);
        displayWindow -> AppendText(pointSymbol);
    }

    evt.Skip();
}

void Interface :: OnOpButtonClick(wxCommandEvent &evt) 
{
    if (eqButtonClick) 
    {
        displayWindow -> Clear();
        eqButtonClick = false;
    }

    int opClicked = evt.GetId() - opsStartID;
    pointButtonPointer -> Enable(false);
    if (operations[opClicked] == closeBracSymbol) 
    {
        numBrackets--;
        if (numBrackets == 0) 
        {
            eqButtonPointer -> Enable(true);
        }

        SetNumButtonsEnable(false);
    }
    else 
    {
        if (operations[opClicked] == openBracSymbol) 
        {
            numBrackets++;
        }
        eqButtonPointer -> Enable(false);
        SetNumButtonsEnable(true);
    }
    SetOpButtonsEnable(opClickToEnable[opClicked]);
    displayWindow -> AppendText(operations[opClicked]);

    evt.Skip();
}

void Interface :: OnEqButtonClick(wxCommandEvent &evt) 
{
    wxString toCalculate = displayWindow -> GetValue();

    try 
    {
        ans = wxString(PerformCalculation :: GetResult(toCalculate.ToStdString()));
    }
    catch (const std :: exception &ex)
    {
        ans = "Error";
    }
    
    displayWindow -> SetValue("=" + ans);
    ResetButtons();
    eqButtonClick = true;

    evt.Skip();
}

void Interface :: SetOpButtonsEnable(bool toEnable[]) 
{
    for (int i = 0; i < numOfOperations; i++) 
    {
        if (opButtons[i] -> GetLabel() == closeBracSymbol) 
        {
            opButtons[i] -> Enable(toEnable[i] && numBrackets > 0);
        }
        else 
        {
            opButtons[i] -> Enable(toEnable[i]);  
        }  
             
    }
}

void Interface :: SetNumButtonsEnable(bool isEnabled) 
{
    for (int i = 0; i < 10; i++) 
    {
        wxButton *numButton = numButtons[i];
        numButton -> Enable(isEnabled);
    }
}

void Interface :: ResetButtons() 
{
    SetNumButtonsEnable(true);
    SetOpButtonsEnable(initialEnable);

    pointButtonPointer -> Enable(false);
    eqButtonPointer -> Enable(false);
}