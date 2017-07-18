#pragma once
#ifndef __WORLD__
#define __WORLD__

typedef float amount;

class BaseCell {
    amount oxygen;
    amount hydrogen;
    // not
    // exist at gas, liquid, solid, temp? objects?
    // atmosphere sim
    // TODO Need clear requirements!
};

class EnergySpace {
    // Oxygen, Hydrogen, Carbon, Nitrogen...
    // algae make starch, use chlorophyll

    // in cells of world exist oxygen etc materials in amount

    public:
        EnergySpace() {}
};

class World {

    public:
        EnergySpace e;
        World() {}
};

#endif
