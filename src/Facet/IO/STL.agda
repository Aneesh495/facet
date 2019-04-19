{-# OPTIONS --safe #-}

module Facet.IO.STL where

open import Data.List using (List; []; _∷_)
open import Facet.Core.Vec3

record STLFacet : Set where
  constructor stlFacet
  field
    normal : Vec3
    v1     : Vec3
    v2     : Vec3
    v3     : Vec3

record STLSolid : Set where
  constructor stlSolid
  field
    facets : List STLFacet
