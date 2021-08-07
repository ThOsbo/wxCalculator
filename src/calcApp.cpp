#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <calcInterface.h>

class CalcApp : public wxApp 
{
    public :
        virtual bool OnInit();
};

wxIMPLEMENT_APP(CalcApp);

bool CalcApp :: OnInit() 
{
    Interface *frame = new Interface();
    frame -> Show(true);
    return true;
}