{-# OPTIONS --safe #-}

module Facet.BSP.Properties where

open import Relation.Binary.PropositionalEquality using (_≡_; refl)
open import Facet.Core.Plane
open import Facet.BSP.Tree
open import Facet.BSP.Boolean

-- Inversion involution theorem: invert (invert Leaf) = Leaf
invertLeafFrontInv : invertTree (invertTree (BSPLeaf Front)) ≡ BSPLeaf Front
invertLeafFrontInv = refl

invertLeafBackInv : invertTree (invertTree (BSPLeaf Back)) ≡ BSPLeaf Back
invertLeafBackInv = refl
