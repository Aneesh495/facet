{-# OPTIONS --safe #-}

module Facet.Geometry.Polyhedron where

open import Data.List using (List; []; _∷_)
open import Data.Bool using (Bool)
open import Facet.Geometry.Polygon

record Polyhedron : Set where
  constructor polyhedron
  field
    faces    : List Polygon
    isClosed : Bool
