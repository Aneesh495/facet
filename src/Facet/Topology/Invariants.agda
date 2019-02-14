{-# OPTIONS --safe #-}

module Facet.Topology.Invariants where

open import Data.Nat using (ℕ; zero; suc; _≡ᵇ_)
open import Data.Bool using (Bool; true; false; _∧_)
open import Relation.Binary.PropositionalEquality using (_≡_; refl)
open import Facet.Topology.HalfEdge

-- Twin involution property: twin of twin is original edge
twinInvolutionProp : (eId twinId : ℕ) → Set
twinInvolutionProp eId twinId = twinId ≡ eId

-- Next-prev cycle inverse: prev of next is original edge
nextPrevInverseProp : (eId nextId prevId : ℕ) → Set
nextPrevInverseProp eId nextId prevId = prevId ≡ eId

-- Valid edge connectivity predicate
isValidConnectivity : HalfEdge → HalfEdge → Bool
isValidConnectivity e1 e2 =
  (HalfEdge.origin e1 ≡ᵇ HalfEdge.target e2) ∧
  (HalfEdge.target e1 ≡ᵇ HalfEdge.origin e2)
