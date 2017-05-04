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
#include "IStringStream.H"
#include "tmp.H"
#include "surfaceInterpolationScheme.H"

using namespace Foam;

namespace Test
{

TEST_CASE("cubicFit_interpolates_constant_scalar_field")
{
	const Foam::Time runTime
    (
        Foam::Time::controlDictName,
        "resources",
        "cartesian4x3Mesh"
    );

	const Foam::fvMesh mesh
	(
		Foam::IOobject
		(
			Foam::fvMesh::defaultRegion,
			runTime.constant(),
			runTime,
			Foam::IOobject::MUST_READ
		)
	);

    const surfaceVectorField Uf
    (
		Foam::IOobject
		(
			"Uf",
			runTime.constant(),
		    mesh,
			Foam::IOobject::MUST_READ
		),
        mesh
    );

    const surfaceScalarField phi = Uf & mesh.Sf();

    const volScalarField T
    (
		Foam::IOobject
		(
            "T",
            runTime.timeName(),
            mesh
        ),
        mesh,
        dimensionedScalar("T", dimless, scalar(1))
    );

    IStringStream interpolationSchemeName("cubicFit");
    const tmp<surfaceInterpolationScheme<scalar> > tCubicFit = 
        surfaceInterpolationScheme<scalar>::New
        (
            mesh,
            phi,
            interpolationSchemeName
        );

    const surfaceInterpolationScheme<scalar>& cubicFit = tCubicFit();

    const tmp<surfaceScalarField> Tf = cubicFit.interpolate(T);

    const surfaceScalarField expectedTf
    (
		Foam::IOobject
		(
            "expectedTf",
            runTime.timeName(),
            mesh
        ),
        mesh,
        dimensionedScalar("expectedTf", dimless, scalar(1))
    );

    // TODO replace checkEqual with a Catch matcher
    // see https://github.com/philsquared/Catch/blob/master/docs/matchers.md
    Test::checkEqual(Tf(), expectedTf);
}

TEST_CASE("cubicFit_averages_stencil_values")
{
	const Foam::Time runTime
    (
        Foam::Time::controlDictName,
        "resources",
        "cartesian4x3Mesh"
    );

	const Foam::fvMesh mesh
	(
		Foam::IOobject
		(
			Foam::fvMesh::defaultRegion,
			runTime.constant(),
			runTime,
			Foam::IOobject::MUST_READ
		)
	);

    const Test::mesh testMesh(mesh);

    const surfaceVectorField Uf
    (
		Foam::IOobject
		(
			"Uf",
			runTime.constant(),
		    mesh,
			Foam::IOobject::MUST_READ
		),
        mesh
    );

    const surfaceScalarField phi = Uf & mesh.Sf();

    volScalarField T
    (
		Foam::IOobject
		(
            "T",
            runTime.timeName(),
            mesh
        ),
        mesh,
        dimensionedScalar("T", dimless, scalar(0))
    );

    forAll(T, cellI)
    {
        T[cellI] = 3*mesh.C()[cellI].x() + 4;
    }

    IStringStream interpolationSchemeName("cubicFit");
    const tmp<surfaceInterpolationScheme<scalar> > tCubicFit =
        surfaceInterpolationScheme<scalar>::New
        (
            mesh,
            phi,
            interpolationSchemeName
        );

    const surfaceInterpolationScheme<scalar>& cubicFit = tCubicFit();

    const tmp<surfaceScalarField> Tf = cubicFit.interpolate(T);

    const label faceI = testMesh.indexOfFaceWithCentreAt(point(3, 1.5, 0));
	CHECK(Tf()[faceI] == Test::approx(10.0));
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Test

// ************************************************************************* //
