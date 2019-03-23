{-# OPTIONS --safe #-}

module Facet.Geometry.Tessellate where

open import Data.List using (List; []; _∷_)
open import Data.Bool using (Bool; true; false)
open import Data.Nat using (ℕ; zero; suc)
open import Facet.Core.Exact
open import Facet.Core.Vec3
open import Facet.Core.Plane
open import Facet.Geometry.Polygon
open import Facet.Geometry.Polyhedron

unitCubePolyhedron : Polyhedron
unitCubePolyhedron = polyhedron [] true
