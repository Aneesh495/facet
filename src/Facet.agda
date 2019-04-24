{-# OPTIONS --safe #-}

module Facet where

-- Core Modules
open import Facet.Core.Exact public
open import Facet.Core.Vec3 public
open import Facet.Core.Mat3 public
open import Facet.Core.Plane public
open import Facet.Core.Predicates public

-- Topology Modules
open import Facet.Topology.HalfEdge public
open import Facet.Topology.Invariants public
open import Facet.Topology.Euler public
open import Facet.Topology.Manifold public
open import Facet.Topology.Boundary public

-- Geometry Modules
open import Facet.Geometry.Polygon public
open import Facet.Geometry.Polyhedron public
open import Facet.Geometry.CSG public
open import Facet.Geometry.Transform public
open import Facet.Geometry.Tessellate public

-- BSP Modules
open import Facet.BSP.Tree public
open import Facet.BSP.Classify public
open import Facet.BSP.Split public
open import Facet.BSP.Boolean public
open import Facet.BSP.Properties public

-- IO Modules
open import Facet.IO.STL public
open import Facet.IO.OBJ public
