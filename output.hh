#ifndef output_hh
#define output_hh

#include "bottom.hh"

class Output
{
private:
    TString output;

public:
    void add(const TString &s, TStringIndex ov);

    TString get() const;
};

inline TString Output::get() const
{
    return output;
}

#endif
