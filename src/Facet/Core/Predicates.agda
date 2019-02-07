{-# OPTIONS --safe #-}

module Facet.Core.Predicates where

open import Data.Bool using (Bool; true; false)
open import Facet.Core.Exact
open import Facet.Core.Vec3
open import Facet.Core.Mat3

data Orientation : Set where
  OrientPositive : Orientation
  OrientNegative : Orientation
  OrientCoplanar : Orientation

orient3dExact : Vec3 → Vec3 → Vec3 → Vec3 → Rat
orient3dExact a b c d =
  let ab = b -ᵥ a
      ac = c -ᵥ a
      ad = d -ᵥ a
  in ab ∙ (ac × ad)

classifyOrient3d : Vec3 → Vec3 → Vec3 → Vec3 → Orientation
classifyOrient3d a b c d =
  let det = orient3dExact a b c d
  in case isZero det of λ
    { true  → OrientCoplanar
    ; false → case isPositive det of λ
      { true  → OrientPositive
      ; false → OrientNegative
      }
    }
  where
    case_of_ : ∀ {a b} {A : Set a} {B : Set b} → A → (A → B) → B
    case x of f = f x
