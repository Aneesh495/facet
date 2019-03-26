{-# OPTIONS --safe #-}

module Facet.BSP.Tree where

open import Data.List using (List; []; _∷_)
open import Facet.Core.Plane
open import Facet.Geometry.Polygon

data BSPTree : Set where
  BSPLeaf : SpatialSide → BSPTree
  BSPNode : Plane → List Polygon → BSPTree → BSPTree → BSPTree
