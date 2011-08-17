#include "output.hh"

void Output::add(const TString &s, TStringIndex ov)
{
    TString t(s.begin() + ov, s.end());
    output += t;
}
