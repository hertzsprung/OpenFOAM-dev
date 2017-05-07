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
    Foam::cubicFitBasis

Description
    A three-dimensional basis that defines the local coordinate system
    for a particular stencil.

SourceFiles
    cubicFitBasis.C

\*---------------------------------------------------------------------------*/

#ifndef cubicFitBasis_H
#define cubicFitBasis_H

#include "vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class cubicFitBasis Declaration
\*---------------------------------------------------------------------------*/

class cubicFitBasis
{
    // Private data

        vector i_;
        vector j_;
        vector k_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        cubicFitBasis(const cubicFitBasis&);

        //- Disallow default bitwise assignment
        void operator=(const cubicFitBasis&);


public:

        //- Construct a default basis with i/j/k unit vectors aligned with
        // the Cartesian coordinate system of the mesh
        cubicFitBasis();

        //- Construct a basis from specified vectors.
        // The user must ensure the vectors are orthogonal.
        cubicFitBasis
        (
            const vector& i,
            const vector& j,
            const vector& k
        );


    // Member Functions

        const vector& i() const;
        const vector& j() const;
        const vector& k() const;

        vector& i();
        vector& j();
        vector& k();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
