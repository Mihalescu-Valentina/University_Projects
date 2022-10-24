#include "Protein.h"

Protein::Protein(const string& organism, const string& name, const string& sequence): organism{organism},name{name},sequence{sequence}
{
}

Protein::Protein(): organism{""},name{""},sequence{""}
{
}
