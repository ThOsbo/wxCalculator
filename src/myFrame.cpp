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
    wxGridSizer *opsSizer = new wxGridSizer(2, 2, 5, 5);

    wxFont font(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    displayWindow = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 10), wxSize(X_MAIN_FRAME_DIMENSION, 50), wxTE_READONLY);
    displayWindow -> SetFont(font);

    displaySizer -> Add(displayWindow, 0, wxEXPAND | wxALL, 5);

    for (int i = 1; i <= 10; i++) 
    {
        wxButton *numButton = new wxButton(this, 2000 + i, std :: to_string(i % 10), wxPoint(0, 0), wxSize(40, 40));
        numButton -> SetFont(font);
        numButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, MyFrame :: OnNumButtonClick, this);

        numbersSizer -> Add(numButton, 1, wxEXPAND | wxALL, 2.5); 
                      
    }

    controlSizer -> Add(numbersSizer, 1, wxEXPAND | wxALL, 5);

    //std :: string operations [4] = {"+", "-", "x", "/"};

    for (int i = 0; i < 4; i++) 
    {
        wxButton *opButton = new wxButton(this, 3000 + i, operations[i], wxPoint(0, 0), wxSize(40, 40));
        opButton -> SetFont(font);
        opButton -> Bind(wxEVT_COMMAND_BUTTON_CLICKED, MyFrame :: OnOpButtonClick, this);

        opsSizer -> Add(opButton, 1, wxEXPAND | wxALL, 2.5);
    }

    controlSizer -> Add(opsSizer, 1, wxEXPAND | wxALL, 5);

    displaySizer -> Add(controlSizer, 1, wxEXPAND | wxALL, 5);

    this -> SetSizer(displaySizer);
    this -> Layout();
}

void MyFrame :: OnNumButtonClick(wxCommandEvent &evt) 
{
    int numClicked = (evt.GetId() - 2000) % 10;
    displayWindow -> AppendText(std :: to_string(numClicked));
}

void MyFrame :: OnOpButtonClick(wxCommandEvent &evt) 
{
    int opClicked = evt.GetId() - 3000;
    displayWindow -> AppendText(operations[opClicked]);
}