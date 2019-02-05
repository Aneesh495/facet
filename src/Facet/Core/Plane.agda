{-# OPTIONS --safe #-}

module Facet.Core.Plane where

open import Data.Bool using (Bool; true; false)
open import Facet.Core.Exact
open import Facet.Core.Vec3

record Plane : Set where
  constructor plane
  field
    normal : Vec3
    dist   : Rat

data SpatialSide : Set where
  Front   : SpatialSide
  Back    : SpatialSide
  OnPlane : SpatialSide

signedDistance : Plane → Vec3 → Rat
signedDistance (plane n d) p = (n ∙ p) -ᵣ d

classifyPoint : Plane → Vec3 → SpatialSide
classifyPoint pl p =
  let d = signedDistance pl p
  in case isZero d of λ
    { true  → OnPlane
    ; false → case isPositive d of λ
      { true  → Front
      ; false → Back
      }
    }
  where
    case_of_ : ∀ {a b} {A : Set a} {B : Set b} → A → (A → B) → B
    case x of f = f x

fromPoints : Vec3 → Vec3 → Vec3 → Plane
fromPoints a b c =
  let ab = b -ᵥ a
      ac = c -ᵥ a
      n  = ab × ac
      d  = n ∙ a
  in plane n d

invertPlane : Plane → Plane
invertPlane (plane n d) = plane (-ᵥ n) (-ᵣ d)
