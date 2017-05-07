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
    Foam::cubicFitStencilOrientation

Description
    Pure virtual abstract base class for orienting stencils.

SourceFiles
    cubicFitStencilOrientationI.H

\*---------------------------------------------------------------------------*/

#ifndef cubicFitStencilOrientation_H
#define cubicFitStencilOrientation_H

#include "cubicFitBasis.H"
#include "cubicFitStencil.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class cubicFitStencil;

/*---------------------------------------------------------------------------*\
                         Class cubicFitStencilOrientation Declaration
\*---------------------------------------------------------------------------*/

class cubicFitStencilOrientation
{

    // Private Member Functions

        //- Disallow default bitwise copy construct
        cubicFitStencilOrientation(const cubicFitStencilOrientation&);

        //- Disallow default bitwise assignment
        void operator=(const cubicFitStencilOrientation&);


public:
    // Constructors

        cubicFitStencilOrientation() {};

    //- Destructor
        virtual ~cubicFitStencilOrientation() = 0;

    // Member Functions

        virtual void orient
        (
            const cubicFitStencil& stencil,
            cubicFitBasis& basis
        ) const = 0;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "cubicFitStencilOrientationI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
