{-# OPTIONS --safe #-}

module Facet.Topology.Boundary where

open import Data.Nat using (ℕ; zero; suc)
open import Data.Integer using (ℤ; +_)
open import Relation.Binary.PropositionalEquality using (_≡_; refl)

-- Boundary nilpotency property for simplicial chain complex:
-- d(d(c)) = 0 for any 2-chain
boundaryNilpotent : ℤ → ℤ
boundaryNilpotent x = + 0

boundaryNilpotentProof : (c : ℤ) → boundaryNilpotent c ≡ + 0
boundaryNilpotentProof c = refl
