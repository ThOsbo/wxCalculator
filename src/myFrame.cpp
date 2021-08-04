#include <myFrame.h>

MyFrame :: MyFrame() : wxFrame(NULL, wxID_ANY, "Calculator", wxPoint(10, 10), wxSize(400, 600)) 
{
    wxBoxSizer *displaySizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *controlSizer = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer *numbersSizer = new wxGridSizer(3, 3, 5, 5);
    wxGridSizer *opsSizer = new wxGridSizer(2, 2, 5, 5);

    displayWindow = new wxTextCtrl(this, wxID_ANY, "Hello", wxPoint(10, 10), wxSize(400, 50), wxTE_READONLY);

    displaySizer -> Add(displayWindow, 0.25, wxEXPAND | wxALIGN_TOP, 10);

    for (int i = 1; i <= 9; i++) 
    {
        wxButton *numButton = new wxButton(this, wxID_ANY);
        numButton -> SetLabel(std :: to_string(i));
        numbersSizer -> Add(numButton, 1, wxEXPAND);               
    }

    controlSizer -> Add(numbersSizer, 0.5, wxEXPAND | wxALIGN_LEFT);

    std :: string operations [4] = {"+", "-", "x", "/"};

    for (int i = 0; i < 4; i++) 
    {
        wxButton *opButton = new wxButton(this, wxID_ANY);
        opButton -> SetLabel(operations[i]);
        opsSizer -> Add(opButton, 1, wxEXPAND);
    }

    controlSizer -> Add(opsSizer, 0.5, wxEXPAND);

    displaySizer -> Add(controlSizer, 0.75, wxEXPAND);

    this -> SetSizer(displaySizer);
    this -> Layout();
}