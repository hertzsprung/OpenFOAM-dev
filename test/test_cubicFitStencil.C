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
#include "stencilOrientation.H"

#include "cubicFitBasis.H"
#include "cubicFitStencil.H"

using namespace Foam;

namespace Test
{

TEST_CASE("cubicFitStencil_translates_and_rescales")
{
    const Test::stencilOrientation orientation
    (
        vector(1, 0, 0),
        vector(0, 1, 0),
        vector(0, 0, 1)
    );

    const point origin(8, 0, 0);

    List<point> points(2);
    points[0] = point(5, 0, 0);
    points[1] = point(9, 0, 0);

    List<point> expectedTransformedPoints(2);
    expectedTransformedPoints[0] = point(-1, 0, 0);
    expectedTransformedPoints[1] = point(1.0/3.0, 0, 0);

    const cubicFitStencil expectedTransformedStencil(point(0, 0, 0), expectedTransformedPoints);

    cubicFitStencil actualStencil(origin, points);
    actualStencil.transform(orientation);

    CHECK(actualStencil[0].x() == approx(expectedTransformedStencil[0].x()));
    CHECK(actualStencil[1].x() == approx(expectedTransformedStencil[1].x()));
}

TEST_CASE("cubicFitStencil_translates_rescales_and_rotates_90_degrees")
{
    const Test::stencilOrientation orientation
    (
        vector(0, 1, 0),
        vector(-1, 0, 0),
        vector(0, 0, 1)
    );

    const point origin(0, 4, 0);

    List<point> points(2);
    points[0] = point(0, 2, 0);
    points[1] = point(0, 5, 0);

    List<point> expectedTransformedPoints(2);
    expectedTransformedPoints[0] = point(-1, 0, 0);
    expectedTransformedPoints[1] = point(0.5, 0, 0);

    const cubicFitStencil expectedTransformedStencil(point(0, 0, 0), expectedTransformedPoints);

    cubicFitStencil actualStencil(origin, points);
    actualStencil.transform(orientation);

    CHECK(actualStencil[0].x() == approx(expectedTransformedStencil[0].x()));
    CHECK(actualStencil[1].x() == approx(expectedTransformedStencil[1].x()));
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Test

// ************************************************************************* //
