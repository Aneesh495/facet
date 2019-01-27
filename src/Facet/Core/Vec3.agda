{-# OPTIONS --safe #-}

module Facet.Core.Vec3 where

open import Data.Nat using (ℕ; zero; suc)
open import Data.Integer using (ℤ; +_)
open import Data.Bool using (Bool; true; false; _∧_)
open import Facet.Core.Exact

record Vec3 : Set where
  constructor vec3
  field
    x : Rat
    y : Rat
    z : Rat

-- Standard basis vectors
vecZero : Vec3
vecZero = vec3 ratZero ratZero ratZero

vecX : Vec3
vecX = vec3 ratOne ratZero ratZero

vecY : Vec3
vecY = vec3 ratZero ratOne ratZero

vecZ : Vec3
vecZ = vec3 ratZero ratZero ratOne

-- Vector addition
_+ᵥ_ : Vec3 → Vec3 → Vec3
(vec3 x₁ y₁ z₁) +ᵥ (vec3 x₂ y₂ z₂) =
  vec3 (x₁ +ᵣ x₂) (y₁ +ᵣ y₂) (z₁ +ᵣ z₂)

-- Vector subtraction
_-ᵥ_ : Vec3 → Vec3 → Vec3
(vec3 x₁ y₁ z₁) -ᵥ (vec3 x₂ y₂ z₂) =
  vec3 (x₁ -ᵣ x₂) (y₁ -ᵣ y₂) (z₁ -ᵣ z₂)

-- Scalar multiplication
_*ᵥ_ : Rat → Vec3 → Vec3
s *ᵥ (vec3 x y z) =
  vec3 (s *ᵣ x) (s *ᵣ y) (s *ᵣ z)

-- Vector negation
-ᵥ_ : Vec3 → Vec3
-ᵥ v = (-ᵣ ratOne) *ᵥ v

-- Dot product
_∙_ : Vec3 → Vec3 → Rat
(vec3 x₁ y₁ z₁) ∙ (vec3 x₂ y₂ z₂) =
  (x₁ *ᵣ x₂) +ᵣ (y₁ *ᵣ y₂) +ᵣ (z₁ *ᵣ z₂)

-- Cross product
_×_ : Vec3 → Vec3 → Vec3
(vec3 x₁ y₁ z₁) × (vec3 x₂ y₂ z₂) =
  vec3
    (det2x2 y₁ z₁ y₂ z₂)
    (det2x2 z₁ x₁ z₂ x₂)
    (det2x2 x₁ y₁ x₂ y₂)

-- Squared Euclidean norm (exact rational)
normSq : Vec3 → Rat
normSq v = v ∙ v

-- Exact equality check for vectors
isZeroVec : Vec3 → Bool
isZeroVec (vec3 x y z) = isZero x ∧ isZero y ∧ isZero z

-- Collinearity check: two vectors are collinear iff their cross product is zero
isCollinear : Vec3 → Vec3 → Vec3 → Bool
isCollinear a b c =
  let ab = b -ᵥ a
      ac = c -ᵥ a
  in isZeroVec (ab × ac)
