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
    Foam::cubicFitWeights

Description
    Generates owner and neighbour weights for a given
    extendedUpwindCellToFaceStencil

SourceFiles
    cubicFitWeights.C

\*---------------------------------------------------------------------------*/

#ifndef cubicFitWeights_H
#define cubicFitWeights_H

#include "fvMesh.H"
#include "extendedUpwindCellToFaceStencil.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class cubicFitWeights Declaration
\*---------------------------------------------------------------------------*/

class cubicFitWeights
{
    // Private data

        const fvMesh& mesh_;

        //- A list of stencil weights for each internal face with faceFlux
        // from the owner side
        List<scalarList> ownerWeights_;

        //- A list of stencil weights for each internal face with faceFlux
        // from the neighbour side
        List<scalarList> neighbourWeights_;


    // Private Member Functions

        void fit
        (
            const List<List<point>>& stencilGeometries,
            List<scalarList>& weights
        );

        //- Disallow default bitwise copy construct
        cubicFitWeights(const cubicFitWeights&);

        //- Disallow default bitwise assignment
        void operator=(const cubicFitWeights&);


public:

    // Constructors

        cubicFitWeights
        (
            const fvMesh& mesh,
            const extendedUpwindCellToFaceStencil& stencil
        );


    // Member Functions

        const List<scalarList>& owner() const
        {
            return ownerWeights_;
        }

        const List<scalarList>& neighbour() const
        {
            return neighbourWeights_;
        }

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
