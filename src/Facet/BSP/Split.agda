{-# OPTIONS --safe #-}

module Facet.BSP.Split where

open import Data.List using (List; []; _∷_)
open import Data.Product using (_×_; _,_)
open import Facet.Core.Plane
open import Facet.Geometry.Polygon

record SplitResult : Set where
  constructor splitResult
  field
    frontParts : List Polygon
    backParts  : List Polygon

splitPolygon : Plane → Polygon → SplitResult
splitPolygon pl p = splitResult (p ∷ []) []
