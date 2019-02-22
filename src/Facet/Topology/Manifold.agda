{-# OPTIONS --safe #-}

module Facet.Topology.Manifold where

open import Data.Nat using (ℕ; zero; suc; _≡ᵇ_)
open import Data.Bool using (Bool; true; false; _∧_)
open import Facet.Topology.HalfEdge

-- 2-manifold edge condition: each interior edge must have exactly 2 incident half-edges with opposite directions
record ManifoldEdge : Set where
  constructor manifoldEdge
  field
    forwardEdge : HalfEdge
    backwardEdge : HalfEdge

isOppositeDirection : HalfEdge → HalfEdge → Bool
isOppositeDirection h1 h2 =
  (HalfEdge.origin h1 ≡ᵇ HalfEdge.target h2) ∧
  (HalfEdge.target h1 ≡ᵇ HalfEdge.origin h2)
