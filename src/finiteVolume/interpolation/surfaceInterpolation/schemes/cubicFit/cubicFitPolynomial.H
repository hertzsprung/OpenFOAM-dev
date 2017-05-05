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
    Foam::cubicFitPolynomial

Description

SourceFiles
    cubicFitPolynomial.C

\*---------------------------------------------------------------------------*/

#ifndef cubicFitPolynomial_H
#define cubicFitPolynomial_H

#include "cubicFitStencil.H"
#include "List.H"
#include "point.H"
#include "scalarList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class cubicFitPolynomial Declaration
\*---------------------------------------------------------------------------*/

class cubicFitPolynomial
{
    // Private data

        //- Description of data_
//        dataType data_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        cubicFitPolynomial(const cubicFitPolynomial&);

        //- Disallow default bitwise assignment
        void operator=(const cubicFitPolynomial&);


public:

    // Constructors

        cubicFitPolynomial();

    // Member Functions

        void fitTo
        (
            const cubicFitStencil& stencil,
            scalarList& weights
        ) const;

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
