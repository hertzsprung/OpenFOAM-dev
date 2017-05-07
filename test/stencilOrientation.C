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

#include "stencilOrientation.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Test::stencilOrientation::stencilOrientation
(
    const vector& i,
    const vector& j,
    const vector& k
)
:
i_(i),
j_(j),
k_(k)
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Test::stencilOrientation::~stencilOrientation()
{}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Test::stencilOrientation::orient
(
    const cubicFitStencil& stencil,
    cubicFitBasis& basis
) const
{
    basis.i() = i_;
    basis.j() = j_;
    basis.k() = k_;
}

// ************************************************************************* //
