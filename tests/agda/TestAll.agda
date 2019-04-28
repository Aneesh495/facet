{-# OPTIONS --safe #-}

module TestAll where

open import Relation.Binary.PropositionalEquality using (_≡_; refl)
open import Data.Integer using (+_)
open import Facet

-- Formal test verifying Euler characteristic computation
testCubeEuler : eulerCharacteristic 8 12 6 ≡ + 2
testCubeEuler = refl

testTetrahedronEuler : eulerCharacteristic 4 6 4 ≡ + 2
testTetrahedronEuler = refl

testInvertInvolution : invertTree (invertTree (BSPLeaf Front)) ≡ BSPLeaf Front
testInvertInvolution = refl
