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
    
    wxBoxSizer *frameSizer = new wxBoxSizer(wxVERTICAL);    
    wxBoxSizer *inputSizer = new wxBoxSizer(wxHORIZONTAL);   

    wxFont font(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    //sets and adds the display window to the main frame
    displayWindow = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 10), wxSize(X_MAIN_FRAME_DIMENSION, 50), wxTE_READONLY);
    displayWindow -> SetFont(font);

    frameSizer -> Add(displayWindow, 0, wxEXPAND | wxALL, 5);

    //sets and adds the control buttons
    wxBoxSizer *controlSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFont ctrlFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxButton *shiftButton = new wxButton(this, ctrlStartID, "Shift", wxPoint(0, 0), wxSize(50, 25));
    shiftButton -> SetFont(ctrlFont);
    shiftButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, Interface :: OnShiftButtonClick, this);

    controlSizer -> Add(shiftButton, 1, wxEXPAND | wxALL, 2.5);

    wxButton *delButton = new wxButton(this, ctrlStartID + 1, "Del", wxPoint(0, 0), wxSize(50, 25));
    delButton -> SetFont(ctrlFont);
    delButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, Interface :: OnDelButtonClick, this);

    controlSizer -> Add(delButton, 1, wxEXPAND | wxALL, 2.5);

    wxButton *clearButton = new wxButton(this, ctrlStartID + 2, "Clear", wxPoint(0, 0), wxSize(50, 25));
    clearButton -> SetFont(ctrlFont);
    clearButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, Interface :: OnClearButtonClick, this);

    controlSizer -> Add(clearButton, 1, wxEXPAND | wxALL, 2.5);

    //adds control buttons to main frame
    frameSizer -> Add(controlSizer, 0, wxEXPAND | wxALL, 5);

    //sets and adds the number buttons
    wxGridSizer *numbersSizer = new wxGridSizer(4, 3, 5, 5);

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

    //adds all number buttons to the inputs sizer
    inputSizer -> Add(numbersSizer, 1, wxEXPAND | wxALL, 5);

    //sets and add the operation buttons
    wxGridSizer *opsSizer = new wxGridSizer(ceil((numOfOperations + 1) / 3.0), 3, 5, 5);

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

    wxButton *eqButton = new wxButton(this, opsStartID + 999, equalSymbol, wxPoint(0, 0), wxSize(40, 40));
    eqButton -> SetFont(font);
    eqButton -> Enable(false);
    eqButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, Interface :: OnEqButtonClick, this);

    eqButtonPointer = eqButton;
    opsSizer -> Add(eqButton, 1, wxEXPAND | wxALL, 2.5);

    //adds the operations buttons to the inputs sizer
    inputSizer -> Add(opsSizer, 1, wxEXPAND | wxALL, 5);

    //adds all the input buttons to the main frame
    frameSizer -> Add(inputSizer, 1, wxEXPAND | wxALL, 5);

    this -> SetSizer(frameSizer);
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
        DisplayInput(std :: to_string(numClicked % 10));
    }
    else if (evt.GetId() == pointButtonPointer -> GetId()) 
    {
        SetOpButtonsEnable(pointClickToEnable);
        eqButtonPointer -> Enable(false);
        pointButtonPointer -> Enable(false);
        DisplayInput(pointSymbol);
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
    DisplayInput(operations[opClicked]);

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
    buttonsPressed.clear();
    ResetButtons();
    eqButtonClick = true;

    evt.Skip();
}

void Interface :: OnShiftButtonClick(wxCommandEvent &evt) 
{
    shiftButtonClick != shiftButtonClick;
}

void Interface :: OnDelButtonClick(wxCommandEvent &evt) 
{

}

void Interface :: OnClearButtonClick(wxCommandEvent &evt) 
{
    displayWindow -> Clear();
    buttonsPressed.clear();
    ResetButtons();
}

void Interface :: SetButtonsEnable(int buttonID) 
{
    
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

void Interface :: DisplayInput(wxString toDisplay) 
{
    displayWindow -> AppendText(toDisplay);
    buttonsPressed.push_back(toDisplay);
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