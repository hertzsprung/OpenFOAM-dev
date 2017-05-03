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
    Foam::checks

Description
    A collection of assertions for use in the Catch test suite

SourceFiles

\*---------------------------------------------------------------------------*/

#ifndef checks_H
#define checks_H

#include "GeometricField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Test
{

    template<template<class> class PatchField, class GeoMesh>
    void checkEqual
    (
        const Foam::GeometricField<Foam::scalar, PatchField, GeoMesh>& actual,
        const Foam::GeometricField<Foam::scalar, PatchField, GeoMesh>& expected,
        Approx approx = Approx::custom().epsilon(1e-12)
    )
    {
        forAll(actual, faceI)
        {
            CHECK(actual[faceI] == approx(expected[faceI]));
            // TODO: check boundary values?
        }
    }

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
