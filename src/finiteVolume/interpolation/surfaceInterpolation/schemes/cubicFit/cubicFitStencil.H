/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2017 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::cubicFitStencil

Description
    Models a stencil geometry in the mesh coordinate system or a
    coordinate system local to the stencil.  The origin of the stencil is the
    interpolation face centre.

SourceFiles
    cubicFitStencil.C

\*---------------------------------------------------------------------------*/

#ifndef cubicFitStencil_H
#define cubicFitStencil_H

#include "cubicFitBasis.H"
#include "List.H"
#include "point.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


/*---------------------------------------------------------------------------*\
                         Class cubicFitStencil Declaration
\*---------------------------------------------------------------------------*/

class cubicFitStencil
{
    // Private data

        point origin_;
        List<point> points_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        cubicFitStencil(const cubicFitStencil&);

        //- Disallow default bitwise assignment
        void operator=(const cubicFitStencil&);


public:

    // Constructors

        //- Construct from components
        cubicFitStencil
        (
            const point& origin,
            const List<point>& points
        );


    // Member Functions

        void transform(const cubicFitBasis& basis);

        // Access
        // Check
        // Edit
        // Write

    // Member Operators

        const point& operator[](int i) const;

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
