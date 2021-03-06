//////////////////////////////// -*- C++ -*- //////////////////////////////
//
// AUTHOR
//    Peter Shirley, Cornell University, shirley@graphics.cornell.edu 
//
// COPYRIGHT
//    Copyright (c) 1995  Peter Shirley. All rights reserved.
//
//    Permission to use, copy, modify, and distribute this software for any
//    purpose without fee is hereby granted, provided that this entire
//    notice is included in all copies of any software which is or includes
//    a copy or modification of this software and in all copies of the
//    a copy or modification of this software and in all copies of the
//    supporting documentation for such software.
//
// DISCLAIMER
//    Neither the Peter Shirley nor Cornell nor any of their
//    employees, makes any warranty, express or implied, or assumes any
//    liability or responsibility for the accuracy, completeness, or
//    usefulness of any information, apparatus, product, or process
//    disclosed, or represents that its use would not infringe
//    privately-owned rights.  
//
///////////////////////////////////////////////////////////////////////////



#ifndef GGCOOKSAMPLE3_H
#define GGCOOKSAMPLE3_H

#include <ggSample2.h>
#include <ggSample3.h>

class ggCookSample3 : public ggSample3 {
public:
    ggCookSample3() { iData = 0; zData = 0;}
    ggCookSample3(int N);
    virtual int Generate(); 
    virtual void SetN(const int&, const int&);
    virtual ggPoint3 getPoint(int num) const;
protected:
    int *iData, *zData;
    int nx, ny;
    int nxTimesNy;
    double dx, dy, dz;
  };

#endif
