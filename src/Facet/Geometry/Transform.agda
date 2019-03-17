{-# OPTIONS --safe #-}

module Facet.Geometry.Transform where

open import Facet.Core.Exact
open import Facet.Core.Vec3
open import Facet.Core.Mat3
open import Facet.Geometry.Polygon
open import Facet.Geometry.Polyhedron

-- Rigid translation
translateVec : Vec3 → Vec3 → Vec3
translateVec t v = v +ᵥ t

-- Transform vector by matrix and translation
transformPoint : Mat3 → Vec3 → Vec3 → Vec3
transformPoint m t p = (m ⊛ p) +ᵥ t
