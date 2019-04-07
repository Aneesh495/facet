{-# OPTIONS --safe #-}

module Facet.BSP.Boolean where

open import Data.List using (List; []; _∷_)
open import Facet.Core.Plane
open import Facet.Geometry.Polygon
open import Facet.BSP.Tree

-- Invert BSP tree: swaps Front and Back leaves, and flips node planes
invertTree : BSPTree → BSPTree
invertTree (BSPLeaf Front) = BSPLeaf Back
invertTree (BSPLeaf Back)  = BSPLeaf Front
invertTree (BSPLeaf OnPlane) = BSPLeaf OnPlane
invertTree (BSPNode pl polys front back) =
  BSPNode (invertPlane pl) polys (invertTree back) (invertTree front)
