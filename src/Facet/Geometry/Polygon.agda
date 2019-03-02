{-# OPTIONS --safe #-}

module Facet.Geometry.Polygon where

open import Data.List using (List; []; _∷_)
open import Data.Nat using (ℕ; zero; suc)
open import Facet.Core.Exact
open import Facet.Core.Vec3
open import Facet.Core.Plane

record Polygon : Set where
  constructor polygon
  field
    vertices : List Vec3
    planeRef : Plane
