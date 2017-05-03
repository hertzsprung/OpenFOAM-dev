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
    Foam::cubicFit

Description

SourceFiles
    cubicFit.C

\*---------------------------------------------------------------------------*/

#ifndef cubicFit_H
#define cubicFit_H

#include "upwind.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes
//class Istream;
//class Ostream;

// Forward declaration of friend functions and operators
//class cubicFit;
//Istream& operator>>(Istream&, cubicFit&);
//Ostream& operator<<(Ostream&, const cubicFit&);


/*---------------------------------------------------------------------------*\
                         Class cubicFit Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class cubicFit
:
    public upwind<Type>
{
    // Private data

        //- Description of data_
//        dataType data_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        cubicFit(const cubicFit&);

        //- Disallow default bitwise assignment
        void operator=(const cubicFit&);


public:

    //- Runtime type information
    TypeName("cubicFit");


    // Constructors

        cubicFit(const fvMesh& mesh, Istream& is)
        :
            upwind<Type>
            (
                mesh,
                mesh.lookupObject<surfaceScalarField>(word(is))
            )
        {}

        cubicFit
        (
            const fvMesh& mesh,
            const surfaceScalarField& faceFlux,
            Istream& is
        )
        :
            upwind<Type>(mesh, faceFlux)
        {}


    // Member Functions
        //- Return true if this scheme uses an explicit correction
        virtual bool corrected() const
        {
            return true;
        }

        //- Return the explicit correction to the face-interpolate
        virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
        correction
        (
            const GeometricField<Type, fvPatchField, volMesh>& vf
        ) const
        {
            const fvMesh& mesh = this->mesh();
            tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsfCorr
            (
                new GeometricField<Type, fvsPatchField, surfaceMesh>
                (
                    IOobject
                    (
                        vf.name(),
                        mesh.time().timeName(),
                        mesh,
                        IOobject::NO_READ,
                        IOobject::NO_WRITE,
                        false
                    ),
                    mesh,
                    dimensioned<Type>
                    (
                        vf.name(),
                        vf.dimensions(),
                        Zero
                    )
                )
            );

            return tsfCorr;
        }

        // Access
        // Check
        // Edit
        // Write


    // IOstream Operators

//        friend Istream& operator>>(Istream&, cubicFit&);
//        friend Ostream& operator<<(Ostream&, const cubicFit&);
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
