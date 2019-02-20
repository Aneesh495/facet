{-# OPTIONS --safe #-}

module Facet.Topology.Euler where

open import Data.Nat using (ℕ; zero; suc; _+_; _*_)
open import Data.Integer using (ℤ; +_; -[1+_]; _+_; _*_) renaming (-_ to -ℤ_)
open import Relation.Binary.PropositionalEquality using (_≡_; refl)

-- Euler-Poincare characteristic for closed 2-manifolds of genus g:
-- chi = V - E + F = 2 * (1 - g)
-- For sphere (genus 0): chi = 2
eulerCharacteristic : ℕ → ℕ → ℕ → ℤ
eulerCharacteristic v e f =
  let vZ = + v
      eZ = + e
      fZ = + f
  in (vZ Data.Integer.+ (-ℤ eZ)) Data.Integer.+ fZ

-- Proof for canonical Tetrahedron: V=4, E=6, F=4 -> chi = 2
tetrahedronEuler : eulerCharacteristic 4 6 4 ≡ + 2
tetrahedronEuler = refl

-- Proof for canonical Cube: V=8, E=12, F=6 -> chi = 2
cubeEuler : eulerCharacteristic 8 12 6 ≡ + 2
cubeEuler = refl

-- Proof for canonical Octahedron: V=6, E=12, F=8 -> chi = 2
octahedronEuler : eulerCharacteristic 6 12 8 ≡ + 2
octahedronEuler = refl

-- Proof for canonical Icosahedron: V=12, E=30, F=20 -> chi = 2
icosahedronEuler : eulerCharacteristic 12 30 20 ≡ + 2
icosahedronEuler = refl
