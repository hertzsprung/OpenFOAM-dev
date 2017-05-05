/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2016 OpenFOAM Foundation
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

#include "catch.hpp"
#include "checks.H"

#include "cubicFitPolynomial.H"
#include "cubicFitStencil.H"
#include "List.H"
#include "point.H"
#include "scalarList.H"

using namespace Foam;

namespace Test
{

TEST_CASE("cubicFitPolynomial_has_equal_weights_for_constant_polynomial")
{
    List<point> stencilPoints(2);
    stencilPoints[0] = point(-1, 0, 0);
    stencilPoints[1] = point(1, 0, 0);

    const cubicFitStencil stencil(point(0, 0, 0), stencilPoints);

    scalarList actualWeights;

    const cubicFitPolynomial polynomial;
    polynomial.fitTo(stencil, actualWeights);

    scalarList expectedWeights(2);
    expectedWeights[0] = -0.5;
    expectedWeights[1] = 0.5;

    checkEqual(actualWeights, expectedWeights);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Test

// ************************************************************************* //
