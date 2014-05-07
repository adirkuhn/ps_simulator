#ifndef SWITCHH_H
#define SWITCHH_H

#include <Switch.h>
#include <LD.h>

class SwitchH: public Switch
{
    public:
        LD ld;
        SwitchH();
};

#endif // SWITCHH_H
