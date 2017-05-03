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
#include "IStringStream.H"
#include "tmp.H"
#include "surfaceInterpolationScheme.H"

namespace Foam
{

TEST_CASE("cubicFit_has_zero_correction_on_upwind")
{
	const Foam::Time runTime(Foam::Time::controlDictName, "resources", "cartesian4x3Mesh");
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

    IStringStream interpolationSchemeName("cubicFit");
    const tmp<surfaceInterpolationScheme<scalar> > tCubicFit = surfaceInterpolationScheme<scalar>::New(mesh, interpolationSchemeName);
    const surfaceInterpolationScheme<scalar>& cubicFit = tCubicFit();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
