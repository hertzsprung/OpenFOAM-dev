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
#include "mesh.H"
#include "interpolation.H"

#include "IOobject.H"
#include "IStringStream.H"
#include "tmp.H"
#include "surfaceInterpolationScheme.H"

using namespace Foam;

namespace Test
{

TEST_CASE("cubicFit_interpolates_constant_scalar_field")
{
    Test::interpolation cubicFit("cartesian4x3Mesh");
    cubicFit.T() = dimensionedScalar("T", dimless, scalar(1));
    const surfaceScalarField expectedTf
    (
        IOobject
        (
            "expectedTf",
            cubicFit.runTime().timeName(),
            cubicFit.mesh()
        ),
        cubicFit.mesh(),
        dimensionedScalar("expectedTf", dimless, scalar(1))
    );

    const tmp<surfaceScalarField> Tf = cubicFit.interpolateT();

    Test::checkEqual(Tf, expectedTf);
}

TEST_CASE("cubicFit_exactly_reconstructs_linear_in_x_for_vertical_face")
{
    Test::interpolation cubicFit("cartesian4x3Mesh");
    const Test::mesh testMesh(cubicFit.mesh());
    forAll(cubicFit.T(), cellI)
    {
        cubicFit.T()[cellI] = 3*cubicFit.mesh().C()[cellI].x() + 4;
    }

    const tmp<surfaceScalarField> Tf = cubicFit.interpolateT();

    const label faceI = testMesh.indexOfFaceWithCentreAt(point(3, 1.5, 0));
    CHECK(Tf()[faceI] == Test::approx(13.0));
}

TEST_CASE("cubicFit_exactly_reconstructs_linear_in_x_for_horizontal_face")
{
    Test::interpolation cubicFit("cartesian3x4Mesh");
    const Test::mesh testMesh(cubicFit.mesh());
    forAll(cubicFit.T(), cellI)
    {
        cubicFit.T()[cellI] = 3*cubicFit.mesh().C()[cellI].y() + 4;
    }

    const tmp<surfaceScalarField> Tf = cubicFit.interpolateT();

    const label faceI = testMesh.indexOfFaceWithCentreAt(point(1.5, 3, 0));
    CHECK(Tf()[faceI] == Test::approx(13.0));
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Test

// ************************************************************************* //
