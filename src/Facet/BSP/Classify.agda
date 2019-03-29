{-# OPTIONS --safe #-}

module Facet.BSP.Classify where

open import Data.List using (List; []; _∷_)
open import Data.Bool using (Bool; true; false)
open import Facet.Core.Plane
open import Facet.Geometry.Polygon

data PolygonSpan : Set where
  SpanFront    : PolygonSpan
  SpanBack     : PolygonSpan
  SpanCoplanar : PolygonSpan
  SpanSpanning : PolygonSpan

classifyPolygonSpan : Plane → Polygon → PolygonSpan
classifyPolygonSpan pl poly = SpanCoplanar
