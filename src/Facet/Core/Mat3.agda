{-# OPTIONS --safe #-}

module Facet.Core.Mat3 where

open import Data.Bool using (Bool)
open import Facet.Core.Exact
open import Facet.Core.Vec3

-- 3x3 matrix represented by three row vectors
record Mat3 : Set where
  constructor mat3
  field
    row0 : Vec3
    row1 : Vec3
    row2 : Vec3

-- Identity matrix
matIdentity : Mat3
matIdentity = mat3 vecX vecY vecZ

-- Zero matrix
matZero : Mat3
matZero = mat3 vecZero vecZero vecZero

-- Matrix-vector multiplication (M * v)
_⊛_ : Mat3 → Vec3 → Vec3
(mat3 r0 r1 r2) ⊛ v =
  vec3 (r0 ∙ v) (r1 ∙ v) (r2 ∙ v)

-- Matrix transpose
transpose : Mat3 → Mat3
transpose (mat3 (vec3 a b c) (vec3 d e f) (vec3 g h i)) =
  mat3 (vec3 a d g) (vec3 b e h) (vec3 c f i)

-- Exact determinant of 3x3 matrix
detMat3 : Mat3 → Rat
detMat3 (mat3 (vec3 a b c) (vec3 d e f) (vec3 g h i)) =
  det3x3 a b c d e f g h i

-- Scaling matrix
matScale : Rat → Mat3
matScale s = mat3 (s *ᵥ vecX) (s *ᵥ vecY) (s *ᵥ vecZ)
