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

\*---------------------------------------------------------------------------*/

#include "cubicFitWeights.H"

#include "cubicFitPolynomial.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::cubicFitWeights::fit
(
    const List<List<point>>& stencilGeometries,
    List<scalarList>& weights
)
{
    for (label faceI = 0; faceI < mesh_.nInternalFaces(); faceI++)
    {
        const cubicFitPolynomial polynomial;
        cubicFitStencil stencil(mesh_.Cf()[faceI], stencilGeometries[faceI]);
        const cubicFitBasis basis
        (
            vector(1, 0, 0),
            vector(0, 1, 0),
            vector(0, 0, 1)
        );
        stencil.transform(basis);

        polynomial.fitTo(stencil, weights[faceI]);
    }

    // TODO: calculate weights for faces on coupled boundaries
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::cubicFitWeights::cubicFitWeights
(
    const fvMesh& mesh,
    const extendedUpwindCellToFaceStencil& stencil
)
:
mesh_(mesh),
ownerWeights_(mesh.nFaces()),
neighbourWeights_(mesh.nFaces())
{
    List<List<point> > stencilGeometries(mesh.nFaces());

    stencil.collectData
    (
        stencil.ownMap(),
        stencil.ownStencil(),
        mesh.C(),
        stencilGeometries
    );
    fit(stencilGeometries, ownerWeights_);

    stencil.collectData
    (
        stencil.neiMap(),
        stencil.neiStencil(),
        mesh.C(),
        stencilGeometries
    );
    fit(stencilGeometries, neighbourWeights_);
}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //


// ************************************************************************* //
