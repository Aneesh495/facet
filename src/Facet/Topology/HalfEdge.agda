{-# OPTIONS --safe #-}

module Facet.Topology.HalfEdge where

open import Data.Nat using (ℕ; zero; suc; _+_)
open import Data.Bool using (Bool; true; false; _∧_)
open import Facet.Core.Exact
open import Facet.Core.Vec3

-- Half-edge mesh vertex
record Vertex : Set where
  constructor vertex
  field
    vertexId : ℕ
    pos      : Vec3

-- Directed half-edge structure
record HalfEdge : Set where
  constructor halfEdge
  field
    edgeId   : ℕ
    origin   : ℕ
    target   : ℕ
    twinId   : ℕ
    nextId   : ℕ
    prevId   : ℕ
    faceId   : ℕ

-- Planar polygon face
record Face : Set where
  constructor face
  field
    faceId   : ℕ
    edgeId   : ℕ
    normal   : Vec3

-- Half-edge mesh topology container
record MeshTopology : Set where
  constructor meshTopology
  field
    vertexCount : ℕ
    edgeCount   : ℕ
    faceCount   : ℕ
