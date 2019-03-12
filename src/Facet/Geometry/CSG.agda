{-# OPTIONS --safe #-}

module Facet.Geometry.CSG where

open import Facet.Geometry.Polyhedron
open import Facet.Core.Mat3
open import Facet.Core.Vec3

data CSGTree : Set where
  PrimitiveNode : Polyhedron → CSGTree
  UnionNode     : CSGTree → CSGTree → CSGTree
  IntersectNode : CSGTree → CSGTree → CSGTree
  SubtractNode  : CSGTree → CSGTree → CSGTree
  TransformNode : Mat3 → Vec3 → CSGTree → CSGTree
